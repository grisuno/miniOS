#include "kernel.h"
#include "ldso.h"
#include "minifs.h"
#include "pcache.h"
#include "vga_fb.h"
#include "sched.h"

/* ================================================================
 *  ELF loader
 *
 *  Two loaders:
 *    elf_load       — ET_REL relocatable .o objects (ring-0 toolchain)
 *    load_exec_elf  — ET_EXEC / ET_DYN Linux binaries (ring-3)
 *  Plus the T8 ld.so glue below: a boot-global shared-library
 *  registry with eager GLOB_DAT binding. Static images never reach
 *  it (no PT_DYNAMIC means no-op), so their behavior is unchanged.
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

/* ET_REL image cap: a hostile .o must not drive an unbounded kmalloc.
 * Measured need (2026-09, host gcc -O2): ld.o carries a 12.6 MB .bss and
 * loads at ~12.7 MB total; minigcc.o ~0.8 MB, cvm.o ~36 KB. 16 MB fails
 * closed with a diagnostic instead of draining the 192 MB kernel heap.
 * Do not tighten below ld.o without remeasuring. */
#define ETREL_IMAGE_MAX (16u * 1024u * 1024u)

#define SHT_SYMTAB  2
#define SHT_STRTAB  3
#define SHT_RELA    4
#define SHT_PROGBITS 1
#define SHT_NOBITS  8
#define SHF_ALLOC   2
#define SHF_EXECINSTR 4

#define EM_X86_64  62
#define PT_LOAD     1
#define PT_NOTE     4

/* ELF note header (namesz, descsz, type); name and descriptor follow, each
 * padded to ELF_NOTE_ALIGN bytes. */
#define ELF_NOTE_HDR   12UL
#define ELF_NOTE_ALIGN 4UL

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

void *elf_load(void *data, unsigned size, void **base_out) {
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
            if (total_alloc > ETREL_IMAGE_MAX) {
                kprintf("load: ET_REL image exceeds %u bytes, refusing\n",
                        ETREL_IMAGE_MAX);
                return 0;
            }
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
    if (base_out != 0) *base_out = base;
    return entry;
}

/* ---- T8 ld.so: boot-global shared-library registry ----
 *
 * One slot per library path basename: the first loader reserves a base
 * in the ABI region, keeps a heap copy of the file (fault-time reads
 * and rebinds) and publishes nothing yet; every bound process faults
 * the same file pages through the pcache, so text is shared while
 * data breaks private on first write and BSS stays per-process zero.
 * Pseudo inodes (LDSO_INO_BASE + slot) keep registry pages apart from
 * MiniFS inodes in the shared cache. No unload in v1: slots and file
 * copies live for the machine's life, and the refcount names how many
 * executables bound since boot (the BDD shared-marker reads it).
 * All validation funnels through headers/ldso.h (host-tested); this
 * file only moves bytes and installs mappings. */

typedef struct {
    int used;
    char name[LDSO_NAME_LEN];
    unsigned long base;
    unsigned long map_len;
    unsigned char *file;
    unsigned file_size;
    int ino;
    int refcount;
} LdsoLibEnt;

static LdsoLibEnt ldso_libs[LDSO_MAX_LIBS];
static unsigned long ldso_bump;

int ldso_pseudo_stat(int ino, unsigned long *size_out) {
    int i;
    if (!size_out) return -1;
    if (ino < LDSO_INO_BASE || ino >= LDSO_INO_BASE + LDSO_MAX_LIBS)
        return -1;
    for (i = 0; i < LDSO_MAX_LIBS; i++) {
        if (ldso_libs[i].used && ldso_libs[i].ino == ino) {
            *size_out = ldso_libs[i].file_size;
            return 0;
        }
    }
    return -1;
}

int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len) {
    int i;
    if (!dst || len > 0x1000) return -1;
    if (ino < LDSO_INO_BASE || ino >= LDSO_INO_BASE + LDSO_MAX_LIBS)
        return -1;
    for (i = 0; i < LDSO_MAX_LIBS; i++) {
        LdsoLibEnt *lib = &ldso_libs[i];
        unsigned long avail;
        if (!lib->used || lib->ino != ino) continue;
        if (!lib->file || off > lib->file_size) return -1;
        avail = lib->file_size - off;
        if (len > avail) {
            kmemcpy(dst, lib->file + off, avail);
            kmemset((char *)dst + avail, 0, len - avail);
            return (int)len;
        }
        kmemcpy(dst, lib->file + off, len);
        return (int)len;
    }
    return -1;
}

/* Read a whole library file by DT_NEEDED name: exact path first, then
 * the basename, ramdisk before MiniFS (the shell's own search order).
 * The buffer is heap-owned; every failure releases it. */
