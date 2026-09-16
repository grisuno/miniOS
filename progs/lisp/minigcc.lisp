;;; minigcc.lisp -- subset C compiler in MiniOS Lisp, v0.3.
;;;
;;; Usage (host):
;;;   lisp progs/lisp/minigcc.lisp source.c > out.s
;;; Usage (MiniOS):
;;;   lisp minigcc.lisp tin.c > asm/tin.s
;;; Flags: -h/--help prints usage, -v/--version prints the version.
;;; With no file argument the compiler prints usage and exits 1;
;;; diagnostics go to stdout (the interpreter has no stderr primitive)
;;; and every failure exits nonzero, never emitting bad assembly.
;;;
;;; Contract v0.3: compile one or more int functions in order:
;;;   int f(int a, ...){ return <expr>; }
;;; where params are int or void, bodies are a single return, and <expr>
;;; is integers, params, calls, + - * / and parentheses (max 6 params
;;; and 6 args, System V registers). Frames mirror ../miniGCC
;;; (-(16+8i)(%rbp) slots, same push-left/pop-rcx operand order with
;;; rax holding right and rcx holding left) plus the same _start entry
;;; wrapper minigcc emits (without it ld sets the entry to main
;;; directly and the first ret jumps wild).
;;; Anything outside the shape is a diagnostic plus exit 1, never bad asm.
;;; Later versions widen the shape toward full minigcc.c; the lexer,
;;; token model and emit helpers below are the stable interface for that.

(define version "0.3")

(define > (lambda (a b) (< b a)))
(define >= (lambda (a b) (if (< a b) nil t)))
(define <= (lambda (a b) (if (< b a) nil t)))
(define not (lambda (x) (if x nil t)))

(define is-space (lambda (c)
  (if (= c 32) t (if (= c 9) t (if (= c 10) t (= c 13))))))
(define is-digit (lambda (c) (if (< c 48) nil (if (< 57 c) nil t))))
(define is-alpha (lambda (c)
  (if (< c 65) (= c 95)
    (if (< 90 c) (if (< c 97) nil (if (< 122 c) (= c 95) t)) t))))
(define is-alnum (lambda (c) (if (is-alpha c) t (is-digit c))))

(define src "")
(define srclen 0)
(define toks nil)
(define ntok 0)
(define pos 0)

(define char-at (lambda (i) (char-code (string-at src i))))

(define lex-num (lambda (p acc)
  (begin
    (define c (if (< p srclen) (char-at p) 0))
    (if (is-digit c)
      (lex-num (+ p 1) (+ (* acc 10) (- c 48)))
      (cons p acc)))))

(define lex-word (lambda (p acc)
  (begin
    (define c (if (< p srclen) (char-at p) 0))
    (if (is-alnum c)
      (lex-word (+ p 1) (string-concat acc (char-code c)))
      (cons p acc)))))

(define lex-one (lambda (p)
  (begin
    (define c (char-at p))
    (if (is-digit c)
      (begin
        (define r (lex-num p 0))
        (cons (car r) (cons 0 (cdr r))))
      (if (is-alpha c)
        (begin
          (define r (lex-word p ""))
          (cons (car r) (cons 1 (cdr r))))
        (cons (+ p 1) (cons 2 c)))))))

;;; Token model: each token is cons(kind, value) with kind 0 number,
;;; 1 word, 2 punctuation code. The token list is built reversed then
;;; flipped once, because the interpreter has no set-cdr primitive.
(define rev-list (lambda (xs acc)
  (if (null? xs) acc (rev-list (cdr xs) (cons (car xs) acc)))))
(define reverse (lambda (xs) (rev-list xs nil)))

;;; Iterative lexer driver without deep recursion over the whole file.
;;; The inner lex-one still recurses per token (bounded by token length).
(define lex-src (lambda ()
  (begin
    (define p 0)
    (define rev nil)
    (define np 0)
    (define go (lambda (d)
      (begin
        (define skipped (lex-skip p))
        (set! p skipped)
        (if (< p srclen)
          (begin
            (define r (lex-one p))
            (set! p (car r))
            (set! rev (cons (cdr r) rev))
            (set! np (+ np 1))
            (if (< np 4096) (go 0) nil))
          nil))))
    (go 0)
    (cons (reverse rev) np))))

