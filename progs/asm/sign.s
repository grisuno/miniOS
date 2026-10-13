    .section .text
    .data
sign_k0:
    .asciz "428a2f98d728ae227137449123ef65cdb5c0fbcfec4d3b2fe9b5dba58189dbbc3956c25bf348b53859f111f1b605d019923f82a4af194f9bab1c5ed5da6d8118d807aa98a303024212835b0145706fbe"
    .text
    .data
sign_k1:
    .asciz "243185be4ee4b28c550c7dc3d5ffb4e272be5d74f27b896f80deb1fe3b1696b19bdc06a725c71235c19bf174cf692694e49b69c19ef14ad2efbe4786384f25e30fc19dc68b8cd5b5240ca1cc77ac9c65"
    .text
    .data
sign_k2:
    .asciz "2de92c6f592b02754a7484aa6ea6e4835cb0a9dcbd41fbd476f988da831153b5983e5152ee66dfaba831c66d2db43210b00327c898fb213fbf597fc7beef0ee4c6e00bf33da88fc2d5a79147930aa725"
    .text
    .data
sign_k3:
    .asciz "06ca6351e003826f142929670a0e6e7027b70a8546d22ffc2e1b21385c26c9264d2c6dfc5ac42aed53380d139d95b3df650a73548baf63de766a0abb3c77b2a881c2c92e47edaee692722c851482353b"
    .text
    .data
sign_k4:
    .asciz "a2bfe8a14cf10364a81a664bbc423001c24b8b70d0f89791c76c51a30654be30d192e819d6ef5218d69906245565a910f40e35855771202a106aa07032bbd1b819a4c116b8d2d0c81e376c085141ab53"
    .text
    .data
sign_k5:
    .asciz "2748774cdf8eeb9934b0bcb5e19b48a8391c0cb3c5c95a634ed8aa4ae3418acb5b9cca4f7763e373682e6ff3d6b2b8a3748f82ee5defb2fc78a5636f43172f6084c87814a1f0ab728cc702081a6439ec"
    .text
    .data
sign_k6:
    .asciz "90befffa23631e28a4506cebde82bde9bef9a3f7b2c67915c67178f2e372532bca273eceea26619cd186b8c721c0c207eada7dd6cde0eb1ef57d4f7fee6ed17806f067aa72176fba0a637dc5a2c898a6"
    .text
    .data
sign_k7:
    .asciz "113f9804bef90dae1b710b35131c471b28db77f523047d8432caab7b40c724933c9ebe0a15c9bebc431d67c49c100d4c4cc5d4becb3e42b6597f299cfc657e2a5fcb6fab3ad6faec6c44198c4a475817"
    .text
    .data
sign_seed_hex:
    .asciz "ff0af8f46894a8f3949ff263703c48a01530e8ce42335bcd33fb0cffa4df704d"
    .text
    .data
sign_bx_hex:
    .asciz "216936d3cd6e53fec0a4e231fdd6dc5c692cc7609525a7b2c9562d608f25d51a"
    .text
    .data
sign_by_hex:
    .asciz "6666666666666666666666666666666666666666666666666666666666666658"
    .text
    .data
sign_ax_hex:
    .asciz "1aa42df16b69c861db1b83d0e94c277e2772d28c6370cabb91fcf7258dc34580"
    .text
    .data
sign_ay_hex:
    .asciz "1e56d7b8acaeb395ebebe52be3941aecb79c6608b2ba22eded5369649d8c96df"
    .text
    .data
sign_pub_hex:
    .asciz "df968c9d646953eded22bab208669cb7ec1a94e32be5ebeb95b3aeacb8d7561e"
    .text
    .data
sign_note_name:
    .asciz "MiniOS"
    .text
    .data
sign_section_name:
    .asciz ".note.minios.sign"
    .text
    .bss
sign_k:
    .space 1280
    .text
    .bss
sign_h:
    .space 128
    .text
    .bss
sign_w:
    .space 1280
    .text
    .bss
sign_buf:
    .space 128
    .text
    .bss
sign_used:
    .space 8
    .text
    .bss
sign_nlo:
    .space 8
    .text
    .bss
sign_nhi:
    .space 8
    .text
    .bss
sign_q4:
    .space 64
    .text
    .bss
sign_l8:
    .space 64
    .text
    .bss
sign_gb:
    .space 256
    .text
    .bss
sign_ga:
    .space 256
    .text
    .globl sign_hexval
sign_hexval:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movzbq -16(%rbp), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    cmpq %rax, %rcx
    setae %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L12
    movzbq -16(%rbp), %rax
    pushq %rax
    movq $57, %rax
    popq %rcx
    cmpq %rax, %rcx
    setbe %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L12
    movl $1, %eax
    jmp .L13
.L12:
    xorl %eax, %eax
.L13:
    cmpq $0, %rax
    je .L14
    movzbq -16(%rbp), %rax
    pushq %rax
    movq $48, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    leave
    ret
.L14:
    movzbq -16(%rbp), %rax
    pushq %rax
    movq $97, %rax
    popq %rcx
    cmpq %rax, %rcx
    setae %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L16
    movzbq -16(%rbp), %rax
    pushq %rax
    movq $102, %rax
    popq %rcx
    cmpq %rax, %rcx
    setbe %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L16
    movl $1, %eax
    jmp .L17
.L16:
    xorl %eax, %eax
.L17:
    cmpq $0, %rax
    je .L18
    movzbq -16(%rbp), %rax
    pushq %rax
    movq $97, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    addq %rcx, %rax
    leave
    ret