static int ldso_read_file(const char *name, unsigned char **out,
        unsigned *size_out) {
    char base[LDSO_NAME_LEN];
    unsigned char *buf = 0;
    RDFile *rf;
    int ino;
    MiniFSInode st;
    if (!name || !out || !size_out) return -1;
    ldso_basename(base, name);
    if (base[0] == '\0') return -1;
    rf = ramdisk_open(name);
    if (!rf && kstrcmp(name, base) != 0) rf = ramdisk_open(base);
    if (rf) {
        if (rf->size == 0 || rf->size > LDSO_FILE_MAX) return -1;
        buf = kmalloc(rf->size);
        if (!buf) return -1;
        ramdisk_read(rf, buf, 0, rf->size);
        *out = buf;
        *size_out = rf->size;
        return 0;
    }
    ino = minifs_resolve_path(name);
    if (ino < 0 && kstrcmp(name, base) != 0)
        ino = minifs_resolve_path(base);
    if (ino < 0) return -1;
    if (minifs_stat(ino, &st) < 0) return -1;
    if (st.size == 0 || st.size > LDSO_FILE_MAX) return -1;
    buf = kmalloc(st.size);
    if (!buf) return -1;
    if (minifs_read(ino, buf, 0, st.size) != (int)st.size) {
        kfree(buf);
        return -1;
    }
    *out = buf;
    *size_out = st.size;
    return 0;
}

/* Resolve a DT_NEEDED name to a registry slot, loading and reserving
 * on first use. Validates the full dynamic contract (tables present,
 * 24-byte symbols, hash-sized count, load span inside the region)
 * before publishing anything. */
static int ldso_ensure_slot(const char *needed, int *slot_out) {
    char key[LDSO_NAME_LEN];
    unsigned char *file = 0;
    unsigned fsize = 0;
    unsigned long long dyn_off = 0;
    unsigned long long dyn_size = 0;
    LdsoDynInfo info;
    LdsoSeg segs[8];
    unsigned nseg = 0;
    unsigned i;
    unsigned long span_end = 0;
    unsigned long span;
    unsigned long long strtab_off = 0;
    unsigned long long symtab_off = 0;
    unsigned nsyms = 0;
    unsigned long long hash_off = 0;
    int slot = -1;
    int trouvent = -1;
    if (!needed || !slot_out) return -1;
    ldso_basename(key, needed);
    if (key[0] == '\0') return -1;
    for (i = 0; i < LDSO_MAX_LIBS; i++) {
        if (ldso_libs[i].used) {
            if (kstrcmp(ldso_libs[i].name, key) == 0) {
                *slot_out = (int)i;
                return 0;
            }
        } else if (trouvent < 0) trouvent = (int)i;
    }
    if (ldso_read_file(needed, &file, &fsize)) {
        kprintf("ld.so: cannot open '%s'\n", key);
        return -1;
    }
    if (ldso_find_dynamic(file, fsize, &dyn_off, &dyn_size) != 1) {
        kprintf("ld.so: '%s' has no dynamic section\n", key);
        goto fail;
    }
    if (ldso_scan_dynamic(file, fsize, dyn_off, dyn_size, &info)) goto fail;
    if (info.strsz == 0 || info.syment != LDSO_SYM_SIZE) goto fail;
    if (ldso_vaddr_to_offset(file, fsize, info.strtab_va, &strtab_off))
        goto fail;
    if (ldso_vaddr_to_offset(file, fsize, info.symtab_va, &symtab_off))
        goto fail;
    if (ldso_vaddr_to_offset(file, fsize, info.hash_va, &hash_off))
        goto fail;
    if (ldso_sym_count(file, fsize, hash_off, &nsyms)) goto fail;
    if (ldso_segments(file, fsize, segs, 8, &nseg)) goto fail;
    for (i = 0; i < nseg; i++) {
        unsigned long end;
        if (segs[i].memsz > LDSO_REGION_SIZE) goto fail;
        if (segs[i].vaddr > LDSO_REGION_SIZE - segs[i].memsz) goto fail;
        end = segs[i].vaddr + segs[i].memsz;
        if (end > span_end) span_end = end;
    }
    span = ALIGN_UP(span_end, 0x1000UL);
    if (span == 0 || span > LDSO_REGION_SIZE) goto fail;
    if (trouvent < 0) {
        kprintf("ld.so: too many libraries\n");
        goto fail;
    }
    if (ldso_bump == 0) ldso_bump = LDSO_REGION_BASE;
    if (ldso_bump < LDSO_REGION_BASE || ldso_bump > LDSO_REGION_END)
        goto fail;
    if (span > LDSO_REGION_END - ldso_bump) {
        kprintf("ld.so: library region full\n");
        goto fail;
    }
    (void)nsyms;
    slot = trouvent;
    kmemset(&ldso_libs[slot], 0, sizeof(ldso_libs[slot]));
    kstrncpy(ldso_libs[slot].name, key, sizeof(ldso_libs[slot].name) - 1);
    ldso_libs[slot].base = ldso_bump;
    ldso_libs[slot].map_len = span;
    ldso_libs[slot].file = file;
    ldso_libs[slot].file_size = fsize;
    ldso_libs[slot].ino = LDSO_INO_BASE + slot;
    ldso_libs[slot].refcount = 0;
    ldso_libs[slot].used = 1;
    ldso_bump += span;
    *slot_out = slot;
    return 0;
fail:
    if (file) kfree(file);
    kprintf("ld.so: '%s' refused (corrupt library)\n", key);
    return -1;
}

/* Install one library in the currently bound VMA view: file-backed
 * node over the reserved range, then explicit publish-and-map of every
 * page (shared text through the pcache on first publish, hits after;
 * private zero pages past the file end). Explicit mapping, never
 * touch-to-fault: the live window is identity pre-mapped, so demand
 * faults cannot fire there, while isolated windows start empty; one
 * path serves both. Data pages start shared read-only and break
 * private on first write; RX marking follows a content check, so only
 * verified bytes ever execute. Failure keeps node, mappings and refs
 * consistent (the next exec forgets them, a dying window frees them),
 * and only reports. */
