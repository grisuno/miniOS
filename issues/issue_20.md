# Issue #20: MiniFS: crash consistency (journaling or ordered-write guarantees)

- **State:** open
- **Created:** 2026-09-10T03:54:42Z
- **Updated:** 2026-09-10T03:54:42Z
- **Labels:** enhancement,filesystem

---

MiniFS has no journal. A power loss / QEMU kill between a data-block write and the block/inode bitmap sync in kfclose (minifs_sync) can leave allocated blocks unreferenced or a directory entry pointing at a partially written inode.\n\nScope: define the smallest crash-consistency contract worth having for a teaching FS (ordered writes + sync-on-close audit vs full WAL), then implement + add a host fault-injection test.\n\nContext: fs/minifs.c, kfclose path, docs/adr/ (new ADR when decided).
