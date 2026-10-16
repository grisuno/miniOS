# Changelog

### Chores

  * binary sign (6329f2b) by grisun0
  * freedom ported gui (767379a) by grisun0
  * wiki (6fb5db3) by grisun0
  * graphrag like context to llm (620275d) by grisun0
  * readmenator: regenerated knowledge base (db67df2) by grisun0
  * FreeDom GUI on MiniOS: Linux ABI for threads, sandbox, sockets and TLS (041956e) by grisun0
  * security fix / docs / some new branches (7c197c4) by grisun0
  * bug fixing in makefile (f352c8e) by grisun0
  * bug fixing in makefile (616379d) by grisun0
  * bug fixing in makefile (f38253b) by grisun0
  * bug fixing in makefile (65a2106) by grisun0
  * bug fixing in makefile (0711278) by grisun0
  * new indexer in doc (17272ba) by grisun0
  * mtop (aac82d2) by grisun0
  * uefi (9f9a1ff) by grisun0
  * usb (aad43a1) by grisun0
  * usb (f7a5e14) by grisun0
  * docs (6e61698) by grisun0
  * some improvements (57e0136) by grisun0
  * mutate: ldso-static-rejected gates the ET_EXEC load fix (4994526) by grisun0
  * T8 L3 fix: do not reject ET_EXEC (base 0) in ldso_bind_into (90210fc) by grisun0
  * ramdisk: deflate-compress payloads, inflate once at boot (c0809de) by grisun0
  * T8 spec: import pruning landed, body pruning deferred, size verdict (c919dcd) by grisun0
  * T8 spec: L4 toolchain landed (-runtime, -shared exports, -d override) + pruning finding (b9fe72d) by grisun0
  * T8 L3: in-kernel minimal dynamic linker (ld.so, functions only) (8d13a9c) by grisun0
  * T8 spec as-built: L1 landed, L2 PLT/GOT+GLOB_DAT, rela/GOT overlap invariant (636f4f3) by grisun0
  * T8 spec: minimal dynamic linking L1-L4 (functions only, no miniGCC changes) (23e7d0b) by grisun0
  * T5 slices 1-2: pcache store + file-backed mmap sharing (2b88cbd) by grisun0
  * some improvements (ea5f0b7) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (6367bc8) by grisun0
  * bump llocator or arena allocator (166ab1b) by grisun0
  * doc (65d9cbf) by grisun0
  * fullscreen doom & quake2 (f927709) by grisun0
  * Fuga de ld (389a891) by grisun0
  * Dashboard with command execution ;) (0de9de5) by grisun0
  * Doc(auto) KNOWLEADGE_BASE.md README.md and agentic documentation (cb9c37b) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (45365ef) by grisun0
  * Doc(auto) KNOWLEADGE_BASE.md README.md and agentic documentation (8ac97d9) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (5da718d) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (61ad9f4) by grisun0
  * FAT32 on real disk plus read-only ext4, shared image backend (5be9a30) by grisun0
  * 1. execve(59) — SHIPPED, probado live do_execve (kernel/sched.c) + wrapper sys_linux_execve + exec_enter (arch/x86/ctx_sw.S). Reemplaza la imagen in place: ventana fresca, VMA/brk/stack/FPU/FSBASE/nombre reconstruidos, entra por user_trampoline sin retornar. ET_REL→-ENOEXEC, threads/pid0→-ENOSYS, argv 32×255 con copia por byte (anti-TOCTOU), siblings CLONE_VM mueren como en Linux. Prueba: mrun bin/execho.elf (fork→exec lxhello argc=2→reap 2→ghost-exec 42, execho: ok exit 0) y execthr.elf (thread girando + exec, Hello exit 2). Mutante execve-never-replaces muerto. Dos bugs reales cazados depurándolo: un doble-free de mi propio scaffolding y el hazard de jmp con operando en C-inline-asm (documentados en CLAUDE.md). 2. ASLR userspace — SHIPPED, probado live aslr_mix (TSC+ticks+contador) en sched.c: stack 1..4096 B, brk 1..256 págs, mmap hasta 255, base ET_DYN hasta 47 slots 2MB. Enganchado en los tres constructores (run/mrun/execve). Prueba: aslr.c self-exec chain, gen1 compara (aslr: ok, flake 1/65536). Mutante aslr-no-entropy muerto. Sin PIE in-tree: el slide DYN comparte mixer con pin pero espera prueba live (declarado). 3. FAT32 read-only — SHIPPED, probado live fs/fat32.c (~600 ln): BPB/FAT/8.3 con toda aritmética acotada, loopback ramdisk→MiniFS con regla basename, bytes por el driver fat: VFS real, fat ls|cat, fixture etc/fat.img generada reproducible. Pruebas: make test-fat (host, imagen sintética, multi-cluster, edges) + 2 escenarios BDD. Mutante fat-lfn-check-inverted muerto. De paso, el harness tenía un gap que me mordió (mutante filtrado al árbol por SOURCES incompleto) — cerrado + fs/fat32.c añadido. 4. SMP más allá de threads — SPEC + RED, no implementado Análisis completo: switch_to ya cambia CR3/FPU/FS, pero la vista mm (g_brk, user_mmap_cur, raíces VMA) es global — dos CPUs con dos procs aislados se la pisan en cada preempt. Token/gang serializan (= throughput uniprocesador, inútil). Lo correcto son vistas per-CPU (112 sitios, 8 ficheros) y eso sin la validación de horas es corrupción silenciosa: no lo rusheo. Queda en CLAUDE.md como SMP Beyond Threads con enumeración, protocolo, prueba (burn.c, checksum 417386880, ya BDD-pinned bajo -smp 2) y mutantes nominales. Bonus: burn.c + escenario mixto existen y pasan. (94123b3) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (6e1ab74) by grisun0
  * vedit improvements, search and meta functions (b18085c) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (2775a93) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (1d66811) by grisun0
  * 1. Pipes + 2> — headers/pipe.h (pure ring, make test-pipe), KFILE pipe ends with refcounted shared ring in fs/kfile.c, Linux pipe/dup/dup2 (22/32/33) in kernel/syscalls.c, sequential-capture pipelines in kernel/shell.c (echo hi | cat works, two doors per direction for ET_REL vs ET_EXEC), 2> alias, cat stdin mode. 5 mutants die. 2. Panic screen — headers/panic.h + kernel/panic.c (frame-pointer walk, validated ranges, re-entry halt), fault handler paints vector/RIP/RSP/5 returns on FB/VGA/serial then halts; panic builtin demos it. 3 mutants die. 3. Dynamic VFS — open refcounts + vfs_lock, real longest-prefix-first (was first-match despite the doc claim), mount/unmount/vfstest, mem: driver, pinned root, append-pos rebase. 3 mutants die. 4. schedtop threads — tgid (lowest pid sharing VMA view) + T/P column. 1 mutant dies. 5. TCP server + httpd — LISTEN/SYN_RCVD states, bind/listen/accept (49/50/43), net_test_inject_tcp, headers/httpd.h wire contract, httpd builtin + --selftest (no NIC needed). Live hostfwd blocked by environment (slirp accepts, never delivers; rx=0). 4 mutants die. 6. Clipboard — kernel/clip.c, syscalls 249/250 (ABI v9), wl_clip_* wire messages, clip builtin. 4 mutants die. App wiring (terminal select, vedit paste) is Phase 2. 7. CoW fork — kernel/mm/cow.c (512-entry table, NX-preserving share, fenced #PF resolve), do_fork + vma_ctx_copy, fork_trampoline (zeroes rax — switch_to doesn't restore it), mm_copy_user_page NX fix, forktest.elf proves both-direction isolation. 3 mutants die. Hard-won mechanisms documented in CLAUDE.md (fenced resolve, rax trampoline, NX preservation). 8. Hardware — drivers/pci.h dedup (rtl8139 converted), drivers/virtio_blk.c (legacy queue; KASLR-DMA lesson: header/status must be heap), vblk builtin + BDD slice, boot/uefi_stub.c + uefi.img + scenario_uefi (MS ABI, 24-byte header, u32 = unsigned int lessons kept in CLAUDE.md). 5 mutants die. USB-HID/E1000/AHCI surveyed, TrueType stays build-time. (fcb0634) by grisun0
  * Update README.md (7ad53b2) by Grisuno
  * Update README.md (cb33c14) by Grisuno
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (2df5533) by grisun0
  * kvm mode bug fixing (c212305) by grisun0
  * Update README.md (0afaf4b) by Grisuno
  * Update README.md (42f1b76) by Grisuno
  * Update README.md (890d94c) by Grisuno
  * Update README.md (2085305) by Grisuno
  * optimize pokemon (3c42beb) by grisun0
  * flicker (6dc8904) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (7722f82) by grisun0
  * jumping icons in dock xD (2891a21) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (2fce389) by grisun0
  * doom with sound blaster 16 melody :D (78ca03f) by grisun0
  * quake2 with sound :D (f5741d0) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (359afb9) by grisun0
  * piano works like a charm (becd285) by grisun0
  * Update README.md (d6c2839) by Grisuno
  * Update README.md (3b959af) by Grisuno
  * Update README.md (230a9c2) by Grisuno
  * Update README.md (b51c154) by Grisuno


_Generated by [deploynator](https://github.com/grisuno/deploynator)_