static int ldso_map_one(LdsoLibEnt *lib, unsigned long cr3) {
    vma_node_t *fnd;
    unsigned char *tmp = 0;
    LdsoSeg segs[8];
    unsigned nseg = 0;
    unsigned long va;
    unsigned long first = 0;
    unsigned i;
    if (!lib || !lib->used) return -1;
    fnd = vma_tree_insert(&vma_live_root, lib->base, lib->map_len);
    if (fnd == VMA_NIL) {
        kprintf("ld.so: cannot map '%s'\n", lib->name);
        return -1;
    }
    fnd->f_file = 1;
    fnd->f_ino = lib->ino;
    fnd->f_off = 0;
    tmp = kmalloc(0x1000);
    if (!tmp) return -1;
    kmemset(tmp, 0, 0x1000);
    for (va = lib->base; va < lib->base + lib->map_len; va += 0x1000) {
        unsigned long idx = (va - lib->base) / 0x1000UL;
        unsigned long foff = idx * 0x1000UL;
        if (foff < lib->file_size) {
            unsigned long avail = lib->file_size - foff;
            if (avail >= 0x1000UL) {
                int slot = pcache_publish(lib->ino, (unsigned)idx,
                    lib->file + foff);
                unsigned char *pg;
                if (slot < 0) {
                    kprintf("ld.so: cache full, refusing '%s'\n",
                        lib->name);
                    kfree(tmp);
                    return -1;
                }
                pg = pcache_data(slot);
                if (!pg) {
                    kfree(tmp);
                    return -1;
                }
                if (mm_user_map_page(cr3, va, (unsigned long)pg, 0,
                        0)) {
                    kfree(tmp);
                    return -1;
                }
            } else {
                void *priv;
                int slot;
                kmemcpy(tmp, lib->file + foff, avail);
                slot = pcache_publish(lib->ino, (unsigned)idx, tmp);
                if (slot < 0) {
                    kprintf("ld.so: cache full, refusing '%s'\n",
                        lib->name);
                    kfree(tmp);
                    return -1;
                }
                priv = (void *)pcache_data(slot);
                if (!priv) {
                    kfree(tmp);
                    return -1;
                }
                if (mm_user_map_page(cr3, va, (unsigned long)priv, 0,
                        0)) {
                    kfree(tmp);
                    return -1;
                }
                kmemset(tmp, 0, 0x1000);
            }
        } else {
            void *zp = pt_page_alloc();
            if (!zp) {
                kfree(tmp);
                return -1;
            }
            kmemset(zp, 0, 0x1000);
            if (mm_user_map_page(cr3, va, (unsigned long)zp, 1, 0)) {
                pt_page_free(zp);
                kfree(tmp);
                return -1;
            }
        }
    }
    kfree(tmp);
    first = lib->file_size < 0x1000UL ? lib->file_size : 0x1000UL;
    if (first > 0 && kmemcmp((void *)lib->base, lib->file, first) != 0) {
        kprintf("ld.so: '%s' content mismatch\n", lib->name);
        return -1;
    }
    if (ldso_segments(lib->file, lib->file_size, segs, 8, &nseg)) return -1;
    for (i = 0; i < nseg; i++) {
        unsigned long start;
        unsigned long end;
        if (!(segs[i].flags & LDSO_PF_X)) continue;
        if (segs[i].filesz == 0) continue;
        if (segs[i].vaddr > lib->map_len) return -1;
        if (segs[i].filesz > lib->map_len - segs[i].vaddr) return -1;
        start = lib->base + segs[i].vaddr;
        end = start + segs[i].filesz;
        if (end < start || end > USER_LOAD_END) return -1;
        mm_user_set_exec(start, end, cr3);
    }
    return 0;
}

/* Forget the previous exec's registry mappings in the live window:
 * registry file nodes release (refs dropped, pages unmapped, range
 * returned to the free tree) before the tree resets, so refcounts
 * never pin the pool across runs. Only pseudo-ino nodes are
 * touched: user MiniFS mappings keep Linux-like exec survival. */
static void ldso_forget_live(void) {
    vma_node_t *stack[16];
    unsigned long bases[LDSO_MAX_LIBS];
    unsigned long lens[LDSO_MAX_LIBS];
    int inos[LDSO_MAX_LIBS];
    unsigned n = 0;
    int sp = 0;
    vma_node_t *x = vma_live_root;
    unsigned i;
    while (x != VMA_NIL || sp > 0) {
        while (x != VMA_NIL) {
            if (sp < 16) stack[sp++] = x;
            x = x->left;
        }
        x = stack[--sp];
        if (x->f_file && x->f_ino >= LDSO_INO_BASE && n < LDSO_MAX_LIBS) {
            bases[n] = x->base;
            lens[n] = x->len;
            inos[n] = x->f_ino;
            n++;
        }
        x = x->right;
    }
    for (i = 0; i < n; i++) {
        mm_file_range_release(0, bases[i], lens[i], inos[i], 0, 1);
        vma_tree_insert(&vma_free_root, bases[i], lens[i]);
        vma_tree_delete(&vma_live_root, bases[i]);
    }
}