(define lex-skip (lambda (p)
  (if (< p srclen)
    (begin
      (define c (char-at p))
      (if (is-space c) (lex-skip (+ p 1)) p))
    p)))

;;; nth element of a proper list or nil when out of range.
(define nth (lambda (xs i)
  (if (null? xs) nil
    (if (= i 0) (car xs) (nth (cdr xs) (- i 1))))))

(define peek-kind (lambda () (car (nth toks pos))))
(define peek-val (lambda () (cdr (nth toks pos))))
(define at-end (lambda () (>= pos ntok)))
(define advance (lambda () (begin (set! pos (+ pos 1)) nil)))

(define expect-punct (lambda (code what)
  (if (at-end) (begin (println (string-concat "minigcc: expected " what)) (exit 1))
    (if (= (peek-kind) 2)
      (if (= (peek-val) code) (advance)
        (begin (println (string-concat "minigcc: expected " what)) (exit 1)))
      (begin (println (string-concat "minigcc: expected " what)) (exit 1))))))

(define expect-word (lambda (text)
  (if (at-end) (begin (println "minigcc: unexpected end") (exit 1))
    (if (= (peek-kind) 1)
      (if (string-eq (peek-val) text) (advance)
        (begin (println (string-concat "minigcc: expected " text)) (exit 1)))
      (begin (println (string-concat "minigcc: expected " text)) (exit 1))))))

;;; Function frame: param i lives at -(16+8i)(%rbp), incoming registers
;;; stored by the prologue. Frame size rounds 16+8*nparams up to 16.
;;; Calls follow System V: args pushed left to right, an odd count padded
;;; so rsp%16==0 before call, pad discarded into r10, args popped into
;;; rdi..r9 in reverse, result in rax. The sequence is stack-neutral, so
;;; nested calls inside arguments just work with no epilogue cleanup.
(define argregs (quote ("rdi" "rsi" "rdx" "rcx" "r8" "r9")))
(define vars nil)

(define list-len (lambda (xs) (if (null? xs) 0 (+ 1 (list-len (cdr xs))))))

(define var-bind (lambda (name off) (begin (set! vars (cons (cons name off) vars)) nil)))

(define var-find (lambda (xs name)
  (if (null? xs) 987654321
    (if (string-eq (car (car xs)) name) (cdr (car xs)) (var-find (cdr xs) name)))))

(define var-off (lambda (name)
  (begin
    (define off (var-find vars name))
    (if (= off 987654321) (begin (println (string-concat "minigcc: unbound variable " name)) (exit 1)) nil)
    off)))

(define emit-func-head (lambda (fname nparams)
  (begin
    (define size (* (/ (+ (+ 16 (* nparams 8)) 15) 16) 16))
    (print "    .globl ") (println fname)
    (print fname) (println ":")
    (println "    pushq %rbp")
    (println "    movq %rsp, %rbp")
    (print "    subq $") (print size) (println ", %rsp")
    (emit-stores 0 nparams)
    nil)))

(define emit-stores (lambda (i n)
  (if (< i n)
    (begin
      (print "    movq %") (print (nth argregs i))
      (print ", ") (print (- 0 (+ 16 (* i 8)))) (println "(%rbp)")
      (emit-stores (+ i 1) n))
    nil)))

(define emit-var (lambda (name)
  (begin
    (print "    movq ") (print (var-off name)) (println "(%rbp), %rax")
    nil)))

(define emit-pops (lambda (i)
  (if (< i 0) nil
    (begin
      (print "    popq %") (println (nth argregs i))
      (emit-pops (- i 1))))))

(define emit-call (lambda (fname nargs)
  (begin
    (define pad (- nargs (* (/ nargs 2) 2)))
    (if (= pad 1)
      (begin (println "    subq $8, %rsp") (println "    popq %r10"))
      nil)
    (emit-pops (- nargs 1))
    (println "    xorl %eax, %eax")
    (print "    call ") (println fname)
    nil)))

(define emit-start (lambda ()
  (begin
    (println "    .weak _start")
    (println "    .globl _start")
    (println "_start:")
    (println "    subq $8, %rsp")
    (println "    movq 8(%rsp), %rdi")
    (println "    leaq 16(%rsp), %rsi")
    (println "    leaq 24(%rsp,%rdi,8), %rdx")
    (println "    call main")
    (println "    addq $8, %rsp")
    (println "    movq %rax, %rdi")
    (println "    movq $60, %rax")
    (println "    syscall")
    nil)))

