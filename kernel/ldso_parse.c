/** Docstring: kernel/ldso_parse.c -- pure dynamic-table parsing (T8 ld.so).
 *
 * Implements headers/ldso.h with no allocation and no kernel calls, so
 * the host unit test exercises the exact code the loader runs. All
 * multi-byte reads are little-endian with explicit bounds; all size
 * arithmetic is overflow-checked before use; every corrupt or
 * unsupported input fails closed with a negative return, never a
 * half-filled struct.
 */

#include "ldso.h"

#define LDSO_EHSIZE 64
#define LDSO_PHENTSZ 56
#define LDSO_DYN_ENT 16
#define LDSO_HASH_HDR 8

static unsigned ldso_rd16(const unsigned char *p) {
    return (unsigned)p[0] | ((unsigned)p[1] << 8);
}

static unsigned long ldso_rd32(const unsigned char *p) {
    return (unsigned long)p[0] | ((unsigned long)p[1] << 8) |
        ((unsigned long)p[2] << 16) | ((unsigned long)p[3] << 24);
}

static unsigned long long ldso_rd64(const unsigned char *p) {
    return (unsigned long long)ldso_rd32(p) |
        ((unsigned long long)ldso_rd32(p + 4) << 32);
}

static int ldso_slice(const unsigned char *file, unsigned long long fsize,
        unsigned long long off, unsigned long long len,
        const unsigned char **out) {
    if (len > fsize || off > fsize - len) return -1;
    *out = file + off;
    return 0;
}

static int ldso_valid_ehdr(const unsigned char *file,
        unsigned long long fsize) {
    const unsigned char *e;
    unsigned type;
    if (ldso_slice(file, fsize, 0, LDSO_EHSIZE, &e)) return -1;
    if (e[0] != 0x7F || e[1] != 'E' || e[2] != 'L' || e[3] != 'F') return -1;
    if (e[4] != 2 || e[5] != 1) return -1;
    type = ldso_rd16(e + 16);
    if (type != LDSO_ET_EXEC && type != LDSO_ET_DYN) return -1;
    if (ldso_rd16(e + 18) != LDSO_EM_X86_64) return -1;
    if (ldso_rd16(e + 54) < LDSO_PHENTSZ) return -1;
    return 0;
}

int ldso_vaddr_to_offset(const unsigned char *file,
        unsigned long long fsize, unsigned long long va,
        unsigned long long *off) {
    const unsigned char *e;
    unsigned long long phoff;
    unsigned phnum;
    unsigned i;
    if (!file || !off) return -1;
    if (ldso_valid_ehdr(file, fsize)) return -1;
    if (ldso_slice(file, fsize, 0, LDSO_EHSIZE, &e)) return -1;
    phoff = ldso_rd64(e + 32);
    phnum = ldso_rd16(e + 56);
    if (phnum > 64) return -1;
    if (phoff > fsize) return -1;
    if ((unsigned long long)phnum * LDSO_PHENTSZ > fsize - phoff) return -1;
    for (i = 0; i < phnum; i++) {
        const unsigned char *p = file + phoff + (unsigned long long)i * LDSO_PHENTSZ;
        unsigned long long ptype = ldso_rd32(p);
        unsigned long long poff = ldso_rd64(p + 8);
        unsigned long long pvaddr = ldso_rd64(p + 16);
        unsigned long long pmemsz = ldso_rd64(p + 40);
        if (ptype != LDSO_PT_LOAD) continue;
        if (pmemsz == 0) continue;
        if (va < pvaddr || va - pvaddr >= pmemsz) continue;
        if (poff > fsize) return -1;
        if (va - pvaddr > fsize - poff) return -1;
        *off = poff + (va - pvaddr);
        return 0;
    }
    return -1;
}

int ldso_segments(const unsigned char *file, unsigned long long fsize,
        LdsoSeg *segs, unsigned ncap, unsigned *nseg) {
    const unsigned char *e;
    unsigned long long phoff;
    unsigned phnum;
    unsigned i;
    unsigned n = 0;
    if (!file || !segs || !nseg || ncap == 0) return -1;
    if (ldso_valid_ehdr(file, fsize)) return -1;
    if (ldso_slice(file, fsize, 0, LDSO_EHSIZE, &e)) return -1;
    phoff = ldso_rd64(e + 32);
    phnum = ldso_rd16(e + 56);
    if (phnum > 64) return -1;
    if (phoff > fsize) return -1;
    if ((unsigned long long)phnum * LDSO_PHENTSZ > fsize - phoff) return -1;
    for (i = 0; i < phnum; i++) {
        const unsigned char *p = file + phoff + (unsigned long long)i * LDSO_PHENTSZ;
        if (ldso_rd32(p) != LDSO_PT_LOAD) continue;
        if (n >= ncap) return -1;
        segs[n].offset = ldso_rd64(p + 8);
        segs[n].vaddr = ldso_rd64(p + 16);
        segs[n].filesz = ldso_rd64(p + 32);
        segs[n].memsz = ldso_rd64(p + 40);
        segs[n].flags = (unsigned)ldso_rd32(p + 4);
        if (segs[n].filesz > segs[n].memsz) return -1;
        if (segs[n].offset > fsize) return -1;
        if (segs[n].filesz > fsize - segs[n].offset) return -1;
        n++;
    }
    if (n == 0) return -1;
    *nseg = n;
    return 0;
}

