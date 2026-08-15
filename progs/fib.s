    .section .text
    .globl fib
fib:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L2
    movq -16(%rbp), %rax
    leave
    ret
.L2:
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fib
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fib
    movq %r12, %rsp
    popq %r12
    popq %rcx
    addq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq $10, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fib
    movq %r12, %rsp
    popq %r12
    leave
    ret
    leave
    ret
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
