#include "kernel.h"
#include "vga_fb.h"

/* ================================================================
 *  ELF loader + VMA tree
 *
 *  Two loaders:
 *    elf_load       — ET_REL relocatable .o objects (ring-0 toolchain)
 *    load_exec_elf  — ET_EXEC / ET_DYN Linux binaries (ring-3)
 *
 *  The VMA red-black tree tracks mmap/brk regions for ring-3
 *  programs.  Two trees: vma_live for active allocations,
 *  vma_free for reclaimed regions.  All entries are page-aligned.
 * ================================================================ */

/* ELF64 types shared with kernel.h: EI_NIDENT, Elf64_{Addr,Off,Word,Half,
 * Xword,Sxword,Ehdr}, ET_{REL,EXEC,DYN}.  Types local to the loader: */

typedef struct {
    Elf64_Word  sh_name;
    Elf64_Word  sh_type;
    Elf64_Xword sh_flags;
    Elf64_Addr  sh_addr;
    Elf64_Off   sh_offset;
    Elf64_Xword sh_size;
    Elf64_Word  sh_link;
    Elf64_Word  sh_info;
    Elf64_Xword sh_addralign;
    Elf64_Xword sh_entsize;
} Elf64_Shdr;

typedef struct {
    Elf64_Word  st_name;
    unsigned char st_info;
    unsigned char st_other;
    Elf64_Half  st_shndx;
    Elf64_Addr  st_value;
    Elf64_Xword st_size;
} Elf64_Sym;

typedef struct {
    Elf64_Addr   r_offset;
    Elf64_Xword  r_info;
    Elf64_Sxword r_addend;
} Elf64_Rela;

typedef struct {
    Elf64_Word  p_type;
    Elf64_Word  p_flags;
    Elf64_Off   p_offset;
    Elf64_Addr  p_vaddr;
    Elf64_Addr  p_paddr;
    Elf64_Xword p_filesz;
    Elf64_Xword p_memsz;
    Elf64_Xword p_align;
} Elf64_Phdr;

#define ELF64_R_SYM(i)    ((i) >> 32)
#define ELF64_R_TYPE(i)   ((i) & 0xffffffff)
#define SHN_UNDEF         0

#define SHT_SYMTAB  2
#define SHT_STRTAB  3
#define SHT_RELA    4
#define SHT_PROGBITS 1
#define SHT_NOBITS  8
#define SHF_ALLOC   2
#define SHF_EXECINSTR 4

#define EM_X86_64  62
#define PT_LOAD     1

#define R_X86_64_64        1
#define R_X86_64_PC32      2
#define R_X86_64_PLT32     4
#define R_X86_64_GLOB_DAT  6
#define R_X86_64_JUMP_SLOT 7
#define R_X86_64_RELATIVE  8
#define R_X86_64_32       10
#define R_X86_64_32S      11
#define R_X86_64_IRELATIVE 37

#define PF_X               1
#define ELF_MAX_SEGMENTS   64
#define ELF_NAME_MAX       64

struct exec_range { unsigned long start, end; };

/* ---- Globals shared with kernel.c (syscall dispatcher, brk/mmap) ---- */

unsigned long g_brk;         /* current program break         */
unsigned long g_brk_limit;   /* upper bound for brk growth    */
unsigned long user_mmap_cur; /* anonymous mmap cursor, grows down */

/* ---- VMA red-black tree ---- */

#define VMA_MAX 4096

vma_node_t vma_pool[VMA_MAX];
int vma_pool_n;

static vma_node_t vma_nil_store;
vma_node_t *VMA_NIL;

vma_node_t *vma_live_root;
vma_node_t *vma_free_root;

void vma_tree_init(void) {
    VMA_NIL = &vma_nil_store;
    VMA_NIL->red = 0;
    VMA_NIL->left = VMA_NIL->right = VMA_NIL->parent = VMA_NIL;
    VMA_NIL->base = 0;
    VMA_NIL->len = 0;
    vma_live_root = VMA_NIL;
    vma_free_root = VMA_NIL;
    vma_pool_n = 0;
}

