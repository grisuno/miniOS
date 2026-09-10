    .section .text
    .globl tls_close
tls_close:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call close
    movq %r12, %rsp
    popq %r12
    leave
    ret
    leave
    ret
    .bss
f_host:
    .space 64
    .text
    .bss
f_path:
    .space 128
    .text
    .bss
f_port:
    .space 8
    .text
    .bss
f_secure:
    .space 8
    .text
    .bss
f_loc:
    .space 192
    .text
    .bss
f_redir:
    .space 8
    .text
    .bss
f_status:
    .space 8
    .text
    .bss
f_clen:
    .space 8
    .text
    .bss
f_has_clen:
    .space 8
    .text
    .bss
f_chunked:
    .space 8
    .text
    .bss
f_hdr:
    .space 16384
    .text
    .bss
f_hlen:
    .space 8
    .text
    .bss
f_tag:
    .space 8
    .text
    .bss
f_suppress:
    .space 8
    .text
    .bss
f_comment:
    .space 8
    .text
    .bss
f_cmdash:
    .space 8
    .text
    .bss
f_tagn:
    .space 8
    .text
    .bss
f_tagnlen:
    .space 8
    .text
    .bss
f_ent:
    .space 8
    .text
    .bss
f_entlen:
    .space 8
    .text
    .bss
f_ws:
    .space 8
    .text
    .bss
f_utbuf:
    .space 4
    .text
    .bss
f_utlen:
    .space 8
    .text
    .bss
f_utrem:
    .space 8
    .text
    .bss
f_attr_on:
    .space 8
    .text
    .bss
f_waitq:
    .space 8
    .text
    .bss
f_inval:
    .space 8
    .text
    .bss
f_inval2:
    .space 8
    .text
    .bss
f_attr:
    .space 8
    .text
    .bss
f_attrlen:
    .space 8
    .text
    .bss
f_val:
    .space 96
    .text
    .bss
f_vallen:
    .space 8
    .text
    .bss
f_id:
    .space 32
    .text
    .bss
f_idlen:
    .space 8
    .text
    .bss
f_cls:
    .space 32
    .text
    .bss
f_clslen:
    .space 8
    .text
    .bss
f_href:
    .space 128
    .text
    .bss
f_hreflen:
    .space 8
    .text
    .bss
f_rel_ss:
    .space 8
    .text
    .bss
f_styleattr:
    .space 96
    .text
    .bss
f_stylelen:
    .space 8
    .text
    .bss
f_dump_css:
    .space 8
    .text
    .bss
f_dump_dom:
    .space 8
    .text
    .bss
f_mode:
    .space 8
    .text
    .bss
f_rawcap:
    .space 8
    .text
    .bss
f_depth:
    .space 8
    .text
    .bss
f_dom:
    .space 8192
    .text
    .bss
f_domlen:
    .space 8
    .text
    .bss
f_css:
    .space 8192
    .text
    .bss
f_csslen:
    .space 8
    .text
    .bss
f_linkhost:
    .space 512
    .text
    .bss
f_linkpath:
    .space 1024
    .text
    .bss
f_linkn:
    .space 8
    .text
    .bss
f_cstage:
    .space 8
    .text
    .bss
f_csize:
    .space 8
    .text
    .bss
f_crem:
    .space 8
    .text
    .bss
f_bdone:
    .space 8
    .text
    .globl atoi
atoi:
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
.L4:
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
    je .L6
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
    je .L6
    movl $1, %eax
    jmp .L7
.L6:
    xorl %eax, %eax
.L7:
    cmpq $0, %rax
    je .L5
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
    jmp .L4