int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize,
        unsigned long long *dyn_off, unsigned long long *dyn_size) {
    const unsigned char *e;
    unsigned long long phoff;
    unsigned long long filesz;
    unsigned phnum;
    unsigned i;
    if (!file || !dyn_off || !dyn_size) return -1;
    if (ldso_valid_ehdr(file, fsize)) return -1;
    if (ldso_slice(file, fsize, 0, LDSO_EHSIZE, &e)) return -1;
    phoff = ldso_rd64(e + 32);
    phnum = ldso_rd16(e + 56);
    if (phnum > 64) return -1;
    if (phoff > fsize) return -1;
    if ((unsigned long long)phnum * LDSO_PHENTSZ > fsize - phoff) return -1;
    for (i = 0; i < phnum; i++) {
        const unsigned char *p = file + phoff + (unsigned long long)i * LDSO_PHENTSZ;
        unsigned long long poff;
        if (ldso_rd32(p) != LDSO_PT_DYNAMIC) continue;
        poff = ldso_rd64(p + 8);
        filesz = ldso_rd64(p + 32);
        if (filesz == 0 || filesz % LDSO_DYN_ENT != 0) return -1;
        if (ldso_slice(file, fsize, poff, filesz, &p)) return -1;
        *dyn_off = poff;
        *dyn_size = filesz;
        return 1;
    }
    return 0;
}

int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize,
        unsigned long long dyn_off, unsigned long long dyn_size,
        LdsoDynInfo *info) {
    const unsigned char *d;
    unsigned long long n;
    unsigned long long i;
    unsigned k;
    if (!file || !info) return -1;
    if (dyn_size == 0 || dyn_size % LDSO_DYN_ENT != 0) return -1;
    if (ldso_slice(file, fsize, dyn_off, dyn_size, &d)) return -1;
    n = dyn_size / LDSO_DYN_ENT;
    if (n > LDSO_MAX_DYN) return -1;
    for (k = 0; k < (unsigned)sizeof(*info); k++)
        ((unsigned char *)info)[k] = 0;
    for (i = 0; i < n; i++) {
        long long tag = (long long)ldso_rd64(d + i * LDSO_DYN_ENT);
        unsigned long long val = ldso_rd64(d + i * LDSO_DYN_ENT + 8);
        switch (tag) {
        case LDSO_DT_NEEDED:
            if (info->needed_count < LDSO_MAX_NEEDED)
                info->needed_off[info->needed_count++] = val;
            break;
        case LDSO_DT_SONAME:
            if (!info->has_soname) {
                info->soname_off = val;
                info->has_soname = 1;
            }
            break;
        case LDSO_DT_STRTAB:
            info->strtab_va = val;
            break;
        case LDSO_DT_SYMTAB:
            info->symtab_va = val;
            break;
        case LDSO_DT_STRSZ:
            info->strsz = val;
            break;
        case LDSO_DT_SYMENT:
            info->syment = val;
            break;
        case LDSO_DT_RELA:
            info->rela_va = val;
            info->has_rela = 1;
            break;
        case LDSO_DT_RELASZ:
            info->relasz = val;
            break;
        case LDSO_DT_RELAENT:
            info->relaent = val;
            break;
        case LDSO_DT_HASH:
            info->hash_va = val;
            break;
        case LDSO_DT_NULL:
            break;
        default:
            break;
        }
        if (tag == LDSO_DT_NULL) break;
    }
    return 0;
}

int ldso_sym_count(const unsigned char *file, unsigned long long fsize,
        unsigned long long hash_off, unsigned *nsyms) {
    const unsigned char *h;
    unsigned long nchain;
    if (!file || !nsyms) return -1;
    if (ldso_slice(file, fsize, hash_off, LDSO_HASH_HDR, &h)) return -1;
    if (ldso_rd32(h) == 0) return -1;
    nchain = ldso_rd32(h + 4);
    if (nchain < 2 || nchain > 100000) return -1;
    if (nchain > (fsize / LDSO_SYM_SIZE)) return -1;
    *nsyms = nchain;
    return 0;
}

