# Recipe: Reduce File Complexity

Target hotspot: `headers/kernel.h`
(complexity 1.0, centrality 0.9)

1. Read dependents: `grep -n 'headers/kernel.h' readmenator-agent/ARCHITECTURE.md`
2. Extract functions/classes into new files in the same subsystem
3. Update imports
4. Regenerate: `readmenator .`
