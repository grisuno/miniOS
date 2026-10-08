# Recipe: Reduce File Complexity

Target hotspot: `progs/doomgeneric/d_main.c`
(complexity 0.1, centrality 1.0)

1. Read dependents: `grep -n 'progs/doomgeneric/d_main.c' readmenator-agent/ARCHITECTURE*.md`
2. Extract functions/classes into new files in the same subsystem
3. Update imports
4. Regenerate: `readmenator .`
