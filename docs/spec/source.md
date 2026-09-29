# Source contract: sibling repos, toolchain kernel-build plan, codec and utility tools

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

## Source Contract
The system spans this repository plus one sibling checkout per external
source: the toolchain ([miniGCC](https://github.com/grisuno/miniGCC),
[ld](https://github.com/grisuno/ld),
[cvm](https://github.com/grisuno/cvm)), the interpreters
([lua](https://github.com/lua/lua),
[micropython](https://github.com/micropython/micropython)), the UI and
audio libraries ([nuklear](https://github.com/Immediate-Mode-UI/Nuklear),
[nuked-opl3](https://github.com/nukeykt/Nuked-OPL3)), the browser
([FreeDom](https://github.com/grisuno/FreeDom)) and the reference-only
[raycastlib](https://github.com/grisuno/raycastlib). Every one of them
carries an `addons/<name>.yaml` (see Addon doctrine); DOOM, Quake 2 and
doomedit live in-repo or nested and carry one too. The build must be
reproducible from those upstreams alone, so:

- `make sources` clones the missing ones and `make sources-update` pulls
  them. Neither ever modifies a directory that already exists, so a checkout
  with local work is never clobbered.
- Every location is overridable (`MINIGCC_DIR`, `LD_DIR`, `CVM_REPO_DIR`,
  `CVM_DIR`, `LUA_DIR`, `MICROPYTHON_DIR`, `NUKLEAR_DIR`, `NUKED_OPL3_DIR`,
  `FREEDOM_DIR`, `RAYCASTLIB_DIR`) and so is every origin (`*_URL`, plus
  `MICROPYTHON_REF`/`LUA_REF` where a release is pinned).
  Nothing in the build assumes an absolute path.
- Everything on the ramdisk is regenerated from source: `minigcc.o`, `ld.o`
  and `cvm.o` from the sibling checkouts, and the demo programs from this
  repository's own C sources in `progs/`, driven through miniGCC and `ld`.
  The prebuilt objects in `progs/` are a convenience for a first boot, never
  an input the build depends on.
- Ramdisk content is owned here. Reaching into another project's test
  fixtures for files to ship would break the moment that project reorganizes
  them, which is exactly what happened when the image was built from
  `ld/tests/*.s`.
- `ramdisk.bin` lists the `Makefile` among its prerequisites: the file list
  lives there, so editing it must invalidate the image even when no
  individual file changed.  `minifs.bin` carries the same rule for the same reason.
- `progs/bin/` ships the command-path utilities: `cp`, `freedom`, `lzss`
  and `unlzss`, compiled from this repository's own sources in `progs/src/`
  through the miniGCC-to-ld chain, with the sources on the ramdisk too so the
  OS can rebuild the utilities from scratch without leaving the machine.
  The ramdisk tree is organized by kind: `objects/` (ET_REL toolchain),
  `bin/` (Linux ELFs + command path), `cvm/` (CVM modules), `src/` (C
  sources), `asm/` (miniGCC assembly), `docs/`.

### Toolchain kernel-build contract (sibling repos miniGCC/ld/cvm)
The end state is that the kernel itself builds through the hosted chain
(`minigcc.o` + `ld.o` on the ramdisk), with `cvm` in lockstep: any asm
miniGCC emits, `ld` assembles/links into both ELF and CVM, and `cvm2`
runs every bytecode `ld` generates. The three repos move as one; a gap
lands in all three specs together. Feature demand is survey-verified, not
assumed: `tools/kernel_feature_survey.py` scans this tree for function
pointers, asm constraints, wide calls, unions, `long long`, bitfields,
privileged mnemonics and section attributes, and every SDD claim about a
gap must reproduce through it first.

- miniGCC landed: `D`/`S` extended-asm constraints (fixed homes
  `%rdi`/`%rsi`, scratch pool excludes pinned registers, overflow is
  fail-closed `too many register asm operands`, `=&` earlyclobber
  accepted; template `%N` stays full-width, narrow outputs go through
  literal `%%dil`/`%%di`/`%%edi` stores). Proven by `tests/t_asm_ds.c`
  (+`neg_asm_ds.c`) in `test_all.sh`, 42/42 green, 5 scoped mutants dead.
  Still open, in survey order: function pointers (kernel tables
  `vfs_ops_t`/syscall dispatch; landed: `(*name)(params)` declarators
  for locals/globals/params/members/arrays, `call *%r10` codegen,
  fail-closed arithmetic/callability, proven by `tests/t_fnptr.c`
  (+4 `neg_fnptr*.c`) with 13 scoped mutants dead), >6-arg stack spill
  (`ksyscall` takes 7; landed: any fixed count through registers plus
  ordered stack spill with static parity padding, proven by
  `tests/t_args7.c` plus the `tools/test_call_align.py` probe,
  pad-inversion mutant dead), `unsigned`/`signed`/`long long` plus user
  `typedef` and struct-member capture (lexer folding with multi-declarator
  reseeds in statements, typedefs and `for`-init; struct `unsigned` capture
  with `long`-as-8; scalar/chained/fnptr alias records; proven by
  `tests/t_unsigned.c` + `t_struct_ul.c` + `t_longlong.c` +
  `neg_typedef_arrcont.c` with 12 scoped mutants dead, 2 documented
  equivalents); unions/bitfields are deferred with survey proof
  (only ring-3 host-built programs use them). Standing gate found while
  proving A7: miniGCC models plain `int` as 8 bytes (`sizeof(int) == 8`,
  64-bit wrap) but the kernel needs LP64 (`minifs.h` superblock
  `unsigned int` fields are 4 bytes on disk), so an LP64 follow-up (A8)
  gates B1; integer `<`/`>` also stay signed-only (u64 >= 2^63 compares
  wrong). Reusable probes live in `tools/` by contract:
  `tools/kernel_feature_survey.py` (survey-verified feature demand, the
  single source every SDD gap claim must reproduce through) and
  `tools/test_call_align.py` (6/7/8-arg direct plus 7-arg indirect stack
  alignment reporting).
- ld open: `call *`/`jmp *` encodings, privileged EA forms
  (`in`/`out`/`lidt`/`lgdt`/`mov-cr`, today documented future work),
  kernel object/link mode per its own spec.
- cvm open: indirect-call opcode + `ld -f cvm` lowering + parity matrix.
- Method per milestone: SDD spec, TDD failing test, scoped suite +
  scoped mutants on touched files only; full `mutate.sh` + `test_bdd.sh`
  run once at the very end because they take hours.

### Compression tools (`lzss` / `unlzss`)
`progs/src/lzss.c` is a single source that builds two command-path binaries:
the linker emits the same program as `bin/lzss` and `bin/unlzss`, and the
program selects its mode from `argv[0]` (any invocation path containing
`unlzss` decodes; `-d` forces decode explicitly).

- The codec is Okumura LZSS (window `LZSS_N` 2048, lookahead `LZSS_F` 17,
  threshold `LZSS_P` 1, MSB-first bit stream) so in-OS output interops with
  a host reference implementation; the window is pre-filled with 0x20
  exactly as the reference.
- The on-disk format is fail-closed: 4-byte magic `LZS1`, then the original
  size as a little-endian u32, then the bit stream. `unlzss` rejects a bad
  magic, a truncated stream and any declared size larger than the expansion
  bound derived from the input length (`LZSS_EXPAND_NUM`/
  `LZSS_EXPAND_DEN`), so a hostile header can never drive an oversized
  allocation, and a stream that would write past the declared size aborts
  before touching the output file.
- The codec works whole-file in memory (bounded, one `malloc` per side,
  sized from the input file and the derived expansion bound), compresses
  only when the result is reported with exact byte counts, and every I/O
  shortfall is a diagnostic plus a nonzero exit code, never a partial
  silent write. Past the first input MB the encoder prints one
  `lzss: <bytes>...` heartbeat per MB (the match search is O(window) per
  byte, so a multi-MB file takes a while and must never look wedged);
  small-file output is a single result line. Proven on `DOOM1.WAD`
  (4196020 -> 2349321 bytes, `unlzss` back byte-identical by `hash`).

### Compression tools (`lz4` / `unlz4`)
`progs/src/lz4.c` builds `bin/lz4` and `bin/unlz4` from a single source, with
the same `argv[0]` dispatch as `lzss` (any invocation path containing
`unlz4` decodes; `-d` forces decode). The codec itself lives in the kernel
(`lz4_kernel.c`, the same one MiniFS uses), so the tools are thin syscall
front-ends over two MiniOS syscalls, 216 `lz4_compress` and 217
`lz4_decompress`, which mirror `minifs_compress`/`minifs_decompress` byte
for byte. A call passes a user pointer validated to lie inside the user
window; a violating pointer returns `-EFAULT`.

- The on-disk block is the MiniFS block format, so `lz4` output interops
  with the filesystem's own LZ4 blocks: a 4-byte little-endian original
  size, then the raw LZ4 stream. `lz4_compress` refuses to write (returns
  0) unless the compressed stream is strictly shorter than the input, and
  `lz4_decompress` refuses a header whose declared size exceeds the output
  capacity or a stream that fails to decode to exactly that size.
- The front-ends work whole-file in memory (one `malloc` per side, the
  output side sized from `LZ4_COMPRESSBOUND` or the declared size), report
  exact byte counts, and every I/O shortfall or implausible declared size
  is a diagnostic plus a nonzero exit code, never a partial silent write.
- The ld stub set grows the `lz4_compress`/`lz4_decompress` entries (216,
  217) beside the other MiniOS syscalls, so the toolchain and the ramdisk
  binary rebuild together.
- The kernel `lz4_kernel.c` decompressor handles the literal-only tail of a
  stream correctly (a valid LZ4 block may end with a final literal sequence
  and no trailing match), so its own compressor round-trips and its output
  interops with a host reference decoder.

### Zip builtins (`unzip` / `zip`)
The shell's `unzip` and `zip` builtins read and write ZIP archives through
the miniz zip library, compiled into the kernel as a pristine upstream
amalgamation (3.0.2) in `third_party/miniz/` with the allocator redirected to
the kernel heap and stdio/time stripped (`MINIZ_NO_STDIO`, `MINIZ_NO_TIME`).
`miniz_impl.c` applies every knob through macros, the same pattern as the stb
wrapper; the amalgamated header forward-declares the writer's internal state,
so the heap writer's output buffer is exposed through two accessors
(`mz_zip_writer_mem_ptr`/`mz_zip_writer_mem_size`) defined where the full
struct is visible.

- Usage: `zip <out.zip> <file...>` stores each file (under its sanitized
  relative name) with the default compression level; `unzip <archive.zip>
  [dir]` extracts into `dir` (default the cwd), creating missing directories,
  and `unzip -l <archive.zip>` lists the entries. Both builtins work
  whole-file in memory over the unified file API (ramdisk first, MiniFS
  fallback), matching the compression tools contract: the archive is fully
  validated before any entry is published, output is written only after the
  whole archive was read, and every failure path reports a diagnostic and
  releases. The ld stub set is untouched: the builtins are shell features,
  not toolchain programs.
- Entry names are hostile data. Each is normalized to forward slashes,
  stripped of leading `/` and `./` repetitions, and **rejected when a
  component is `.`/`..` or empty** (`zip_sanitize_name`), so a crafted
  archive can never write outside the directory the user named — an absolute
  name degrades to a relative one, a traversal name is skipped. The BDD
  fixture `etc/hostile.zip` (generated by `tools/gen_zip_fixtures.py`, one
  entry `../escape.txt` beside a plain file, a directory marker and an
  absolute name) proves `escape.txt` is never created.
- `etc/host.zip` is a second generated fixture: a host-produced archive with
  a nested directory, proving the extractor interops with a reference ZIP
  writer and not just its own output. Both fixtures are regenerated from
  source at build time (fixed timestamps, reproducible) like the desktop
  icons.
- Fail-closed surface: a non-zip input is `unzip: <f>: not a zip archive`, a
  missing file is `unzip: <f>: cannot read`, an entry whose declared size does
  not match what the extractor produced aborts that entry, and a destination
  that is an existing file is refused. The mutation suite kills a traversal
  bypass (the hostile fixture), a bad-magic accept and a skipped finalize.

### JSON tool (`json`)
`bin/json` is a self-contained JSON validator, pretty-printer and query tool
built from `progs/src/json.c` through the miniGCC-to-ld chain; like DOOM and
MicroPython it ships on MiniFS (bare-name command at the MiniFS root), not on
the size-budgeted ramdisk. It is written
in the miniGCC subset, which has no structs, so the parsed value is a flat
node table of parallel arrays (`js_type`/`js_num`/`js_str`/`js_key`/
`js_first`/`js_count`/`js_next`); object members keep their key in `js_key`
and their value in the node itself.

- Usage: `json <file>` validates and pretty-prints; `json <file> <path>`
  prints the value at a dotted path (`.a.b`, `.a.3`, bare `.a`). A missing
  path is `json: <path>: not found` with exit 1, never a crash.
- The parser is fail-closed: truncated input, a trailing non-whitespace
  token, an unbalanced `}`/`]` and an unknown escape all report
  `json: <file>: invalid JSON` with exit 1. String escapes (`\n \t \r \b \f
  \" \\ \/`, and `\u` mapped to `?`) decode into a bounded string pool, and
  the pretty-printer re-escapes them so its output is itself valid JSON.
- The node table, string pool and query segment are all size-bounded by named
  constants (`JS_MAX_NODES`, `JS_POOL`); an input that would exceed a bound
  is a diagnostic plus exit 1, never a silent overflow.
- cJSON (single-file, struct-based) was tried as a portable engine and does
  not compile under miniGCC (structs, `->`, `double`, `CJSON_PUBLIC`), which
  is why this hand-rolled flat-table parser exists.

### Encryption tool (`aes` / `unaes`)
`progs/src/aes.c` builds `bin/aes` and `bin/un aes` from a single source with
the same `argv[0]` dispatch as the other command pairs (a path containing
`unaes` decrypts; `-d` forces decrypt). Like DOOM, MicroPython and `json` it
ships on MiniFS (bare-name commands at the MiniFS root) instead of the
size-budgeted ramdisk.

- The cipher is AES-256 (NIST FIPS-197) written in the miniGCC subset: no
  structs, flat int arrays masked to bytes at every step, and an S-box
  generated procedurally from the GF(2^8) multiplicative inverse plus the
  FIPS-197 affine transform, so the file carries no magic tables.  Round
  expansion follows FIPS-197 for Nk=8/Nr=14, including the extra SubWord
  pass every Nk/2 words.
- The mode is CTR (NIST SP 800-38A): no padding, encrypt and decrypt share
  one code path, and the big-endian counter increments over the full block.
  Usage: `aes [-d] <key-hex64> <nonce-hex32> <src> <dst>`; a nonce must
  never repeat under the same key.  CTR gives confidentiality only, not
  authentication - a flipped ciphertext byte flips the matching plaintext
  byte, so integrity needs a MAC layered above this tool.
- The container is fail-closed: 4-byte magic `AES1`, then the original size
  as a little-endian u32, then the raw keystream XOR.  Decoding refuses a
  bad magic, a truncated header, and any body whose length does not equal
  the declared size exactly; key and nonce hex are length- and alphabet-
  validated before anything runs.
- Host verification lives in `tests/host_aes.sh`: the NIST F.5.5 CTR-AES256
  known answer, byte-for-byte ciphertext equality against OpenSSL across a
  multi-block stream, reverse-direction interop (OpenSSL ciphertext decoded
  by `unaes`), dispatch modes, empty input, and the fail-closed set.  Five
  one-line mutants of the codec (ShiftRows drop, polynomial, affine
  constant, AES-256 extra SubWord, size-mismatch check) all die against it.
