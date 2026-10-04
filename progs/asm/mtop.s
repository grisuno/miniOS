    .section .text
    .bss
h_cpu:
    .space 256
    .text
    .bss
h_mem:
    .space 256
    .text
    .bss
h_fill:
    .space 8
    .text
    .bss
last_dns:
    .space 8
    .text
    .bss
last_dns_ms:
    .space 8
    .text
    .bss
last_sock:
    .space 8
    .text
    .bss
prev_total:
    .space 8
    .text
    .bss
prev_idle:
    .space 8
    .text
    .bss
have_prev:
    .space 8
    .text
    .bss
disk_f:
    .space 8
    .text
    .bss
disk_path:
    .space 8
    .text
    .globl sc3
sc3:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    pushq %rbx
    movq 32(%rsp), %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
syscall
    movq %rax, -80(%rbp)
    addq $32, %rsp
    popq %rbx
    movq -80(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl mtop_time
mtop_time:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq $204, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sc3
    movq %r12, %rsp
    popq %r12
    leave
    ret
    leave
    ret
    .globl mtop_rtc
mtop_rtc:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq $212, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sc3
    movq %r12, %rsp
    popq %r12
    leave
    ret
    leave
    ret
    .globl mtop_key
mtop_key:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq $236, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sc3
    movq %r12, %rsp
    popq %r12
    leave
    ret
    leave
    ret
    .globl mtop_minfo
mtop_minfo:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq $251, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sc3
    movq %r12, %rsp
    popq %r12
    leave
    ret
    leave
    ret
    .globl emit
emit:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $1, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call strlen
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call write
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl mtop_quit_key
mtop_quit_key:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $113, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L10
    movq $1, %rax
    leave
    ret
.L10:
    movq -16(%rbp), %rax
    pushq %rax
    movq $81, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L12
    movq $1, %rax
    leave
    ret
.L12:
    movq -16(%rbp), %rax
    pushq %rax
    movq $27, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L14
    movq $1, %rax
    leave
    ret
.L14:
    movq -16(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L16
    movq $1, %rax
    leave
    ret
.L16:
    movq -16(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L18
    movq $1, %rax
    leave
    ret
.L18:
    movq $0, %rax
    leave
    ret
    leave
    ret
    .globl mtop_clear_ansi
mtop_clear_ansi:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $27, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $91, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $50, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $74, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $27, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $91, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $72, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl mtop_clear
mtop_clear:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq $251, %rax
    pushq %rax
    movq $5, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sc3
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L22
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_clear_ansi
    movq %r12, %rsp
    popq %r12
.L22:
    leave
    ret
    .globl mtop_atoi
mtop_atoi:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L32
    leaq -64(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L32:
.L34:
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L36
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $57, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L36
    movl $1, %eax
    jmp .L37
.L36:
    xorl %eax, %eax
.L37:
    cmpq $0, %rax
    je .L35
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L34
.L35:
    movq -64(%rbp), %rax
    cmpq $0, %rax
    je .L38
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
.L38:
    movq -32(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl mtop_putu
mtop_putu:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $24, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    subq $1, (%rax)
    movq %rcx, %rax
    leaq -48(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L48
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr1(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    leaq -16(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
.L48:
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L50
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    subq $1, (%rax)
    movq %rcx, %rax
    leaq -48(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    movb %al, (%rcx)
.L50:
.L52:
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L54
    movq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L54
    movl $1, %eax
    jmp .L55
.L54:
    xorl %eax, %eax
.L55:
    cmpq $0, %rax
    je .L53
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    subq $1, (%rax)
    movq %rcx, %rax
    leaq -48(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $48, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    movq %rdx, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -16(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    popq %rcx
    movq %rax, (%rcx)
    jmp .L52
.L53:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -48(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl mtop_put2
mtop_put2:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L58
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr3(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L58:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl mtop_put_kb
mtop_put_kb:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $1024, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L62
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr7(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L62:
    leaq -32(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $1024, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $1024, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    movq %rdx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1024, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr8(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr9(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl mtop_bar
mtop_bar:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L76
    leaq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L76:
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L78
    leaq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L78:
    leaq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    popq %rcx
    movq %rax, (%rcx)
    movq -64(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L80
    leaq -64(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
.L80:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $91, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leaq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L84
.L82:
    movq -80(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L86
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $35, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    jmp .L87
.L86:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $45, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
.L87:
.L83:
    leaq -80(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L84
.L84:
    movq -80(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .L82
.L85:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $93, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl mtop_hist_max
mtop_hist_max:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L96
.L94:
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L98
    leaq -48(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
.L98:
.L95:
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L96
.L96:
    movq -64(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .L94
.L97:
    movq -48(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl mtop_hist_push
mtop_hist_push:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq h_fill(%rip), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L106
    movq -16(%rbp), %rax
    pushq %rax
    movq h_fill(%rip), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
.L106:
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L110
.L108:
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
.L109:
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L110
.L110:
    movq -48(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .L108
.L111:
    movq -16(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
    .globl mtop_spark
mtop_spark:
    pushq %rbp
    movq %rsp, %rbp
    subq $160, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $46, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $58, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $61, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $43, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $42, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $35, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $37, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -112(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call mtop_hist_max
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L124
.L122:
    leaq -144(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    popq %rcx
    movq %rax, (%rcx)
    movq -144(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L126
    leaq -144(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L126:
    movq -144(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L128
    leaq -144(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    movq %rax, (%rcx)
.L128:
    leaq -96(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -48(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
.L123:
    leaq -128(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L124
.L124:
    movq -128(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L130
    movq -128(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L130
    movl $1, %eax
    jmp .L131
.L130:
    xorl %eax, %eax
.L131:
    cmpq $0, %rax
    jne .L122
.L125:
    leaq -96(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -96(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl mtop_mem
mtop_mem:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    leaq -64(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $0, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_minfo
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L140
    movq $1, %rax
    negq %rax
    leave
    ret
.L140:
    movq -16(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L142
    movq $1, %rax
    negq %rax
    leave
    ret
.L142:
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L144
    movq $1, %rax
    negq %rax
    leave
    ret
.L144:
    movq -48(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq -32(%rbp), %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -48(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L146
    movq $1, %rax
    negq %rax
    leave
    ret
.L146:
    movq $0, %rax
    leave
    ret
    leave
    ret
    .globl mtop_cpu
mtop_cpu:
    pushq %rbp
    movq %rsp, %rbp
    subq $144, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -96(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $4, %rax
    pushq %rax
    leaq -80(%rbp), %rax
    pushq %rax
    leaq -96(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_minfo
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L170
    movq $1, %rax
    negq %rax
    leave
    ret
.L170:
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L172
    movq $1, %rax
    negq %rax
    leave
    ret
.L172:
    movq -80(%rbp), %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L174
    movq $1, %rax
    negq %rax
    leave
    ret
.L174:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $3, %rax
    pushq %rax
    leaq -48(%rbp), %rax
    pushq %rax
    leaq -64(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_minfo
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L176
    movq $1, %rax
    negq %rax
    leave
    ret
.L176:
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L178
    movq $1, %rax
    negq %rax
    leave
    ret
.L178:
    movq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L180
    movq $1, %rax
    negq %rax
    leave
    ret
.L180:
    movq -64(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L182
    movq $1, %rax
    negq %rax
    leave
    ret
.L182:
    movq -16(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq have_prev(%rip), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L184
    leaq prev_total(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq prev_idle(%rip), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq have_prev(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    leave
    ret
.L184:
    leaq -112(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq prev_total(%rip), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq prev_idle(%rip), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq prev_total(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq prev_idle(%rip), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -112(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L186
    movq $1, %rax
    leave
    ret
.L186:
    movq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L188
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L188:
    movq -128(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L190
    leaq -128(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
.L190:
    movq -32(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $100, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    popq %rcx
    movq %rax, (%rcx)
    movq $0, %rax
    leave
    ret
    leave
    ret
    .globl mtop_disk_open
mtop_disk_open:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    leaq disk_f(%rip), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr22(%rip), %rax
    pushq %rax
    leaq .Lstr23(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fopen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq disk_f(%rip), %rax
    cmpq $0, %rax
    je .L200
    leaq disk_path(%rip), %rax
    pushq %rax
    leaq .Lstr24(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
.L200:
    leaq disk_f(%rip), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr25(%rip), %rax
    pushq %rax
    leaq .Lstr26(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fopen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq disk_f(%rip), %rax
    cmpq $0, %rax
    je .L202
    leaq disk_path(%rip), %rax
    pushq %rax
    leaq .Lstr27(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
.L202:
    leaq disk_f(%rip), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr28(%rip), %rax
    pushq %rax
    leaq .Lstr29(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fopen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq disk_f(%rip), %rax
    cmpq $0, %rax
    je .L204
    leaq disk_path(%rip), %rax
    pushq %rax
    leaq .Lstr30(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
.L204:
    leaq disk_f(%rip), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr31(%rip), %rax
    pushq %rax
    leaq .Lstr32(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fopen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq disk_f(%rip), %rax
    cmpq $0, %rax
    je .L206
    leaq disk_path(%rip), %rax
    pushq %rax
    leaq .Lstr33(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
.L206:
    leaq disk_path(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
    .globl mtop_disk_read
mtop_disk_read:
    pushq %rbp
    movq %rsp, %rbp
    subq $4192, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq disk_f(%rip), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L221
    movq $1, %rax
    negq %rax
    leave
    ret
.L221:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq disk_f(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call rewind
    movq %r12, %rsp
    popq %r12
    leaq -4128(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_time
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -4160(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L224
.L223:
    leaq -4176(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -4112(%rbp), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq $4096, %rax
    pushq %rax
    movq disk_f(%rip), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call fread
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -4176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L226
    jmp .L225
.L226:
    leaq -4160(%rbp), %rax
    pushq %rax
    movq -4160(%rbp), %rax
    pushq %rax
    movq -4176(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -4160(%rbp), %rax
    pushq %rax
    movq $65536, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L228
    jmp .L225
.L228:
.L224:
    jmp .L223
.L225:
    leaq -4144(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_time
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq -4160(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -4128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L230
    movq $2, %rax
    negq %rax
    leave
    ret
.L230:
    movq -4144(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L232
    movq $2, %rax
    negq %rax
    leave
    ret
.L232:
    movq -4144(%rbp), %rax
    pushq %rax
    movq -4128(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl mtop_net_probe
mtop_net_probe:
    pushq %rbp
    movq %rsp, %rbp
    subq $112, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $2, %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call socket
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L240
    movq $1, %rax
    negq %rax
    leave
    ret
.L240:
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call close
    movq %r12, %rsp
    popq %r12
    leaq -64(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_time
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -96(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr35(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call net_dns_resolve
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_time
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L242
    movq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L242
    movl $1, %eax
    jmp .L243
.L242:
    xorl %eax, %eax
.L243:
    cmpq $0, %rax
    je .L244
    movq -16(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L244:
    movq -96(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl mtop_frame
mtop_frame:
    pushq %rbp
    movq %rsp, %rbp
    subq $448, %rsp
    movq %rdi, -16(%rbp)
    leaq -32(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_time
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L304
    leaq -48(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1000, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    popq %rcx
    movq %rax, (%rcx)
.L304:
    leaq -432(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -384(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -400(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -416(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -384(%rbp), %rax
    pushq %rax
    leaq -400(%rbp), %rax
    pushq %rax
    leaq -416(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_rtc
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L306
    leaq -432(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L306:
    leaq -112(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -64(%rbp), %rax
    pushq %rax
    leaq -80(%rbp), %rax
    pushq %rax
    leaq -96(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_mem
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -144(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call mtop_cpu
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -256(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $1, %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    leaq -208(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_minfo
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -256(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L308
    movq -208(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L310
    leaq -256(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
.L310:
    movq -192(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L312
    leaq -256(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
.L312:
    movq -192(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L314
    leaq -256(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
.L314:
.L308:
    leaq -224(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -240(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $2, %rax
    pushq %rax
    leaq -224(%rbp), %rax
    pushq %rax
    leaq -240(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_minfo
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L316
    leaq -224(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -240(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L316:
    leaq -272(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -288(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_disk_read
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -320(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -336(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -352(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L318
    leaq -352(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L318:
    movq -16(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    movq %rdx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L320
    leaq -352(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L320:
    movq -352(%rbp), %rax
    cmpq $0, %rax
    je .L322
    leaq -320(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -304(%rbp), %rax
    pushq %rax
    leaq -336(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call mtop_net_probe
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq last_dns(%rip), %rax
    pushq %rax
    movq -320(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq last_dns_ms(%rip), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq last_sock(%rip), %rax
    pushq %rax
    movq -336(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L323
.L322:
    leaq -320(%rbp), %rax
    pushq %rax
    movq last_dns(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq last_dns_ms(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -336(%rbp), %rax
    pushq %rax
    movq last_sock(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
.L323:
    movq -112(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L324
    leaq -128(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq $100, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq h_mem(%rip), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call mtop_hist_push
    movq %r12, %rsp
    popq %r12
.L324:
    movq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L326
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq h_cpu(%rip), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call mtop_hist_push
    movq %r12, %rsp
    popq %r12
.L326:
    movq h_fill(%rip), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L328
    leaq h_fill(%rip), %rax
    pushq %rax
    movq h_fill(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L328:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr87(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L330
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr88(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr89(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L330:
    movq -432(%rbp), %rax
    cmpq $0, %rax
    je .L332
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr90(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -384(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_put2
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr91(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -400(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_put2
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr92(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -416(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_put2
    movq %r12, %rsp
    popq %r12
.L332:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr93(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr94(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq -112(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L334
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr95(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L335
.L334:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr96(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -64(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_put_kb
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr97(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -96(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_put_kb
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr98(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -128(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr99(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -80(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_put_kb
    movq %r12, %rsp
    popq %r12
.L335:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr100(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    leaq -368(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq h_mem(%rip), %rax
    pushq %rax
    movq h_fill(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call mtop_hist_max
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -112(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L336
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $0, %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq $20, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_bar
    movq %r12, %rsp
    popq %r12
    jmp .L337
.L336:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -128(%rbp), %rax
    pushq %rax
    movq $100, %rax
    pushq %rax
    movq $20, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_bar
    movq %r12, %rsp
    popq %r12
.L337:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr101(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq h_mem(%rip), %rax
    pushq %rax
    movq h_fill(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call mtop_spark
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr102(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr103(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L338
    movq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L340
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr104(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L341
.L340:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr105(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L341:
    jmp .L339
.L338:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -144(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    movq -144(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L342
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr106(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L343
.L342:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr107(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L343:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -160(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr108(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L339:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr109(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L344
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $0, %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq $20, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_bar
    movq %r12, %rsp
    popq %r12
    jmp .L345
.L344:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -160(%rbp), %rax
    pushq %rax
    movq $100, %rax
    pushq %rax
    movq $20, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call mtop_bar
    movq %r12, %rsp
    popq %r12
.L345:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr110(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq h_cpu(%rip), %rax
    pushq %rax
    movq h_fill(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call mtop_spark
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr111(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr112(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq -256(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L346
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr113(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L347
.L346:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr114(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -192(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_put_kb
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr115(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -208(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_put_kb
    movq %r12, %rsp
    popq %r12
    movq -240(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L348
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr116(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -224(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr117(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -240(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr118(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L349
.L348:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr119(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L349:
.L347:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr120(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq disk_f(%rip), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L350
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr121(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L351
.L350:
    movq -272(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L352
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr122(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq disk_path(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L353
.L352:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq disk_path(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr123(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -288(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr124(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq -272(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L354
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr125(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L355
.L354:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -272(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr126(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -288(%rbp), %rax
    pushq %rax
    movq $1000, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq -272(%rbp), %rax
    pushq %rax
    movq $1024, %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr127(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L355:
.L353:
.L351:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr128(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr129(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq -336(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L356
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr130(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L357
.L356:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr131(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L357:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr132(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq -320(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L358
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr133(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    jmp .L359
.L358:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr134(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L359:
    movq -304(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L360
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr135(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -304(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_putu
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr136(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
.L360:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr137(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $176, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L425
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq .Lstr143(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call strcmp
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L425
    movl $1, %eax
    jmp .L426
.L425:
    xorl %eax, %eax
.L426:
    cmpq $0, %rax
    je .L427
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr144(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr145(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L427:
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L429
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq .Lstr146(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call strcmp
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L429
    movl $1, %eax
    jmp .L430
.L429:
    xorl %eax, %eax
.L430:
    cmpq $0, %rax
    je .L431
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr147(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call emit
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L431:
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $500, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L433
    leaq -48(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_atoi
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
.L433:
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L435
    leaq -64(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_atoi
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
.L435:
    movq -64(%rbp), %rax
    pushq %rax
    movq $100, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L437
    leaq -64(%rbp), %rax
    pushq %rax
    movq $100, %rax
    popq %rcx
    movq %rax, (%rcx)
.L437:
    movq -64(%rbp), %rax
    pushq %rax
    movq $5000, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L439
    leaq -64(%rbp), %rax
    pushq %rax
    movq $5000, %rax
    popq %rcx
    movq %rax, (%rcx)
.L439:
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L441
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L441:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_disk_open
    movq %r12, %rsp
    popq %r12
    leaq h_fill(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq have_prev(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L444
.L443:
    leaq -80(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L446
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L448
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_clear
    movq %r12, %rsp
    popq %r12
.L448:
.L446:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -80(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_frame
    movq %r12, %rsp
    popq %r12
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L450
    movq -80(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L450
    movl $1, %eax
    jmp .L451
.L450:
    xorl %eax, %eax
.L451:
    cmpq $0, %rax
    je .L452
    jmp .L445
.L452:
    leaq -96(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_time
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -96(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L454
    leaq -160(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_key
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -160(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_quit_key
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L456
    movq $0, %rax
    leave
    ret
.L456:
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L458
    jmp .L445
.L458:
    jmp .L444
.L454:
    leaq -96(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L460:
    movq $1, %rax
    cmpq $0, %rax
    je .L461
    leaq -112(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_time
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -112(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L462
    jmp .L461
.L462:
    movq -112(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L464
    jmp .L461
.L464:
    leaq -128(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -128(%rbp), %rax
    pushq %rax
    movq $50, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L466
    leaq -128(%rbp), %rax
    pushq %rax
    movq $50, %rax
    popq %rcx
    movq %rax, (%rcx)
.L466:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq $251, %rax
    pushq %rax
    movq $6, %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sc3
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L468
    leaq -144(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L471
.L470:
    leaq -112(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_time
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -112(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L473
    jmp .L472
.L473:
    movq -112(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L475
    jmp .L472
.L475:
.L471:
    jmp .L470
.L472:
.L468:
    jmp .L478
.L477:
    leaq -160(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_key
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -160(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L480
    jmp .L479
.L480:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -160(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_quit_key
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L482
    movq $0, %rax
    leave
    ret
.L482:
.L478:
    jmp .L477
.L479:
    jmp .L460
.L461:
    leaq -160(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call mtop_key
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -160(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call mtop_quit_key
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L484
    jmp .L445
.L484:
.L444:
    jmp .L443
.L445:
    movq disk_f(%rip), %rax
    cmpq $0, %rax
    je .L486
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq disk_f(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fclose
    movq %r12, %rsp
    popq %r12
.L486:
    movq $0, %rax
    leave
    ret
    leave
    ret
    .section .rodata
.Lstr0:
    .asciz "-"
.Lstr1:
    .asciz "-"
.Lstr2:
    .asciz "0"
.Lstr3:
    .asciz "0"
.Lstr4:
    .asciz " KB"
.Lstr5:
    .asciz "."
.Lstr6:
    .asciz " MB"
.Lstr7:
    .asciz " KB"
.Lstr8:
    .asciz "."
.Lstr9:
    .asciz " MB"
.Lstr10:
    .asciz "src/mtop.c"
.Lstr11:
    .asciz "r"
.Lstr12:
    .asciz "src/mtop.c"
.Lstr13:
    .asciz "progs/src/mtop.c"
.Lstr14:
    .asciz "r"
.Lstr15:
    .asciz "progs/src/mtop.c"
.Lstr16:
    .asciz "src/fib.c"
.Lstr17:
    .asciz "r"
.Lstr18:
    .asciz "src/fib.c"
.Lstr19:
    .asciz "progs/src/fib.c"
.Lstr20:
    .asciz "r"
.Lstr21:
    .asciz "progs/src/fib.c"
.Lstr22:
    .asciz "src/mtop.c"
.Lstr23:
    .asciz "r"
.Lstr24:
    .asciz "src/mtop.c"
.Lstr25:
    .asciz "progs/src/mtop.c"
.Lstr26:
    .asciz "r"
.Lstr27:
    .asciz "progs/src/mtop.c"
.Lstr28:
    .asciz "src/fib.c"
.Lstr29:
    .asciz "r"
.Lstr30:
    .asciz "src/fib.c"
.Lstr31:
    .asciz "progs/src/fib.c"
.Lstr32:
    .asciz "r"
.Lstr33:
    .asciz "progs/src/fib.c"
.Lstr34:
    .asciz "localhost"
.Lstr35:
    .asciz "localhost"
.Lstr36:
    .asciz "================ mtop ================\n"
.Lstr37:
    .asciz "encendido hace "
.Lstr38:
    .asciz " s"
.Lstr39:
    .asciz "  hora "
.Lstr40:
    .asciz ":"
.Lstr41:
    .asciz ":"
.Lstr42:
    .asciz "  (q sale)\n"
.Lstr43:
    .asciz "RAM  "
.Lstr44:
    .asciz "no disponible"
.Lstr45:
    .asciz "ocupada "
.Lstr46:
    .asciz " de "
.Lstr47:
    .asciz " ("
.Lstr48:
    .asciz "%) libres "
.Lstr49:
    .asciz "\n  "
.Lstr50:
    .asciz " ultimos valores "
.Lstr51:
    .asciz "\n"
.Lstr52:
    .asciz "CPU  "
.Lstr53:
    .asciz "no disponible"
.Lstr54:
    .asciz "midiendo..."
.Lstr55:
    .asciz " nucleo, en uso "
.Lstr56:
    .asciz " nucleos, en uso "
.Lstr57:
    .asciz "%"
.Lstr58:
    .asciz "\n  "
.Lstr59:
    .asciz " ultimos valores "
.Lstr60:
    .asciz "\n"
.Lstr61:
    .asciz "DISCO "
.Lstr62:
    .asciz "capacidad no disponible"
.Lstr63:
    .asciz "ramdisk ocupado "
.Lstr64:
    .asciz " de "
.Lstr65:
    .asciz ", MiniFS libres "
.Lstr66:
    .asciz " de "
.Lstr67:
    .asciz " bloques"
.Lstr68:
    .asciz ", MiniFS no montado"
.Lstr69:
    .asciz "\n  lectura "
.Lstr70:
    .asciz "sin fichero de prueba"
.Lstr71:
    .asciz "no se puede leer "
.Lstr72:
    .asciz " "
.Lstr73:
    .asciz " bytes en "
.Lstr74:
    .asciz "menos de 1 ms"
.Lstr75:
    .asciz " ms ("
.Lstr76:
    .asciz " KB/s)"
.Lstr77:
    .asciz "\n"
.Lstr78:
    .asciz "RED  "
.Lstr79:
    .asciz "no disponible"
.Lstr80:
    .asciz "disponible"
.Lstr81:
    .asciz "  DNS "
.Lstr82:
    .asciz "sin respuesta"
.Lstr83:
    .asciz "responde"
.Lstr84:
    .asciz " en "
.Lstr85:
    .asciz " ms"
.Lstr86:
    .asciz "\n"
.Lstr87:
    .asciz "================ mtop ================\n"
.Lstr88:
    .asciz "encendido hace "
.Lstr89:
    .asciz " s"
.Lstr90:
    .asciz "  hora "
.Lstr91:
    .asciz ":"
.Lstr92:
    .asciz ":"
.Lstr93:
    .asciz "  (q sale)\n"
.Lstr94:
    .asciz "RAM  "
.Lstr95:
    .asciz "no disponible"
.Lstr96:
    .asciz "ocupada "
.Lstr97:
    .asciz " de "
.Lstr98:
    .asciz " ("
.Lstr99:
    .asciz "%) libres "
.Lstr100:
    .asciz "\n  "
.Lstr101:
    .asciz " ultimos valores "
.Lstr102:
    .asciz "\n"
.Lstr103:
    .asciz "CPU  "
.Lstr104:
    .asciz "no disponible"
.Lstr105:
    .asciz "midiendo..."
.Lstr106:
    .asciz " nucleo, en uso "
.Lstr107:
    .asciz " nucleos, en uso "
.Lstr108:
    .asciz "%"
.Lstr109:
    .asciz "\n  "
.Lstr110:
    .asciz " ultimos valores "
.Lstr111:
    .asciz "\n"
.Lstr112:
    .asciz "DISCO "
.Lstr113:
    .asciz "capacidad no disponible"
.Lstr114:
    .asciz "ramdisk ocupado "
.Lstr115:
    .asciz " de "
.Lstr116:
    .asciz ", MiniFS libres "
.Lstr117:
    .asciz " de "
.Lstr118:
    .asciz " bloques"
.Lstr119:
    .asciz ", MiniFS no montado"
.Lstr120:
    .asciz "\n  lectura "
.Lstr121:
    .asciz "sin fichero de prueba"
.Lstr122:
    .asciz "no se puede leer "
.Lstr123:
    .asciz " "
.Lstr124:
    .asciz " bytes en "
.Lstr125:
    .asciz "menos de 1 ms"
.Lstr126:
    .asciz " ms ("
.Lstr127:
    .asciz " KB/s)"
.Lstr128:
    .asciz "\n"
.Lstr129:
    .asciz "RED  "
.Lstr130:
    .asciz "no disponible"
.Lstr131:
    .asciz "disponible"
.Lstr132:
    .asciz "  DNS "
.Lstr133:
    .asciz "sin respuesta"
.Lstr134:
    .asciz "responde"
.Lstr135:
    .asciz " en "
.Lstr136:
    .asciz " ms"
.Lstr137:
    .asciz "\n"
.Lstr138:
    .asciz "help"
.Lstr139:
    .asciz "uso: mtop [fotos] [milisegundos]\n"
.Lstr140:
    .asciz "  fotos 0 = hasta q, -1 = una foto\n"
.Lstr141:
    .asciz "-h"
.Lstr142:
    .asciz "uso: mtop [fotos] [milisegundos]\n"
.Lstr143:
    .asciz "help"
.Lstr144:
    .asciz "uso: mtop [fotos] [milisegundos]\n"
.Lstr145:
    .asciz "  fotos 0 = hasta q, -1 = una foto\n"
.Lstr146:
    .asciz "-h"
.Lstr147:
    .asciz "uso: mtop [fotos] [milisegundos]\n"
    .section .text
    .weak _start
    .globl _start
_start:
    subq $8, %rsp
    movq 8(%rsp), %rdi
    leaq 16(%rsp), %rsi
    leaq 24(%rsp,%rdi,8), %rdx
    call main
    addq $8, %rsp
    movq %rax, %rdi
    movq $60, %rax
    syscall