int ldso_copy_str(const unsigned char *file, unsigned long long fsize,
        unsigned long long strtab_off, unsigned long long strsz,
        unsigned long long name_off, char *out, unsigned out_cap) {
    const unsigned char *tab;
    unsigned long long max;
    unsigned i = 0;
    if (!file || !out || out_cap == 0) return -1;
    if (strsz == 0 || strsz > fsize) return -1;
    if (ldso_slice(file, fsize, strtab_off, strsz, &tab)) return -1;
    if (name_off >= strsz) return -1;
    max = strsz - name_off;
    while (i < out_cap - 1 && (unsigned long long)i < max) {
        out[i] = (char)tab[name_off + i];
        if (out[i] == '\0') return 0;
        i++;
    }
    if ((unsigned long long)i < max && tab[name_off + i] == '\0') {
        out[i] = '\0';
        return 0;
    }
    return -1;
}

static int ldso_name_eq(const unsigned char *tab, unsigned long long strsz,
        unsigned long long name_off, const char *name) {
    unsigned i = 0;
    if (name_off >= strsz) return 0;
    for (;;) {
        unsigned char c = (name_off + i >= strsz) ? 0 : tab[name_off + i];
        if (name[i] == '\0') return c == '\0';
        if (c == '\0' || c != (unsigned char)name[i]) return 0;
        i++;
        if (i >= LDSO_NAME_LEN) return 0;
    }
}

int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize,
        unsigned long long symtab_off, unsigned nsyms,
        unsigned long long strtab_off, unsigned long long strsz,
        const char *name, unsigned long long *value) {
    const unsigned char *syms;
    const unsigned char *tab;
    unsigned long long total;
    unsigned i;
    if (!file || !name || !value) return -1;
    if (nsyms < 2) return -1;
    if (strsz == 0 || strsz > fsize) return -1;
    total = (unsigned long long)nsyms * LDSO_SYM_SIZE;
    if (total / LDSO_SYM_SIZE != nsyms) return -1;
    if (ldso_slice(file, fsize, symtab_off, total, &syms)) return -1;
    if (ldso_slice(file, fsize, strtab_off, strsz, &tab)) return -1;
    for (i = 1; i < nsyms; i++) {
        const unsigned char *s = syms + (unsigned long long)i * LDSO_SYM_SIZE;
        unsigned long name_off = ldso_rd32(s);
        unsigned info = s[4];
        unsigned bind = info >> 4;
        unsigned type = info & 15;
        unsigned shndx = (unsigned)s[6] | ((unsigned)s[7] << 8);
        if (bind != LDSO_STB_GLOBAL) continue;
        if (type != LDSO_STT_FUNC && type != LDSO_STT_NOTYPE) continue;
        if (shndx == LDSO_SHN_UNDEF) continue;
        if (ldso_name_eq(tab, strsz, name_off, name)) {
            *value = ldso_rd64(s + 8);
            return 1;
        }
    }
    return 0;
}

int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela) {
    if (!info || !nrela) return -1;
    if (!info->has_rela) {
        *nrela = 0;
        return 0;
    }
    if (info->relaent != LDSO_RELA_SIZE) return -1;
    if (info->relasz % LDSO_RELA_SIZE != 0) return -1;
    if (info->relasz / LDSO_RELA_SIZE > 100000) return -1;
    *nrela = (unsigned)(info->relasz / LDSO_RELA_SIZE);
    return 0;
}

int ldso_read_rela(const unsigned char *file, unsigned long long fsize,
        unsigned long long rela_off, unsigned nrela, unsigned idx,
        unsigned nsyms, LdsoRelaRow *row) {
    const unsigned char *r;
    unsigned long long info;
    unsigned type;
    unsigned sym;
    if (!file || !row) return -1;
    if (idx >= nrela) return -1;
    if (ldso_slice(file, fsize, rela_off + (unsigned long long)idx * LDSO_RELA_SIZE,
            LDSO_RELA_SIZE, &r)) return -1;
    info = ldso_rd64(r + 8);
    type = (unsigned)(info & 0xffffffffu);
    sym = (unsigned)(info >> 32);
    if (type != LDSO_R_GLOB_DAT && type != LDSO_R_JUMP_SLOT) return -2;
    if (sym == 0 || sym >= nsyms) return -1;
    row->offset = ldso_rd64(r);
    row->sym = sym;
    row->type = type;
    return 0;
}

void ldso_basename(char *out, const char *src) {
    unsigned n = 0;
    unsigned start = 0;
    unsigned i = 0;
    if (!out) return;
    if (!src) {
        out[0] = '\0';
        return;
    }
    while (src[i] != '\0' && i < 4096) {
        if (src[i] == '/') start = i + 1;
        i++;
    }
    while (src[start + n] != '\0' && n < LDSO_NAME_LEN - 1) {
        out[n] = src[start + n];
        n++;
    }
    out[n] = '\0';
}
