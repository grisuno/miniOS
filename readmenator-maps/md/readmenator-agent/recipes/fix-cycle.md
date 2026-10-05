# Recipe: Fix a Dependency Cycle

Target cycle: `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`

1. Read the imports between these files: `grep -n '^import\|^from\|#include' progs/doomgeneric/r_data.h`, `grep -n '^import\|^from\|#include' progs/doomgeneric/r_state.h`
2. Move the shared symbols into a new leaf module both sides import
3. Verify: `readmenator . && grep -c 'Dependency Cycles' readmenator-agent/GOTCHAS.md`