/* Resolve one imported name: the executable's own definition first
 * (standard scope order), then each DT_NEEDED library in order, then
 * the kernel symbol table (the runtime cohort the toolchain leaves
 * undefined but never calls stays bound to whatever the kernel
 * exports, exactly like the static apply path). Unresolvable names
 * stay zero and fault only if called. */
static int ldso_resolve_one(const char *name,
        const unsigned char *exefile, unsigned long exefsize,
        unsigned long long exsym_off, unsigned exnsyms,
        unsigned long long exstr_off, unsigned long long exstrsz,
        unsigned long exebase, int *libs, unsigned nlibs,
        unsigned long long *value_out) {
    unsigned long long v = 0;
    unsigned i;
    int rc;
    if (!name || !value_out) return -1;
    if (exnsyms >= 2) {
        rc = ldso_sym_lookup(exefile, exefsize, exsym_off, exnsyms,
            exstr_off, exstrsz, name, &v);
        if (rc < 0) return -1;
        if (rc == 1) {
            if (v >= USER_LOAD_END - exebase) return -1;
            *value_out = exebase + (unsigned long)v;
            return 1;
        }
    }
    for (i = 0; i < nlibs; i++) {
        LdsoLibEnt *lib = &ldso_libs[libs[i]];
        unsigned long long dyn_off = 0;
        unsigned long long dyn_size = 0;
        LdsoDynInfo info;
        unsigned long long strtab_off = 0;
        unsigned long long symtab_off = 0;
        unsigned long long hash_off = 0;
        unsigned nsyms = 0;
        if (ldso_find_dynamic(lib->file, lib->file_size, &dyn_off,
                &dyn_size) != 1) return -1;
        if (ldso_scan_dynamic(lib->file, lib->file_size, dyn_off,
                dyn_size, &info)) return -1;
        if (ldso_vaddr_to_offset(lib->file, lib->file_size,
                info.strtab_va, &strtab_off)) return -1;
        if (ldso_vaddr_to_offset(lib->file, lib->file_size,
                info.symtab_va, &symtab_off)) return -1;
        if (ldso_vaddr_to_offset(lib->file, lib->file_size,
                info.hash_va, &hash_off)) return -1;
        if (ldso_sym_count(lib->file, lib->file_size, hash_off, &nsyms))
            return -1;
        rc = ldso_sym_lookup(lib->file, lib->file_size, symtab_off,
            nsyms, strtab_off, info.strsz, name, &v);
        if (rc < 0) return -1;
        if (rc == 1) {
            if (v >= lib->map_len) continue;
            if (lib->base > USER_LOAD_END - (unsigned long)v) return -1;
            *value_out = lib->base + (unsigned long)v;
            return 1;
        }
    }
    {
        void *a = ksym_resolve(name);
        if (!a && name[0] == '_') a = ksym_resolve(name + 1);
        if (a) {
            *value_out = (unsigned long)a;
            return 1;
        }
    }
    return 0;
}

/* Bind one executable image with DT_NEEDED libraries: map every
 * library into the target window, then resolve each GLOB_DAT row.
 * Static images (no dynamic section, or none needed) return 0 at
 * once, so the legacy paths never observe a difference. Live callers
 * pass cr3 0 and vma 0 (current tables, legacy view already bound);
 * isolated callers pass the child's tables and context. */
