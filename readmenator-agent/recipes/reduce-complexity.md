# Recipe: Reduce File Complexity

Target hotspot: `kernel/syscalls.c`
(complexity 0.6, centrality 0.7)

1. Read dependents: `grep -n 'kernel/syscalls.c' readmenator-agent/ARCHITECTURE*.md`
2. Extract functions/classes into new files in the same subsystem
3. Update imports
4. Regenerate: `readmenator .`
