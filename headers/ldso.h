/** Docstring: headers/ldso.h -- minimal dynamic-linking (T8 ld.so) contract.
 *
 * Pure ELF/dynamic-table parsing shared by the kernel loader and the host
 * unit test. Every function is bounds- and overflow-checked, allocates
 * nothing and touches no kernel state: raw file bytes in, validated facts
 * out. Fail-closed integers only: 0 means ok/found, negative means corrupt
 * or unsupported, so callers never act on half-parsed tables.
 *
 * Address model: MiniOS-built images are zero-based identity ET_DYN
 * (link VA equals file offset inside PT_LOAD). vaddr_to_offset still walks
 * PT_LOAD properly, so a foreign layout fails closed instead of aliasing.
 */

#ifndef LDSO_H
#define LDSO_H

#define LDSO_MAX_LIBS   8
#define LDSO_MAX_NEEDED 8
#define LDSO_NAME_LEN   64
#define LDSO_MAX_DYN    64
#define LDSO_FILE_MAX   (4u * 1024u * 1024u)
#define LDSO_INO_BASE   0x1000000

#define LDSO_ET_EXEC    2
#define LDSO_ET_DYN     3
#define LDSO_EM_X86_64  62
#define LDSO_PT_LOAD    1
#define LDSO_PT_DYNAMIC 2
#define LDSO_PF_X       1

#define LDSO_DT_NULL    0
#define LDSO_DT_NEEDED  1
#define LDSO_DT_HASH    4
#define LDSO_DT_STRTAB  5
#define LDSO_DT_SYMTAB  6
#define LDSO_DT_RELA    7
#define LDSO_DT_RELASZ  8
#define LDSO_DT_RELAENT 9
#define LDSO_DT_STRSZ   10
#define LDSO_DT_SYMENT  11
#define LDSO_DT_SONAME  14

#define LDSO_R_GLOB_DAT  6
#define LDSO_R_JUMP_SLOT 7

#define LDSO_STB_GLOBAL 1
#define LDSO_STT_NOTYPE 0
#define LDSO_STT_FUNC   2
#define LDSO_SHN_UNDEF  0
#define LDSO_SYM_SIZE   24
#define LDSO_RELA_SIZE  24

typedef struct {
    unsigned long long vaddr;
    unsigned long long filesz;
    unsigned long long memsz;
    unsigned long long offset;
    unsigned flags;
} LdsoSeg;

typedef struct {
    unsigned long long needed_off[LDSO_MAX_NEEDED];
    unsigned needed_count;
    unsigned long long soname_off;
    int has_soname;
    unsigned long long strtab_va;
    unsigned long long symtab_va;
    unsigned long long strsz;
    unsigned long long syment;
    unsigned long long rela_va;
    unsigned long long relasz;
    unsigned long long relaent;
    unsigned long long hash_va;
    int has_rela;
} LdsoDynInfo;

typedef struct {
    unsigned long long offset;
    unsigned sym;
    unsigned type;
} LdsoRelaRow;

/** Docstring: Locate the PT_DYNAMIC file range. Returns 1 with offsets on
 * success, 0 when the image carries no dynamic section (static binary,
 * not an error), -1 when any header, count or bound is corrupt. */
int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize,
    unsigned long long *dyn_off, unsigned long long *dyn_size);

/** Docstring: Translate a link VA through PT_LOAD into a file offset.
 * Returns 0 with the offset on success, -1 when no segment contains it
 * or any arithmetic overflows. */
int ldso_vaddr_to_offset(const unsigned char *file, unsigned long long fsize,
    unsigned long long va, unsigned long long *off);

/** Docstring: Collect PT_LOAD spans (at most ncap) for reservation and
 * GOT-range checks. Returns 0 with the count, -1 on corrupt headers. */
int ldso_segments(const unsigned char *file, unsigned long long fsize,
    LdsoSeg *segs, unsigned ncap, unsigned *nseg);

/** Docstring: Walk the dynamic array into info. Caps entries at
 * LDSO_MAX_DYN, keeps the first SONAME, records up to LDSO_MAX_NEEDED
 * NEEDED offsets. Returns 0 on success, -1 on truncation or overflow. */
int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize,
    unsigned long long dyn_off, unsigned long long dyn_size,
    LdsoDynInfo *info);

/** Docstring: Read the SYSV hash header at a file offset into bucket and
 * chain counts. The chain count is the dynamic symbol count. Returns 0
 * on success, -1 when the table is truncated or claims no symbols. */
int ldso_sym_count(const unsigned char *file, unsigned long long fsize,
    unsigned long long hash_off, unsigned *nsyms);

/** Docstring: Bounded copy of one dynamic string (NEEDED/SONAME/symbol).
 * The NUL must land inside strsz. Returns 0 with a terminated buffer,
 * -1 on any out-of-range offset or missing terminator. */
int ldso_copy_str(const unsigned char *file, unsigned long long fsize,
    unsigned long long strtab_off, unsigned long long strsz,
    unsigned long long name_off, char *out, unsigned out_cap);

/** Docstring: Linear search of a dynamic symbol table by name. Accepts
 * GLOBAL FUNC/NOTYPE definitions only (v1 links functions, nothing
 * else). Returns 1 with st_value on hit, 0 on clean miss, -1 on any
 * corrupt table bound. */
int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize,
    unsigned long long symtab_off, unsigned nsyms,
    unsigned long long strtab_off, unsigned long long strsz,
    const char *name, unsigned long long *value);

/** Docstring: Validate the RELA header triple and report the row count.
 * Only 24-byte entries are supported (v1 emits exactly those).
 * Returns 0 with the count, -1 on any mismatch or overflow. */
int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela);

/** Docstring: Read one RELA row with full validation: row inside the
 * table, type GLOB_DAT/JUMP_SLOT (anything else is -2, unsupported),
 * symbol index below nsyms. Returns 0 on success. */
int ldso_read_rela(const unsigned char *file, unsigned long long fsize,
    unsigned long long rela_off, unsigned nrela, unsigned idx,
    unsigned nsyms, LdsoRelaRow *row);

/** Docstring: Basename normalization for registry keys ("a/b.so" to
 * "b.so", bounded, always terminated). Two spellings of one library
 * share one registry slot and one load. */
void ldso_basename(char *out, const char *src);

#endif