int ldso_bind_into(void *data, unsigned size, unsigned long base,
        unsigned long cr3, vma_ctx_t *vma) {
    unsigned char *exefile = (unsigned char *)data;
    unsigned long long dyn_off = 0;
    unsigned long long dyn_size = 0;
    LdsoDynInfo info;
    LdsoSeg segs[8];
    unsigned nseg = 0;
    unsigned long exspan = 0;
    unsigned long long strtab_off = 0;
    unsigned long long symtab_off = 0;
    unsigned long long rela_off = 0;
    unsigned nsyms = 0;
    unsigned nrela = 0;
    unsigned long long hash_off = 0;
    int libs[LDSO_MAX_NEEDED];
    unsigned nlibs = 0;
    unsigned i;
    unsigned long usecr3 = cr3;
    unsigned long saved_cr3 = 0;
    vma_view_t view;
    irqflags_t flags;
    int live;
    int rc = -1;
    unsigned li;
    if (!data || size < 64) return -1;
    /* No base guard here: ET_EXEC passes base 0 with absolute segment
     * VAs (host gcc static non-PIE binaries), ET_DYN passes its load
     * base. The per-segment memsz and per-row slot_va window checks
     * below validate every address regardless. */
    {
        int fr = ldso_find_dynamic(exefile, size, &dyn_off, &dyn_size);
        if (fr == 0) return 0;
        if (fr != 1) return -1;
    }
    if (ldso_scan_dynamic(exefile, size, dyn_off, dyn_size, &info))
        return -1;
    if (info.needed_count == 0) return 0;
    if (ldso_vaddr_to_offset(exefile, size, info.strtab_va, &strtab_off))
        return -1;
    if (ldso_vaddr_to_offset(exefile, size, info.symtab_va, &symtab_off))
        return -1;
    if (info.has_rela) {
        if (ldso_vaddr_to_offset(exefile, size, info.rela_va, &rela_off))
            return -1;
    }
    if (ldso_vaddr_to_offset(exefile, size, info.hash_va, &hash_off))
        return -1;
    if (ldso_sym_count(exefile, size, hash_off, &nsyms)) return -1;
    if (ldso_rela_count(&info, &nrela)) return -1;
    if (ldso_segments(exefile, size, segs, 8, &nseg)) return -1;
    for (i = 0; i < nseg; i++) {
        unsigned long end;
        if (segs[i].memsz > USER_LOAD_END) return -1;
        if (segs[i].vaddr > USER_LOAD_END - segs[i].memsz) return -1;
        end = segs[i].vaddr + segs[i].memsz;
        if (end > exspan) exspan = end;
    }
    if (exspan == 0) return -1;
    /* File I/O and heap live outside the target window: the child CR3
     * owns user pages only, so resolution runs on the caller side and
     * only mappings and GOT stores go inside. */
    for (li = 0; li < info.needed_count; li++) {
        char need[LDSO_NAME_LEN];
        int slot = -1;
        if (ldso_copy_str(exefile, size, strtab_off, info.strsz,
                info.needed_off[li], need, sizeof(need))) {
            kprintf("ld.so: bad NEEDED string\n");
            return -1;
        }
        if (ldso_ensure_slot(need, &slot)) return -1;
        {
            unsigned d;
            int seen = 0;
            for (d = 0; d < nlibs; d++) {
                if (libs[d] == slot) {
                    seen = 1;
                    break;
                }
            }
            if (!seen && nlibs < LDSO_MAX_NEEDED) libs[nlibs++] = slot;
        }
    }
    live = (vma == 0);
    if (live) {
        __asm__ volatile("mov %%cr3, %0" : "=r"(usecr3));
        flags = spin_save_irq();
    } else {
        vma_view_save(&view);
        vma_ctx_bind(vma);
        __asm__ volatile("mov %%cr3, %0" : "=r"(saved_cr3));
        flags = spin_save_irq();
        __asm__ volatile("mov %0, %%cr3" :: "r"(cr3) : "memory");
    }
    for (li = 0; li < nlibs; li++) {
        if (ldso_map_one(&ldso_libs[libs[li]], usecr3)) goto out;
        ldso_libs[libs[li]].refcount++;
        kprintf("ld.so: %s shared x%d\n", ldso_libs[libs[li]].name,
            ldso_libs[libs[li]].refcount);
    }
    for (i = 0; i < nrela; i++) {
        LdsoRelaRow row;
        char symname[LDSO_NAME_LEN];
        unsigned long long symval = 0;
        unsigned long slot_va;
        int r;
        unsigned k;
        int in_image = 0;
        r = ldso_read_rela(exefile, size, rela_off, nrela, i, nsyms,
            &row);
        if (r == -2) {
            kprintf("ld.so: reloc %u: unsupported type\n", i);
            goto out;
        }
        if (r) {
            kprintf("ld.so: reloc %u: bad row\n", i);
            goto out;
        }
        {
            const unsigned char *syms;
            unsigned long long total = (unsigned long long)nsyms *
                LDSO_SYM_SIZE;
            if (symtab_off > size || total > size - symtab_off) {
                kprintf("ld.so: reloc %u: bad symtab\n", i);
                goto out;
            }
            syms = exefile + symtab_off;
            if (row.sym * LDSO_SYM_SIZE + 4 > total) {
                kprintf("ld.so: reloc %u: bad sym\n", i);
                goto out;
            }
            {
                unsigned long nmoff =
                    (unsigned)syms[row.sym * LDSO_SYM_SIZE] |
                    ((unsigned)syms[row.sym * LDSO_SYM_SIZE + 1] << 8) |
                    ((unsigned)syms[row.sym * LDSO_SYM_SIZE + 2] << 16) |
                    ((unsigned)syms[row.sym * LDSO_SYM_SIZE + 3] << 24);
                if (ldso_copy_str(exefile, size, strtab_off,
                        info.strsz, nmoff, symname,
                        sizeof(symname))) {
                    kprintf("ld.so: reloc %u: bad name\n", i);
                    goto out;
                }
            }
        }
        if (row.offset > exspan || 8 > exspan - row.offset) {
            kprintf("ld.so: reloc %u: slot %lx outside image %lx\n", i,
                row.offset, exspan);
            goto out;
        }
        slot_va = base + row.offset;
        if (slot_va < USER_LOAD_BASE || slot_va > USER_LOAD_END - 8) {
            kprintf("ld.so: reloc %u: slot outside window\n", i);
            goto out;
        }
        for (k = 0; k < nseg; k++) {
            if (row.offset >= segs[k].vaddr &&
                    row.offset <= segs[k].vaddr + segs[k].memsz - 8) {
                in_image = 1;
                break;
            }
        }
        if (!in_image) {
            kprintf("ld.so: reloc %u: slot outside segments\n", i);
            goto out;
        }
        r = ldso_resolve_one(symname, exefile, size, symtab_off, nsyms,
            strtab_off, info.strsz, (unsigned long)base, libs, nlibs,
            &symval);
        if (r < 0) {
            kprintf("ld.so: reloc %u: resolve failed\n", i);
            goto out;
        }
        if (r == 1) *(unsigned long *)slot_va = symval;
    }
    rc = 0;
out:
    if (live) {
        spin_restore_irq(flags);
    } else {
        vma_ctx_save(vma);
        vma_view_load(&view);
        __asm__ volatile("mov %0, %%cr3" :: "r"(saved_cr3) : "memory");
        spin_restore_irq(flags);
    }
    return rc;
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
    if (e->e_type == ET_DYN) base += aslr_dyn_base();

    Elf64_Phdr *ph = (Elf64_Phdr *)((char *)data + e->e_phoff);
    struct exec_range xr[ELF_MAX_SEGMENTS];
    unsigned nxr = 0;
    unsigned long max_end = 0;
    unsigned i;
    /* The segments land in the LIVE user window and the tail below
     * rewrites the shared brk/mmap view, so the whole load is one
     * atomic section: a 100 Hz tick between two segments would switch
     * CR3 into another process (copies landing in its pages, NX marks
     * and brk carved from its view) and corrupt whoever loses. The
     * isolated loader already works this way (irq saved around every
     * CR3 switch); the only difference here is that no switch is
     * needed, just no preemption. Serial output stays polled,
     * allocation stays heap-local, relocs stay pure, so nothing inside
     * needs interrupts. Every exit below restores them.
     * Interrupt masking uses spin_save_irq/spin_restore_irq (the same
     * primitive spin_lock_irqsave is built on), never bare cli/sti: a
     * bare sti on a path entered with IF=0 would wrongly enable
     * interrupts, and on SMP the saved-flags form nests safely. */
    irqflags_t irqf = spin_save_irq();
    for (i = 0; i < e->e_phnum; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        if (ph[i].p_vaddr > USER_LOAD_END - base) { kprintf("exec: vaddr %lx too big\n", ph[i].p_vaddr); goto fail; }
        unsigned long dst = base + ph[i].p_vaddr;
        if (dst < USER_LOAD_BASE || dst >= USER_LOAD_END) {
            kprintf("exec: seg %d dst %lx outside user window\n", i, dst);
            goto fail;
        }
        if (ph[i].p_memsz > USER_LOAD_END - dst) { kprintf("exec: memsz overflow\n"); goto fail; }
        if (ph[i].p_filesz > USER_LOAD_END - dst) { kprintf("exec: filesz overflow\n"); goto fail; }
        if (ph[i].p_offset > size || ph[i].p_filesz > size - ph[i].p_offset)
            { kprintf("exec: seg data beyond file\n"); goto fail; }
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
    if (max_end == 0) { kprintf("exec: no loadable segments\n"); goto fail; }

    /* Fail closed on torn images: re-read every file-backed byte and
     * refuse to enter ring 3 when the window disagrees with the file.
     * This runs BEFORE apply_exec_relocs on purpose: relocations
     * legitimately rewrite GOT/data in the window, so anything after
     * them would cry wolf on every static binary. A concurrent writer
     * (or a torn block fill) used to sail through validation and jump
     * anywhere; now it is a diagnostic, and the diagnostic firing also
     * names the corruption source outright. */
    for (i = 0; i < e->e_phnum; i++) {
        if (ph[i].p_type != PT_LOAD) continue;
        if (ph[i].p_filesz > 0) {
            unsigned long dst = base + ph[i].p_vaddr;
            if (kmemcmp((void *)dst, (char *)data + ph[i].p_offset,
                        (unsigned long)ph[i].p_filesz) != 0) {
                kprintf("exec: image changed during load (seg %d)\n", i);
                goto fail;
            }
        }
    }

    unsigned long cur_cr3;
    __asm__ volatile("mov %%cr3, %0" : "=r"(cur_cr3));
    for (i = 0; i < nxr; i++)
        mm_user_set_exec(xr[i].start, xr[i].end, cur_cr3);

    apply_exec_relocs(data, size, base, xr, nxr);

    g_brk       = ALIGN_UP(max_end, 0x1000);
    g_brk_limit = USER_HEAP_CEIL;
    user_mmap_cur = USER_HEAP_CEIL;
    if (DOOM_BACKBUF_ADDR < g_brk_limit) g_brk_limit = DOOM_BACKBUF_ADDR;
    if (DOOM_BACKBUF_ADDR < user_mmap_cur) user_mmap_cur = DOOM_BACKBUF_ADDR;
    /* ASLR: the heap starts past a random pad (clamped, never past the
     * cap) and the mmap cursor starts below the ceiling (clamped above
     * brk_limit), so consecutive runs map differently. */
    {
        unsigned long pad = aslr_brk_pages() * 0x1000UL;
        if (g_brk + pad <= g_brk_limit && g_brk + pad >= g_brk)
            g_brk += pad;
        pad = aslr_mmap_pages() * 0x1000UL;
        if (user_mmap_cur > g_brk_limit + pad)
            user_mmap_cur -= pad;
    }
    vma_tree_init();
    /* Registry mappings from the previous run release first (refs,
     * pages, ranges), then the fresh image binds its DT_NEEDED set.
     * Static images return 0 at once inside the binder. */
    ldso_forget_live();
    if (ldso_bind_into(data, size, base, 0, 0)) goto fail;
    {
        int was = redirect_suspend();
        kprintf("exec: loaded at %lx entry %lx brk %lx\n", base + USER_LOAD_BASE, base + e->e_entry, g_brk);
        redirect_resume(was);
    }
    spin_restore_irq(irqf);
    return (void *)(base + e->e_entry);
fail:
    spin_restore_irq(irqf);
    return 0;
}

/* ---- Isolated loader (multitask foundation) ----
 *
 * Same validation as load_exec_elf, but the segments land in the user
 * window of `cr3` (built by pt_clone_user_empty) instead of the live
 * one. Pages are allocated with mm_user_ensure_page and filled under
 * a short CR3 switch with interrupts off; the caller's address space
 * is restored before return. Globals (g_brk, VMA) stay untouched: the
 * caller owns the per-process brk, reported via brk_out, and learns
 * the link base via base_out (0 when the caller runs static images
 * only: the dynamic binder needs the same base the segments used,
 * and ASLR never repeats it). Shared graphics slots are never
 * written. Returns the entry VA, or 0 with a diagnostic. Relocation
 * fixups stay with the caller: static images need none, and DT_NEEDED
 * images bind through ldso_bind_into once their VMA context exists.
 * No function symbol is ever resolved to a null address:
 * unresolvable imports stay zero and fault only if called. */
/* Size of one note field rounded up to ELF_NOTE_ALIGN. */
static unsigned long elf_note_pad(unsigned long n) {
    return (n + ELF_NOTE_ALIGN - 1UL) & ~(ELF_NOTE_ALIGN - 1UL);
}

/* 1 when one PT_NOTE segment [off, off + len) of the image carries the
 * MiniOS process note with a nonzero descriptor. Every field is checked
 * against the segment before it is read. */
static int elf_note_segment_wants_process(const unsigned char *img,
                                          unsigned long off, unsigned long len) {
    const unsigned long namesz_want = (unsigned long)sizeof(MINIOS_NOTE_NAME);
    unsigned long pos = 0;
    while (len - pos >= ELF_NOTE_HDR) {
        const unsigned char *n = img + off + pos;
        unsigned long namesz = *(const Elf64_Word *)(n + 0);
        unsigned long descsz = *(const Elf64_Word *)(n + 4);
        unsigned long type = *(const Elf64_Word *)(n + 8);
        unsigned long body = elf_note_pad(namesz) + elf_note_pad(descsz);
        if (body > len - pos - ELF_NOTE_HDR) return 0;
        if (namesz == namesz_want && type == MINIOS_NOTE_PROCESS &&
            descsz >= sizeof(Elf64_Word) &&
            kmemcmp(n + ELF_NOTE_HDR, MINIOS_NOTE_NAME, namesz_want) == 0 &&
            *(const Elf64_Word *)(n + ELF_NOTE_HDR + elf_note_pad(namesz)) != 0)
            return 1;
        pos += ELF_NOTE_HDR + body;
    }
    return 0;
}

/* Does an ET_EXEC/ET_DYN image ask to run as a process (minios_abi.h,
 * process note)? Header and program-header table are bounds checked like
 * load_exec_elf_into; any malformed table answers 0 and leaves the load
 * itself to report it. */
int elf_wants_process(const void *data, unsigned size) {
    const Elf64_Ehdr *e = (const Elf64_Ehdr *)data;
    const Elf64_Phdr *ph;
    unsigned i;
    if (!data || size < sizeof(Elf64_Ehdr)) return 0;
    if (e->e_ident[0] != 0x7F || e->e_ident[1] != 'E' ||
        e->e_ident[2] != 'L'  || e->e_ident[3] != 'F') return 0;
    if (e->e_type != ET_EXEC && e->e_type != ET_DYN) return 0;
    if (e->e_phentsize < sizeof(Elf64_Phdr)) return 0;
    if (e->e_phoff > size) return 0;
    if (e->e_phnum > (size - e->e_phoff) / e->e_phentsize) return 0;
    for (i = 0; i < e->e_phnum; i++) {
        ph = (const Elf64_Phdr *)((const unsigned char *)data + e->e_phoff +
                                  (unsigned long)i * e->e_phentsize);
        if (ph->p_type != PT_NOTE) continue;
        if (ph->p_offset > size || ph->p_filesz > size - ph->p_offset) continue;
        if (elf_note_segment_wants_process((const unsigned char *)data,
                                           (unsigned long)ph->p_offset,
                                           (unsigned long)ph->p_filesz))
            return 1;
    }
    return 0;
}

void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3,
                         unsigned long *brk_out, unsigned long *base_out) {
    Elf64_Ehdr *e = (Elf64_Ehdr *)data;
    unsigned long base;
    Elf64_Phdr *ph;
    struct exec_range xr[ELF_MAX_SEGMENTS];
    unsigned nxr = 0;
    unsigned long max_end = 0;
    unsigned long saved_cr3;
    unsigned i;
    if (!data || !brk_out) return 0;
    if (cr3 == 0) { kprintf("exec_into: null cr3\n"); return 0; }
    if (size < sizeof(Elf64_Ehdr)) { kprintf("exec_into: too small\n"); return 0; }
    if (e->e_ident[0] != 0x7F || e->e_ident[1] != 'E' ||
        e->e_ident[2] != 'L'  || e->e_ident[3] != 'F') { kprintf("exec_into: bad magic\n"); return 0; }
    if (e->e_machine != EM_X86_64) { kprintf("exec_into: bad machine\n"); return 0; }
    if (e->e_type != ET_EXEC && e->e_type != ET_DYN) { kprintf("exec_into: bad type\n"); return 0; }
    if (e->e_phentsize < sizeof(Elf64_Phdr)) { kprintf("exec_into: phentsize\n"); return 0; }
    if (e->e_phoff > size) { kprintf("exec_into: phoff\n"); return 0; }
    if (e->e_phnum > (size - e->e_phoff) / e->e_phentsize) { kprintf("exec_into: phnum\n"); return 0; }
    if (e->e_phnum > ELF_MAX_SEGMENTS) { kprintf("exec_into: too many segs\n"); return 0; }
    base = (e->e_type == ET_DYN) ? USER_LOAD_BASE : 0;
    if (e->e_type == ET_DYN) base += aslr_dyn_base();
    ph = (Elf64_Phdr *)((char *)data + e->e_phoff);
    __asm__ volatile("mov %%cr3, %0" : "=r"(saved_cr3));
    for (i = 0; i < e->e_phnum; i++) {
        unsigned long dst;
        unsigned long p;
        if (ph[i].p_type != PT_LOAD) continue;
        if (ph[i].p_vaddr > USER_LOAD_END - base) { kprintf("exec_into: vaddr big\n"); goto fail; }
        dst = base + ph[i].p_vaddr;
        if (dst < USER_LOAD_BASE || dst >= USER_LOAD_END) { kprintf("exec_into: outside window\n"); goto fail; }
        if (ph[i].p_memsz > USER_LOAD_END - dst) { kprintf("exec_into: memsz\n"); goto fail; }
        if (ph[i].p_filesz > USER_LOAD_END - dst) { kprintf("exec_into: filesz\n"); goto fail; }
        if (ph[i].p_offset > size || ph[i].p_filesz > size - ph[i].p_offset) { kprintf("exec_into: beyond file\n"); goto fail; }
        for (p = dst & ~0xFFFUL; p < dst + ph[i].p_memsz; p += 0x1000)
            if (mm_user_ensure_page(cr3, p)) { kprintf("exec_into: OOM at %lx\n", p); goto fail; }
        /* CR3 switch window: interrupts off locally with flags saved,
         * so a tick can never observe the foreign address space and a
         * caller that entered with IF=0 is restored exactly. */
        { irqflags_t wflags = spin_save_irq();
        __asm__ volatile("mov %0, %%cr3" :: "r"((unsigned long)cr3) : "memory");
        kmemcpy((void *)dst, (char *)data + ph[i].p_offset,
                (unsigned long)ph[i].p_filesz);
        if (ph[i].p_memsz > ph[i].p_filesz)
            kmemset((void *)(dst + ph[i].p_filesz), 0,
                    (unsigned long)(ph[i].p_memsz - ph[i].p_filesz));
        __asm__ volatile("mov %0, %%cr3" :: "r"(saved_cr3) : "memory");
        spin_restore_irq(wflags); }
        if (ph[i].p_filesz > 0 && (ph[i].p_flags & PF_X) && nxr < ELF_MAX_SEGMENTS) {
            xr[nxr].start = dst;
            xr[nxr].end   = dst + ph[i].p_filesz;
            nxr++;
        }
        if (dst + ph[i].p_memsz > max_end) max_end = dst + ph[i].p_memsz;
    }
    if (max_end == 0) { kprintf("exec_into: no segments\n"); goto fail; }
    for (i = 0; i < nxr; i++)
        mm_user_set_exec(xr[i].start, xr[i].end, cr3);
    /* TEMPORARY torn-load probe (diagnosing concurrent-spawn #UD root
     * cause; removed once the writer is found): re-read every byte of
     * every PT_LOAD under the child CR3 and compare with the file
     * image. A mismatch names a torn copy or torn file buffer at load
     * time (with the failing offset); a full match proves the
     * corruption lands after publish (post-spawn writer). */
    for (i = 0; i < e->e_phnum; i++) {
        unsigned long dst;
        unsigned long want;
        unsigned long k;
        unsigned long badat = 0;
        int bad = 0;
        if (ph[i].p_type != PT_LOAD) continue;
        if (ph[i].p_filesz == 0) continue;
        dst = base + ph[i].p_vaddr;
        want = ph[i].p_filesz;
        { irqflags_t vflags = spin_save_irq();
        __asm__ volatile("mov %0, %%cr3" :: "r"((unsigned long)cr3) : "memory");
        for (k = 0; k < want; k++)
            if (((unsigned char *)dst)[k] != ((unsigned char *)data)[ph[i].p_offset + k]) { bad = 1; badat = k; break; }
        __asm__ volatile("mov %0, %%cr3" :: "r"(saved_cr3) : "memory");
        spin_restore_irq(vflags); }
        if (bad) kprintf("exec_into: VERIFY-FAIL seg %u dst %lx off %lx\n",
                         i, dst, badat);
    }
    {
        unsigned long b = ALIGN_UP(max_end, 0x1000);
        unsigned long lim = USER_HEAP_CEIL;
        unsigned long pad;
        if (DOOM_BACKBUF_ADDR < lim) lim = DOOM_BACKBUF_ADDR;
        if (b > lim) { kprintf("exec_into: brk over cap\n"); goto fail; }
        pad = aslr_brk_pages() * 0x1000UL;
        if (b + pad <= lim && b + pad >= b) b += pad;
        *brk_out = b;
    }
    if (base_out) *base_out = base;
    return (void *)(base + e->e_entry);
fail:
    /* IF is the caller's property: every CR3 window above restores its
     * own flags, so this path must not sti (the old bare sti enabled
     * interrupts mid-spawn whenever the caller had them off). */
    __asm__ volatile("mov %0, %%cr3" :: "r"(saved_cr3) : "memory");
    return 0;
}