(define emit-num (lambda (n)
  (begin (print "    movq $") (print n) (println ", %rax") nil)))

(define emit-add (lambda () (begin (println "    addq %rcx, %rax") nil)))
(define emit-sub (lambda ()
  (begin (println "    subq %rax, %rcx") (println "    movq %rcx, %rax") nil)))
(define emit-mul (lambda () (begin (println "    imulq %rcx, %rax") nil)))
(define emit-div (lambda ()
  (begin
    (println "    movq %rax, %r8")
    (println "    movq %rcx, %rax")
    (println "    cqto")
    (println "    idivq %r8")
    nil)))

(define emit-push-rax (lambda () (begin (println "    pushq %rax") nil)))
;;; After the right operand is in rax, one pop puts left in rcx.
;;; Order follows ../miniGCC additive/multiplicative codegen exactly:
;;; rax holds right, rcx holds left on entry to each emit below.
(define emit-pop-rcx (lambda () (begin (println "    popq %rcx") nil)))

(define parse-expr (lambda (d) (begin (parse-term 0) (parse-expr-rest 0) nil)))
(define parse-expr-rest (lambda (d)
  (if (at-end) nil
    (if (= (peek-kind) 2)
      (begin
        (define c (peek-val))
        (if (= c 43)
          (begin (advance) (emit-push-rax) (parse-term 0) (emit-pop-rcx) (emit-add) (parse-expr-rest 0))
          (if (= c 45)
            (begin (advance) (emit-push-rax) (parse-term 0) (emit-pop-rcx) (emit-sub) (parse-expr-rest 0))
            nil)))
      nil))))

(define parse-term (lambda (d) (begin (parse-factor 0) (parse-term-rest 0) nil)))
(define parse-term-rest (lambda (d)
  (if (at-end) nil
    (if (= (peek-kind) 2)
      (begin
        (define c (peek-val))
        (if (= c 42)
          (begin (advance) (emit-push-rax) (parse-factor 0) (emit-pop-rcx) (emit-mul) (parse-term-rest 0))
          (if (= c 47)
            (begin (advance) (emit-push-rax) (parse-factor 0) (emit-pop-rcx) (emit-div) (parse-term-rest 0))
            nil)))
      nil))))

(define next-is-lparen (lambda ()
  (if (< pos ntok)
    (begin
      (define t (nth toks pos))
      (if (= (car t) 2) (if (= (cdr t) 40) t nil) nil))
    nil)))

(define parse-factor (lambda (d)
  (if (at-end) (begin (println "minigcc: unexpected end in factor") (exit 1))
    (if (= (peek-kind) 0)
      (begin (define v (peek-val)) (advance) (emit-num v) nil)
      (if (= (peek-kind) 1)
        (begin
          (define w (peek-val)) (advance)
          (if (next-is-lparen) (parse-call w) (emit-var w))
          nil)
        (if (= (peek-kind) 2)
          (if (= (peek-val) 40)
            (begin (advance) (parse-expr 0) (expect-punct 41 ")") nil)
            (begin (println "minigcc: bad factor") (exit 1)))
          (begin (println "minigcc: bad factor") (exit 1))))))))

(define parse-call (lambda (fname)
  (begin
    (expect-punct 40 "(")
    (define nargs (parse-args 0))
    (expect-punct 41 ")")
    (if (> nargs 6) (begin (println "minigcc: too many arguments") (exit 1)) nil)
    (emit-call fname nargs)
    nil)))

(define parse-args (lambda (d)
  (if (at-end) (begin (println "minigcc: unexpected end in call") (exit 1))
    (if (= (peek-kind) 2)
      (if (= (peek-val) 41) 0
        (begin (println "minigcc: bad argument") (exit 1)))
      (begin
        (parse-expr 0)
        (emit-push-rax)
        (parse-args-rest 0 1))))))

(define parse-args-rest (lambda (d n)
  (if (at-end) (begin (println "minigcc: unexpected end in call") (exit 1))
    (if (= (peek-kind) 2)
      (if (= (peek-val) 44)
        (begin (advance) (parse-expr 0) (emit-push-rax) (parse-args-rest 0 (+ n 1)))
        n)
      (begin (println "minigcc: expected , or )") (exit 1))))))