static vma_node_t *vma_alloc_node(void) {
    if (vma_pool_n >= VMA_MAX) return VMA_NIL;
    return &vma_pool[vma_pool_n++];
}

static void vma_rotate_left(vma_node_t **root, vma_node_t *x) {
    vma_node_t *y = x->right;
    x->right = y->left;
    if (y->left != VMA_NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == VMA_NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

static void vma_rotate_right(vma_node_t **root, vma_node_t *x) {
    vma_node_t *y = x->left;
    x->left = y->right;
    if (y->right != VMA_NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == VMA_NIL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

static void vma_insert_fixup(vma_node_t **root, vma_node_t *z) {
    while (z->parent->red) {
        if (z->parent == z->parent->parent->left) {
            vma_node_t *y = z->parent->parent->right;
            if (y->red) {
                z->parent->red = 0;
                y->red = 0;
                z->parent->parent->red = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    vma_rotate_left(root, z);
                }
                z->parent->red = 0;
                z->parent->parent->red = 1;
                vma_rotate_right(root, z->parent->parent);
            }
        } else {
            vma_node_t *y = z->parent->parent->left;
            if (y->red) {
                z->parent->red = 0;
                y->red = 0;
                z->parent->parent->red = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    vma_rotate_right(root, z);
                }
                z->parent->red = 0;
                z->parent->parent->red = 1;
                vma_rotate_left(root, z->parent->parent);
            }
        }
    }
    (*root)->red = 0;
}

vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len) {
    vma_node_t *z = vma_alloc_node();
    if (z == VMA_NIL) return VMA_NIL;
    z->base = base;
    z->len = len;
    z->left = z->right = z->parent = VMA_NIL;
    z->red = 1;

    vma_node_t *y = VMA_NIL;
    vma_node_t *x = *root;
    while (x != VMA_NIL) {
        y = x;
        if (z->base < x->base) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == VMA_NIL) *root = z;
    else if (z->base < y->base) y->left = z;
    else y->right = z;
    vma_insert_fixup(root, z);
    return z;
}

vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base) {
    vma_node_t *x = root;
    while (x != VMA_NIL) {
        if (base == x->base) return x;
        else if (base < x->base) x = x->left;
        else x = x->right;
    }
    return VMA_NIL;
}

