#include "kernel.h"

/* ================================================================
 *  Symbol table — resolves names to kernel addresses
 * ================================================================ */

KSym  ksym_table[KSYM_MAX];
int   ksym_count;

void k_register_symbol(const char *name, void *addr) {
    if (ksym_count < KSYM_MAX) {
        ksym_table[ksym_count].name = name;
        ksym_table[ksym_count].addr = addr;
        ksym_count++;
    }
}

void *ksym_resolve(const char *name) {
    int i;
    for (i = 0; i < ksym_count; i++) {
        if (kstrcmp(ksym_table[i].name, name) == 0)
            return ksym_table[i].addr;
    }
    return 0;
}

/* ================================================================
 *  Program registry — maps names to ET_REL / ET_EXEC entry points
 * ================================================================ */

KProg kprog_table[KPROG_MAX];
int   kprog_count;

KProg *kprog_slot(const char *name) {
    int i;
    for (i = 0; i < kprog_count; i++)
        if (kstrcmp(kprog_table[i].name, name) == 0) return &kprog_table[i];
    if (kprog_count < KPROG_MAX) return &kprog_table[kprog_count++];
    return 0;
}

KProg *kprog_lookup(const char *name) {
    int i;
    for (i = 0; i < kprog_count; i++)
        if (kstrcmp(kprog_table[i].name, name) == 0) return &kprog_table[i];
    return 0;
}

void k_register_program(const char *name, prog_entry_t entry) {
    KProg *p = kprog_slot(name);
    if (!p) return;
    kstrncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = 0;
    p->entry = entry; p->proc_entry = 0; p->is_proc = 0;
}

void k_register_process(const char *name, void *proc_entry) {
    KProg *p = kprog_slot(name);
    if (!p) return;
    kstrncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = 0;
    p->entry = 0; p->proc_entry = proc_entry; p->is_proc = 1;
}

int k_spawn(const char *name, int argc, char **argv) {
    int i;
    for (i = 0; i < kprog_count; i++) {
        if (kstrcmp(kprog_table[i].name, name) == 0) {
            if (kprog_table[i].is_proc)
                return k_exec_user(kprog_table[i].proc_entry, argc, argv);
            return k_run_rel(kprog_table[i].entry, argc, argv);
        }
    }
    return -1;
}