(define parse-params (lambda (d)
  (if (at-end) (begin (println "minigcc: unexpected end in params") (exit 1))
    (if (= (peek-kind) 2)
      (if (= (peek-val) 41) nil
        (begin (println "minigcc: bad parameter") (exit 1)))
      (if (= (peek-kind) 1)
        (if (string-eq (peek-val) "void")
          (begin (advance) nil)
          (parse-param-list 0 0))
        (begin (println "minigcc: bad parameter") (exit 1)))))))

(define parse-param-list (lambda (d idx)
  (begin
    (expect-word "int")
    (if (at-end) (begin (println "minigcc: unexpected end in params") (exit 1)) nil)
    (if (= (peek-kind) 1)
      (begin
        (define pname (peek-val))
        (advance)
        (var-bind pname (- 0 (+ 16 (* idx 8))))
        (if (at-end) (begin (println "minigcc: unexpected end in params") (exit 1)) nil)
        (if (= (peek-kind) 2)
          (if (= (peek-val) 44)
            (begin (advance) (cons pname (parse-param-list 0 (+ idx 1))))
            (cons pname nil))
          (begin (println "minigcc: expected , or )") (exit 1))))
      (begin (println "minigcc: expected parameter name") (exit 1))))))

(define parse-function (lambda (d)
  (begin
    (expect-word "int")
    (if (at-end) (begin (println "minigcc: expected function name") (exit 1)) nil)
    (if (= (peek-kind) 1) nil (begin (println "minigcc: expected function name") (exit 1)))
    (define fname (peek-val)) (advance)
    (expect-punct 40 "(")
    (set! vars nil)
    (define names (parse-params 0))
    (define nparams (list-len names))
    (if (> nparams 6) (begin (println "minigcc: too many parameters") (exit 1)) nil)
    (expect-punct 41 ")")
    (expect-punct 123 "{")
    (expect-word "return")
    (emit-func-head fname nparams)
    (parse-expr 0)
    (expect-punct 59 ";")
    (expect-punct 125 "}")
    (println "    leave")
    (println "    ret")
    nil)))

(define parse-functions (lambda (d)
  (if (at-end) nil (begin (parse-function 0) (parse-functions 0)))))

(define parse-program (lambda (d)
  (begin
    (println "    .section .text")
    (parse-functions 0)
    (emit-start)
    nil)))

(define read-all (lambda (f acc)
  (begin
    (define c (read-char f))
    (if (null? c) acc (read-all f (string-concat acc (char-code c)))))))

(define load-source (lambda (path)
  (begin
    (define f (open-file path "r"))
    (define bad (if (null? f) t (if (string? (error-message f)) t nil)))
    (if bad (begin (println (string-concat "minigcc: cannot read " path)) (exit 1)) nil)
    (define data (read-all f ""))
    (close-file f)
    data)))

(define usage (lambda (d)
  (begin
    (print "minigcc.lisp v")
    (print version)
    (println " (MiniOS Lisp subset C compiler)")
    (println "usage: lisp minigcc.lisp <source.c> > out.s")
    (println "compiles: int f(int a, ...){ return <expr>; } with params, calls, + - * / and parens")
    nil)))

(define main (lambda (d)
  (begin
    (define args *argv*)
    (define rest (cdr args))
    (define path (if (null? rest) nil (car rest)))
    (if (null? path) (begin (usage 0) (exit 1)) nil)
    (if (string-eq path "-h") (begin (usage 0) (exit 0)) nil)
    (if (string-eq path "--help") (begin (usage 0) (exit 0)) nil)
    (if (string-eq path "-v") (begin (print "minigcc.lisp v") (println version) (exit 0)) nil)
    (if (string-eq path "--version") (begin (print "minigcc.lisp v") (println version) (exit 0)) nil)
    (define given (load-source path))
    (set! src given)
    (set! srclen (string-length src))
    (define lr (lex-src))
    (set! toks (car lr))
    (set! ntok (cdr lr))
    (set! pos 0)
    (if (= ntok 0) (begin (println "minigcc: empty input") (exit 1)) nil)
    (parse-program 0)
    (exit 0))))

(main 0)
