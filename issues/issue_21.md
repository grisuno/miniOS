# Issue #21: SMP: per-AP LAPIC timer calibration (remove BSP tick dependency)

- **State:** open
- **Created:** 2026-09-10T03:54:52Z
- **Updated:** 2026-09-10T05:00:13Z
- **Labels:** enhancement,smp

---

APs have no timer of their own by design: the only AP tick is the BSP 100 Hz IPI broadcast (smp.c). A per-AP LAPIC timer would allow decentralized scheduling, but a LAPIC count derived from PIT_HZ fires ~84 kHz under QEMU and wedges the machine (measured 2.6x slowdown + 176 percent host CPU on idle guest) — see CLAUDE.md SMP section.\n\nScope: proper per-AP calibration (divide-by + initial-count from PIT or TSC-deadline), storm guard, BDD proof (smp counters per CPU). Do NOT just divide PIT_HZ into the LAPIC.