static void vma_transplant(vma_node_t **root, vma_node_t *u, vma_node_t *v) {
    if (u->parent == VMA_NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

static vma_node_t *vma_tree_minimum(vma_node_t *x) {
    while (x->left != VMA_NIL) x = x->left;
    return x;
}

static void vma_delete_fixup(vma_node_t **root, vma_node_t *x) {
    while (x != *root && !x->red) {
        if (x == x->parent->left) {
            vma_node_t *w = x->parent->right;
            if (w->red) {
                w->red = 0;
                x->parent->red = 1;
                vma_rotate_left(root, x->parent);
                w = x->parent->right;
            }
            if (!w->left->red && !w->right->red) {
                w->red = 1;
                x = x->parent;
            } else {
                if (!w->right->red) {
                    w->left->red = 0;
                    w->red = 1;
                    vma_rotate_right(root, w);
                    w = x->parent->right;
                }
                w->red = x->parent->red;
                x->parent->red = 0;
                w->right->red = 0;
                vma_rotate_left(root, x->parent);
                x = *root;
            }
        } else {
            vma_node_t *w = x->parent->left;
            if (w->red) {
                w->red = 0;
                x->parent->red = 1;
                vma_rotate_right(root, x->parent);
                w = x->parent->left;
            }
            if (!w->right->red && !w->left->red) {
                w->red = 1;
                x = x->parent;
            } else {
                if (!w->left->red) {
                    w->right->red = 0;
                    w->red = 1;
                    vma_rotate_left(root, w);
                    w = x->parent->left;
                }
                w->red = x->parent->red;
                x->parent->red = 0;
                w->left->red = 0;
                vma_rotate_right(root, x->parent);
                x = *root;
            }
        }
    }
    x->red = 0;
}

int vma_tree_delete(vma_node_t **root, unsigned long base) {
    vma_node_t *z = vma_tree_find(*root, base);
    if (z == VMA_NIL) return -1;
    vma_node_t *y = z;
    vma_node_t *x;
    int y_orig_red = y->red;
    if (z->left == VMA_NIL) {
        x = z->right;
        vma_transplant(root, z, z->right);
    } else if (z->right == VMA_NIL) {
        x = z->left;
        vma_transplant(root, z, z->left);
    } else {
        y = vma_tree_minimum(z->right);
        y_orig_red = y->red;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            vma_transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        vma_transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->red = y_orig_red;
    }
    if (!y_orig_red) vma_delete_fixup(root, x);
    return 0;
}

/* ---- ELF helper functions ---- */

static void elf_name_copy(char *out, unsigned out_cap, const char *tab,
                          Elf64_Xword tab_size, Elf64_Word off) {
    unsigned long i = 0;
    if (out_cap == 0) return;
    if (off < tab_size) {
        while (i < out_cap - 1 && off + i < tab_size) {
            out[i] = tab[off + i];
            if (out[i] == '\0') break;
            i++;
        }
    }
    out[i] = '\0';
}

static void elf_load_fail(void *base, void **sec_addrs, const char *why) {
    if (why) kprintf("load: %s\n", why);
    if (sec_addrs) kfree(sec_addrs);
    if (base) kfree(base);
}

/* ---- ET_REL loader (ring-0 toolchain objects) ---- */

void *elf_load(void *data, unsigned size) {
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)data;

    if (size < sizeof(Elf64_Ehdr)) return 0;
    if (ehdr->e_ident[0] != 0x7F || ehdr->e_ident[1] != 'E' ||
        ehdr->e_ident[2] != 'L'  || ehdr->e_ident[3] != 'F')
        return 0;
    if (ehdr->e_type != ET_REL)   return 0;
    if (ehdr->e_machine != EM_X86_64) return 0;

    if (ehdr->e_shentsize < sizeof(Elf64_Shdr)) return 0;
    if (ehdr->e_shoff > size ||
        (Elf64_Xword)ehdr->e_shnum * ehdr->e_shentsize > size - ehdr->e_shoff)
        return 0;
    if (ehdr->e_shstrndx >= ehdr->e_shnum) return 0;

    Elf64_Shdr *shdrs = (Elf64_Shdr *)((char *)data + ehdr->e_shoff);
    Elf64_Half  shnum = ehdr->e_shnum;

    Elf64_Shdr *shstr = &shdrs[ehdr->e_shstrndx];
    if (shstr->sh_offset > size || shstr->sh_size > size - shstr->sh_offset)
        return 0;
    const char *shstrtab = (const char *)data + shstr->sh_offset;
    char        secname[ELF_NAME_MAX];

    Elf64_Sym  *symtab = 0;
    unsigned    symcount = 0;
    const char *strtab = 0;
    Elf64_Xword strtab_size = 0;

    unsigned total_alloc = 0;
    unsigned i;
    for (i = 0; i < shnum; i++) {
        elf_name_copy(secname, sizeof(secname), shstrtab, shstr->sh_size,
                      shdrs[i].sh_name);
        if (kstrcmp(secname, ".symtab") == 0) {
            if (shdrs[i].sh_offset > size ||
                shdrs[i].sh_size > size - shdrs[i].sh_offset)
                return 0;
            symtab = (Elf64_Sym *)((char *)data + shdrs[i].sh_offset);
            symcount = (unsigned)(shdrs[i].sh_size / sizeof(Elf64_Sym));
        }
        if (kstrcmp(secname, ".strtab") == 0) {
            if (shdrs[i].sh_offset > size ||
                shdrs[i].sh_size > size - shdrs[i].sh_offset)
                return 0;
            strtab = (const char *)data + shdrs[i].sh_offset;
            strtab_size = shdrs[i].sh_size;
        }
        if (shdrs[i].sh_flags & SHF_ALLOC) {
            if (shdrs[i].sh_size >
                (Elf64_Xword)0xFFFFFFFFu - 32 - (Elf64_Xword)total_alloc)
                return 0;
            total_alloc += (unsigned)shdrs[i].sh_size + 32;
        }
    }
    if (!symtab || !strtab) {
        kprintf("load: object has no symbol table\n");
        return 0;
    }

    char *base = kmalloc(total_alloc);
    if (!base) {
        kprintf("load: cannot allocate %u bytes for the image\n", total_alloc);
        return 0;
    }
    kmemset(base, 0, total_alloc);

    void **sec_addrs = kmalloc(shnum * sizeof(void *));
    if (!sec_addrs) { kfree(base); return 0; }
    for (i = 0; i < shnum; i++) sec_addrs[i] = 0;

    unsigned off = 0;
    for (i = 0; i < shnum; i++) {
        if (!(shdrs[i].sh_flags & SHF_ALLOC)) continue;
        sec_addrs[i] = base + off;
        Elf64_Xword ssize = shdrs[i].sh_size;
        if (shdrs[i].sh_type == SHT_PROGBITS && ssize > 0) {
            if (shdrs[i].sh_offset > size ||
                ssize > size - shdrs[i].sh_offset) {
                elf_load_fail(base, sec_addrs, 0);
                return 0;
            }
            kmemcpy(sec_addrs[i], (char *)data + shdrs[i].sh_offset, (unsigned long)ssize);
        }
        off += (unsigned)ssize + 16;
        off = (off + 15) & ~15U;
    }

    for (i = 0; i < shnum; i++) {
        if (shdrs[i].sh_type != SHT_RELA) continue;
        if (shdrs[i].sh_offset > size ||
            shdrs[i].sh_size > size - shdrs[i].sh_offset) {
            elf_load_fail(base, sec_addrs, 0);
            return 0;
        }

        unsigned target_sec = shdrs[i].sh_info;
        if (target_sec >= shnum) continue;
        char *target_base = (char *)sec_addrs[target_sec];
        if (!target_base) continue;
        Elf64_Xword target_size = shdrs[target_sec].sh_size;

        unsigned symsec = shdrs[i].sh_link;
        if (symsec >= shnum) { elf_load_fail(base, sec_addrs, "bad symtab link"); return 0; }
        if (shdrs[symsec].sh_offset > size ||
            shdrs[symsec].sh_size > size - shdrs[symsec].sh_offset) {
            elf_load_fail(base, sec_addrs, 0);
            return 0;
        }
        Elf64_Sym *rela_symtab = (Elf64_Sym *)((char *)data + shdrs[symsec].sh_offset);
        unsigned   rela_symcount = (unsigned)(shdrs[symsec].sh_size / sizeof(Elf64_Sym));

        Elf64_Rela *relas = (Elf64_Rela *)((char *)data + shdrs[i].sh_offset);
        unsigned    rcount = (unsigned)(shdrs[i].sh_size / sizeof(Elf64_Rela));
        unsigned j;
        for (j = 0; j < rcount; j++) {
            Elf64_Word   sym_idx = ELF64_R_SYM(relas[j].r_info);
            unsigned     rtype   = ELF64_R_TYPE(relas[j].r_info);
            Elf64_Addr   S = 0;
            unsigned     width;

            if (sym_idx >= rela_symcount) {
                elf_load_fail(base, sec_addrs, "relocation symbol out of range");
                return 0;
            }
            Elf64_Sym *sym = &rela_symtab[sym_idx];

            switch (rtype) {
            case R_X86_64_64:   width = 8; break;
            case R_X86_64_PC32:
            case R_X86_64_PLT32:
            case R_X86_64_32:
            case R_X86_64_32S:  width = 4; break;
            default:
                kprintf("load: unsupported relocation type %u\n", rtype);
                elf_load_fail(base, sec_addrs, 0);
                return 0;
            }
            if (relas[j].r_offset > target_size ||
                width > target_size - relas[j].r_offset) {
                elf_load_fail(base, sec_addrs, "relocation outside section");
                return 0;
            }

            if (sym->st_shndx != SHN_UNDEF && sym->st_shndx < shnum) {
                if (sec_addrs[sym->st_shndx]) {
                    S = (Elf64_Addr)(unsigned long)sec_addrs[sym->st_shndx] + sym->st_value;
                } else {
                    S = (Elf64_Addr)((char *)data + shdrs[sym->st_shndx].sh_offset + sym->st_value);
                }
            } else {
                char symname[ELF_NAME_MAX];
                elf_name_copy(symname, sizeof(symname), strtab, strtab_size,
                              sym->st_name);
                void *addr = ksym_resolve(symname);
                if (!addr && symname[0] == '_') addr = ksym_resolve(symname + 1);
                if (!addr) {
                    kprintf("load: undefined symbol '%s'\n", symname);
                    elf_load_fail(base, sec_addrs, 0);
                    return 0;
                }
                S = (Elf64_Addr)(unsigned long)addr;
            }
            S += relas[j].r_addend;

            Elf64_Addr *P = (Elf64_Addr *)(target_base + relas[j].r_offset);

            if (S < 0x1000) {
                char rname[ELF_NAME_MAX];
                elf_name_copy(rname, sizeof(rname), strtab, strtab_size, sym->st_name);
                kprintf("rel[%u] t=%u '%s' S=%lx P=%lx addend=%ld\n",
                        j, rtype, rname, (unsigned long)S,
                        (unsigned long)P, (long)relas[j].r_addend);
            }

            switch (rtype) {
            case R_X86_64_64:
                *P = S;
                break;
            case R_X86_64_PC32:
            case R_X86_64_PLT32: {
                long long delta = (long long)(S - (Elf64_Addr)(unsigned long)P);
                *(int *)P = (int)delta;
                break;
            }
            case R_X86_64_32:
                *(unsigned int *)P = (unsigned int)S;
                break;
            case R_X86_64_32S:
                *(int *)P = (int)(long)S;
                break;
            }
        }
    }

    void *entry = 0;
    const char *entry_names[] = {"go", "kmain", "minigcc_main", "cvm_main", "main", 0};
    int ei;
    for (ei = 0; entry_names[ei] && !entry; ei++) {
        unsigned k;
        for (k = 0; k < symcount; k++) {
            char symname[ELF_NAME_MAX];
            elf_name_copy(symname, sizeof(symname), strtab, strtab_size,
                          symtab[k].st_name);
            if (kstrcmp(symname, entry_names[ei]) != 0) continue;
            if (symtab[k].st_shndx == SHN_UNDEF || symtab[k].st_shndx >= shnum) continue;
            if (!sec_addrs[symtab[k].st_shndx]) {
                kprintf("load: skip '%s' in non-alloc sec %d\n", symname, symtab[k].st_shndx);
                continue;
            }
            entry = (char *)sec_addrs[symtab[k].st_shndx] + symtab[k].st_value;
            break;
        }
    }

    if (!entry) {
        kprintf("load: NO ENTRY. symbols:\n");
        for (unsigned k = 0; k < symcount && k < 20; k++) {
            char sn[ELF_NAME_MAX];
            elf_name_copy(sn, sizeof(sn), strtab, strtab_size, symtab[k].st_name);
            int alloc = (symtab[k].st_shndx < shnum && sec_addrs[symtab[k].st_shndx]) ? 1 : 0;
            kprintf("  [%u] '%s' sec=%u val=%lu alloc=%d\n",
                    k, sn, symtab[k].st_shndx, symtab[k].st_value, alloc);
        }
        elf_load_fail(base, sec_addrs, "no valid entry point");
        return 0;
    }
    kfree(sec_addrs);
    return entry;
}

/* ---- ET_EXEC / ET_DYN loader (Linux ring-3 binaries) ---- */

static void apply_exec_relocs(void *data, unsigned size, unsigned long base,
                              const struct exec_range *xr, unsigned nxr) {
    Elf64_Ehdr *e = (Elf64_Ehdr *)data;
    if (size < sizeof(Elf64_Ehdr)) return;
    if (e->e_shentsize < sizeof(Elf64_Shdr)) return;
    if (e->e_shoff > size) return;
    if (e->e_shnum > (size - e->e_shoff) / e->e_shentsize) return;
    Elf64_Shdr *sh = (Elf64_Shdr *)((char *)data + e->e_shoff);
    unsigned i;
    for (i = 0; i < e->e_shnum; i++) {
        if (sh[i].sh_type != SHT_RELA) continue;
        if (sh[i].sh_offset > size || sh[i].sh_size > size - sh[i].sh_offset)
            continue;
        Elf64_Rela *rela = (Elf64_Rela *)((char *)data + sh[i].sh_offset);
        unsigned n = (unsigned)(sh[i].sh_size / sizeof(Elf64_Rela));
        Elf64_Sym  *syms = 0;
        unsigned    syms_count = 0;
        const char *str  = 0;
        Elf64_Xword str_size = 0;
        if (sh[i].sh_link && sh[i].sh_link < e->e_shnum) {
            Elf64_Shdr *ss = &sh[sh[i].sh_link];
            if (ss->sh_offset <= size && ss->sh_size <= size - ss->sh_offset) {
                syms = (Elf64_Sym *)((char *)data + ss->sh_offset);
                syms_count = (unsigned)(ss->sh_size / sizeof(Elf64_Sym));
                if (ss->sh_link && ss->sh_link < e->e_shnum) {
                    Elf64_Shdr *ts = &sh[ss->sh_link];
                    if (ts->sh_offset <= size &&
                        ts->sh_size <= size - ts->sh_offset) {
                        str = (const char *)data + ts->sh_offset;
                        str_size = ts->sh_size;
                    }
                }
            }
        }
        unsigned j;
        for (j = 0; j < n; j++) {
            unsigned    type = ELF64_R_TYPE(rela[j].r_info);
            unsigned    si   = ELF64_R_SYM(rela[j].r_info);
            unsigned long P = base + rela[j].r_offset;
            if (P < USER_LOAD_BASE || P > USER_LOAD_END - 8)
                continue;
            unsigned long *PP = (unsigned long *)P;
            unsigned long S  = 0;
            if (syms && si < syms_count) {
                Elf64_Sym *sym = &syms[si];
                if (sym->st_shndx != SHN_UNDEF) S = base + sym->st_value;
                else if (str) {
                    char symname[ELF_NAME_MAX];
                    elf_name_copy(symname, sizeof(symname), str, str_size,
                                  sym->st_name);
                    void *a = ksym_resolve(symname);
                    if (!a && symname[0] == '_')
                        a = ksym_resolve(symname + 1);
                    S = (unsigned long)a;
                }
            }
            switch (type) {
            case R_X86_64_RELATIVE:
                *PP = base + (unsigned long)rela[j].r_addend;
                break;
            case R_X86_64_IRELATIVE: {
                unsigned long fn = base + (unsigned long)rela[j].r_addend;
                unsigned k;
                int in_exec = 0;
                for (k = 0; k < nxr; k++) {
                    if (fn >= xr[k].start && fn < xr[k].end) { in_exec = 1; break; }
                }
                if (!in_exec) continue;
                *PP = ((unsigned long (*)(void))fn)();
                break;
            }
            case R_X86_64_64:
                *PP = S + (unsigned long)rela[j].r_addend;
                break;
            case R_X86_64_GLOB_DAT:
            case R_X86_64_JUMP_SLOT:
                *PP = S;
                break;
            }
        }
    }
}

void *load_exec_elf(void *data, unsigned size) {
    Elf64_Ehdr *e = (Elf64_Ehdr *)data;
    if (size < sizeof(Elf64_Ehdr)) { kprintf("exec: too small %u\n", size); return 0; }
    if (e->e_ident[0] != 0x7F || e->e_ident[1] != 'E' ||
        e->e_ident[2] != 'L'  || e->e_ident[3] != 'F') { kprintf("exec: bad magic\n"); return 0; }
    if (e->e_machine != EM_X86_64) { kprintf("exec: bad machine %d\n", e->e_machine); return 0; }
    if (e->e_type != ET_EXEC && e->e_type != ET_DYN) { kprintf("exec: bad type %d\n", e->e_type); return 0; }

    if (e->e_phentsize < sizeof(Elf64_Phdr)) { kprintf("exec: phentsize %d\n", e->e_phentsize); return 0; }
    if (e->e_phoff > size) { kprintf("exec: phoff too big %lu > %u\n", e->e_phoff, size); return 0; }
    if (e->e_phnum > (size - e->e_phoff) / e->e_phentsize) { kprintf("exec: phnum overflow\n"); return 0; }
    if (e->e_phnum > ELF_MAX_SEGMENTS) { kprintf("exec: too many segments %d\n", e->e_phnum); return 0; }

    unsigned long base = (e->e_type == ET_DYN) ? USER_LOAD_BASE : 0;

    Elf64_Phdr *ph = (Elf64_Phdr *)((char *)data + e->e_phoff);
    struct exec_range xr[ELF_MAX_SEGMENTS];
    unsigned nxr = 0;
    unsigned long max_end = 0;
    unsigned i;
    for (i = 0; i < e->e_phnum; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        if (ph[i].p_vaddr > USER_LOAD_END - base) { kprintf("exec: vaddr %lx too big\n", ph[i].p_vaddr); return 0; }
        unsigned long dst = base + ph[i].p_vaddr;
        if (dst < USER_LOAD_BASE || dst >= USER_LOAD_END) {
            kprintf("exec: seg %d dst %lx outside user window\n", i, dst);
            return 0;
        }
        if (ph[i].p_memsz > USER_LOAD_END - dst) { kprintf("exec: memsz overflow\n"); return 0; }
        if (ph[i].p_filesz > USER_LOAD_END - dst) { kprintf("exec: filesz overflow\n"); return 0; }
        if (ph[i].p_offset > size || ph[i].p_filesz > size - ph[i].p_offset)
            { kprintf("exec: seg data beyond file\n"); return 0; }
        if (ph[i].p_filesz > 0 && (ph[i].p_flags & PF_X) && nxr < ELF_MAX_SEGMENTS) {
            xr[nxr].start = dst;
            xr[nxr].end   = dst + ph[i].p_filesz;
            nxr++;
        }
        kmemcpy((void *)dst, (char *)data + ph[i].p_offset,
                (unsigned long)ph[i].p_filesz);
        if (ph[i].p_memsz > ph[i].p_filesz)
            kmemset((void *)(dst + ph[i].p_filesz), 0,
                    (unsigned long)(ph[i].p_memsz - ph[i].p_filesz));
        if (dst + ph[i].p_memsz > max_end) max_end = dst + ph[i].p_memsz;
    }
    if (max_end == 0) { kprintf("exec: no loadable segments\n"); return 0; }

    unsigned long cur_cr3;
    __asm__ volatile("mov %%cr3, %0" : "=r"(cur_cr3));
    for (i = 0; i < nxr; i++)
        mm_user_set_exec(xr[i].start, xr[i].end, cur_cr3);

    apply_exec_relocs(data, size, base, xr, nxr);

    g_brk       = ALIGN_UP(max_end, 0x1000);
    g_brk_limit = USER_BRK_END;
    user_mmap_cur = USER_BRK_END;
    if (DOOM_BACKBUF_ADDR < g_brk_limit) g_brk_limit = DOOM_BACKBUF_ADDR;
    if (DOOM_BACKBUF_ADDR < user_mmap_cur) user_mmap_cur = DOOM_BACKBUF_ADDR;
    vma_tree_init();
    {
        int was = redirect_suspend();
        kprintf("exec: loaded at %lx entry %lx brk %lx\n", base + USER_LOAD_BASE, base + e->e_entry, g_brk);
        redirect_resume(was);
    }
    return (void *)(base + e->e_entry);
}
