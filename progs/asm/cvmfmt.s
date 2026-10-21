    .section .text
    .bss
fwin:
    .space 8
    .text
    .bss
fcanary:
    .space 9
    .text
    .globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -32(%rbp), %rax
    pushq %rax
    movq $35, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call memset
    movq %r12, %rsp
    popq %r12
    leaq -48(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -32(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    leaq .Lstr8(%rip), %rax
    pushq %rax
    movq $42, %rax
    pushq %rax
    leaq .Lstr9(%rip), %rax
    pushq %rax
    movq 32(%rsp), %rdi
    movq 24(%rsp), %rsi
    movq 16(%rsp), %rdx
    movq 8(%rsp), %rcx
    movq 0(%rsp), %r8
    xorl %eax, %eax
    call snprintf
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr10(%rip), %rax
    pushq %rax
    leaq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -32(%rbp), %rax
    pushq %rax
    movq $35, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call memset
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -32(%rbp), %rax
    pushq %rax
    leaq .Lstr11(%rip), %rax
    pushq %rax
    movq $7, %rax
    pushq %rax
    movq $255, %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sprintf
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr12(%rip), %rax
    pushq %rax
    leaq -32(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq fwin(%rip), %rax
    pushq %rax
    movq $35, %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call memset
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq fcanary(%rip), %rax
    pushq %rax
    movq $67, %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call memset
    movq %r12, %rsp
    popq %r12
    leaq fcanary(%rip), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq fwin(%rip), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    leaq .Lstr13(%rip), %rax
    pushq %rax
    leaq .Lstr14(%rip), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call snprintf
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr15(%rip), %rax
    pushq %rax
    leaq fwin(%rip), %rax
    pushq %rax
    leaq fcanary(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
    leave
    ret
    .section .rodata
.Lstr0:
    .asciz "n=%d s=%s"
.Lstr1:
    .asciz "ok"
.Lstr2:
    .asciz "%s len=%d\n"
.Lstr3:
    .asciz "t=%u x=%x"
.Lstr4:
    .asciz "%s\n"
.Lstr5:
    .asciz "%s"
.Lstr6:
    .asciz "0123456789ABCDEF"
.Lstr7:
    .asciz "win=%s canary=%s\n"
.Lstr8:
    .asciz "n=%d s=%s"
.Lstr9:
    .asciz "ok"
.Lstr10:
    .asciz "%s len=%d\n"
.Lstr11:
    .asciz "t=%u x=%x"
.Lstr12:
    .asciz "%s\n"
.Lstr13:
    .asciz "%s"
.Lstr14:
    .asciz "0123456789ABCDEF"
.Lstr15:
    .asciz "win=%s canary=%s\n"
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
