    .section .text
    .bss
js_key:
    .space 4096
    .text
    .bss
js_str:
    .space 4096
    .text
    .bss
js_type:
    .space 4096
    .text
    .bss
js_num:
    .space 4096
    .text
    .bss
js_first:
    .space 4096
    .text
    .bss
js_count:
    .space 4096
    .text
    .bss
js_next:
    .space 4096
    .text
    .bss
js_n:
    .space 8
    .text
    .bss
js_pool:
    .space 16384
    .text
    .bss
js_plen:
    .space 8
    .text
    .bss
js_src:
    .space 8
    .text
    .bss
js_pos:
    .space 8
    .text
    .bss
js_len:
    .space 8
    .text
    .bss
js_err:
    .space 8
    .text
    .globl js_read_all
js_read_all:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr1(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fopen
    movq %r12, %rsp
    popq %r12
    movq %rax, -80(%rbp)
    movq -80(%rbp), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L8
    movq $0, %rax
    leave
    ret
.L8:
    movq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fseek
    movq %r12, %rsp
    popq %r12
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ftell
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movb %al, (%rcx)
    movq -80(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call rewind
    movq %r12, %rsp
    popq %r12
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L10
    movq -80(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fclose
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L10:
    leaq -48(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call malloc
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -48(%rbp), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L12
    movq -80(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fclose
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L12:
    leaq -64(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    addq $32, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fread
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -80(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fclose
    movq %r12, %rsp
    popq %r12
    movq -64(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    movq (%rax), %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L14
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call free
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L14:
    movq -48(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -48(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl js_new
js_new:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq js_n(%rip), %rax
    pushq %rax
    movq $512, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L18
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L18:
    leaq js_n(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl js_skip_ws
js_skip_ws:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
.L30:
    movq js_pos(%rip), %rax
    pushq %rax
    movq js_len(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L31
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    movq %rax, -16(%rbp)
    movsbq -16(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L32
    movsbq -16(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L32
    xorl %eax, %eax
    jmp .L33
.L32:
    movl $1, %eax
.L33:
    testq %rax, %rax
    jne .L34
    movsbq -16(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L34
    xorl %eax, %eax
    jmp .L35
.L34:
    movl $1, %eax
.L35:
    testq %rax, %rax
    jne .L36
    movsbq -16(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L36
    xorl %eax, %eax
    jmp .L37
.L36:
    movl $1, %eax
.L37:
    cmpq $0, %rax
    je .L38
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L39
.L38:
    jmp .L31
.L39:
    jmp .L30
.L31:
    leave
    ret
    .globl js_peek
js_peek:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_skip_ws
    movq %r12, %rsp
    popq %r12
    movq js_pos(%rip), %rax
    pushq %rax
    movq js_len(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L42
    movq $1, %rax
    negq %rax
    leave
    ret
.L42:
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl js_parse_string
js_parse_string:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq js_pos(%rip), %rax
    pushq %rax
    movq js_len(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L80
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $34, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L80
    xorl %eax, %eax
    jmp .L81
.L80:
    movl $1, %eax
.L81:
    cmpq $0, %rax
    je .L82
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L82:
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -16(%rbp), %rax
    pushq %rax
    movq js_plen(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
.L84:
    movq $1, %rax
    cmpq $0, %rax
    je .L85
    movq js_pos(%rip), %rax
    pushq %rax
    movq js_len(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L86
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L86:
    leaq -32(%rbp), %rax
    pushq %rax
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    movsbq -32(%rbp), %rax
    pushq %rax
    movq $34, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L88
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L85
.L88:
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movsbq -32(%rbp), %rax
    pushq %rax
    movq $92, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L90
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq js_len(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L92
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L92:
    leaq -64(%rbp), %rax
    pushq %rax
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $110, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L94
    leaq -32(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L95
.L94:
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $116, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L96
    leaq -32(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L97
.L96:
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $114, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L98
    leaq -32(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L99
.L98:
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $98, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L100
    leaq -32(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L101
.L100:
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $102, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L102
    leaq -32(%rbp), %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L103
.L102:
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L104
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $92, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L104
    xorl %eax, %eax
    jmp .L105
.L104:
    movl $1, %eax
.L105:
    testq %rax, %rax
    jne .L106
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $34, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L106
    xorl %eax, %eax
    jmp .L107
.L106:
    movl $1, %eax
.L107:
    cmpq $0, %rax
    je .L108
    leaq -32(%rbp), %rax
    pushq %rax
    movsbq -64(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L109
.L108:
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $117, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L110
    leaq -32(%rbp), %rax
    pushq %rax
    movq $63, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq js_pos(%rip), %rax
    pushq %rax
    movq (%rax), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L111
.L110:
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L111:
.L109:
.L103:
.L101:
.L99:
.L97:
.L95:
.L90:
    movq js_plen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $16384, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L112
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L112:
    leaq js_pool(%rip), %rax
    pushq %rax
    leaq js_plen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movsbq -32(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    movq -48(%rbp), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L114
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
.L114:
    jmp .L84
.L85:
    leaq js_pool(%rip), %rax
    pushq %rax
    movq js_plen(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq js_plen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    movq -16(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl js_parse_number
js_parse_number:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    leaq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L122:
    movq js_pos(%rip), %rax
    pushq %rax
    movq js_len(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L124
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
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
    je .L124
    movl $1, %eax
    jmp .L125
.L124:
    xorl %eax, %eax
.L125:
    testq %rax, %rax
    je .L126
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
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
    je .L126
    movl $1, %eax
    jmp .L127
.L126:
    xorl %eax, %eax
.L127:
    cmpq $0, %rax
    je .L123
    leaq -16(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
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
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L122
.L123:
    movq -16(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl js_key_match
js_key_match:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq js_str(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
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
    leave
    ret
    leave
    ret
    .globl js_parse_object
js_parse_object:
    pushq %rbp
    movq %rsp, %rbp
    subq $112, %rsp
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -16(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_new
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L148
    movq $1, %rax
    negq %rax
    leave
    ret
.L148:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $125, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L150
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq js_first(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_count(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    leave
    ret
.L150:
.L152:
    movq $1, %rax
    cmpq $0, %rax
    je .L153
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $34, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L154
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L154:
    leaq -80(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_parse_string
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L156
    movq $1, %rax
    negq %rax
    leave
    ret
.L156:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $58, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L158
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L158:
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -96(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_parse_value
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
    je .L160
    movq $1, %rax
    negq %rax
    leave
    ret
.L160:
    leaq js_key(%rip), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq js_pool(%rip), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L162
    leaq -32(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L163
.L162:
    leaq js_next(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
.L163:
    leaq js_next(%rip), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $44, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L164
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L152
.L164:
    jmp .L153
    jmp .L152
.L153:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $125, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L166
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L166:
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq js_first(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_count(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl js_parse_array
js_parse_array:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -16(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_new
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L182
    movq $1, %rax
    negq %rax
    leave
    ret
.L182:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $93, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L184
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq js_first(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_count(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    leave
    ret
.L184:
.L186:
    movq $1, %rax
    cmpq $0, %rax
    je .L187
    leaq -80(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_parse_value
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L188
    movq $1, %rax
    negq %rax
    leave
    ret
.L188:
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L190
    leaq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L191
.L190:
    leaq js_next(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
.L191:
    leaq js_next(%rip), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $44, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L192
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L186
.L192:
    jmp .L187
    jmp .L186
.L187:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $93, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L194
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L194:
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq js_first(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_count(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl js_parse_value
js_parse_value:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    leaq -16(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L264
    movq $1, %rax
    negq %rax
    leave
    ret
.L264:
    movq -16(%rbp), %rax
    pushq %rax
    movq $123, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L266
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_parse_object
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L266:
    movq -16(%rbp), %rax
    pushq %rax
    movq $91, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L268
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_parse_array
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L268:
    movq -16(%rbp), %rax
    pushq %rax
    movq $34, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L270
    leaq -48(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_parse_string
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
    je .L272
    movq $1, %rax
    negq %rax
    leave
    ret
.L272:
    leaq -32(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_new
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L274
    movq $1, %rax
    negq %rax
    leave
    ret
.L274:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_str(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq js_pool(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    leave
    ret
.L270:
    movq -16(%rbp), %rax
    pushq %rax
    movq $116, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L276
    movq js_len(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L278
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $116, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L278
    movl $1, %eax
    jmp .L279
.L278:
    xorl %eax, %eax
.L279:
    testq %rax, %rax
    je .L280
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $114, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L280
    movl $1, %eax
    jmp .L281
.L280:
    xorl %eax, %eax
.L281:
    testq %rax, %rax
    je .L282
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $117, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L282
    movl $1, %eax
    jmp .L283
.L282:
    xorl %eax, %eax
.L283:
    testq %rax, %rax
    je .L284
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $101, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L284
    movl $1, %eax
    jmp .L285
.L284:
    xorl %eax, %eax
.L285:
    cmpq $0, %rax
    je .L286
    leaq js_pos(%rip), %rax
    pushq %rax
    movq (%rax), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_new
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L288
    movq $1, %rax
    negq %rax
    leave
    ret
.L288:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_num(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    leave
    ret
.L286:
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L276:
    movq -16(%rbp), %rax
    pushq %rax
    movq $102, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L290
    movq js_len(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L292
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $102, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L292
    movl $1, %eax
    jmp .L293
.L292:
    xorl %eax, %eax
.L293:
    testq %rax, %rax
    je .L294
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $97, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L294
    movl $1, %eax
    jmp .L295
.L294:
    xorl %eax, %eax
.L295:
    testq %rax, %rax
    je .L296
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $108, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L296
    movl $1, %eax
    jmp .L297
.L296:
    xorl %eax, %eax
.L297:
    testq %rax, %rax
    je .L298
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $115, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L298
    movl $1, %eax
    jmp .L299
.L298:
    xorl %eax, %eax
.L299:
    testq %rax, %rax
    je .L300
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $101, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L300
    movl $1, %eax
    jmp .L301
.L300:
    xorl %eax, %eax
.L301:
    cmpq $0, %rax
    je .L302
    leaq js_pos(%rip), %rax
    pushq %rax
    movq (%rax), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_new
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L304
    movq $1, %rax
    negq %rax
    leave
    ret
.L304:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_num(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    leave
    ret
.L302:
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L290:
    movq -16(%rbp), %rax
    pushq %rax
    movq $110, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L306
    movq js_len(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L308
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $110, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L308
    movl $1, %eax
    jmp .L309
.L308:
    xorl %eax, %eax
.L309:
    testq %rax, %rax
    je .L310
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $117, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L310
    movl $1, %eax
    jmp .L311
.L310:
    xorl %eax, %eax
.L311:
    testq %rax, %rax
    je .L312
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $108, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L312
    movl $1, %eax
    jmp .L313
.L312:
    xorl %eax, %eax
.L313:
    testq %rax, %rax
    je .L314
    movq js_src(%rip), %rax
    pushq %rax
    movq js_pos(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $108, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L314
    movl $1, %eax
    jmp .L315
.L314:
    xorl %eax, %eax
.L315:
    cmpq $0, %rax
    je .L316
    leaq js_pos(%rip), %rax
    pushq %rax
    movq (%rax), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_new
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L318
    movq $1, %rax
    negq %rax
    leave
    ret
.L318:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    leave
    ret
.L316:
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
.L306:
    movq -16(%rbp), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L320
    movq -16(%rbp), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L322
    movq -16(%rbp), %rax
    pushq %rax
    movq $57, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L322
    movl $1, %eax
    jmp .L323
.L322:
    xorl %eax, %eax
.L323:
    testq %rax, %rax
    jne .L320
    xorl %eax, %eax
    jmp .L321
.L320:
    movl $1, %eax
.L321:
    cmpq $0, %rax
    je .L324
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L326
    leaq -64(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_pos(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
.L326:
    leaq -32(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_new
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L328
    movq $1, %rax
    negq %rax
    leave
    ret
.L328:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_num(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_parse_number
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -64(%rbp), %rax
    cmpq $0, %rax
    je .L330
    leaq js_num(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    leaq js_num(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L330:
    movq -32(%rbp), %rax
    leave
    ret
.L324:
    leaq js_err(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    negq %rax
    leave
    ret
    leave
    ret
    .globl js_indent
js_indent:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L338
.L336:
    movq $32, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
.L337:
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L338
.L338:
    movq -32(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .L336
.L339:
    leave
    ret
    .globl js_print_str
js_print_str:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq $34, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L352:
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    cmpq $0, %rax
    je .L353
    leaq -48(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $34, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L354
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $92, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L354
    xorl %eax, %eax
    jmp .L355
.L354:
    movl $1, %eax
.L355:
    cmpq $0, %rax
    je .L356
    movq $92, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    movsbq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    jmp .L357
.L356:
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L358
    movq $92, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    movq $110, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    jmp .L359
.L358:
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L360
    movq $92, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    movq $116, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    jmp .L361
.L360:
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L362
    movq $92, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    movq $114, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    jmp .L363
.L362:
    movsbq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
.L363:
.L361:
.L359:
.L357:
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L352
.L353:
    movq $34, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl js_print_value
js_print_value:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L390
    leave
    ret
.L390:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L392
    leaq .Lstr7(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L392:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L394
    leaq js_num(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    testq %rax, %rax
    je .L396
    leaq .Lstr8(%rip), %rax
    jmp .L397
.L396:
    leaq .Lstr9(%rip), %rax
.L397:
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L394:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L398
    leaq .Lstr10(%rip), %rax
    pushq %rax
    leaq js_num(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L398:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L400
    leaq js_str(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_print_str
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L400:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L402
    movq $123, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leaq js_count(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L404
    movq $10, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
.L404:
    leaq -64(%rbp), %rax
    pushq %rax
    leaq js_first(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L406:
    movq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L407
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_indent
    movq %r12, %rsp
    popq %r12
    leaq js_key(%rip), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_print_str
    movq %r12, %rsp
    popq %r12
    leaq .Lstr11(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq -64(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_print_value
    movq %r12, %rsp
    popq %r12
    movq -48(%rbp), %rax
    pushq %rax
    leaq js_count(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
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
    je .L408
    movq $44, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
.L408:
    movq $10, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -64(%rbp), %rax
    pushq %rax
    leaq js_next(%rip), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L406
.L407:
    movq -32(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_indent
    movq %r12, %rsp
    popq %r12
    movq $125, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L402:
    movq $91, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leaq js_count(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L410
    movq $10, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
.L410:
    leaq -64(%rbp), %rax
    pushq %rax
    leaq js_first(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L412:
    movq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L413
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_indent
    movq %r12, %rsp
    popq %r12
    movq -64(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_print_value
    movq %r12, %rsp
    popq %r12
    movq -48(%rbp), %rax
    pushq %rax
    leaq js_count(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
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
    je .L414
    movq $44, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
.L414:
    movq $10, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -64(%rbp), %rax
    pushq %rax
    leaq js_next(%rip), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L412
.L413:
    movq -32(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_indent
    movq %r12, %rsp
    popq %r12
    movq $93, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl js_find_member
js_find_member:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    leaq js_first(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
.L420:
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L421
    leaq js_key(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
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
    cmpq $0, %rax
    je .L422
    movq -48(%rbp), %rax
    leave
    ret
.L422:
    leaq -48(%rbp), %rax
    pushq %rax
    leaq js_next(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L420
.L421:
    movq $1, %rax
    negq %rax
    leave
    ret
    leave
    ret
    .globl js_array_at
js_array_at:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    leaq js_first(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L428:
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L429
    movq -64(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L430
    movq -48(%rbp), %rax
    leave
    ret
.L430:
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -48(%rbp), %rax
    pushq %rax
    leaq js_next(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L428
.L429:
    movq $1, %rax
    negq %rax
    leave
    ret
    leave
    ret
    .globl js_query
js_query:
    pushq %rbp
    movq %rsp, %rbp
    subq $176, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $46, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L460
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
.L460:
.L462:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    cmpq $0, %rax
    je .L463
    leaq -144(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L464:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    testq %rax, %rax
    je .L470
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $46, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L470
    movl $1, %eax
    jmp .L471
.L470:
    xorl %eax, %eax
.L471:
    testq %rax, %rax
    je .L472
    movq -144(%rbp), %rax
    pushq %rax
    movq $63, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L472
    movl $1, %eax
    jmp .L473
.L472:
    xorl %eax, %eax
.L473:
    cmpq $0, %rax
    je .L465
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -144(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L464
.L465:
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L474
    movq $1, %rax
    negq %rax
    leave
    ret
.L474:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L476
    leaq -48(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_find_member
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    jmp .L477
.L476:
    leaq js_type(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L478
    leaq -160(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L480:
    leaq -128(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
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
    je .L482
    leaq -128(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
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
    je .L482
    movl $1, %eax
    jmp .L483
.L482:
    xorl %eax, %eax
.L483:
    cmpq $0, %rax
    je .L481
    leaq -160(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
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
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L480
.L481:
    leaq -128(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L484
    movq $1, %rax
    negq %rax
    leave
    ret
.L484:
    leaq -48(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_array_at
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    jmp .L479
.L478:
    movq $1, %rax
    negq %rax
    leave
    ret
.L479:
.L477:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $46, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L486
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
.L486:
    jmp .L462
.L463:
    movq -48(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $112, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L502
    leaq .Lstr16(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call puts
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L502:
    leaq -48(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -64(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_read_all
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -48(%rbp), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L504
    leaq .Lstr17(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L504:
    leaq js_src(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_pos(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_len(%rip), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_n(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_plen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq js_err(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_parse_value
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L506
    movq js_err(%rip), %rax
    testq %rax, %rax
    jne .L506
    xorl %eax, %eax
    jmp .L507
.L506:
    movl $1, %eax
.L507:
    testq %rax, %rax
    jne .L508
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_peek
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L508
    xorl %eax, %eax
    jmp .L509
.L508:
    movl $1, %eax
.L509:
    cmpq $0, %rax
    je .L510
    leaq .Lstr18(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call free
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L510:
    movq -16(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L512
    leaq -96(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_query
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
    je .L514
    leaq .Lstr19(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call free
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L514:
    movq -96(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_print_value
    movq %r12, %rsp
    popq %r12
    movq $10, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call free
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L512:
    movq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call js_print_value
    movq %r12, %rsp
    popq %r12
    movq $10, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call putchar
    movq %r12, %rsp
    popq %r12
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call free
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
    leave
    ret
    .section .rodata
.Lstr0:
    .asciz "r"
.Lstr1:
    .asciz "r"
.Lstr2:
    .asciz "null"
.Lstr3:
    .asciz "true"
.Lstr4:
    .asciz "false"
.Lstr5:
    .asciz "%d"
.Lstr6:
    .asciz ": "
.Lstr7:
    .asciz "null"
.Lstr8:
    .asciz "true"
.Lstr9:
    .asciz "false"
.Lstr10:
    .asciz "%d"
.Lstr11:
    .asciz ": "
.Lstr12:
    .asciz "usage: json <file> [path]"
.Lstr13:
    .asciz "json: cannot open %s\n"
.Lstr14:
    .asciz "json: %s: invalid JSON\n"
.Lstr15:
    .asciz "json: %s: not found\n"
.Lstr16:
    .asciz "usage: json <file> [path]"
.Lstr17:
    .asciz "json: cannot open %s\n"
.Lstr18:
    .asciz "json: %s: invalid JSON\n"
.Lstr19:
    .asciz "json: %s: not found\n"
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
