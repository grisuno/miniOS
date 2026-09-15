;;; test.lisp -- in-OS test suite for MiniOS, driven by Lisp.
;;;
;;; Usage (inside MiniOS):
;;;   lisp src/test.lisp

(define pass 0)
(define fail 0)

(define check (lambda (name cond)
  (if cond
    (begin (set! pass (+ pass 1)) (println (string-concat "PASS " name)))
    (begin (set! fail (+ fail 1)) (println (string-concat "FAIL " name))))))

(define write-file (lambda (path contents)
  (begin
    (define f (open-file path "w"))
    (write f contents)
    (close-file f)
    t)))

(define read-all (lambda (f acc)
  (begin
    (define c (read-char f))
    (if (null? c) acc (read-all f (string-concat acc (char-code c)))))))

(define read-file (lambda (path)
  (begin
    (define f (open-file path "r"))
    (define data (read-all f ""))
    (close-file f)
    data)))

(println "MiniOS in-OS test suite (Lisp)")

(check "add" (= (+ 40 2) 42))
(check "sub" (= (- 10 4) 6))
(check "mul" (= (* 6 7) 42))
(check "div" (= (/ 42 6) 7))
(check "lt" (< 3 4))
(define check-error (lambda (name thunk msg)
  (begin
    (define err (error-message thunk))
    (if (string? err)
      (check name (string-eq err msg))
      (check name nil)))))

(define check-spawn (lambda (name thunk want)
  (begin
    (define rc thunk)
    (if (number? rc)
      (check name (= rc want))
      (check name nil)))))

(check-error "add-overflow" (+ 9223372036854775807 1) "integer overflow")
(check-error "div-zero" (/ 1 0) "division by zero")
(check-error "unbound" nosuchsymbol "unbound symbol")
(check-error "arity" (+ 1) "+ expects two numbers")
(check-error "call-nonfunction" (1 2) "attempt to call a non-function")
(check "quote" (= (car (quote (1 2))) 1))
(check "quasi-literal" (= (car '(7 8)) 7))
(check "closure" (= ((lambda (x) (+ x 1)) 41) 42))
(check "let" (= (let ((x 2) (y 3)) (+ x y)) 5))
(check "define-set" (begin (define probe 10) (set! probe 20) (= probe 20)))
(check "string-concat" (string-eq (string-concat "foo" "bar") "foobar"))
(check "string-length" (= (string-length "hello") 5))
(check "string-at" (string-eq (string-at "hi" 0) "h"))
(check "string-at-oob" (null? (string-at "hi" 9)))
(check "char-code" (= (char-code "A") 65))
(check "car-cdr" (= (car (cons 1 2)) 1))
(check "cdr-atom" (null? (cdr 7)))
(check "null-pred" (null? nil))
(check "number-pred" (number? 42))
(check "string-pred" (string? "hi"))

(check "time-ms-is-num" (number? (time-ms)))
(check "vol-is-num" (number? (vol)))
(check "vol-in-range" (if (number? (vol)) (< (vol) 101) nil))

(write-file "/tmp/lisptest.txt" "hello from test.lisp")
(check "fs-write-read" (string-eq (read-file "/tmp/lisptest.txt") "hello from test.lisp"))

(check-spawn "xxhash-selftest" (minios-run "/objects/xxhash.o") 0)
(check-spawn "stb-selftest" (minios-run "/objects/stb.o") 0)
(check-spawn "dlmalloc-selftest" (minios-run "/objects/dlmalloc.o") 0)
(check-spawn "minigcc-compiles" (minios-run "/objects/minigcc.o" '("/src/fib.c") "/asm/_t_lisp.s") 0)
(check-spawn "ld-links" (minios-run "/objects/ld.o" '("-f" "elf" "-o" "/bin/_t_lisp.elf" "/asm/_t_lisp.s")) 0)
(check-spawn "toolchain-roundtrip" (minios-run "/bin/_t_lisp.elf") 55)

(print "TOTAL pass=")
(print pass)
(print " fail=")
(println fail)
(exit (if (= fail 0) 0 1))