.L5:
    movq -32(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl append
append:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L12
    movq $1, %rax
    negq %rax
    leave
    ret
.L12:
    leaq -80(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strlen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L14
    movq $1, %rax
    negq %rax
    leave
    ret
.L14:
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl ci_lower
ci_lower:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L20
    movq -16(%rbp), %rax
    pushq %rax
    movq $90, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L20
    movl $1, %eax
    jmp .L21
.L20:
    xorl %eax, %eax
.L21:
    cmpq $0, %rax
    je .L22
    movq -16(%rbp), %rax
    pushq %rax
    movq $97, %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    leave
    ret
.L22:
    movq -16(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl ci_starts
ci_starts:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
.L30:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    cmpq $0, %rax
    je .L31
    movq -16(%rbp), %rax
    movsbq (%rax), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L32
    movq $0, %rax
    leave
    ret
.L32:
    movq -16(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_lower
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_lower
    movq %r12, %rsp
    popq %r12
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L34
    movq $0, %rax
    leave
    ret
.L34:
    leaq -16(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L30
.L31:
    movq $1, %rax
    leave
    ret
    leave
    ret
    .globl ci_eq
ci_eq:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
.L48:
    movq -16(%rbp), %rax
    movsbq (%rax), %rax
    testq %rax, %rax
    je .L52
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    testq %rax, %rax
    je .L52
    movl $1, %eax
    jmp .L53
.L52:
    xorl %eax, %eax
.L53:
    cmpq $0, %rax
    je .L49
    movq -16(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_lower
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_lower
    movq %r12, %rsp
    popq %r12
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L54
    movq $0, %rax
    leave
    ret
.L54:
    leaq -16(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L48
.L49:
    movq -16(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L58
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L58
    movl $1, %eax
    jmp .L59
.L58:
    xorl %eax, %eax
.L59:
    leave
    ret
    leave
    ret
    .globl ci_index
ci_index:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L68
.L66:
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
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
    call ci_starts
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L70
    movq -48(%rbp), %rax
    leave
    ret
.L70:
.L67:
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L68
.L68:
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    cmpq $0, %rax
    jne .L66
.L69:
    movq $1, %rax
    negq %rax
    leave
    ret
    leave
    ret
    .globl looks_like_url
looks_like_url:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L82:
    movq -16(%rbp), %rax
    movsbq (%rax), %rax
    cmpq $0, %rax
    je .L83
    movq -16(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L86
    movq -16(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L86
    xorl %eax, %eax
    jmp .L87
.L86:
    movl $1, %eax
.L87:
    cmpq $0, %rax
    je .L88
    movq $0, %rax
    leave
    ret
.L88:
    movq -16(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $46, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L90
    leaq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L90:
    leaq -16(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L82
.L83:
    movq -32(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl has_scheme
has_scheme:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L124
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $90, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L124
    movl $1, %eax
    jmp .L125
.L124:
    xorl %eax, %eax
.L125:
    testq %rax, %rax
    jne .L126
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $97, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L128
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $122, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L128
    movl $1, %eax
    jmp .L129
.L128:
    xorl %eax, %eax
.L129:
    testq %rax, %rax
    jne .L126
    xorl %eax, %eax
    jmp .L127
.L126:
    movl $1, %eax
.L127:
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L130
    movq $0, %rax
    leave
    ret
.L130:
    leaq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L134
.L132:
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
    movq $58, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L136
    movq $1, %rax
    leave
    ret
.L136:
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L138
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $90, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L138
    movl $1, %eax
    jmp .L139
.L138:
    xorl %eax, %eax
.L139:
    testq %rax, %rax
    jne .L140
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $97, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L142
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $122, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L142
    movl $1, %eax
    jmp .L143
.L142:
    xorl %eax, %eax
.L143:
    testq %rax, %rax
    jne .L140
    xorl %eax, %eax
    jmp .L141
.L140:
    movl $1, %eax
.L141:
    testq %rax, %rax
    jne .L144
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L146
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $57, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L146
    movl $1, %eax
    jmp .L147
.L146:
    xorl %eax, %eax
.L147:
    testq %rax, %rax
    jne .L144
    xorl %eax, %eax
    jmp .L145
.L144:
    movl $1, %eax
.L145:
    testq %rax, %rax
    jne .L148
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $43, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L148
    xorl %eax, %eax
    jmp .L149
.L148:
    movl $1, %eax
.L149:
    testq %rax, %rax
    jne .L150
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L150
    xorl %eax, %eax
    jmp .L151
.L150:
    movl $1, %eax
.L151:
    testq %rax, %rax
    jne .L152
    movsbq -48(%rbp), %rax
    pushq %rax
    movq $46, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L152
    xorl %eax, %eax
    jmp .L153
.L152:
    movl $1, %eax
.L153:
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L154
    movq $0, %rax
    leave
    ret
.L154:
.L133:
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L134
.L134:
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    cmpq $0, %rax
    jne .L132
.L135:
    movq $0, %rax
    leave
    ret
    leave
    ret
    .globl make_search
make_search:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    leaq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    leaq .Lstr5(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
.L170:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    testq %rax, %rax
    je .L174
    movq -64(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L174
    movl $1, %eax
    jmp .L175
.L174:
    xorl %eax, %eax
.L175:
    cmpq $0, %rax
    je .L171
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L176
    leaq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    leaq .Lstr6(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    jmp .L177
.L176:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $38, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L178
    leaq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    leaq .Lstr7(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    jmp .L179
.L178:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $61, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L180
    leaq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    leaq .Lstr8(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    jmp .L181
.L180:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $43, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L182
    leaq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    leaq .Lstr9(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    jmp .L183
.L182:
    movq -16(%rbp), %rax
    pushq %rax
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
.L183:
.L181:
.L179:
.L177:
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L170
.L171:
    leave
    ret
    .globl split_url
split_url:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr12(%rip), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strncmp
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L218
    leaq f_secure(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -112(%rbp), %rax
    pushq %rax
    movq $443, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L219
.L218:
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr13(%rip), %rax
    pushq %rax
    movq $7, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strncmp
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L220
    leaq f_secure(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -112(%rbp), %rax
    pushq %rax
    movq $80, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L221
.L220:
    movq $0, %rax
    leave
    ret
.L221:
.L219:
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L222:
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    testq %rax, %rax
    je .L224
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $58, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L224
    movl $1, %eax
    jmp .L225
.L224:
    xorl %eax, %eax
.L225:
    testq %rax, %rax
    je .L226
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L226
    movl $1, %eax
    jmp .L227
.L226:
    xorl %eax, %eax
.L227:
    testq %rax, %rax
    je .L228
    movq -48(%rbp), %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L228
    movl $1, %eax
    jmp .L229
.L228:
    xorl %eax, %eax
.L229:
    cmpq $0, %rax
    je .L223
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L222
.L223:
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L230
    movq -48(%rbp), %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L230
    xorl %eax, %eax
    jmp .L231
.L230:
    movl $1, %eax
.L231:
    cmpq $0, %rax
    je .L232
    movq $0, %rax
    leave
    ret
.L232:
    leaq f_host(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_host(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_port(%rip), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $58, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L234
    leaq -80(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -96(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L236:
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
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
    je .L238
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
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
    je .L238
    movl $1, %eax
    jmp .L239
.L238:
    xorl %eax, %eax
.L239:
    cmpq $0, %rax
    je .L237
    leaq -96(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
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
    leaq -80(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L236
.L237:
    movq -96(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L240
    movq -96(%rbp), %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L240
    xorl %eax, %eax
    jmp .L241
.L240:
    movl $1, %eax
.L241:
    cmpq $0, %rax
    je .L242
    movq $0, %rax
    leave
    ret
.L242:
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L244
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L244
    movl $1, %eax
    jmp .L245
.L244:
    xorl %eax, %eax
.L245:
    cmpq $0, %rax
    je .L246
    movq $0, %rax
    leave
    ret
.L246:
    leaq f_port(%rip), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
.L234:
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L248
    leaq -64(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strlen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -64(%rbp), %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L250
    movq $0, %rax
    leave
    ret
.L250:
    leaq f_path(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_path(%rip), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L249
.L248:
    leaq f_path(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_path(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
.L249:
    movq $1, %rax
    leave
    ret
    leave
    ret
    .globl resolve_redirect
resolve_redirect:
    pushq %rbp
    movq %rsp, %rbp
    subq $304, %rsp
    leaq -208(%rbp), %rax
    pushq %rax
    leaq f_loc(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -208(%rbp), %rax
    pushq %rax
    leaq .Lstr19(%rip), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strncmp
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L282
    movq -208(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call split_url
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L282:
    movq -208(%rbp), %rax
    pushq %rax
    leaq .Lstr20(%rip), %rax
    pushq %rax
    movq $7, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strncmp
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L284
    movq -208(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call split_url
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L284:
    movq -208(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L286
    movq -208(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L286
    movl $1, %eax
    jmp .L287
.L286:
    xorl %eax, %eax
.L287:
    cmpq $0, %rax
    je .L288
    leaq -224(%rbp), %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq f_secure(%rip), %rax
    testq %rax, %rax
    je .L290
    leaq .Lstr21(%rip), %rax
    jmp .L291
.L290:
    leaq .Lstr22(%rip), %rax
.L291:
    pushq %rax
    movq $192, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -224(%rbp), %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq $192, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -224(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L292
    movq $0, %rax
    leave
    ret
.L292:
    leaq -192(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call split_url
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L288:
    movq -208(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call has_scheme
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L294
    leaq .Lstr23(%rip), %rax
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
    movq $0, %rax
    leave
    ret
.L294:
    movq -208(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L296
    leaq -240(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strlen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -240(%rbp), %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L298
    movq $0, %rax
    leave
    ret
.L298:
    leaq f_path(%rip), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq -240(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_path(%rip), %rax
    pushq %rax
    movq -240(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    movq $1, %rax
    leave
    ret
.L296:
    leaq -288(%rbp), %rax
    pushq %rax
    leaq f_path(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strlen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -256(%rbp), %rax
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
    jmp .L302
.L300:
    leaq f_path(%rip), %rax
    pushq %rax
    movq -240(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L304
    leaq -256(%rbp), %rax
    pushq %rax
    movq -240(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
.L304:
.L301:
    leaq -240(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L302
.L302:
    movq -240(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .L300
.L303:
    leaq -272(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strlen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -256(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L306
    movq -272(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L308
    movq $0, %rax
    leave
    ret
.L308:
    leaq f_path(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_path(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq -272(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_path(%rip), %rax
    pushq %rax
    movq -272(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L307
.L306:
    movq -256(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -272(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L310
    movq $0, %rax
    leave
    ret
.L310:
    leaq f_path(%rip), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq -272(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_path(%rip), %rax
    pushq %rax
    movq -256(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -272(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
.L307:
    movq $1, %rax
    leave
    ret
    leave
    ret
    .globl put_ws
put_ws:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq f_ws(%rip), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L316
    movq f_mode(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L316
    movl $1, %eax
    jmp .L317
.L316:
    xorl %eax, %eax
.L317:
    cmpq $0, %rax
    je .L318
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
    leaq f_ws(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L318:
    leave
    ret
    .globl put_utf
put_utf:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    leaq -16(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L364
    movq -16(%rbp), %rax
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
.L364:
    movq f_utrem(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L366
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $194, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L368
    movq -16(%rbp), %rax
    pushq %rax
    movq $223, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L368
    movl $1, %eax
    jmp .L369
.L368:
    xorl %eax, %eax
.L369:
    cmpq $0, %rax
    je .L370
    leaq -48(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L371
.L370:
    movq -16(%rbp), %rax
    pushq %rax
    movq $224, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L372
    movq -16(%rbp), %rax
    pushq %rax
    movq $239, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L372
    movl $1, %eax
    jmp .L373
.L372:
    xorl %eax, %eax
.L373:
    cmpq $0, %rax
    je .L374
    leaq -48(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L375
.L374:
    movq -16(%rbp), %rax
    pushq %rax
    movq $240, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L376
    movq -16(%rbp), %rax
    pushq %rax
    movq $244, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L376
    movl $1, %eax
    jmp .L377
.L376:
    xorl %eax, %eax
.L377:
    cmpq $0, %rax
    je .L378
    leaq -48(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    movq %rax, (%rcx)
.L378:
.L375:
.L371:
    movq -48(%rbp), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L380
    movq $63, %rax
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
.L380:
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_utlen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_utrem(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
.L366:
    movq -16(%rbp), %rax
    pushq %rax
    movq $192, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L382
    leaq f_utrem(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_utlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $63, %rax
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
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_utf
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L382:
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq f_utlen(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_utlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq f_utrem(%rip), %rax
    movq (%rax), %rcx
    subq $1, (%rax)
    movq %rcx, %rax
    movq f_utrem(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L384
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $224, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L386
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $160, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L386
    movl $1, %eax
    jmp .L387
.L386:
    xorl %eax, %eax
.L387:
    cmpq $0, %rax
    je .L388
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L388:
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $237, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L390
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $159, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L390
    movl $1, %eax
    jmp .L391
.L390:
    xorl %eax, %eax
.L391:
    cmpq $0, %rax
    je .L392
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L392:
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $240, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L394
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $144, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L394
    movl $1, %eax
    jmp .L395
.L394:
    xorl %eax, %eax
.L395:
    cmpq $0, %rax
    je .L396
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L396:
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $244, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L398
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $143, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L398
    movl $1, %eax
    jmp .L399
.L398:
    xorl %eax, %eax
.L399:
    cmpq $0, %rax
    je .L400
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L400:
    movq -48(%rbp), %rax
    cmpq $0, %rax
    je .L402
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L406
.L404:
    leaq f_utbuf(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
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
.L405:
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L406
.L406:
    movq -32(%rbp), %rax
    pushq %rax
    movq f_utlen(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .L404
.L407:
    jmp .L403
.L402:
    movq $63, %rax
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
.L403:
    leaq f_utlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L384:
    leave
    ret
    .globl put_text
put_text:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq f_mode(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L418
    leave
    ret
.L418:
    movq -16(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L420
    movq -16(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L420
    xorl %eax, %eax
    jmp .L421
.L420:
    movl $1, %eax
.L421:
    testq %rax, %rax
    jne .L422
    movq -16(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L422
    xorl %eax, %eax
    jmp .L423
.L422:
    movl $1, %eax
.L423:
    testq %rax, %rax
    jne .L424
    movq -16(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L424
    xorl %eax, %eax
    jmp .L425
.L424:
    movl $1, %eax
.L425:
    cmpq $0, %rax
    je .L426
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_ws
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L426:
    leaq f_ws(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_utf
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl put_entity
put_entity:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr30(%rip), %rax
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
    je .L488
    movq $38, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    jmp .L489
.L488:
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr31(%rip), %rax
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
    je .L490
    movq $60, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    jmp .L491
.L490:
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr32(%rip), %rax
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
    je .L492
    movq $62, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    jmp .L493
.L492:
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr33(%rip), %rax
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
    je .L494
    movq $34, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    jmp .L495
.L494:
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr34(%rip), %rax
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
    je .L496
    movq $39, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    jmp .L497
.L496:
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr35(%rip), %rax
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
    je .L498
    movq $32, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    jmp .L499
.L498:
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $35, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L500
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $120, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L502
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $88, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L502
    xorl %eax, %eax
    jmp .L503
.L502:
    movl $1, %eax
.L503:
    cmpq $0, %rax
    je .L504
    leaq -48(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    movq %rax, (%rcx)
.L504:
.L506:
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    cmpq $0, %rax
    je .L507
    leaq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $120, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L508
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $88, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
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
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L512
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $57, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L512
    movl $1, %eax
    jmp .L513
.L512:
    xorl %eax, %eax
.L513:
    cmpq $0, %rax
    je .L514
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movsbq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L515
.L514:
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $97, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L516
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $102, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L516
    movl $1, %eax
    jmp .L517
.L516:
    xorl %eax, %eax
.L517:
    cmpq $0, %rax
    je .L518
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movsbq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $97, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L519
.L518:
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L520
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $70, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L520
    movl $1, %eax
    jmp .L521
.L520:
    xorl %eax, %eax
.L521:
    cmpq $0, %rax
    je .L522
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movsbq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L522:
.L519:
.L515:
    jmp .L511
.L510:
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L524
    movsbq -64(%rbp), %rax
    pushq %rax
    movq $57, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L524
    movl $1, %eax
    jmp .L525
.L524:
    xorl %eax, %eax
.L525:
    cmpq $0, %rax
    je .L526
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movsbq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L526:
.L511:
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L506
.L507:
    movq -32(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L528
    movq -32(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L528
    xorl %eax, %eax
    jmp .L529
.L528:
    movl $1, %eax
.L529:
    cmpq $0, %rax
    je .L530
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_ws
    movq %r12, %rsp
    popq %r12
    jmp .L531
.L530:
    movq -32(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L532
    movq -32(%rbp), %rax
    pushq %rax
    movq $127, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L532
    movl $1, %eax
    jmp .L533
.L532:
    xorl %eax, %eax
.L533:
    cmpq $0, %rax
    je .L534
    movq -32(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    jmp .L535
.L534:
    movq -32(%rbp), %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L536
    movq -32(%rbp), %rax
    pushq %rax
    movq $2048, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L536
    movl $1, %eax
    jmp .L537
.L536:
    xorl %eax, %eax
.L537:
    cmpq $0, %rax
    je .L538
    movq $192, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $6, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    movq $128, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $63, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    jmp .L539
.L538:
    movq -32(%rbp), %rax
    pushq %rax
    movq $2048, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L540
    movq -32(%rbp), %rax
    pushq %rax
    movq $65536, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L540
    movl $1, %eax
    jmp .L541
.L540:
    xorl %eax, %eax
.L541:
    cmpq $0, %rax
    je .L542
    movq $224, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $12, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    movq $128, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $6, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $63, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    movq $128, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $63, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
.L542:
.L539:
.L535:
.L531:
    jmp .L501
.L500:
    movq $38, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L546
.L544:
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
.L545:
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L546
.L546:
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    cmpq $0, %rax
    jne .L544
.L547:
    movq $59, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
.L501:
.L499:
.L497:
.L495:
.L493:
.L491:
.L489:
    leave
    ret
    .globl css_append
css_append:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L556
.L554:
    leaq f_css(%rip), %rax
    pushq %rax
    leaq f_csslen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
.L555:
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L556
.L556:
    movq -48(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L558
    movq f_csslen(%rip), %rax
    pushq %rax
    movq $8192, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L558
    movl $1, %eax
    jmp .L559
.L558:
    xorl %eax, %eax
.L559:
    cmpq $0, %rax
    jne .L554
.L557:
    leave
    ret
    .globl css_line
css_line:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strlen
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call css_append
    movq %r12, %rsp
    popq %r12
    movq f_csslen(%rip), %rax
    pushq %rax
    movq $8192, %rax
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
    je .L562
    leaq f_css(%rip), %rax
    pushq %rax
    leaq f_csslen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    movb %al, (%rcx)
.L562:
    leave
    ret
    .globl dom_append
dom_append:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L572
.L570:
    leaq f_dom(%rip), %rax
    pushq %rax
    leaq f_domlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
.L571:
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L572
.L572:
    movq -48(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L574
    movq f_domlen(%rip), %rax
    pushq %rax
    movq $8192, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L574
    movl $1, %eax
    jmp .L575
.L574:
    xorl %eax, %eax
.L575:
    cmpq $0, %rax
    jne .L570
.L573:
    leave
    ret
    .globl dom_space
dom_space:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq f_domlen(%rip), %rax
    pushq %rax
    movq $8192, %rax
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
    je .L578
    leaq f_dom(%rip), %rax
    pushq %rax
    leaq f_domlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    movb %al, (%rcx)
.L578:
    leave
    ret
    .globl dom_nl
dom_nl:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq f_domlen(%rip), %rax
    pushq %rax
    movq $8192, %rax
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
    je .L582
    leaq f_dom(%rip), %rax
    pushq %rax
    leaq f_domlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    movb %al, (%rcx)
.L582:
    leave
    ret
    .globl record_attr
record_attr:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq f_attrlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L606
    movq f_vallen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L606
    xorl %eax, %eax
    jmp .L607
.L606:
    movl $1, %eax
.L607:
    cmpq $0, %rax
    je .L608
    leave
    ret
.L608:
    leaq f_attr(%rip), %rax
    pushq %rax
    leaq .Lstr42(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L610
    leaq f_idlen(%rip), %rax
    pushq %rax
    movq f_vallen(%rip), %rax
    pushq %rax
    movq $31, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L612
    movq f_vallen(%rip), %rax
    jmp .L613
.L612:
    movq $31, %rax
.L613:
    popq %rcx
    movq %rax, (%rcx)
    leaq f_id(%rip), %rax
    pushq %rax
    leaq f_val(%rip), %rax
    pushq %rax
    movq f_idlen(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_id(%rip), %rax
    pushq %rax
    movq f_idlen(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L611
.L610:
    leaq f_attr(%rip), %rax
    pushq %rax
    leaq .Lstr43(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L614
    leaq f_clslen(%rip), %rax
    pushq %rax
    movq f_vallen(%rip), %rax
    pushq %rax
    movq $31, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L616
    movq f_vallen(%rip), %rax
    jmp .L617
.L616:
    movq $31, %rax
.L617:
    popq %rcx
    movq %rax, (%rcx)
    leaq f_cls(%rip), %rax
    pushq %rax
    leaq f_val(%rip), %rax
    pushq %rax
    movq f_clslen(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_cls(%rip), %rax
    pushq %rax
    movq f_clslen(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L615
.L614:
    leaq f_attr(%rip), %rax
    pushq %rax
    leaq .Lstr44(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L618
    leaq f_hreflen(%rip), %rax
    pushq %rax
    movq f_vallen(%rip), %rax
    pushq %rax
    movq $127, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L620
    movq f_vallen(%rip), %rax
    jmp .L621
.L620:
    movq $127, %rax
.L621:
    popq %rcx
    movq %rax, (%rcx)
    leaq f_href(%rip), %rax
    pushq %rax
    leaq f_val(%rip), %rax
    pushq %rax
    movq f_hreflen(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_href(%rip), %rax
    pushq %rax
    movq f_hreflen(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L619
.L618:
    leaq f_attr(%rip), %rax
    pushq %rax
    leaq .Lstr45(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L622
    leaq f_stylelen(%rip), %rax
    pushq %rax
    movq f_vallen(%rip), %rax
    pushq %rax
    movq $96, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L624
    movq f_vallen(%rip), %rax
    jmp .L625
.L624:
    movq $96, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
.L625:
    popq %rcx
    movq %rax, (%rcx)
    leaq f_styleattr(%rip), %rax
    pushq %rax
    leaq f_val(%rip), %rax
    pushq %rax
    movq f_stylelen(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_styleattr(%rip), %rax
    pushq %rax
    movq f_stylelen(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L623
.L622:
    leaq f_attr(%rip), %rax
    pushq %rax
    leaq .Lstr46(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L626
    leaq f_rel_ss(%rip), %rax
    pushq %rax
    leaq f_val(%rip), %rax
    pushq %rax
    leaq .Lstr47(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_index
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    popq %rcx
    movq %rax, (%rcx)
.L626:
.L623:
.L619:
.L615:
.L611:
    leave
    ret
    .globl is_void_tag
is_void_tag:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr62(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L654
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr63(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L654
    xorl %eax, %eax
    jmp .L655
.L654:
    movl $1, %eax
.L655:
    testq %rax, %rax
    jne .L656
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr64(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L656
    xorl %eax, %eax
    jmp .L657
.L656:
    movl $1, %eax
.L657:
    testq %rax, %rax
    jne .L658
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr65(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L658
    xorl %eax, %eax
    jmp .L659
.L658:
    movl $1, %eax
.L659:
    testq %rax, %rax
    jne .L660
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr66(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L660
    xorl %eax, %eax
    jmp .L661
.L660:
    movl $1, %eax
.L661:
    testq %rax, %rax
    jne .L662
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr67(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L662
    xorl %eax, %eax
    jmp .L663
.L662:
    movl $1, %eax
.L663:
    testq %rax, %rax
    jne .L664
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr68(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L664
    xorl %eax, %eax
    jmp .L665
.L664:
    movl $1, %eax
.L665:
    testq %rax, %rax
    jne .L666
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr69(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L666
    xorl %eax, %eax
    jmp .L667
.L666:
    movl $1, %eax
.L667:
    testq %rax, %rax
    jne .L668
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr70(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L668
    xorl %eax, %eax
    jmp .L669
.L668:
    movl $1, %eax
.L669:
    testq %rax, %rax
    jne .L670
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr71(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L670
    xorl %eax, %eax
    jmp .L671
.L670:
    movl $1, %eax
.L671:
    testq %rax, %rax
    jne .L672
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr72(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L672
    xorl %eax, %eax
    jmp .L673
.L672:
    movl $1, %eax
.L673:
    testq %rax, %rax
    jne .L674
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr73(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L674
    xorl %eax, %eax
    jmp .L675
.L674:
    movl $1, %eax
.L675:
    testq %rax, %rax
    jne .L676
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr74(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L676
    xorl %eax, %eax
    jmp .L677
.L676:
    movl $1, %eax
.L677:
    testq %rax, %rax
    jne .L678
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr75(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L678
    xorl %eax, %eax
    jmp .L679
.L678:
    movl $1, %eax
.L679:
    leave
    ret
    leave
    ret
    .globl classify_tag
classify_tag:
    pushq %rbp
    movq %rsp, %rbp
    subq $192, %rsp
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq f_tagnlen(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    movq f_tagnlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L772
    leave
    ret
.L772:
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $33, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L774
    movq f_tagnlen(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L776
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L776
    movl $1, %eax
    jmp .L777
.L776:
    xorl %eax, %eax
.L777:
    testq %rax, %rax
    je .L778
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L778
    movl $1, %eax
    jmp .L779
.L778:
    xorl %eax, %eax
.L779:
    cmpq $0, %rax
    je .L780
    leaq f_comment(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_cmdash(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L780:
    leave
    ret
.L774:
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L782
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq .Lstr103(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L784
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq .Lstr104(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L784
    xorl %eax, %eax
    jmp .L785
.L784:
    movl $1, %eax
.L785:
    cmpq $0, %rax
    je .L786
    leaq f_suppress(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L787
.L786:
    movq f_dump_dom(%rip), %rax
    testq %rax, %rax
    je .L788
    movq f_depth(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L788
    movl $1, %eax
    jmp .L789
.L788:
    xorl %eax, %eax
.L789:
    cmpq $0, %rax
    je .L790
    leaq f_depth(%rip), %rax
    movq (%rax), %rcx
    subq $1, (%rax)
    movq %rcx, %rax
.L790:
.L787:
    leave
    ret
.L782:
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr105(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L792
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr106(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L792
    xorl %eax, %eax
    jmp .L793
.L792:
    movl $1, %eax
.L793:
    cmpq $0, %rax
    je .L794
    leaq f_suppress(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq f_dump_css(%rip), %rax
    testq %rax, %rax
    je .L796
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr107(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    je .L796
    movl $1, %eax
    jmp .L797
.L796:
    xorl %eax, %eax
.L797:
    cmpq $0, %rax
    je .L798
    leaq .Lstr108(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call css_line
    movq %r12, %rsp
    popq %r12
    leaq f_rawcap(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L798:
    leave
    ret
.L794:
    movq f_dump_css(%rip), %rax
    cmpq $0, %rax
    je .L800
    movq f_stylelen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L802
    leaq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $160, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq f_idlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L804
    leaq -176(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq .Lstr109(%rip), %rax
    pushq %rax
    movq $160, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq f_id(%rip), %rax
    pushq %rax
    movq $160, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
.L804:
    movq f_clslen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L806
    leaq -176(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq .Lstr110(%rip), %rax
    pushq %rax
    movq $160, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq f_cls(%rip), %rax
    pushq %rax
    movq $160, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
.L806:
    leaq -176(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq .Lstr111(%rip), %rax
    pushq %rax
    movq $160, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq f_styleattr(%rip), %rax
    pushq %rax
    movq $160, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq f_stylelen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L808
    leaq f_styleattr(%rip), %rax
    pushq %rax
    movq f_stylelen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $59, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L808
    movl $1, %eax
    jmp .L809
.L808:
    xorl %eax, %eax
.L809:
    cmpq $0, %rax
    je .L810
    leaq -176(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq .Lstr112(%rip), %rax
    pushq %rax
    movq $160, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
.L810:
    leaq -176(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq .Lstr113(%rip), %rax
    pushq %rax
    movq $160, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L812
    leaq -160(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call css_line
    movq %r12, %rsp
    popq %r12
.L812:
.L802:
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr114(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    je .L814
    movq f_rel_ss(%rip), %rax
    testq %rax, %rax
    je .L814
    movl $1, %eax
    jmp .L815
.L814:
    xorl %eax, %eax
.L815:
    testq %rax, %rax
    je .L816
    movq f_hreflen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L816
    movl $1, %eax
    jmp .L817
.L816:
    xorl %eax, %eax
.L817:
    testq %rax, %rax
    je .L818
    leaq f_href(%rip), %rax
    pushq %rax
    leaq .Lstr115(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_starts
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L818
    movl $1, %eax
    jmp .L819
.L818:
    xorl %eax, %eax
.L819:
    testq %rax, %rax
    je .L820
    leaq f_href(%rip), %rax
    pushq %rax
    leaq .Lstr116(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_starts
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L820
    movl $1, %eax
    jmp .L821
.L820:
    xorl %eax, %eax
.L821:
    testq %rax, %rax
    je .L822
    movq f_linkn(%rip), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L822
    movl $1, %eax
    jmp .L823
.L822:
    xorl %eax, %eax
.L823:
    cmpq $0, %rax
    je .L824
    leaq f_linkhost(%rip), %rax
    pushq %rax
    movq f_linkn(%rip), %rax
    popq %rcx
    imulq $64, %rax
    addq %rcx, %rax
    pushq %rax
    leaq f_host(%rip), %rax
    pushq %rax
    movq $63, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_linkhost(%rip), %rax
    pushq %rax
    movq f_linkn(%rip), %rax
    popq %rcx
    imulq $64, %rax
    addq %rcx, %rax
    pushq %rax
    movq $63, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_linkpath(%rip), %rax
    pushq %rax
    movq f_linkn(%rip), %rax
    popq %rcx
    imulq $128, %rax
    addq %rcx, %rax
    pushq %rax
    leaq f_href(%rip), %rax
    pushq %rax
    movq $127, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_linkpath(%rip), %rax
    pushq %rax
    movq f_linkn(%rip), %rax
    popq %rcx
    imulq $128, %rax
    addq %rcx, %rax
    pushq %rax
    movq $127, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_linkn(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
.L824:
.L800:
    movq f_dump_dom(%rip), %rax
    cmpq $0, %rax
    je .L826
    leaq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L830
.L828:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call dom_space
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call dom_space
    movq %r12, %rsp
    popq %r12
.L829:
    leaq -16(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L830
.L830:
    movq -16(%rbp), %rax
    pushq %rax
    movq f_depth(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L832
    movq -16(%rbp), %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L832
    movl $1, %eax
    jmp .L833
.L832:
    xorl %eax, %eax
.L833:
    cmpq $0, %rax
    jne .L828
.L831:
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq f_tagnlen(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call dom_append
    movq %r12, %rsp
    popq %r12
    movq f_idlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L834
    leaq .Lstr117(%rip), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call dom_append
    movq %r12, %rsp
    popq %r12
    leaq f_id(%rip), %rax
    pushq %rax
    movq f_idlen(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call dom_append
    movq %r12, %rsp
    popq %r12
.L834:
    movq f_clslen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L836
    leaq .Lstr118(%rip), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call dom_append
    movq %r12, %rsp
    popq %r12
    leaq f_cls(%rip), %rax
    pushq %rax
    movq f_clslen(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call dom_append
    movq %r12, %rsp
    popq %r12
.L836:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call dom_nl
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call is_void_tag
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L838
    leaq f_depth(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
.L838:
.L826:
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr119(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L840
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr120(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L840
    xorl %eax, %eax
    jmp .L841
.L840:
    movl $1, %eax
.L841:
    testq %rax, %rax
    jne .L842
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr121(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L842
    xorl %eax, %eax
    jmp .L843
.L842:
    movl $1, %eax
.L843:
    testq %rax, %rax
    jne .L844
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr122(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L844
    xorl %eax, %eax
    jmp .L845
.L844:
    movl $1, %eax
.L845:
    testq %rax, %rax
    jne .L846
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr123(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L846
    xorl %eax, %eax
    jmp .L847
.L846:
    movl $1, %eax
.L847:
    testq %rax, %rax
    jne .L848
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr124(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L848
    xorl %eax, %eax
    jmp .L849
.L848:
    movl $1, %eax
.L849:
    testq %rax, %rax
    jne .L850
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr125(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L850
    xorl %eax, %eax
    jmp .L851
.L850:
    movl $1, %eax
.L851:
    testq %rax, %rax
    jne .L852
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr126(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L852
    xorl %eax, %eax
    jmp .L853
.L852:
    movl $1, %eax
.L853:
    testq %rax, %rax
    jne .L854
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr127(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L854
    xorl %eax, %eax
    jmp .L855
.L854:
    movl $1, %eax
.L855:
    testq %rax, %rax
    jne .L856
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr128(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L856
    xorl %eax, %eax
    jmp .L857
.L856:
    movl $1, %eax
.L857:
    testq %rax, %rax
    jne .L858
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq .Lstr129(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L858
    xorl %eax, %eax
    jmp .L859
.L858:
    movl $1, %eax
.L859:
    cmpq $0, %rax
    je .L860
    movq f_mode(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L862
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
.L862:
    leaq f_ws(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L860:
    leave
    ret
    .globl body_byte
body_byte:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq f_comment(%rip), %rax
    cmpq $0, %rax
    je .L978
    movq -16(%rbp), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L980
    leaq f_cmdash(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L981
.L980:
    movq -16(%rbp), %rax
    pushq %rax
    movq $62, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L982
    movq f_cmdash(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L982
    movl $1, %eax
    jmp .L983
.L982:
    xorl %eax, %eax
.L983:
    cmpq $0, %rax
    je .L984
    leaq f_comment(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_cmdash(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L985
.L984:
    leaq f_cmdash(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L985:
.L981:
    leave
    ret
.L978:
    movq f_suppress(%rip), %rax
    cmpq $0, %rax
    je .L986
    movq -16(%rbp), %rax
    pushq %rax
    movq $60, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L988
    leaq f_tag(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_tagnlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
.L988:
    movq f_tag(%rip), %rax
    cmpq $0, %rax
    je .L990
    movq -16(%rbp), %rax
    pushq %rax
    movq $62, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L992
    leaq f_tag(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq f_tagnlen(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    movq f_tagnlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L994
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L994
    movl $1, %eax
    jmp .L995
.L994:
    xorl %eax, %eax
.L995:
    testq %rax, %rax
    je .L996
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq .Lstr133(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L998
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq .Lstr134(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    jne .L998
    xorl %eax, %eax
    jmp .L999
.L998:
    movl $1, %eax
.L999:
    testq %rax, %rax
    je .L996
    movl $1, %eax
    jmp .L997
.L996:
    xorl %eax, %eax
.L997:
    cmpq $0, %rax
    je .L1000
    leaq f_suppress(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq f_rawcap(%rip), %rax
    testq %rax, %rax
    je .L1002
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq .Lstr135(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_eq
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    je .L1002
    movl $1, %eax
    jmp .L1003
.L1002:
    xorl %eax, %eax
.L1003:
    cmpq $0, %rax
    je .L1004
    movq f_csslen(%rip), %rax
    pushq %rax
    movq $8192, %rax
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
    je .L1006
    leaq f_css(%rip), %rax
    pushq %rax
    leaq f_csslen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    movb %al, (%rcx)
.L1006:
    leaq f_rawcap(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1004:
.L1000:
    jmp .L993
.L992:
    movq -16(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1008
    movq -16(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1008
    movl $1, %eax
    jmp .L1009
.L1008:
    xorl %eax, %eax
.L1009:
    testq %rax, %rax
    je .L1010
    movq f_tagnlen(%rip), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1010
    movl $1, %eax
    jmp .L1011
.L1010:
    xorl %eax, %eax
.L1011:
    cmpq $0, %rax
    je .L1012
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq f_tagnlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
.L1012:
.L993:
    leave
    ret
.L990:
    movq f_rawcap(%rip), %rax
    testq %rax, %rax
    je .L1014
    movq f_csslen(%rip), %rax
    pushq %rax
    movq $8192, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1014
    movl $1, %eax
    jmp .L1015
.L1014:
    xorl %eax, %eax
.L1015:
    cmpq $0, %rax
    je .L1016
    leaq f_css(%rip), %rax
    pushq %rax
    leaq f_csslen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
.L1016:
    leave
    ret
.L986:
    movq f_tag(%rip), %rax
    cmpq $0, %rax
    je .L1018
    movq f_inval(%rip), %rax
    cmpq $0, %rax
    je .L1020
    movq -16(%rbp), %rax
    pushq %rax
    movq $34, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1022
    leaq f_inval(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call record_attr
    movq %r12, %rsp
    popq %r12
    jmp .L1023
.L1022:
    movq f_vallen(%rip), %rax
    pushq %rax
    movq $96, %rax
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
    je .L1024
    leaq f_val(%rip), %rax
    pushq %rax
    leaq f_vallen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
.L1024:
.L1023:
    leave
    ret
.L1020:
    movq f_inval2(%rip), %rax
    cmpq $0, %rax
    je .L1026
    movq -16(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1028
    movq -16(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1028
    xorl %eax, %eax
    jmp .L1029
.L1028:
    movl $1, %eax
.L1029:
    cmpq $0, %rax
    je .L1030
    leaq f_inval2(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call record_attr
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L1030:
    movq -16(%rbp), %rax
    pushq %rax
    movq $62, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1032
    leaq f_inval2(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call record_attr
    movq %r12, %rsp
    popq %r12
    leaq f_tag(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call classify_tag
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L1032:
    movq f_vallen(%rip), %rax
    pushq %rax
    movq $96, %rax
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
    je .L1034
    leaq f_val(%rip), %rax
    pushq %rax
    leaq f_vallen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
.L1034:
    leave
    ret
.L1026:
    movq f_waitq(%rip), %rax
    cmpq $0, %rax
    je .L1036
    movq -16(%rbp), %rax
    pushq %rax
    movq $34, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1038
    leaq f_waitq(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_inval(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1039
.L1038:
    movq -16(%rbp), %rax
    pushq %rax
    movq $62, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1040
    leaq f_waitq(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_tag(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call record_attr
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call classify_tag
    movq %r12, %rsp
    popq %r12
    jmp .L1041
.L1040:
    movq -16(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1042
    movq -16(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1042
    movl $1, %eax
    jmp .L1043
.L1042:
    xorl %eax, %eax
.L1043:
    cmpq $0, %rax
    je .L1044
    leaq f_waitq(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_inval2(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_vallen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_val(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
.L1044:
.L1041:
.L1039:
    leave
    ret
.L1036:
    movq f_attr_on(%rip), %rax
    cmpq $0, %rax
    je .L1046
    movq -16(%rbp), %rax
    pushq %rax
    movq $61, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1048
    leaq f_attr_on(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_waitq(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_vallen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1049
.L1048:
    movq -16(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1050
    movq -16(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1050
    movl $1, %eax
    jmp .L1051
.L1050:
    xorl %eax, %eax
.L1051:
    testq %rax, %rax
    je .L1052
    movq f_attrlen(%rip), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1052
    movl $1, %eax
    jmp .L1053
.L1052:
    xorl %eax, %eax
.L1053:
    cmpq $0, %rax
    je .L1054
    leaq f_attr(%rip), %rax
    pushq %rax
    leaq f_attrlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_attr(%rip), %rax
    pushq %rax
    movq f_attrlen(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
.L1054:
.L1049:
    leave
    ret
.L1046:
    movq -16(%rbp), %rax
    pushq %rax
    movq $62, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1056
    leaq f_tag(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call classify_tag
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L1056:
    movq -16(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1058
    movq -16(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1058
    xorl %eax, %eax
    jmp .L1059
.L1058:
    movl $1, %eax
.L1059:
    cmpq $0, %rax
    je .L1060
    movq f_tagnlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1062
    leaq f_attr_on(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_attrlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1062:
    leave
    ret
.L1060:
    movq -16(%rbp), %rax
    pushq %rax
    movq $47, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1064
    movq f_tagnlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1066
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq f_tagnlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
.L1066:
    leave
    ret
.L1064:
    movq f_tagnlen(%rip), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1068
    leaq f_tagn(%rip), %rax
    pushq %rax
    leaq f_tagnlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    movq f_tagnlen(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1070
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $33, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1070
    movl $1, %eax
    jmp .L1071
.L1070:
    xorl %eax, %eax
.L1071:
    testq %rax, %rax
    je .L1072
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1072
    movl $1, %eax
    jmp .L1073
.L1072:
    xorl %eax, %eax
.L1073:
    testq %rax, %rax
    je .L1074
    leaq f_tagn(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1074
    movl $1, %eax
    jmp .L1075
.L1074:
    xorl %eax, %eax
.L1075:
    cmpq $0, %rax
    je .L1076
    leaq f_tag(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_comment(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_cmdash(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1076:
.L1068:
    leave
    ret
.L1018:
    movq f_entlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1078
    movq -16(%rbp), %rax
    pushq %rax
    movq $59, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1080
    leaq f_ent(%rip), %rax
    pushq %rax
    movq f_entlen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_entlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_ent(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_entity
    movq %r12, %rsp
    popq %r12
    jmp .L1081
.L1080:
    movq f_entlen(%rip), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1082
    leaq f_ent(%rip), %rax
    pushq %rax
    movq f_entlen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_entlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1083
.L1082:
    movq $38, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1086
.L1084:
    leaq f_ent(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
.L1085:
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1086
.L1086:
    movq -32(%rbp), %rax
    pushq %rax
    movq f_entlen(%rip), %rax
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
    jne .L1084
.L1087:
    leaq f_entlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call body_byte
    movq %r12, %rsp
    popq %r12
.L1083:
.L1081:
    leave
    ret
.L1078:
    movq -16(%rbp), %rax
    pushq %rax
    movq $60, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1088
    leaq f_tag(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_tagnlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_attr_on(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_waitq(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_inval(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_inval2(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_attrlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_vallen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_idlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_clslen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_hreflen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_stylelen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_rel_ss(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
.L1088:
    movq -16(%rbp), %rax
    pushq %rax
    movq $38, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1090
    leaq f_entlen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_ent(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leave
    ret
.L1090:
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_text
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl head_line
head_line:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr140(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_starts
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L1116
    leaq -32(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1118:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1122
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1122
    xorl %eax, %eax
    jmp .L1123
.L1122:
    movl $1, %eax
.L1123:
    cmpq $0, %rax
    je .L1119
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1118
.L1119:
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1124:
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    testq %rax, %rax
    je .L1126
    movq -48(%rbp), %rax
    pushq %rax
    movq $191, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1126
    movl $1, %eax
    jmp .L1127
.L1126:
    xorl %eax, %eax
.L1127:
    cmpq $0, %rax
    je .L1125
    leaq f_loc(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1124
.L1125:
    leaq f_loc(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_redir(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1117
.L1116:
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr141(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_starts
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L1128
    leaq -32(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $15, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1130:
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1134
    movq -32(%rbp), %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1134
    xorl %eax, %eax
    jmp .L1135
.L1134:
    movl $1, %eax
.L1135:
    cmpq $0, %rax
    je .L1131
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1130
.L1131:
    leaq f_clen(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call atoi
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq f_has_clen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1129
.L1128:
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr142(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_starts
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L1136
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr143(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call ci_index
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1138
    leaq f_chunked(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1138:
.L1136:
.L1129:
.L1117:
    leave
    ret
    .globl parse_head
parse_head:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    leaq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1154:
    movq -16(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1155
    leaq -32(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
.L1156:
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1158
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1160
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1160
    movl $1, %eax
    jmp .L1161
.L1160:
    xorl %eax, %eax
.L1161:
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1158
    movl $1, %eax
    jmp .L1159
.L1158:
    xorl %eax, %eax
.L1159:
    cmpq $0, %rax
    je .L1157
    leaq -32(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1156
.L1157:
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
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
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1162
    leaq -48(%rbp), %rax
    pushq %rax
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strchr
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -48(%rbp), %rax
    cmpq $0, %rax
    je .L1164
    leaq f_status(%rip), %rax
    pushq %rax
    movq -48(%rbp), %rax
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
    call atoi
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
.L1164:
    jmp .L1163
.L1162:
    movq -32(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1166
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call head_line
    movq %r12, %rsp
    popq %r12
.L1166:
.L1163:
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1154
.L1155:
    leave
    ret
    .globl recv_body
recv_body:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq f_secure(%rip), %rax
    cmpq $0, %rax
    je .L1170
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_recv
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L1170:
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 40(%rsp), %rdi
    movq 32(%rsp), %rsi
    movq 24(%rsp), %rdx
    movq 16(%rsp), %rcx
    movq 8(%rsp), %r8
    movq 0(%rsp), %r9
    addq $48, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call recvfrom
    movq %r12, %rsp
    popq %r12
    leave
    ret
    leave
    ret
    .globl send_all
send_all:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq f_secure(%rip), %rax
    cmpq $0, %rax
    je .L1176
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_send
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1178
    movq $1, %rax
    negq %rax
    leave
    ret
.L1178:
    movq -48(%rbp), %rax
    leave
    ret
.L1176:
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 40(%rsp), %rdi
    movq 32(%rsp), %rsi
    movq 24(%rsp), %rdx
    movq 16(%rsp), %rcx
    movq 8(%rsp), %r8
    movq 0(%rsp), %r9
    addq $48, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sendto
    movq %r12, %rsp
    popq %r12
    leave
    ret
    leave
    ret
    .globl fetch
fetch:
    pushq %rbp
    movq %rsp, %rbp
    subq $1760, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    leaq -1664(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call net_dns_resolve
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -1664(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1269
    movq -1664(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1269
    xorl %eax, %eax
    jmp .L1270
.L1269:
    movl $1, %eax
.L1270:
    cmpq $0, %rax
    je .L1271
    leaq .Lstr157(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
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
    movq $0, %rax
    leave
    ret
.L1271:
    leaq -1616(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call socket
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -1616(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1273
    leaq .Lstr158(%rip), %rax
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
    movq $0, %rax
    leave
    ret
.L1273:
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memset
    movq %r12, %rsp
    popq %r12
    leaq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -1616(%rbp), %rax
    pushq %rax
    leaq -64(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call connect
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1275
    leaq .Lstr159(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
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
    movq -1616(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L1275:
    movq f_secure(%rip), %rax
    cmpq $0, %rax
    je .L1277
    movq -1616(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_handshake
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1279
    leaq .Lstr160(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
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
    movq -1616(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L1279:
.L1277:
    leaq -1680(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1680(%rbp), %rax
    pushq %rax
    leaq -1600(%rbp), %rax
    pushq %rax
    movq -1680(%rbp), %rax
    pushq %rax
    leaq .Lstr161(%rip), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1680(%rbp), %rax
    pushq %rax
    leaq -1600(%rbp), %rax
    pushq %rax
    movq -1680(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1680(%rbp), %rax
    pushq %rax
    leaq -1600(%rbp), %rax
    pushq %rax
    movq -1680(%rbp), %rax
    pushq %rax
    leaq .Lstr162(%rip), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1680(%rbp), %rax
    pushq %rax
    leaq -1600(%rbp), %rax
    pushq %rax
    movq -1680(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1680(%rbp), %rax
    pushq %rax
    leaq -1600(%rbp), %rax
    pushq %rax
    movq -1680(%rbp), %rax
    pushq %rax
    leaq .Lstr163(%rip), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1680(%rbp), %rax
    pushq %rax
    leaq -1600(%rbp), %rax
    pushq %rax
    movq -1680(%rbp), %rax
    pushq %rax
    leaq .Lstr164(%rip), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1680(%rbp), %rax
    pushq %rax
    leaq -1600(%rbp), %rax
    pushq %rax
    movq -1680(%rbp), %rax
    pushq %rax
    leaq .Lstr165(%rip), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -1616(%rbp), %rax
    pushq %rax
    leaq -1600(%rbp), %rax
    pushq %rax
    movq -1680(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call send_all
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1281
    leaq .Lstr166(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
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
    movq -1616(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L1281:
    leaq f_hlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_status(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_clen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_has_clen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_chunked(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_redir(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_cstage(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_csize(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_crem(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_bdone(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_tag(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_suppress(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_comment(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_cmdash(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_tagnlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_entlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_ws(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_utlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_utrem(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_attr_on(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_waitq(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_inval(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_inval2(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_rawcap(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_depth(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_idlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_clslen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_hreflen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_stylelen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_rel_ss(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1696(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1712(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1284
.L1283:
    movq f_bdone(%rip), %rax
    cmpq $0, %rax
    je .L1286
    jmp .L1285
.L1286:
    movq f_chunked(%rip), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1288
    movq f_has_clen(%rip), %rax
    testq %rax, %rax
    je .L1288
    movl $1, %eax
    jmp .L1289
.L1288:
    xorl %eax, %eax
.L1289:
    testq %rax, %rax
    je .L1290
    movq -1712(%rbp), %rax
    pushq %rax
    movq f_clen(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1290
    movl $1, %eax
    jmp .L1291
.L1290:
    xorl %eax, %eax
.L1291:
    cmpq $0, %rax
    je .L1292
    jmp .L1285
.L1292:
    leaq -1632(%rbp), %rax
    pushq %rax
    movq -1616(%rbp), %rax
    pushq %rax
    leaq -832(%rbp), %rax
    pushq %rax
    movq $768, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call recv_body
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -1632(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1294
    jmp .L1285
.L1294:
    leaq -1648(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1296:
    movq -1648(%rbp), %rax
    pushq %rax
    movq -1632(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1298
    movq f_bdone(%rip), %rax
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1298
    movl $1, %eax
    jmp .L1299
.L1298:
    xorl %eax, %eax
.L1299:
    cmpq $0, %rax
    je .L1297
    leaq -1728(%rbp), %rax
    pushq %rax
    leaq -832(%rbp), %rax
    pushq %rax
    leaq -1648(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -1696(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1300
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $16384, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1302
    movq -1616(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    leaq .Lstr167(%rip), %rax
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
    movq $0, %rax
    leave
    ret
.L1302:
    leaq f_hdr(%rip), %rax
    pushq %rax
    leaq f_hlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1728(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1304
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1304
    movl $1, %eax
    jmp .L1305
.L1304:
    xorl %eax, %eax
.L1305:
    testq %rax, %rax
    je .L1306
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1306
    movl $1, %eax
    jmp .L1307
.L1306:
    xorl %eax, %eax
.L1307:
    testq %rax, %rax
    je .L1308
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1308
    movl $1, %eax
    jmp .L1309
.L1308:
    xorl %eax, %eax
.L1309:
    testq %rax, %rax
    je .L1310
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1310
    movl $1, %eax
    jmp .L1311
.L1310:
    xorl %eax, %eax
.L1311:
    cmpq $0, %rax
    je .L1312
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call parse_head
    movq %r12, %rsp
    popq %r12
    leaq -1696(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1312:
    jmp .L1296
.L1300:
    movq f_chunked(%rip), %rax
    cmpq $0, %rax
    je .L1314
    movq f_cstage(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1316
    movq -1728(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1318
    movq f_csize(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1320
    leaq f_bdone(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1321
.L1320:
    leaq f_crem(%rip), %rax
    pushq %rax
    movq f_csize(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_csize(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_cstage(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1321:
    jmp .L1319
.L1318:
    movq -1728(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1322
    leaq -1744(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -1728(%rbp), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1324
    movq -1728(%rbp), %rax
    pushq %rax
    movq $57, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1324
    movl $1, %eax
    jmp .L1325
.L1324:
    xorl %eax, %eax
.L1325:
    cmpq $0, %rax
    je .L1326
    leaq -1744(%rbp), %rax
    pushq %rax
    movq -1728(%rbp), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1327
.L1326:
    movq -1728(%rbp), %rax
    pushq %rax
    movq $97, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1328
    movq -1728(%rbp), %rax
    pushq %rax
    movq $102, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1328
    movl $1, %eax
    jmp .L1329
.L1328:
    xorl %eax, %eax
.L1329:
    cmpq $0, %rax
    je .L1330
    leaq -1744(%rbp), %rax
    pushq %rax
    movq -1728(%rbp), %rax
    pushq %rax
    movq $97, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1331
.L1330:
    movq -1728(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1332
    movq -1728(%rbp), %rax
    pushq %rax
    movq $70, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1332
    movl $1, %eax
    jmp .L1333
.L1332:
    xorl %eax, %eax
.L1333:
    cmpq $0, %rax
    je .L1334
    leaq -1744(%rbp), %rax
    pushq %rax
    movq -1728(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1334:
.L1331:
.L1327:
    movq -1744(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1336
    leaq f_csize(%rip), %rax
    pushq %rax
    movq f_csize(%rip), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq -1744(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1336:
    movq f_csize(%rip), %rax
    pushq %rax
    movq $16777216, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1338
    movq -1616(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    leaq .Lstr168(%rip), %rax
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
    movq $0, %rax
    leave
    ret
.L1338:
.L1322:
.L1319:
    jmp .L1317
.L1316:
    movq f_cstage(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1340
    movq -1728(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call body_byte
    movq %r12, %rsp
    popq %r12
    leaq -1712(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq f_crem(%rip), %rax
    movq (%rax), %rcx
    subq $1, (%rax)
    movq %rcx, %rax
    movq f_crem(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1342
    leaq f_cstage(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1342:
    jmp .L1341
.L1340:
    movq f_cstage(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1344
    movq -1728(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1346
    leaq f_cstage(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1347
.L1346:
    movq -1728(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1348
    leaq f_cstage(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1348:
.L1347:
    jmp .L1345
.L1344:
    movq -1728(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1350
    leaq f_cstage(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1350:
.L1345:
.L1341:
.L1317:
    jmp .L1315
.L1314:
    movq f_has_clen(%rip), %rax
    testq %rax, %rax
    je .L1352
    movq -1712(%rbp), %rax
    pushq %rax
    movq f_clen(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1352
    movl $1, %eax
    jmp .L1353
.L1352:
    xorl %eax, %eax
.L1353:
    cmpq $0, %rax
    je .L1354
    leaq f_bdone(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1297
.L1354:
    movq -1728(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call body_byte
    movq %r12, %rsp
    popq %r12
    leaq -1712(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
.L1315:
    jmp .L1296
.L1297:
.L1284:
    jmp .L1283
.L1285:
    movq -1616(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    movq f_mode(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1356
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
.L1356:
    leaq .Lstr169(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -1712(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq f_status(%rip), %rax
    leave
    ret
    leave
    ret
    .globl fetch_css
fetch_css:
    pushq %rbp
    movq %rsp, %rbp
    subq $1728, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq -1648(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call net_dns_resolve
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -1648(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1393
    movq -1648(%rbp), %rax
    pushq %rax
    movq $1, %rax
    negq %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L1393
    xorl %eax, %eax
    jmp .L1394
.L1393:
    movl $1, %eax
.L1394:
    cmpq $0, %rax
    je .L1395
    leaq .Lstr178(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
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
.L1395:
    leaq -1600(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call socket
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -1600(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1397
    leave
    ret
.L1397:
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memset
    movq %r12, %rsp
    popq %r12
    leaq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq f_port(%rip), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq f_port(%rip), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1648(%rbp), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1648(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1648(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1648(%rbp), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -1600(%rbp), %rax
    pushq %rax
    leaq -48(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call connect
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1399
    leaq .Lstr179(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
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
    movq -1600(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L1399:
    movq f_secure(%rip), %rax
    cmpq $0, %rax
    je .L1401
    movq -1600(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_handshake
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1403
    leaq .Lstr180(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
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
    movq -1600(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L1403:
.L1401:
    leaq -1664(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1664(%rbp), %rax
    pushq %rax
    leaq -1584(%rbp), %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    leaq .Lstr181(%rip), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1664(%rbp), %rax
    pushq %rax
    leaq -1584(%rbp), %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1664(%rbp), %rax
    pushq %rax
    leaq -1584(%rbp), %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    leaq .Lstr182(%rip), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1664(%rbp), %rax
    pushq %rax
    leaq -1584(%rbp), %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1664(%rbp), %rax
    pushq %rax
    leaq -1584(%rbp), %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    leaq .Lstr183(%rip), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -1664(%rbp), %rax
    pushq %rax
    leaq -1584(%rbp), %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    leaq .Lstr184(%rip), %rax
    pushq %rax
    movq $768, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -1600(%rbp), %rax
    pushq %rax
    leaq -1584(%rbp), %rax
    pushq %rax
    movq -1664(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call send_all
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1405
    movq -1600(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L1405:
    leaq f_hlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1680(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1696(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1408
.L1407:
    leaq -1616(%rbp), %rax
    pushq %rax
    movq -1600(%rbp), %rax
    pushq %rax
    leaq -816(%rbp), %rax
    pushq %rax
    movq $768, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call recv_body
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -1616(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1410
    jmp .L1409
.L1410:
    leaq -1632(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1412:
    movq -1632(%rbp), %rax
    pushq %rax
    movq -1616(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1413
    leaq -1712(%rbp), %rax
    pushq %rax
    leaq -816(%rbp), %rax
    pushq %rax
    leaq -1632(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -1680(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1414
    leaq f_hdr(%rip), %rax
    pushq %rax
    leaq f_hlen(%rip), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -1712(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $16384, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1416
    movq -1600(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L1416:
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1418
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1418
    movl $1, %eax
    jmp .L1419
.L1418:
    xorl %eax, %eax
.L1419:
    testq %rax, %rax
    je .L1420
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1420
    movl $1, %eax
    jmp .L1421
.L1420:
    xorl %eax, %eax
.L1421:
    testq %rax, %rax
    je .L1422
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1422
    movl $1, %eax
    jmp .L1423
.L1422:
    xorl %eax, %eax
.L1423:
    testq %rax, %rax
    je .L1424
    leaq f_hdr(%rip), %rax
    pushq %rax
    movq f_hlen(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1424
    movl $1, %eax
    jmp .L1425
.L1424:
    xorl %eax, %eax
.L1425:
    cmpq $0, %rax
    je .L1426
    leaq -1680(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1426:
    jmp .L1412
.L1414:
    leaq f_ws(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -1712(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_utf
    movq %r12, %rsp
    popq %r12
    leaq -1696(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1412
.L1413:
.L1408:
    jmp .L1407
.L1409:
    movq -1600(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call tls_close
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
    leaq .Lstr185(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -1696(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl print_css_dump
print_css_dump:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    leaq .Lstr188(%rip), %rax
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
    leaq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1438
.L1436:
    leaq f_css(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_utf
    movq %r12, %rsp
    popq %r12
.L1437:
    leaq -16(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1438
.L1438:
    movq -16(%rbp), %rax
    pushq %rax
    movq f_csslen(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .L1436
.L1439:
    movq f_csslen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1440
    leaq .Lstr189(%rip), %rax
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
.L1440:
    movq f_linkn(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1442
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
.L1442:
    leave
    ret
    .globl print_dom_dump
print_dom_dump:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    leaq .Lstr192(%rip), %rax
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
    leaq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1452
.L1450:
    leaq f_dom(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call put_utf
    movq %r12, %rsp
    popq %r12
.L1451:
    leaq -16(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1452
.L1452:
    movq -16(%rbp), %rax
    pushq %rax
    movq f_domlen(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .L1450
.L1453:
    movq f_domlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1454
    leaq .Lstr193(%rip), %rax
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
.L1454:
    leave
    ret
    .globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $304, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    leaq f_dump_css(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_dump_dom(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_mode(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_csslen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_domlen(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_linkn(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -256(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1515
    leaq .Lstr209(%rip), %rax
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
.L1515:
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq .Lstr210(%rip), %rax
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
    je .L1517
    leaq f_dump_css(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_mode(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -256(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1519
    leaq .Lstr211(%rip), %rax
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
.L1519:
    jmp .L1518
.L1517:
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq .Lstr212(%rip), %rax
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
    je .L1521
    leaq f_dump_dom(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_mode(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -256(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1523
    leaq .Lstr213(%rip), %rax
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
.L1523:
    jmp .L1522
.L1521:
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
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
    testq %rax, %rax
    je .L1525
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $45, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1525
    movl $1, %eax
    jmp .L1526
.L1525:
    xorl %eax, %eax
.L1526:
    cmpq $0, %rax
    je .L1527
    leaq .Lstr214(%rip), %rax
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
    leaq .Lstr215(%rip), %rax
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
.L1527:
.L1522:
.L1518:
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
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
    call has_scheme
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L1529
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq .Lstr216(%rip), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strncmp
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1531
    leaq -288(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
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
    call strlen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -288(%rbp), %rax
    pushq %rax
    movq $192, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1533
    leaq -288(%rbp), %rax
    pushq %rax
    movq $191, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1533:
    leaq -224(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq -224(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L1532
.L1531:
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq .Lstr217(%rip), %rax
    pushq %rax
    movq $7, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call strncmp
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1535
    leaq -288(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
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
    call strlen
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -288(%rbp), %rax
    pushq %rax
    movq $192, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1537
    leaq -288(%rbp), %rax
    pushq %rax
    movq $191, %rax
    popq %rcx
    movq %rax, (%rcx)
.L1537:
    leaq -224(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq -224(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L1536
.L1535:
    leaq f_path(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $128, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call make_search
    movq %r12, %rsp
    popq %r12
    leaq f_host(%rip), %rax
    pushq %rax
    leaq .Lstr218(%rip), %rax
    pushq %rax
    movq $19, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_host(%rip), %rax
    pushq %rax
    movq $19, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_port(%rip), %rax
    pushq %rax
    movq $443, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_secure(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_host(%rip), %rax
    pushq %rax
    leaq f_path(%rip), %rax
    pushq %rax
    movq f_port(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fetch
    movq %r12, %rsp
    popq %r12
    movq f_dump_css(%rip), %rax
    cmpq $0, %rax
    je .L1539
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call print_css_dump
    movq %r12, %rsp
    popq %r12
.L1539:
    movq f_dump_dom(%rip), %rax
    cmpq $0, %rax
    je .L1541
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call print_dom_dump
    movq %r12, %rsp
    popq %r12
.L1541:
    movq $0, %rax
    leave
    ret
.L1536:
.L1532:
    jmp .L1530
.L1529:
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
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
    call looks_like_url
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L1543
    leaq -224(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    leaq .Lstr219(%rip), %rax
    pushq %rax
    movq $192, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    leaq -224(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $192, %rax
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
    call append
    movq %r12, %rsp
    popq %r12
    jmp .L1544
.L1543:
    leaq f_path(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $128, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call make_search
    movq %r12, %rsp
    popq %r12
    leaq f_host(%rip), %rax
    pushq %rax
    leaq .Lstr220(%rip), %rax
    pushq %rax
    movq $19, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call memcpy
    movq %r12, %rsp
    popq %r12
    leaq f_host(%rip), %rax
    pushq %rax
    movq $19, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq f_port(%rip), %rax
    pushq %rax
    movq $443, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_secure(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq f_host(%rip), %rax
    pushq %rax
    leaq f_path(%rip), %rax
    pushq %rax
    movq f_port(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fetch
    movq %r12, %rsp
    popq %r12
    movq f_dump_css(%rip), %rax
    cmpq $0, %rax
    je .L1545
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call print_css_dump
    movq %r12, %rsp
    popq %r12
.L1545:
    movq f_dump_dom(%rip), %rax
    cmpq $0, %rax
    je .L1547
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call print_dom_dump
    movq %r12, %rsp
    popq %r12
.L1547:
    movq $0, %rax
    leave
    ret
.L1544:
.L1530:
    leaq -224(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    addq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call split_url
    movq %r12, %rsp
    popq %r12
    testq %rax, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1549
    leaq .Lstr221(%rip), %rax
    pushq %rax
    leaq -224(%rbp), %rax
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
    movq $3, %rax
    leave
    ret
.L1549:
    leaq -240(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1552
.L1551:
    leaq -288(%rbp), %rax
    pushq %rax
    leaq f_host(%rip), %rax
    pushq %rax
    leaq f_path(%rip), %rax
    pushq %rax
    movq f_port(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    addq $24, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fetch
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -288(%rbp), %rax
    pushq %rax
    movq $300, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1554
    movq -288(%rbp), %rax
    pushq %rax
    movq $400, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L1554
    movl $1, %eax
    jmp .L1555
.L1554:
    xorl %eax, %eax
.L1555:
    testq %rax, %rax
    je .L1556
    movq f_redir(%rip), %rax
    testq %rax, %rax
    je .L1556
    movl $1, %eax
    jmp .L1557
.L1556:
    xorl %eax, %eax
.L1557:
    cmpq $0, %rax
    je .L1558
    movq -240(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1560
    leaq .Lstr222(%rip), %rax
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
    jmp .L1553
.L1560:
    leaq -240(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call resolve_redirect
    movq %r12, %rsp
    popq %r12
    cmpq $0, %rax
    je .L1562
    jmp .L1552
.L1562:
.L1558:
    jmp .L1553
.L1552:
    jmp .L1551
.L1553:
    movq f_dump_css(%rip), %rax
    cmpq $0, %rax
    je .L1564
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call print_css_dump
    movq %r12, %rsp
    popq %r12
    movq f_linkn(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L1566
    leaq -272(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L1570
.L1568:
    leaq .Lstr223(%rip), %rax
    pushq %rax
    leaq f_linkpath(%rip), %rax
    pushq %rax
    movq -272(%rbp), %rax
    popq %rcx
    imulq $128, %rax
    addq %rcx, %rax
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
    leaq f_linkhost(%rip), %rax
    pushq %rax
    movq -272(%rbp), %rax
    popq %rcx
    imulq $64, %rax
    addq %rcx, %rax
    pushq %rax
    leaq f_linkpath(%rip), %rax
    pushq %rax
    movq -272(%rbp), %rax
    popq %rcx
    imulq $128, %rax
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    addq $16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call fetch_css
    movq %r12, %rsp
    popq %r12
.L1569:
    leaq -272(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L1570
.L1570:
    movq -272(%rbp), %rax
    pushq %rax
    movq f_linkn(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .L1568
.L1571:
.L1566:
.L1564:
    movq f_dump_dom(%rip), %rax
    cmpq $0, %rax
    je .L1572
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call print_dom_dump
    movq %r12, %rsp
    popq %r12
.L1572:
    movq $0, %rax
    leave
    ret
    leave
    ret
    .section .rodata
.Lstr0:
    .asciz "/html/?q="
.Lstr1:
    .asciz "+"
.Lstr2:
    .asciz "%26"
.Lstr3:
    .asciz "%3D"
.Lstr4:
    .asciz "%2B"
.Lstr5:
    .asciz "/html/?q="
.Lstr6:
    .asciz "+"
.Lstr7:
    .asciz "%26"
.Lstr8:
    .asciz "%3D"
.Lstr9:
    .asciz "%2B"
.Lstr10:
    .asciz "https://"
.Lstr11:
    .asciz "http://"
.Lstr12:
    .asciz "https://"
.Lstr13:
    .asciz "http://"
.Lstr14:
    .asciz "https://"
.Lstr15:
    .asciz "http://"
.Lstr16:
    .asciz "https:"
.Lstr17:
    .asciz "http:"
.Lstr18:
    .asciz "freedom: redirect scheme refused"
.Lstr19:
    .asciz "https://"
.Lstr20:
    .asciz "http://"
.Lstr21:
    .asciz "https:"
.Lstr22:
    .asciz "http:"
.Lstr23:
    .asciz "freedom: redirect scheme refused"
.Lstr24:
    .asciz "amp"
.Lstr25:
    .asciz "lt"
.Lstr26:
    .asciz "gt"
.Lstr27:
    .asciz "quot"
.Lstr28:
    .asciz "apos"
.Lstr29:
    .asciz "nbsp"
.Lstr30:
    .asciz "amp"
.Lstr31:
    .asciz "lt"
.Lstr32:
    .asciz "gt"
.Lstr33:
    .asciz "quot"
.Lstr34:
    .asciz "apos"
.Lstr35:
    .asciz "nbsp"
.Lstr36:
    .asciz "id"
.Lstr37:
    .asciz "class"
.Lstr38:
    .asciz "href"
.Lstr39:
    .asciz "style"
.Lstr40:
    .asciz "rel"
.Lstr41:
    .asciz "stylesheet"
.Lstr42:
    .asciz "id"
.Lstr43:
    .asciz "class"
.Lstr44:
    .asciz "href"
.Lstr45:
    .asciz "style"
.Lstr46:
    .asciz "rel"
.Lstr47:
    .asciz "stylesheet"
.Lstr48:
    .asciz "br"
.Lstr49:
    .asciz "img"
.Lstr50:
    .asciz "meta"
.Lstr51:
    .asciz "link"
.Lstr52:
    .asciz "input"
.Lstr53:
    .asciz "hr"
.Lstr54:
    .asciz "area"
.Lstr55:
    .asciz "base"
.Lstr56:
    .asciz "col"
.Lstr57:
    .asciz "embed"
.Lstr58:
    .asciz "param"
.Lstr59:
    .asciz "source"
.Lstr60:
    .asciz "track"
.Lstr61:
    .asciz "wbr"
.Lstr62:
    .asciz "br"
.Lstr63:
    .asciz "img"
.Lstr64:
    .asciz "meta"
.Lstr65:
    .asciz "link"
.Lstr66:
    .asciz "input"
.Lstr67:
    .asciz "hr"
.Lstr68:
    .asciz "area"
.Lstr69:
    .asciz "base"
.Lstr70:
    .asciz "col"
.Lstr71:
    .asciz "embed"
.Lstr72:
    .asciz "param"
.Lstr73:
    .asciz "source"
.Lstr74:
    .asciz "track"
.Lstr75:
    .asciz "wbr"
.Lstr76:
    .asciz "script"
.Lstr77:
    .asciz "style"
.Lstr78:
    .asciz "script"
.Lstr79:
    .asciz "style"
.Lstr80:
    .asciz "style"
.Lstr81:
    .asciz "== style =="
.Lstr82:
    .asciz "#"
.Lstr83:
    .asciz "."
.Lstr84:
    .asciz " { "
.Lstr85:
    .asciz ";"
.Lstr86:
    .asciz " }"
.Lstr87:
    .asciz "link"
.Lstr88:
    .asciz "http://"
.Lstr89:
    .asciz "https://"
.Lstr90:
    .asciz "#"
.Lstr91:
    .asciz "."
.Lstr92:
    .asciz "br"
.Lstr93:
    .asciz "p"
.Lstr94:
    .asciz "div"
.Lstr95:
    .asciz "h1"
.Lstr96:
    .asciz "h2"
.Lstr97:
    .asciz "h3"
.Lstr98:
    .asciz "h4"
.Lstr99:
    .asciz "h5"
.Lstr100:
    .asciz "h6"
.Lstr101:
    .asciz "li"
.Lstr102:
    .asciz "tr"
.Lstr103:
    .asciz "script"
.Lstr104:
    .asciz "style"
.Lstr105:
    .asciz "script"
.Lstr106:
    .asciz "style"
.Lstr107:
    .asciz "style"
.Lstr108:
    .asciz "== style =="
.Lstr109:
    .asciz "#"
.Lstr110:
    .asciz "."
.Lstr111:
    .asciz " { "
.Lstr112:
    .asciz ";"
.Lstr113:
    .asciz " }"
.Lstr114:
    .asciz "link"
.Lstr115:
    .asciz "http://"
.Lstr116:
    .asciz "https://"
.Lstr117:
    .asciz "#"
.Lstr118:
    .asciz "."
.Lstr119:
    .asciz "br"
.Lstr120:
    .asciz "p"
.Lstr121:
    .asciz "div"
.Lstr122:
    .asciz "h1"
.Lstr123:
    .asciz "h2"
.Lstr124:
    .asciz "h3"
.Lstr125:
    .asciz "h4"
.Lstr126:
    .asciz "h5"
.Lstr127:
    .asciz "h6"
.Lstr128:
    .asciz "li"
.Lstr129:
    .asciz "tr"
.Lstr130:
    .asciz "script"
.Lstr131:
    .asciz "style"
.Lstr132:
    .asciz "style"
.Lstr133:
    .asciz "script"
.Lstr134:
    .asciz "style"
.Lstr135:
    .asciz "style"
.Lstr136:
    .asciz "location:"
.Lstr137:
    .asciz "content-length:"
.Lstr138:
    .asciz "transfer-encoding:"
.Lstr139:
    .asciz "chunked"
.Lstr140:
    .asciz "location:"
.Lstr141:
    .asciz "content-length:"
.Lstr142:
    .asciz "transfer-encoding:"
.Lstr143:
    .asciz "chunked"
.Lstr144:
    .asciz "freedom: cannot resolve %s\n"
.Lstr145:
    .asciz "freedom: socket failed"
.Lstr146:
    .asciz "freedom: connect to %s failed\n"
.Lstr147:
    .asciz "freedom: https handshake with %s failed\n"
.Lstr148:
    .asciz "GET "
.Lstr149:
    .asciz " HTTP/1.0\r\nHost: "
.Lstr150:
    .asciz "\r\nUser-Agent: freedom/1.0 (MiniOS)"
.Lstr151:
    .asciz "\r\nAccept: text/html"
.Lstr152:
    .asciz "\r\nConnection: close\r\n\r\n"
.Lstr153:
    .asciz "freedom: send to %s failed\n"
.Lstr154:
    .asciz "freedom: response header too large"
.Lstr155:
    .asciz "freedom: chunk too large"
.Lstr156:
    .asciz "freedom: %s (%d bytes)\n"
.Lstr157:
    .asciz "freedom: cannot resolve %s\n"
.Lstr158:
    .asciz "freedom: socket failed"
.Lstr159:
    .asciz "freedom: connect to %s failed\n"
.Lstr160:
    .asciz "freedom: https handshake with %s failed\n"
.Lstr161:
    .asciz "GET "
.Lstr162:
    .asciz " HTTP/1.0\r\nHost: "
.Lstr163:
    .asciz "\r\nUser-Agent: freedom/1.0 (MiniOS)"
.Lstr164:
    .asciz "\r\nAccept: text/html"
.Lstr165:
    .asciz "\r\nConnection: close\r\n\r\n"
.Lstr166:
    .asciz "freedom: send to %s failed\n"
.Lstr167:
    .asciz "freedom: response header too large"
.Lstr168:
    .asciz "freedom: chunk too large"
.Lstr169:
    .asciz "freedom: %s (%d bytes)\n"
.Lstr170:
    .asciz "freedom: cannot resolve %s\n"
.Lstr171:
    .asciz "freedom: connect to %s failed\n"
.Lstr172:
    .asciz "freedom: https handshake with %s failed\n"
.Lstr173:
    .asciz "GET "
.Lstr174:
    .asciz " HTTP/1.0\r\nHost: "
.Lstr175:
    .asciz "\r\nUser-Agent: freedom/1.0 (MiniOS)"
.Lstr176:
    .asciz "\r\nConnection: close\r\n\r\n"
.Lstr177:
    .asciz "freedom: %s (%d bytes)\n"
.Lstr178:
    .asciz "freedom: cannot resolve %s\n"
.Lstr179:
    .asciz "freedom: connect to %s failed\n"
.Lstr180:
    .asciz "freedom: https handshake with %s failed\n"
.Lstr181:
    .asciz "GET "
.Lstr182:
    .asciz " HTTP/1.0\r\nHost: "
.Lstr183:
    .asciz "\r\nUser-Agent: freedom/1.0 (MiniOS)"
.Lstr184:
    .asciz "\r\nConnection: close\r\n\r\n"
.Lstr185:
    .asciz "freedom: %s (%d bytes)\n"
.Lstr186:
    .asciz "=== freedom css ==="
.Lstr187:
    .asciz "(no css)"
.Lstr188:
    .asciz "=== freedom css ==="
.Lstr189:
    .asciz "(no css)"
.Lstr190:
    .asciz "=== freedom dom ==="
.Lstr191:
    .asciz "(no dom)"
.Lstr192:
    .asciz "=== freedom dom ==="
.Lstr193:
    .asciz "(no dom)"
.Lstr194:
    .asciz "usage: freedom [--dump-css|--dump-dom] [url-or-query]"
.Lstr195:
    .asciz "--dump-css"
.Lstr196:
    .asciz "usage: freedom --dump-css <url>"
.Lstr197:
    .asciz "--dump-dom"
.Lstr198:
    .asciz "usage: freedom --dump-dom <url>"
.Lstr199:
    .asciz "freedom: unknown flag %s\n"
.Lstr200:
    .asciz "usage: freedom [--dump-css|--dump-dom] [url-or-query]"
.Lstr201:
    .asciz "https://"
.Lstr202:
    .asciz "http://"
.Lstr203:
    .asciz "html.duckduckgo.com"
.Lstr204:
    .asciz "https://"
.Lstr205:
    .asciz "html.duckduckgo.com"
.Lstr206:
    .asciz "freedom: cannot parse %s\n"
.Lstr207:
    .asciz "freedom: too many redirects"
.Lstr208:
    .asciz "\n== %s ==\n"
.Lstr209:
    .asciz "usage: freedom [--dump-css|--dump-dom] [url-or-query]"
.Lstr210:
    .asciz "--dump-css"
.Lstr211:
    .asciz "usage: freedom --dump-css <url>"
.Lstr212:
    .asciz "--dump-dom"
.Lstr213:
    .asciz "usage: freedom --dump-dom <url>"
.Lstr214:
    .asciz "freedom: unknown flag %s\n"
.Lstr215:
    .asciz "usage: freedom [--dump-css|--dump-dom] [url-or-query]"
.Lstr216:
    .asciz "https://"
.Lstr217:
    .asciz "http://"
.Lstr218:
    .asciz "html.duckduckgo.com"
.Lstr219:
    .asciz "https://"
.Lstr220:
    .asciz "html.duckduckgo.com"
.Lstr221:
    .asciz "freedom: cannot parse %s\n"
.Lstr222:
    .asciz "freedom: too many redirects"
.Lstr223:
    .asciz "\n== %s ==\n"
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
