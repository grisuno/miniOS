    .section .text
    .globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq $1, %rax
    pushq %rax
    leaq .Lstr1(%rip), %rax
    pushq %rax
    movq $9, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call write
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
    leave
    ret
    .section .rodata
.Lstr0:
    .asciz "hola cvm\n"
.Lstr1:
    .asciz "hola cvm\n"
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