.L18:
    movzbq -16(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    cmpq %rax, %rcx
    setae %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L20
    movzbq -16(%rbp), %rax
    pushq %rax
    movq $70, %rax
    popq %rcx
    cmpq %rax, %rcx
    setbe %al
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
    movzbq -16(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    addq %rcx, %rax
    leave
    ret
.L22:
    movq $0, %rax
    leave
    ret
    leave
    ret
    .globl sign_unhex
sign_unhex:
    pushq %rbp
    movq %rsp, %rbp
    subq $112, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq $0, %rax
    movq %rax, -64(%rbp)
.L26:
    movq -64(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L27
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_hexval
    movq %r12, %rsp
    popq %r12
    movq %rax, -80(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_hexval
    movq %r12, %rsp
    popq %r12
    movq %rax, -96(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L26
.L27:
    leave
    ret
    .globl sign_byte
sign_byte:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movzbq (%rax), %rax
    movq %rax, -48(%rbp)
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L30
    leaq -48(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $256, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L30:
    movq -48(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl sign_copy
sign_copy:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq $0, %rax
    movq %rax, -64(%rbp)
.L34:
    movq -64(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L35
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -64(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L34
.L35:
    leave
    ret
    .globl sign_strlen
sign_strlen:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq $0, %rax
    movq %rax, -32(%rbp)
.L38:
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
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
    je .L39
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L38
.L39:
    movq -32(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl sign_le16
sign_le16:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
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
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl sign_le32
sign_le32:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
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
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl sign_put32
sign_put32:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
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
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leave
    ret
    .globl sign_hexout
sign_hexout:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq $0, %rax
    movq %rax, -64(%rbp)
.L46:
    movq -64(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L47
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    movq %rax, -80(%rbp)
    movq -80(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $15, %rax
    popq %rcx
    andq %rcx, %rax
    movq %rax, -96(%rbp)
    movq -80(%rbp), %rax
    pushq %rax
    movq $15, %rax
    popq %rcx
    andq %rcx, %rax
    movq %rax, -112(%rbp)
    movq -96(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    setb %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L48
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $48, %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L49
.L48:
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $87, %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
.L49:
    movq -112(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    setb %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L50
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $48, %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    jmp .L51
.L50:
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $87, %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
.L51:
    leaq -64(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L46
.L47:
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leave
    ret
    .globl sign_offok
sign_offok:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le32
    movq %r12, %rsp
    popq %r12
    movq %rax, -64(%rbp)
    movq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
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
    movq -48(%rbp), %rax
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
    call sign_le32
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    leave
    ret
    leave
    ret
    .globl sign_rotr
sign_rotr:
    pushq %rbp
    movq %rsp, %rbp
    subq $112, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq -16(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    movq %rax, -64(%rbp)
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    movq %rax, -80(%rbp)
    movq -48(%rbp), %rax
    movq %rax, -96(%rbp)
    movq -96(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L60
    leaq -64(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -96(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L60:
    movq -96(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L62
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
.L62:
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
    .globl sign_carry2
sign_carry2:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    notq %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    orq %rcx, %rax
    movq %rax, -64(%rbp)
    leaq -64(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -64(%rbp), %rax
    pushq %rax
    movq $31, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    andq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl sign_borrow2
sign_borrow2:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq -16(%rbp), %rax
    notq %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    notq %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    orq %rcx, %rax
    movq %rax, -64(%rbp)
    leaq -64(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -64(%rbp), %rax
    pushq %rax
    movq $31, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    andq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl sign_add3
sign_add3:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -80(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    movq %rax, -96(%rbp)
    movq -80(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -112(%rbp)
    leaq -96(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -80(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -96(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl sign_be32
sign_be32:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
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
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    popq %rcx
    orq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl sign_block
sign_block:
    pushq %rbp
    movq %rsp, %rbp
    subq $528, %rsp
    movq $0, %rax
    movq %rax, -144(%rbp)
.L74:
    movq -144(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L75
    movq -144(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq %rcx, %rax
    movq %rax, -160(%rbp)
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_buf(%rip), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_be32
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_buf(%rip), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_be32
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L74
.L75:
    leaq -144(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    movq %rax, (%rcx)
.L76:
    movq -144(%rbp), %rax
    pushq %rax
    movq $80, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L77
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $15, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -160(%rbp)
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $15, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -176(%rbp)
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -192(%rbp)
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -208(%rbp)
    movq $0, %rax
    movq %rax, -224(%rbp)
    movq $0, %rax
    movq %rax, -240(%rbp)
    movq $0, %rax
    movq %rax, -256(%rbp)
    movq $0, %rax
    movq %rax, -272(%rbp)
    movq $0, %rax
    movq %rax, -288(%rbp)
    movq $0, %rax
    movq %rax, -304(%rbp)
    movq $0, %rax
    movq %rax, -320(%rbp)
    movq $0, %rax
    movq %rax, -336(%rbp)
    movq $0, %rax
    movq %rax, -352(%rbp)
    movq $0, %rax
    movq %rax, -368(%rbp)
    movq $0, %rax
    movq %rax, -384(%rbp)
    leaq -160(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -192(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -208(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -224(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -240(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -256(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -272(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -288(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -320(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -336(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -224(%rbp), %rax
    pushq %rax
    leaq -240(%rbp), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -256(%rbp), %rax
    pushq %rax
    leaq -272(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    leaq -352(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq $25, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq $7, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -368(%rbp), %rax
    pushq %rax
    movq -240(%rbp), %rax
    pushq %rax
    movq -272(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq $7, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -288(%rbp), %rax
    pushq %rax
    leaq -304(%rbp), %rax
    pushq %rax
    movq $19, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -336(%rbp), %rax
    pushq %rax
    movq $61, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    leaq -288(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq $26, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $6, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -208(%rbp), %rax
    pushq %rax
    movq $6, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    movq %rax, -400(%rbp)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    pushq %rax
    movq -336(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    pushq %rax
    movq -400(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -384(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -352(%rbp), %rax
    pushq %rax
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -352(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sign_add3
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -384(%rbp), %rax
    pushq %rax
    movq -384(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -352(%rbp), %rax
    pushq %rax
    movq -352(%rbp), %rax
    pushq %rax
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sign_add3
    movq %r12, %rsp
    popq %r12
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -368(%rbp), %rax
    pushq %rax
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -368(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -384(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -352(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -368(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L76
.L77:
    leaq -144(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L78:
    movq -144(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L79
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq sign_h(%rip), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L78
.L79:
    leaq -144(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L80:
    movq -144(%rbp), %rax
    pushq %rax
    movq $80, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L81
    leaq -128(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -160(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -176(%rbp)
    movq -160(%rbp), %rax
    movq %rax, -192(%rbp)
    movq -176(%rbp), %rax
    movq %rax, -208(%rbp)
    movq -160(%rbp), %rax
    movq %rax, -224(%rbp)
    movq -176(%rbp), %rax
    movq %rax, -240(%rbp)
    movq -160(%rbp), %rax
    movq %rax, -256(%rbp)
    movq -176(%rbp), %rax
    movq %rax, -272(%rbp)
    movq -160(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq -160(%rbp), %rax
    notq %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    movq %rax, -288(%rbp)
    movq -176(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $11, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq -176(%rbp), %rax
    notq %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    movq %rax, -304(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -320(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -336(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -352(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -368(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -384(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -400(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    movq %rax, -416(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    movq %rax, -432(%rbp)
    movq $0, %rax
    movq %rax, -448(%rbp)
    movq $0, %rax
    movq %rax, -464(%rbp)
    movq $0, %rax
    movq %rax, -480(%rbp)
    movq $0, %rax
    movq %rax, -496(%rbp)
    movq $0, %rax
    movq %rax, -512(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    leaq -208(%rbp), %rax
    pushq %rax
    movq $14, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -224(%rbp), %rax
    pushq %rax
    leaq -240(%rbp), %rax
    pushq %rax
    movq $18, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -256(%rbp), %rax
    pushq %rax
    leaq -272(%rbp), %rax
    pushq %rax
    movq $41, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    leaq -192(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -208(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq -240(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    movq -272(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -336(%rbp), %rax
    pushq %rax
    movq $28, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -352(%rbp), %rax
    pushq %rax
    leaq -368(%rbp), %rax
    pushq %rax
    movq $34, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -384(%rbp), %rax
    pushq %rax
    leaq -400(%rbp), %rax
    pushq %rax
    movq $39, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_rotr
    movq %r12, %rsp
    popq %r12
    leaq -320(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq -352(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    movq -384(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -336(%rbp), %rax
    pushq %rax
    movq -336(%rbp), %rax
    pushq %rax
    movq -368(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    pushq %rax
    movq -400(%rbp), %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -512(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -448(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $14, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sign_add3
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -512(%rbp), %rax
    pushq %rax
    movq -512(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -448(%rbp), %rax
    pushq %rax
    movq -448(%rbp), %rax
    pushq %rax
    leaq sign_k(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sign_add3
    movq %r12, %rsp
    popq %r12
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -464(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $15, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -208(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq sign_k(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq sign_w(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -512(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -512(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -480(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq -416(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sign_add3
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -496(%rbp), %rax
    pushq %rax
    movq -336(%rbp), %rax
    pushq %rax
    movq -432(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -512(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $14, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $15, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $11, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $11, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -512(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -128(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -448(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sign_add3
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -464(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -512(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -512(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -448(%rbp), %rax
    pushq %rax
    movq -480(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sign_add3
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -464(%rbp), %rax
    pushq %rax
    movq -496(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -512(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L80
.L81:
    leaq -144(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L82:
    movq -144(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L83
    leaq sign_h(%rip), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -160(%rbp)
    movq $0, %rax
    movq %rax, -176(%rbp)
    leaq -176(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq sign_h(%rip), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    leaq -160(%rbp), %rax
    pushq %rax
    leaq sign_h(%rip), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    movq (%rax), %rcx
    addq $1, (%rax)
    movq %rcx, %rax
    jmp .L82
.L83:
    leave
    ret
    .globl sign_sha_init
sign_sha_init:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4089235720, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1779033703, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $2227873595, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $3144134277, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4271175723, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1013904242, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1595750129, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $2773480762, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $2917565137, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1359893119, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $725511199, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $11, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $2600822924, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4215389547, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $13, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $528734635, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $14, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $327033209, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $15, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1541459225, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_nlo(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_nhi(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_used(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
    .globl sign_sha_update
sign_sha_update:
    pushq %rbp
    movq %rsp, %rbp
    subq $144, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -48(%rbp)
    movq -32(%rbp), %rax
    pushq %rax
    movq $3, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    movq %rax, -64(%rbp)
    movq sign_nlo(%rip), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -80(%rbp)
    movq -80(%rbp), %rax
    pushq %rax
    movq sign_nlo(%rip), %rax
    popq %rcx
    cmpq %rax, %rcx
    setb %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L94
    leaq sign_nhi(%rip), %rax
    pushq %rax
    movq sign_nhi(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L94:
    leaq sign_nlo(%rip), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_nhi(%rip), %rax
    pushq %rax
    movq sign_nhi(%rip), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $29, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L96:
    movq -48(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L97
    movq $128, %rax
    pushq %rax
    movq sign_used(%rip), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -96(%rbp)
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -112(%rbp)
    movq $0, %rax
    movq %rax, -128(%rbp)
    movq -96(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L98
    leaq -96(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
.L98:
.L100:
    movq -128(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L101
    leaq sign_buf(%rip), %rax
    pushq %rax
    movq sign_used(%rip), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L100
.L101:
    leaq sign_used(%rip), %rax
    pushq %rax
    movq sign_used(%rip), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq sign_used(%rip), %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L102
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_block
    movq %r12, %rsp
    popq %r12
    leaq sign_used(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L102:
    jmp .L96
.L97:
    leave
    ret
    .globl sign_sha_final
sign_sha_final:
    pushq %rbp
    movq %rsp, %rbp
    subq $112, %rsp
    movq %rdi, -16(%rbp)
    movq $0, %rax
    movq %rax, -32(%rbp)
    movq $0, %rax
    movq %rax, -48(%rbp)
    leaq sign_buf(%rip), %rax
    pushq %rax
    movq sign_used(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq sign_used(%rip), %rax
    pushq %rax
    movq sign_used(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq sign_used(%rip), %rax
    pushq %rax
    movq $112, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L122
.L124:
    movq sign_used(%rip), %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L125
    leaq sign_buf(%rip), %rax
    pushq %rax
    movq sign_used(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq sign_used(%rip), %rax
    pushq %rax
    movq sign_used(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L124
.L125:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_block
    movq %r12, %rsp
    popq %r12
    leaq sign_used(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L122:
.L126:
    movq sign_used(%rip), %rax
    pushq %rax
    movq $112, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L127
    leaq sign_buf(%rip), %rax
    pushq %rax
    movq sign_used(%rip), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq sign_used(%rip), %rax
    pushq %rax
    movq sign_used(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L126
.L127:
.L128:
    movq -32(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L129
    leaq sign_buf(%rip), %rax
    pushq %rax
    movq $112, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L128
.L129:
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L130:
    movq -32(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L131
    leaq sign_buf(%rip), %rax
    pushq %rax
    movq $120, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L130
.L131:
.L132:
    movq -32(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L133
    leaq sign_buf(%rip), %rax
    pushq %rax
    movq $120, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq sign_nlo(%rip), %rax
    pushq %rax
    movq $56, %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L132
.L133:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_block
    movq %r12, %rsp
    popq %r12
.L134:
    movq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L135
    movq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq %rcx, %rax
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -80(%rbp)
.L136:
    movq -80(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L137
    movq $0, %rax
    movq %rax, -96(%rbp)
    movq -80(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L138
    leaq -96(%rbp), %rax
    pushq %rax
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L139
.L138:
    leaq -96(%rbp), %rax
    pushq %rax
    leaq sign_h(%rip), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $56, %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L139:
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L136
.L137:
    leaq -48(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L134
.L135:
    leave
    ret
    .globl sign_feed32
sign_feed32:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    leaq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -32(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_sha_update
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl sign_key_init
sign_key_init:
    pushq %rbp
    movq %rsp, %rbp
    subq $176, %rsp
    movq $0, %rax
    movq %rax, -96(%rbp)
.L158:
    movq -96(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L159
    leaq sign_k0(%rip), %rax
    movq %rax, -112(%rbp)
    movq $0, %rax
    movq %rax, -128(%rbp)
    movq -96(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L160
    leaq -112(%rbp), %rax
    pushq %rax
    leaq sign_k1(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
.L160:
    movq -96(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L162
    leaq -112(%rbp), %rax
    pushq %rax
    leaq sign_k2(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
.L162:
    movq -96(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L164
    leaq -112(%rbp), %rax
    pushq %rax
    leaq sign_k3(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
.L164:
    movq -96(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L166
    leaq -112(%rbp), %rax
    pushq %rax
    leaq sign_k4(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
.L166:
    movq -96(%rbp), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L168
    leaq -112(%rbp), %rax
    pushq %rax
    leaq sign_k5(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
.L168:
    movq -96(%rbp), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L170
    leaq -112(%rbp), %rax
    pushq %rax
    leaq sign_k6(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
.L170:
    movq -96(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L172
    leaq -112(%rbp), %rax
    pushq %rax
    leaq sign_k7(%rip), %rax
    popq %rcx
    movq %rax, (%rcx)
.L172:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -80(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq $80, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_unhex
    movq %r12, %rsp
    popq %r12
.L174:
    movq -128(%rbp), %rax
    pushq %rax
    movq $10, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L175
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -80(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_be32
    movq %r12, %rsp
    popq %r12
    movq %rax, -144(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -80(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_be32
    movq %r12, %rsp
    popq %r12
    movq %rax, -160(%rbp)
    leaq sign_k(%rip), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq $20, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_k(%rip), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq $20, %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L174
.L175:
    leaq -96(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L158
.L159:
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4294967277, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4294967295, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4294967295, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4294967295, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4294967295, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4294967295, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $4294967295, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $2147483647, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1559614445, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1477600026, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $2734136534, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $350157278, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq $5, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $268435456, %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
    .globl fe_copy
fe_copy:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -48(%rbp)
.L178:
    movq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L179
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L178
.L179:
    leave
    ret
    .globl fe_zero
fe_zero:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq $0, %rax
    movq %rax, -32(%rbp)
.L182:
    movq -32(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L183
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L182
.L183:
    leave
    ret
    .globl fe_one
fe_one:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_zero
    movq %r12, %rsp
    popq %r12
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leave
    ret
    .globl fe_cmov
fe_cmov:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq $0, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -80(%rbp)
.L186:
    movq -80(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L187
    movq -16(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L186
.L187:
    leave
    ret
    .globl fe_ge
fe_ge:
    pushq %rbp
    movq %rsp, %rbp
    subq $144, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -48(%rbp)
    movq $0, %rax
    movq %rax, -64(%rbp)
.L190:
    movq -64(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L191
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
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -80(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_borrow2
    movq %r12, %rsp
    popq %r12
    movq %rax, -96(%rbp)
    movq -80(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -112(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -80(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_borrow2
    movq %r12, %rsp
    popq %r12
    movq %rax, -128(%rbp)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L190
.L191:
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    xorq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl fe_rawsub
fe_rawsub:
    pushq %rbp
    movq %rsp, %rbp
    subq $176, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq $0, %rax
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -80(%rbp)
.L194:
    movq -80(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L195
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -96(%rbp)
    movq -96(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -112(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -96(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_borrow2
    movq %r12, %rsp
    popq %r12
    movq %rax, -128(%rbp)
    movq -112(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -144(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -112(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_borrow2
    movq %r12, %rsp
    popq %r12
    movq %rax, -160(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L194
.L195:
    leave
    ret
    .globl fe_add
fe_add:
    pushq %rbp
    movq %rsp, %rbp
    subq $224, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq $0, %rax
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -144(%rbp)
.L202:
    movq -144(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L203
    movq -32(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -160(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    movq %rax, -176(%rbp)
    movq -160(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -192(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -160(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    movq %rax, -208(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -192(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L202
.L203:
    movq -64(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L204
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -128(%rbp), %rax
    pushq %rax
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_ge
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L204
    xorl %eax, %eax
    jmp .L205
.L204:
    movl $1, %eax
.L205:
    cmpq $0, %rax
    je .L206
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -128(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_rawsub
    movq %r12, %rsp
    popq %r12
.L206:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl fe_sub
fe_sub:
    pushq %rbp
    movq %rsp, %rbp
    subq $240, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq $0, %rax
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -144(%rbp)
.L214:
    movq -144(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L215
    movq -32(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -160(%rbp)
    movq -160(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -176(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -160(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_borrow2
    movq %r12, %rsp
    popq %r12
    movq %rax, -192(%rbp)
    movq -176(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -208(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -176(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_borrow2
    movq %r12, %rsp
    popq %r12
    movq %rax, -224(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -208(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L214
.L215:
    movq -64(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L216
    movq $0, %rax
    movq %rax, -160(%rbp)
    leaq -144(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L218:
    movq -144(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L219
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -176(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    movq %rax, -192(%rbp)
    movq -176(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -208(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -176(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    movq %rax, -224(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -208(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -160(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L218
.L219:
.L216:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl fe_rowadd
fe_rowadd:
    pushq %rbp
    movq %rsp, %rbp
    subq $128, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq -32(%rbp), %rax
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -80(%rbp)
    leaq -80(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
.L224:
    movq -64(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L226
    movq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
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
    cmpq $0, %rax
    je .L225
    movq $0, %rax
    movq %rax, -96(%rbp)
    movq $0, %rax
    movq %rax, -112(%rbp)
    leaq -96(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -112(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -64(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L224
.L225:
    leave
    ret
    .globl fe_foldadd
fe_foldadd:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq -48(%rbp), %rax
    pushq %rax
    movq $5, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -64(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_rowadd
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl fe_mul
fe_mul:
    pushq %rbp
    movq %rsp, %rbp
    subq $768, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq $0, %rax
    movq %rax, -576(%rbp)
    movq $0, %rax
    movq %rax, -592(%rbp)
    movq $0, %rax
    movq %rax, -608(%rbp)
    movq $0, %rax
    movq %rax, -624(%rbp)
.L252:
    movq -576(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L253
    leaq -176(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -576(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L252
.L253:
.L254:
    movq -608(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L255
    leaq -560(%rbp), %rax
    pushq %rax
    movq -608(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -608(%rbp), %rax
    pushq %rax
    movq -608(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L254
.L255:
    leaq -576(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L256:
    movq -576(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L257
    leaq -592(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L258:
    movq -592(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L259
    leaq -176(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -304(%rbp), %rax
    pushq %rax
    movq -592(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    imulq %rcx, %rax
    movq %rax, -640(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -560(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    pushq %rax
    movq -592(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -640(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_rowadd
    movq %r12, %rsp
    popq %r12
    leaq -592(%rbp), %rax
    pushq %rax
    movq -592(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L258
.L259:
    leaq -576(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L256
.L257:
.L260:
    movq -624(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L261
    movq $0, %rax
    movq %rax, -640(%rbp)
    movq $0, %rax
    movq %rax, -656(%rbp)
.L262:
    movq -640(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L263
    leaq -560(%rbp), %rax
    pushq %rax
    movq -640(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L264
    leaq -656(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L264:
    leaq -640(%rbp), %rax
    pushq %rax
    movq -640(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L262
.L263:
    movq -656(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L266
    jmp .L261
.L266:
    leaq -640(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L268:
    movq -640(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L269
    leaq -560(%rbp), %rax
    pushq %rax
    movq -640(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -672(%rbp)
    leaq -560(%rbp), %rax
    pushq %rax
    movq -640(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -560(%rbp), %rax
    pushq %rax
    movq -640(%rbp), %rax
    pushq %rax
    movq -672(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_foldadd
    movq %r12, %rsp
    popq %r12
    leaq -640(%rbp), %rax
    pushq %rax
    movq -640(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L268
.L269:
    leaq -624(%rbp), %rax
    pushq %rax
    movq -624(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L260
.L261:
    leaq -576(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L270:
    movq -576(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L271
    leaq -688(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -560(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    leaq -560(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -576(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -576(%rbp), %rax
    pushq %rax
    movq -576(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L270
.L271:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -752(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_zero
    movq %r12, %rsp
    popq %r12
    leaq -752(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -560(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $38, %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -688(%rbp), %rax
    pushq %rax
    leaq -688(%rbp), %rax
    pushq %rax
    leaq -752(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    leaq -608(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L272:
    movq -608(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L273
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -688(%rbp), %rax
    pushq %rax
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_ge
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L274
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -688(%rbp), %rax
    pushq %rax
    leaq -688(%rbp), %rax
    pushq %rax
    leaq sign_q4(%rip), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_rawsub
    movq %r12, %rsp
    popq %r12
.L274:
    leaq -608(%rbp), %rax
    pushq %rax
    movq -608(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L272
.L273:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -688(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl fe_sq
fe_sq:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl fe_inv
fe_inv:
    pushq %rbp
    movq %rsp, %rbp
    subq $208, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -176(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -96(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_one
    movq %r12, %rsp
    popq %r12
.L282:
    movq -176(%rbp), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L283
    movq $1, %rax
    movq %rax, -192(%rbp)
    movq -176(%rbp), %rax
    pushq %rax
    movq $252, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L284
    movq -176(%rbp), %rax
    pushq %rax
    movq $250, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L284
    xorl %eax, %eax
    jmp .L285
.L284:
    movl $1, %eax
.L285:
    cmpq $0, %rax
    je .L286
    leaq -192(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L286:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -160(%rbp), %rax
    pushq %rax
    leaq -96(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_sq
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -96(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -160(%rbp), %rax
    pushq %rax
    leaq -96(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -96(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_cmov
    movq %r12, %rsp
    popq %r12
    leaq -176(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L282
.L283:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -96(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl fe_frombytes
fe_frombytes:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -48(%rbp)
.L290:
    movq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L291
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L290
.L291:
    leave
    ret
    .globl fe_tobytes
fe_tobytes:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -48(%rbp)
.L294:
    movq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L295
    movq -16(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
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
    movq -16(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
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
    movq -16(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
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
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L294
.L295:
    leave
    ret
    .globl fe_curved
fe_curved:
    pushq %rbp
    movq %rsp, %rbp
    subq $304, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -96(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_zero
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -160(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_zero
    movq %r12, %rsp
    popq %r12
    leaq -96(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $121665, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -160(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $121666, %rax
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -224(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_inv
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -96(%rbp), %rax
    pushq %rax
    leaq -224(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -288(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_zero
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -288(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl ge_copy
ge_copy:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -48(%rbp)
.L298:
    movq -48(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L299
    movq -16(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -48(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L298
.L299:
    leave
    ret
    .globl fe_off
fe_off:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    leave
    ret
    leave
    ret
    .globl ge_cmov
ge_cmov:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq $0, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -80(%rbp)
.L302:
    movq -80(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L303
    movq -16(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    xorq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -80(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L302
.L303:
    leave
    ret
    .globl ge_add
ge_add:
    pushq %rbp
    movq %rsp, %rbp
    subq $720, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -640(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -704(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -128(%rbp), %rax
    pushq %rax
    leaq -640(%rbp), %rax
    pushq %rax
    leaq -704(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -640(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -704(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    leaq -640(%rbp), %rax
    pushq %rax
    leaq -704(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -640(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -256(%rbp), %rax
    pushq %rax
    leaq -640(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -640(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -640(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -384(%rbp), %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -448(%rbp), %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -256(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -512(%rbp), %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -256(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -576(%rbp), %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -384(%rbp), %rax
    pushq %rax
    leaq -448(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -512(%rbp), %rax
    pushq %rax
    leaq -576(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -448(%rbp), %rax
    pushq %rax
    leaq -512(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -384(%rbp), %rax
    pushq %rax
    leaq -576(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl ge_double
ge_double:
    pushq %rbp
    movq %rsp, %rbp
    subq $752, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -96(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_sq
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -160(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_sq
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -544(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_sq
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -224(%rbp), %rax
    pushq %rax
    leaq -544(%rbp), %rax
    pushq %rax
    leaq -544(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -544(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -544(%rbp), %rax
    pushq %rax
    leaq -544(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_sq
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -608(%rbp), %rax
    pushq %rax
    leaq -544(%rbp), %rax
    pushq %rax
    leaq -96(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -288(%rbp), %rax
    pushq %rax
    leaq -608(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -672(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_zero
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -672(%rbp), %rax
    pushq %rax
    leaq -672(%rbp), %rax
    pushq %rax
    leaq -96(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -416(%rbp), %rax
    pushq %rax
    leaq -672(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -352(%rbp), %rax
    pushq %rax
    leaq -416(%rbp), %rax
    pushq %rax
    leaq -224(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -736(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_zero
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -736(%rbp), %rax
    pushq %rax
    leaq -736(%rbp), %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_sub
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -480(%rbp), %rax
    pushq %rax
    leaq -672(%rbp), %rax
    pushq %rax
    leaq -736(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -288(%rbp), %rax
    pushq %rax
    leaq -352(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -416(%rbp), %rax
    pushq %rax
    leaq -480(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -352(%rbp), %rax
    pushq %rax
    leaq -416(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -288(%rbp), %rax
    pushq %rax
    leaq -480(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl ge_scalarmult
ge_scalarmult:
    pushq %rbp
    movq %rsp, %rbp
    subq $624, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    movq $0, %rax
    movq %rax, -592(%rbp)
.L310:
    movq -592(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L311
    leaq -320(%rbp), %rax
    pushq %rax
    movq -592(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -592(%rbp), %rax
    pushq %rax
    movq -592(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L310
.L311:
    leaq -320(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -320(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -592(%rbp), %rax
    pushq %rax
    movq $254, %rax
    popq %rcx
    movq %rax, (%rcx)
.L312:
    movq -592(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L313
    movq $0, %rax
    movq %rax, -608(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq -592(%rbp), %rax
    pushq %rax
    movq $3, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq -592(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L314
    leaq -608(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L314:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -576(%rbp), %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call ge_double
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -576(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call ge_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -576(%rbp), %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call ge_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -576(%rbp), %rax
    pushq %rax
    movq -608(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call ge_cmov
    movq %r12, %rsp
    popq %r12
    leaq -592(%rbp), %rax
    pushq %rax
    movq -592(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L312
.L313:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call ge_copy
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl sc_mod_l
sc_mod_l:
    pushq %rbp
    movq %rsp, %rbp
    subq $400, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -128(%rbp)
    movq $0, %rax
    movq %rax, -144(%rbp)
    movq $0, %rax
    movq %rax, -160(%rbp)
    movq $0, %rax
    movq %rax, -176(%rbp)
.L336:
    movq -144(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L337
    leaq -112(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L336
.L337:
.L338:
    movq -128(%rbp), %rax
    pushq %rax
    movq $512, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L339
    movq $63, %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -192(%rbp)
    movq $7, %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    movq %rdx, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -208(%rbp)
    movq $0, %rax
    movq %rax, -224(%rbp)
    movq -192(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    movq %rax, -240(%rbp)
    movq -192(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    movq %rdx, %rax
    movq %rax, -256(%rbp)
    movq $0, %rax
    movq %rax, -272(%rbp)
    leaq -272(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -240(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -224(%rbp), %rax
    pushq %rax
    movq -272(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq -208(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    popq %rcx
    popq %rax
    shrq %cl, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L340:
    movq -176(%rbp), %rax
    pushq %rax
    movq $9, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L341
    movq $0, %rax
    movq %rax, -288(%rbp)
    leaq -112(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $31, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L342
    leaq -288(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L342:
    leaq -112(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -112(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq -224(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -224(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L340
.L341:
    leaq -160(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L344:
    movq -160(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L345
    movq $0, %rax
    movq %rax, -288(%rbp)
    leaq -112(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L346
    leaq -288(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L347
.L346:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -112(%rbp), %rax
    pushq %rax
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_ge
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L348
    leaq -288(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L348:
.L347:
    movq -288(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L350
    movq $0, %rax
    movq %rax, -304(%rbp)
    leaq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L352:
    movq -176(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L353
    leaq -112(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    movq %rax, -320(%rbp)
    movq -320(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -336(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -320(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    pushq %rax
    movq -336(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_borrow2
    movq %r12, %rsp
    popq %r12
    movq %rax, -352(%rbp)
    movq -336(%rbp), %rax
    pushq %rax
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -368(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -336(%rbp), %rax
    pushq %rax
    leaq sign_l8(%rip), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -368(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_borrow2
    movq %r12, %rsp
    popq %r12
    movq %rax, -384(%rbp)
    leaq -112(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -368(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -352(%rbp), %rax
    pushq %rax
    movq -384(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L352
.L353:
    leaq -112(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -112(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L350:
    leaq -160(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L344
.L345:
    leaq -128(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L338
.L339:
    leaq -144(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L354:
    movq -144(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L355
    movq -16(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -112(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -144(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L354
.L355:
    leave
    ret
    .globl sc_mul_add
sc_mul_add:
    pushq %rbp
    movq %rsp, %rbp
    subq $848, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    movq $0, %rax
    movq %rax, -720(%rbp)
    movq $0, %rax
    movq %rax, -736(%rbp)
    movq $0, %rax
    movq %rax, -752(%rbp)
.L370:
    movq -720(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L371
    leaq -192(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -192(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -320(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -320(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -720(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L370
.L371:
.L372:
    movq -752(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L373
    leaq -576(%rbp), %rax
    pushq %rax
    movq -752(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -752(%rbp), %rax
    pushq %rax
    movq -752(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L372
.L373:
    leaq -720(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L374:
    movq -720(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L375
    leaq -736(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L376:
    movq -736(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L377
    leaq -192(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    movq -736(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    imulq %rcx, %rax
    movq %rax, -768(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -576(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    pushq %rax
    movq -736(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -768(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_rowadd
    movq %r12, %rsp
    popq %r12
    leaq -736(%rbp), %rax
    pushq %rax
    movq -736(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L376
.L377:
    leaq -720(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L374
.L375:
    leaq -720(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L378:
    movq -720(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L379
    leaq -704(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    leaq -576(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $65535, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    leaq -576(%rbp), %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -720(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L378
.L379:
    movq $0, %rax
    movq %rax, -768(%rbp)
    leaq -720(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L380:
    movq -720(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L381
    leaq -704(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -784(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -704(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -784(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    movq %rax, -800(%rbp)
    movq -784(%rbp), %rax
    pushq %rax
    movq -768(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -816(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -784(%rbp), %rax
    pushq %rax
    movq -768(%rbp), %rax
    pushq %rax
    movq -816(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    movq %rax, -832(%rbp)
    leaq -704(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -816(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -768(%rbp), %rax
    pushq %rax
    movq -800(%rbp), %rax
    pushq %rax
    movq -832(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -720(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L380
.L381:
.L382:
    movq -720(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L383
    leaq -704(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -768(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -784(%rbp)
    leaq -768(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -704(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq -768(%rbp), %rax
    pushq %rax
    movq -784(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_carry2
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -704(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq -784(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -720(%rbp), %rax
    pushq %rax
    movq -720(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L382
.L383:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -704(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sc_mod_l
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl sign_rev32
sign_rev32:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq $0, %rax
    movq %rax, -32(%rbp)
.L386:
    movq -32(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L387
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    movq %rax, -48(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $31, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    movq -16(%rbp), %rax
    pushq %rax
    movq $31, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movsbq -48(%rbp), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -32(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L386
.L387:
    leave
    ret
    .globl sign_points_init
sign_points_init:
    pushq %rbp
    movq %rsp, %rbp
    subq $208, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -32(%rbp), %rax
    pushq %rax
    leaq sign_bx_hex(%rip), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_unhex
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -64(%rbp), %rax
    pushq %rax
    leaq sign_by_hex(%rip), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_unhex
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -96(%rbp), %rax
    pushq %rax
    leaq sign_ax_hex(%rip), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_unhex
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -128(%rbp), %rax
    pushq %rax
    leaq sign_ay_hex(%rip), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_unhex
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -32(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_rev32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -64(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_rev32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -96(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_rev32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -128(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_rev32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    leaq -32(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_frombytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_gb(%rip), %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    leaq -64(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_frombytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_gb(%rip), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_gb(%rip), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_one
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    leaq sign_gb(%rip), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_gb(%rip), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_gb(%rip), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    leaq -96(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_frombytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_ga(%rip), %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_frombytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_ga(%rip), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_ga(%rip), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fe_one
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    leaq sign_ga(%rip), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_ga(%rip), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq sign_ga(%rip), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl sign_digest
sign_digest:
    pushq %rbp
    movq %rsp, %rbp
    subq $1504, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -1360(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -64(%rbp), %rax
    pushq %rax
    leaq sign_seed_hex(%rip), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_unhex
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_sha_init
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -64(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_sha_update
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -128(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_sha_final
    movq %r12, %rsp
    popq %r12
    leaq -1360(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L406:
    movq -1360(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L407
    leaq -320(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -1360(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L406
.L407:
    leaq -320(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $248, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -320(%rbp), %rax
    pushq %rax
    movq $31, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    movq $31, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $63, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -448(%rbp), %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_frombytes
    movq %r12, %rsp
    popq %r12
    leaq -1360(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L408:
    movq -1360(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L409
    leaq -1488(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1360(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L408
.L409:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -448(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_tobytes
    movq %r12, %rsp
    popq %r12
    leaq -1360(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L410:
    movq -1360(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L411
    leaq -1488(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1360(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L410
.L411:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -448(%rbp), %rax
    pushq %rax
    leaq -1488(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sc_mod_l
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -448(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_tobytes
    movq %r12, %rsp
    popq %r12
    leaq -1360(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L412:
    movq -1360(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L413
    leaq -64(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -1360(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L412
.L413:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_sha_init
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -64(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_sha_update
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $64, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_sha_update
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_sha_final
    movq %r12, %rsp
    popq %r12
    leaq -1360(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L414:
    movq -1360(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L415
    leaq -1344(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1360(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L414
.L415:
    leaq -1360(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L416:
    movq -1360(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L417
    leaq -1344(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -192(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1360(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L416
.L417:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -512(%rbp), %rax
    pushq %rax
    leaq -1344(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sc_mod_l
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -352(%rbp), %rax
    pushq %rax
    leaq -512(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_tobytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -704(%rbp), %rax
    pushq %rax
    leaq -768(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_curved
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -384(%rbp), %rax
    pushq %rax
    leaq -768(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_tobytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -1024(%rbp), %rax
    pushq %rax
    leaq sign_gb(%rip), %rax
    pushq %rax
    leaq -352(%rbp), %rax
    pushq %rax
    leaq -768(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call ge_scalarmult
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -1088(%rbp), %rax
    pushq %rax
    leaq -1024(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -1152(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -1024(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -1088(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_tobytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -1152(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_tobytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -1216(%rbp), %rax
    pushq %rax
    leaq -1152(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_inv
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -1088(%rbp), %rax
    pushq %rax
    leaq -1088(%rbp), %rax
    pushq %rax
    leaq -1216(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    movq %rax, -1440(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -1424(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -1024(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_off
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -1424(%rbp), %rax
    pushq %rax
    leaq -1424(%rbp), %rax
    pushq %rax
    leaq -1216(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fe_mul
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -224(%rbp), %rax
    pushq %rax
    leaq -1424(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_tobytes
    movq %r12, %rsp
    popq %r12
    leaq -1088(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    andq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L418
    leaq -1440(%rbp), %rax
    pushq %rax
    movq $128, %rax
    popq %rcx
    movq %rax, (%rcx)
.L418:
    leaq -224(%rbp), %rax
    pushq %rax
    movq $31, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -224(%rbp), %rax
    pushq %rax
    movq $31, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq -1440(%rbp), %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -1392(%rbp), %rax
    pushq %rax
    leaq sign_pub_hex(%rip), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_unhex
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_sha_init
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -224(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_sha_update
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -1392(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_sha_update
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $64, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_sha_update
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -288(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_sha_final
    movq %r12, %rsp
    popq %r12
    leaq -1360(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L420:
    movq -1360(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L421
    leaq -1344(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1360(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L420
.L421:
    leaq -1360(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L422:
    movq -1360(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L423
    leaq -1344(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -288(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -288(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -288(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $16, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -288(%rbp), %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq -1360(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_byte
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $24, %rax
    pushq %rax
    popq %rcx
    popq %rax
    salq %cl, %rax
    popq %rcx
    orq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -1360(%rbp), %rax
    pushq %rax
    movq -1360(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L422
.L423:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -576(%rbp), %rax
    pushq %rax
    leaq -1344(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sc_mod_l
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -384(%rbp), %rax
    pushq %rax
    leaq -576(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_tobytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -640(%rbp), %rax
    pushq %rax
    leaq -576(%rbp), %rax
    pushq %rax
    leaq -448(%rbp), %rax
    pushq %rax
    leaq -512(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sc_mul_add
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -224(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_copy
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -320(%rbp), %rax
    pushq %rax
    leaq -640(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fe_tobytes
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -320(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_copy
    movq %r12, %rsp
    popq %r12
    leave
    ret
    .globl sign_read
sign_read:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr1(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fopen
    movq %r12, %rsp
    popq %r12
    movq %rax, -48(%rbp)
    movq $0, %rax
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -80(%rbp)
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L438
    movq $0, %rax
    leave
    ret
.L438:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fseek
    movq %r12, %rsp
    popq %r12
    movq -32(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call ftell
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call fseek
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
    testq %rax, %rax
    jne .L442
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $16777216, %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L442
    xorl %eax, %eax
    jmp .L443
.L442:
    movl $1, %eax
.L443:
    cmpq $0, %rax
    je .L444
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fclose
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L444:
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L446
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L446:
    leaq -80(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call malloc
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L448
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fclose
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L448:
    leaq -64(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq -32(%rbp), %rax
    movq (%rax), %rax
    pushq %rax
    movq -48(%rbp), %rax
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
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
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
    je .L450
    movq $0, %rax
    leave
    ret
.L450:
    movq -80(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl sign_write
sign_write:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq .Lstr3(%rip), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call fopen
    movq %r12, %rsp
    popq %r12
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -80(%rbp)
    movq -64(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L456
    movq $1, %rax
    leave
    ret
.L456:
    leaq -80(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call fwrite
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -64(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call fclose
    movq %r12, %rsp
    popq %r12
    movq -80(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L458
    movq $1, %rax
    leave
    ret
.L458:
    movq $0, %rax
    leave
    ret
    leave
    ret
    .globl sign_note_span
sign_note_span:
    pushq %rbp
    movq %rsp, %rbp
    subq $208, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    movq $0, %rax
    movq %rax, -80(%rbp)
.L476:
    movq -48(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L477
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le32
    movq %r12, %rsp
    popq %r12
    movq %rax, -96(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le32
    movq %r12, %rsp
    popq %r12
    movq %rax, -112(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le32
    movq %r12, %rsp
    popq %r12
    movq %rax, -128(%rbp)
    movq -48(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    movq %rax, -144(%rbp)
    movq -96(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    pushq %rax
    movq $4, %rax
    popq %rcx
    imulq %rcx, %rax
    movq %rax, -160(%rbp)
    movq $0, %rax
    movq %rax, -176(%rbp)
    movq $0, %rax
    movq %rax, -192(%rbp)
    movq -160(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -144(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L478
    movq $1, %rax
    negq %rax
    leave
    ret
.L478:
    movq -96(%rbp), %rax
    pushq %rax
    movq $7, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L480
    movq -128(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L480
    movl $1, %eax
    jmp .L481
.L480:
    xorl %eax, %eax
.L481:
    testq %rax, %rax
    je .L482
    movq -112(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L482
    movl $1, %eax
    jmp .L483
.L482:
    xorl %eax, %eax
.L483:
    cmpq $0, %rax
    je .L484
    leaq -176(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L486:
    movq -192(%rbp), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L487
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -192(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    leaq sign_note_name(%rip), %rax
    pushq %rax
    movq -192(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L488
    leaq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L488:
    leaq -192(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L486
.L487:
    movq -176(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L490
    movq -64(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $1, %rax
    leave
    ret
.L490:
.L484:
    leaq -80(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    movq %rax, %r8
    movq %rcx, %rax
    cqto
    idivq %r8
    pushq %rax
    movq $4, %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L476
.L477:
    movq $0, %rax
    leave
    ret
    leave
    ret
    .globl sign_digest_of
sign_digest_of:
    pushq %rbp
    movq %rsp, %rbp
    subq $272, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    movq %r8, -80(%rbp)
    movq %r9, -96(%rbp)
    movq $0, %rax
    movq %rax, -112(%rbp)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -128(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_sha_init
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
    call sign_feed32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $0, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_feed32
    movq %r12, %rsp
    popq %r12
.L512:
    movq -112(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L513
    movq -112(%rbp), %rax
    pushq %rax
    movq $56, %rax
    popq %rcx
    imulq %rcx, %rax
    movq %rax, -144(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -64(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le32
    movq %r12, %rsp
    popq %r12
    movq %rax, -160(%rbp)
    movq $0, %rax
    movq %rax, -176(%rbp)
    movq $0, %rax
    movq %rax, -192(%rbp)
    movq $0, %rax
    movq %rax, -208(%rbp)
    movq $0, %rax
    movq %rax, -224(%rbp)
    movq $0, %rax
    movq %rax, -240(%rbp)
    movq $0, %rax
    movq %rax, -256(%rbp)
    movq -160(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L514
    leaq -112(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L512
.L514:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -64(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -176(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_offok
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L516
    movq $1, %rax
    leave
    ret
.L516:
    leaq -208(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -64(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $16, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le32
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -224(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -64(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le32
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -64(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_offok
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L518
    movq $1, %rax
    leave
    ret
.L518:
    movq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L520
    movq -192(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L520
    xorl %eax, %eax
    jmp .L521
.L520:
    movl $1, %eax
.L521:
    testq %rax, %rax
    jne .L522
    movq -176(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L522
    xorl %eax, %eax
    jmp .L523
.L522:
    movl $1, %eax
.L523:
    testq %rax, %rax
    jne .L524
    movq -176(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L524
    xorl %eax, %eax
    jmp .L525
.L524:
    movl $1, %eax
.L525:
    cmpq $0, %rax
    je .L526
    movq $1, %rax
    leave
    ret
.L526:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -208(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_feed32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $0, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_feed32
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
    call sign_feed32
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
    call sign_feed32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq $0, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_feed32
    movq %r12, %rsp
    popq %r12
    leaq -240(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -240(%rbp), %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L528
    leaq -240(%rbp), %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    movq %rax, (%rcx)
.L528:
    leaq -256(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq -240(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L530
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -240(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -256(%rbp), %rax
    pushq %rax
    movq -240(%rbp), %rax
    popq %rcx
    subq %rax, %rcx
    movq %rcx, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_sha_update
    movq %r12, %rsp
    popq %r12
.L530:
    leaq -112(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L512
.L513:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -96(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_sha_final
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
    leave
    ret
    .globl sign_patch_notes
sign_patch_notes:
    pushq %rbp
    movq %rsp, %rbp
    subq $240, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    movq %r8, -80(%rbp)
    movq $0, %rax
    movq %rax, -96(%rbp)
    movq $0, %rax
    movq %rax, -112(%rbp)
.L552:
    movq -96(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L553
    movq -96(%rbp), %rax
    pushq %rax
    movq $56, %rax
    popq %rcx
    imulq %rcx, %rax
    movq %rax, -128(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le32
    movq %r12, %rsp
    popq %r12
    movq %rax, -144(%rbp)
    movq $0, %rax
    movq %rax, -160(%rbp)
    movq $0, %rax
    movq %rax, -176(%rbp)
    movq $0, %rax
    movq %rax, -192(%rbp)
    movq $0, %rax
    movq %rax, -208(%rbp)
    movq $0, %rax
    movq %rax, -224(%rbp)
    movq -144(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L554
    leaq -96(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L552
.L554:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -160(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_offok
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L556
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -48(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -176(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_offok
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L556
    xorl %eax, %eax
    jmp .L557
.L556:
    movl $1, %eax
.L557:
    cmpq $0, %rax
    je .L558
    leaq -96(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L552
.L558:
    movq -160(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L560
    movq -176(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L560
    xorl %eax, %eax
    jmp .L561
.L560:
    movl $1, %eax
.L561:
    testq %rax, %rax
    jne .L562
    movq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L562
    xorl %eax, %eax
    jmp .L563
.L562:
    movl $1, %eax
.L563:
    cmpq $0, %rax
    je .L564
    leaq -96(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L552
.L564:
    leaq -208(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 24(%rsp), %rdi
    movq 16(%rsp), %rsi
    movq 8(%rsp), %rdx
    movq 0(%rsp), %rcx
    xorl %eax, %eax
    call sign_note_span
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -208(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L566
    movq -16(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L566
    movl $1, %eax
    jmp .L567
.L566:
    xorl %eax, %eax
.L567:
    cmpq $0, %rax
    je .L568
.L570:
    movq -224(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L571
    movq -16(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -224(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L570
.L571:
    leaq -112(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    movq %rax, (%rcx)
.L568:
    leaq -96(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L552
.L553:
    movq -112(%rbp), %rax
    leave
    ret
    leave
    ret
    .globl sign_append
sign_append:
    pushq %rbp
    movq %rsp, %rbp
    subq $368, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq %rdx, -48(%rbp)
    movq %rcx, -64(%rbp)
    movq %r8, -80(%rbp)
    movq %r9, -96(%rbp)
    movq $0, %rax
    movq %rax, -112(%rbp)
    movq $0, %rax
    movq %rax, -128(%rbp)
    movq -64(%rbp), %rax
    pushq %rax
    movq 16(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -144(%rbp)
    movq $0, %rax
    movq %rax, -160(%rbp)
    movq $0, %rax
    movq %rax, -176(%rbp)
    movq -48(%rbp), %rax
    movq %rax, -192(%rbp)
    movq $0, %rax
    movq %rax, -208(%rbp)
    movq $0, %rax
    movq %rax, -224(%rbp)
    movq $0, %rax
    movq %rax, -240(%rbp)
    movq $0, %rax
    movq %rax, -256(%rbp)
    movq $0, %rax
    movq %rax, -272(%rbp)
    movq $0, %rax
    movq %rax, -288(%rbp)
    movq $0, %rax
    movq %rax, -304(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $24, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -112(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_offok
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L618
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq -144(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -128(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_offok
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L618
    xorl %eax, %eax
    jmp .L619
.L618:
    movl $1, %eax
.L619:
    testq %rax, %rax
    jne .L620
    movq -112(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L620
    xorl %eax, %eax
    jmp .L621
.L620:
    movl $1, %eax
.L621:
    testq %rax, %rax
    jne .L622
    movq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L622
    xorl %eax, %eax
    jmp .L623
.L622:
    movl $1, %eax
.L623:
    testq %rax, %rax
    jne .L624
    movq -112(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L624
    xorl %eax, %eax
    jmp .L625
.L624:
    movl $1, %eax
.L625:
    cmpq $0, %rax
    je .L626
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr9(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L626:
    leaq -160(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq sign_section_name(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_strlen
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -176(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    movq %rax, (%rcx)
.L628:
    movq -192(%rbp), %rax
    pushq %rax
    movq $8, %rax
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
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L629
    leaq -192(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L628
.L629:
    leaq -208(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $88, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L630:
    movq -208(%rbp), %rax
    pushq %rax
    movq $8, %rax
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
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L631
    leaq -208(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L630
.L631:
    leaq -224(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L632:
    movq -224(%rbp), %rax
    pushq %rax
    movq $8, %rax
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
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L633
    leaq -224(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L632
.L633:
    leaq -240(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -256(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -240(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call malloc
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
    je .L634
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr10(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L634:
.L636:
    movq -288(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L637
    movq -256(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -288(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L636
.L637:
.L638:
    movq -288(%rbp), %rax
    pushq %rax
    movq -240(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L639
    movq -256(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -288(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L638
.L639:
    leaq -272(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -128(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call malloc
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -272(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L640
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr11(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L640:
    leaq -288(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L642:
    movq -288(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L643
    movq -272(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -288(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L642
.L643:
    leaq -304(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L644:
    movq -304(%rbp), %rax
    pushq %rax
    movq $88, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L645
    movq -256(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L644
.L645:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $7, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $65, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    leaq -304(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L646:
    movq -304(%rbp), %rax
    pushq %rax
    movq $6, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L647
    movq -256(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $12, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq sign_note_name(%rip), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L646
.L647:
    leaq -304(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L648:
    movq -304(%rbp), %rax
    pushq %rax
    movq $65, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L649
    movq -256(%rbp), %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq $20, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 24(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L648
.L649:
    leaq -304(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L650:
    movq -304(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L651
    movq -256(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -272(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L650
.L651:
    leaq -304(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L652:
    movq -304(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L653
    movq -256(%rbp), %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq sign_section_name(%rip), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L652
.L653:
    leaq -288(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L654:
    movq -288(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L655
    movq -64(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -320(%rbp)
    leaq -304(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L656:
    movq -304(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L657
    movq -256(%rbp), %rax
    pushq %rax
    movq -224(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -304(%rbp), %rax
    pushq %rax
    movq -304(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L656
.L657:
    leaq -288(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L654
.L655:
    movq -224(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -320(%rbp)
    movq $0, %rax
    movq %rax, -336(%rbp)
.L658:
    movq -336(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L659
    movq -256(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq -336(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -336(%rbp), %rax
    pushq %rax
    movq -336(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L658
.L659:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq -176(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq $4, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $7, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq $24, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -192(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $88, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq $52, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    movq -64(%rbp), %rax
    pushq %rax
    movq 16(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -320(%rbp)
    movq -224(%rbp), %rax
    pushq %rax
    movq 16(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -336(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -336(%rbp), %rax
    pushq %rax
    movq $24, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -208(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -256(%rbp), %rax
    pushq %rax
    movq -336(%rbp), %rax
    pushq %rax
    movq $32, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq -160(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_put32
    movq %r12, %rsp
    popq %r12
    leaq -320(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    movq $0, %rax
    movq %rax, -320(%rbp)
    movq -224(%rbp), %rax
    movq %rax, -336(%rbp)
.L660:
    movq -320(%rbp), %rax
    pushq %rax
    movq $8, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L661
    movq -256(%rbp), %rax
    pushq %rax
    movq $40, %rax
    pushq %rax
    movq -320(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -336(%rbp), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -336(%rbp), %rax
    pushq %rax
    movq -336(%rbp), %rax
    pushq %rax
    movq $8, %rax
    pushq %rax
    popq %rcx
    popq %rax
    sarq %cl, %rax
    popq %rcx
    movq %rax, (%rcx)
    leaq -320(%rbp), %rax
    pushq %rax
    movq -320(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L660
.L661:
    movq -80(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movq %rax, -352(%rbp)
    movq -256(%rbp), %rax
    pushq %rax
    movq $60, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -352(%rbp), %rax
    pushq %rax
    movq $255, %rax
    popq %rcx
    andq %rcx, %rax
    popq %rcx
    movb %al, (%rcx)
    movq -256(%rbp), %rax
    pushq %rax
    movq $61, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -352(%rbp), %rax
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
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -256(%rbp), %rax
    pushq %rax
    movq -240(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_write
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L662
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr12(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L662:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr13(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
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
    .globl sign_file
sign_file:
    pushq %rbp
    movq %rsp, %rbp
    subq $432, %rsp
    movq %rdi, -16(%rbp)
    movq $0, %rax
    movq %rax, -32(%rbp)
    movq $0, %rax
    movq %rax, -48(%rbp)
    movq $0, %rax
    movq %rax, -64(%rbp)
    movq $0, %rax
    movq %rax, -80(%rbp)
    movq $0, %rax
    movq %rax, -96(%rbp)
    movq $0, %rax
    movq %rax, -112(%rbp)
    movq $0, %rax
    movq %rax, -128(%rbp)
    movq $0, %rax
    movq %rax, -352(%rbp)
    leaq -32(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    leaq -48(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_read
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L724
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr27(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L724:
    movq -48(%rbp), %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L726
    movq -32(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $127, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L726
    xorl %eax, %eax
    jmp .L727
.L726:
    movl $1, %eax
.L727:
    testq %rax, %rax
    jne .L728
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $69, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L728
    xorl %eax, %eax
    jmp .L729
.L728:
    movl $1, %eax
.L729:
    testq %rax, %rax
    jne .L730
    movq -32(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $76, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L730
    xorl %eax, %eax
    jmp .L731
.L730:
    movl $1, %eax
.L731:
    testq %rax, %rax
    jne .L732
    movq -32(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    pushq %rax
    movq $70, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L732
    xorl %eax, %eax
    jmp .L733
.L732:
    movl $1, %eax
.L733:
    cmpq $0, %rax
    je .L734
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr28(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L734:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $16, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le16
    movq %r12, %rsp
    popq %r12
    movq %rax, -368(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $18, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le16
    movq %r12, %rsp
    popq %r12
    movq %rax, -384(%rbp)
    movq -384(%rbp), %rax
    pushq %rax
    movq $62, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L736
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr29(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L736:
    movq -368(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L738
    movq -368(%rbp), %rax
    pushq %rax
    movq $3, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L738
    movl $1, %eax
    jmp .L739
.L738:
    xorl %eax, %eax
.L739:
    cmpq $0, %rax
    je .L740
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr30(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
.L740:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $24, %rax
    pushq %rax
    leaq -64(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_offok
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L742
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr31(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L742:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $32, %rax
    pushq %rax
    leaq -80(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_offok
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L744
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr32(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L744:
    leaq -112(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $54, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le16
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -96(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $56, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le16
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -112(%rbp), %rax
    pushq %rax
    movq $56, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L746
    movq -80(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L746
    xorl %eax, %eax
    jmp .L747
.L746:
    movl $1, %eax
.L747:
    testq %rax, %rax
    jne .L748
    movq -96(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L748
    xorl %eax, %eax
    jmp .L749
.L748:
    movl $1, %eax
.L749:
    testq %rax, %rax
    jne .L750
    movq -80(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L750
    xorl %eax, %eax
    jmp .L751
.L750:
    movl $1, %eax
.L751:
    testq %rax, %rax
    jne .L752
    movq -80(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -80(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L752
    xorl %eax, %eax
    jmp .L753
.L752:
    movl $1, %eax
.L753:
    cmpq $0, %rax
    je .L754
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr33(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L754:
    leaq -128(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -96(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call malloc
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -128(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L756
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr34(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L756:
    leaq -352(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L758:
    movq -352(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    movq -112(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L759
    movq -128(%rbp), %rax
    pushq %rax
    movq -352(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    pushq %rax
    movq -352(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -352(%rbp), %rax
    pushq %rax
    movq -352(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L758
.L759:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 40(%rsp), %rdi
    movq 32(%rsp), %rsi
    movq 24(%rsp), %rdx
    movq 16(%rsp), %rcx
    movq 8(%rsp), %r8
    movq 0(%rsp), %r9
    xorl %eax, %eax
    call sign_digest_of
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L760
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr35(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L760:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -256(%rbp), %rax
    pushq %rax
    leaq -192(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_digest
    movq %r12, %rsp
    popq %r12
    leaq -336(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -352(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movq %rax, (%rcx)
.L762:
    movq -352(%rbp), %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L763
    leaq -336(%rbp), %rax
    pushq %rax
    movq $1, %rax
    pushq %rax
    movq -352(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    leaq -256(%rbp), %rax
    pushq %rax
    movq -352(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    movsbq (%rax), %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -352(%rbp), %rax
    pushq %rax
    movq -352(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L762
.L763:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -128(%rbp), %rax
    pushq %rax
    movq -96(%rbp), %rax
    pushq %rax
    leaq -336(%rbp), %rax
    pushq %rax
    movq 32(%rsp), %rdi
    movq 24(%rsp), %rsi
    movq 16(%rsp), %rdx
    movq 8(%rsp), %rcx
    movq 0(%rsp), %r8
    xorl %eax, %eax
    call sign_patch_notes
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $1, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L764
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_write
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L766
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr36(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L766:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr37(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $0, %rax
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
.L764:
    movq $0, %rax
    movq %rax, -368(%rbp)
    movq $0, %rax
    movq %rax, -384(%rbp)
    movq $0, %rax
    movq %rax, -400(%rbp)
    movq $0, %rax
    movq %rax, -416(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $40, %rax
    pushq %rax
    leaq -368(%rbp), %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_offok
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    sete %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L768
    movq -368(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L768
    xorl %eax, %eax
    jmp .L769
.L768:
    movl $1, %eax
.L769:
    cmpq $0, %rax
    je .L770
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr38(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L770:
    leaq -400(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $58, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le16
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -384(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $60, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le16
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    leaq -416(%rbp), %rax
    pushq %rax
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq $62, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_le16
    movq %r12, %rsp
    popq %r12
    popq %rcx
    movq %rax, (%rcx)
    movq -400(%rbp), %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L772
    movq -384(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setle %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L772
    xorl %eax, %eax
    jmp .L773
.L772:
    movl $1, %eax
.L773:
    testq %rax, %rax
    jne .L774
    movq -416(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L774
    xorl %eax, %eax
    jmp .L775
.L774:
    movl $1, %eax
.L775:
    testq %rax, %rax
    jne .L776
    movq -416(%rbp), %rax
    pushq %rax
    movq -384(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L776
    xorl %eax, %eax
    jmp .L777
.L776:
    movl $1, %eax
.L777:
    testq %rax, %rax
    jne .L778
    movq -368(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L778
    xorl %eax, %eax
    jmp .L779
.L778:
    movl $1, %eax
.L779:
    testq %rax, %rax
    jne .L780
    movq -368(%rbp), %rax
    pushq %rax
    movq -384(%rbp), %rax
    pushq %rax
    movq -400(%rbp), %rax
    popq %rcx
    imulq %rcx, %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setg %al
    movzbq %al, %rax
    testq %rax, %rax
    jne .L780
    xorl %eax, %eax
    jmp .L781
.L780:
    movl $1, %eax
.L781:
    cmpq $0, %rax
    je .L782
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr39(%rip), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L782:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    movq -16(%rbp), %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -368(%rbp), %rax
    pushq %rax
    movq -384(%rbp), %rax
    pushq %rax
    movq -400(%rbp), %rax
    pushq %rax
    movq -416(%rbp), %rax
    pushq %rax
    leaq -336(%rbp), %rax
    pushq %rax
    movq 56(%rsp), %rdi
    movq 48(%rsp), %rsi
    movq 40(%rsp), %rdx
    movq 32(%rsp), %rcx
    movq 24(%rsp), %r8
    movq 16(%rsp), %r9
    movq 0(%rsp), %r10
    movq 8(%rsp), %rax
    movq %rax, 0(%rsp)
    movq %r10, 8(%rsp)
    xorl %eax, %eax
    call sign_append
    movq %r12, %rsp
    popq %r12
    leave
    ret
    leave
    ret
    .globl sign_selftest
sign_selftest:
    pushq %rbp
    movq %rsp, %rbp
    subq $304, %rsp
    movq $0, %rax
    movq %rax, -288(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_sha_init
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr43(%rip), %rax
    pushq %rax
    movq $3, %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_sha_update
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -208(%rbp), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_sha_final
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -144(%rbp), %rax
    pushq %rax
    leaq -208(%rbp), %rax
    pushq %rax
    movq $64, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_hexout
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr44(%rip), %rax
    pushq %rax
    leaq -144(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
.L786:
    movq -288(%rbp), %rax
    pushq %rax
    movq $64, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L787
    leaq -208(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    popq %rcx
    addq %rcx, %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    movb %al, (%rcx)
    leaq -288(%rbp), %rax
    pushq %rax
    movq -288(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L786
.L787:
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq -272(%rbp), %rax
    pushq %rax
    leaq -208(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call sign_digest
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq -144(%rbp), %rax
    pushq %rax
    leaq -272(%rbp), %rax
    pushq %rax
    movq $64, %rax
    pushq %rax
    movq 16(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 0(%rsp), %rdx
    xorl %eax, %eax
    call sign_hexout
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    leaq .Lstr45(%rip), %rax
    pushq %rax
    leaq -144(%rbp), %rax
    pushq %rax
    movq 8(%rsp), %rdi
    movq 0(%rsp), %rsi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $0, %rax
    leave
    ret
    leave
    ret
    .globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp
    movq %rdi, -16(%rbp)
    movq %rsi, -32(%rbp)
    movq $0, %rax
    movq %rax, -48(%rbp)
    movq $1, %rax
    movq %rax, -64(%rbp)
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_key_init
    movq %r12, %rsp
    popq %r12
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_points_init
    movq %r12, %rsp
    popq %r12
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    setge %al
    movzbq %al, %rax
    testq %rax, %rax
    je .L800
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
    leaq .Lstr48(%rip), %rax
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
    je .L800
    movl $1, %eax
    jmp .L801
.L800:
    xorl %eax, %eax
.L801:
    cmpq $0, %rax
    je .L802
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    xorl %eax, %eax
    call sign_selftest
    movq %r12, %rsp
    popq %r12
    leave
    ret
.L802:
    movq -16(%rbp), %rax
    pushq %rax
    movq $2, %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L804
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    leaq .Lstr49(%rip), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call printf
    movq %r12, %rsp
    popq %r12
    movq $1, %rax
    leave
    ret
.L804:
.L806:
    movq -64(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    popq %rcx
    cmpq %rax, %rcx
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L807
    pushq %r12
    movq %rsp, %r12
    andq $-16, %rsp
    subq $8, %rsp
    movq -32(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    popq %rcx
    imulq $8, %rax
    addq %rcx, %rax
    movq (%rax), %rax
    pushq %rax
    movq 0(%rsp), %rdi
    xorl %eax, %eax
    call sign_file
    movq %r12, %rsp
    popq %r12
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L808
    leaq -48(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
.L808:
    leaq -64(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    pushq %rax
    movq $1, %rax
    popq %rcx
    addq %rcx, %rax
    popq %rcx
    movq %rax, (%rcx)
    jmp .L806
.L807:
    movq -48(%rbp), %rax
    pushq %rax
    movq $0, %rax
    popq %rcx
    cmpq %rax, %rcx
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .L810
    movq $1, %rax
    leave
    ret
.L810:
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
    .asciz "w"
.Lstr3:
    .asciz "w"
.Lstr4:
    .asciz "sign: %s: bad string table\n"
.Lstr5:
    .asciz "sign: out of memory\n"
.Lstr6:
    .asciz "sign: out of memory\n"
.Lstr7:
    .asciz "sign: cannot write %s\n"
.Lstr8:
    .asciz "sign: %s: signed (key %d)\n"
.Lstr9:
    .asciz "sign: %s: bad string table\n"
.Lstr10:
    .asciz "sign: out of memory\n"
.Lstr11:
    .asciz "sign: out of memory\n"
.Lstr12:
    .asciz "sign: cannot write %s\n"
.Lstr13:
    .asciz "sign: %s: signed (key %d)\n"
.Lstr14:
    .asciz "sign: cannot read %s\n"
.Lstr15:
    .asciz "sign: %s: not an ELF image, skipped\n"
.Lstr16:
    .asciz "sign: %s: not x86-64, skipped\n"
.Lstr17:
    .asciz "sign: %s: not an executable, skipped\n"
.Lstr18:
    .asciz "sign: %s: bad entry\n"
.Lstr19:
    .asciz "sign: %s: bad phoff\n"
.Lstr20:
    .asciz "sign: %s: bad program headers\n"
.Lstr21:
    .asciz "sign: out of memory\n"
.Lstr22:
    .asciz "sign: %s: digest failed\n"
.Lstr23:
    .asciz "sign: cannot write %s\n"
.Lstr24:
    .asciz "sign: %s: signed (key %d)\n"
.Lstr25:
    .asciz "sign: %s: no section table to extend\n"
.Lstr26:
    .asciz "sign: %s: no section table to extend\n"
.Lstr27:
    .asciz "sign: cannot read %s\n"
.Lstr28:
    .asciz "sign: %s: not an ELF image, skipped\n"
.Lstr29:
    .asciz "sign: %s: not x86-64, skipped\n"
.Lstr30:
    .asciz "sign: %s: not an executable, skipped\n"
.Lstr31:
    .asciz "sign: %s: bad entry\n"
.Lstr32:
    .asciz "sign: %s: bad phoff\n"
.Lstr33:
    .asciz "sign: %s: bad program headers\n"
.Lstr34:
    .asciz "sign: out of memory\n"
.Lstr35:
    .asciz "sign: %s: digest failed\n"
.Lstr36:
    .asciz "sign: cannot write %s\n"
.Lstr37:
    .asciz "sign: %s: signed (key %d)\n"
.Lstr38:
    .asciz "sign: %s: no section table to extend\n"
.Lstr39:
    .asciz "sign: %s: no section table to extend\n"
.Lstr40:
    .asciz "abc"
.Lstr41:
    .asciz "SHA-ABC %s\n"
.Lstr42:
    .asciz "SIG-ZERO %s\n"
.Lstr43:
    .asciz "abc"
.Lstr44:
    .asciz "SHA-ABC %s\n"
.Lstr45:
    .asciz "SIG-ZERO %s\n"
.Lstr46:
    .asciz "--selftest"
.Lstr47:
    .asciz "usage: sign <file> [...]\n"
.Lstr48:
    .asciz "--selftest"
.Lstr49:
    .asciz "usage: sign <file> [...]\n"
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
