# `tools/mutate.sh`

> Source: [tools/mutate.sh:1](../../tools/mutate.sh#L1) | language `sh` | coverage 33.3% | [API index](../index.md)

Mutation testing for MiniOS.

Each mutation is applied to the source in place, the disk image is rebuilt and the behavioural suite is run in fail-fast mode. A mutant that survives a full green suite exposes a gap that must be closed by adding a scenario, never by deleting the mutant.  The sources are backed up before the first mutation and restored on every exit path, including interrupts. A mutation whose expression matches nothing is reported as broken rather than surviving: `sed -i` exits zero when it changes nothing, which would otherwise rebuild pristine sources and look like a test gap.  Progress is persisted to a state file (default .mutate-state in the repo root, overridable with --state or MINIOS_MUTATE_STATE). A run therefore RESUMES where it left off: mutants already recorded are skipped, so a timed-out run can be picked up without re-running the finished ones. The state file is just a list of "name outcome" lines and can be edited by hand to re-target work.  Usage: mutate.sh                     full run, resuming from the first mutant not yet recorded in the state file mutate.sh --from NAME         force-run from the mutant NAME onward, ignoring recorded state for those mutants mutate.sh --match REGEX       only run mutants whose name matches REGEX mutate.sh --limit N           run at most N mutants this invocation mutate.sh --state FILE        use FILE as the progress file mutate.sh --reset             clear the state file and run the full suite

## Contents

- **Functions:** [`usage`](#usage), [`restore_sources`](#restore_sources), [`cleanup`](#cleanup), [`record`](#record), [`find_index`](#find_index)

## Functions

<a id="usage"></a>

### `usage`

`function` | [tools/mutate.sh:51](../../tools/mutate.sh#L51)

```bash
usage()
```

---

<a id="restore_sources"></a>

### `restore_sources`

`function` | [tools/mutate.sh:139](../../tools/mutate.sh#L139)

```bash
restore_sources()
```

---

<a id="cleanup"></a>

### `cleanup`

`function` | [tools/mutate.sh:146](../../tools/mutate.sh#L146)

```bash
cleanup()
```

*Called by:* [`arity`](progs.lisp.lisp.c.md#arity), [`main`](progs.lisp.lisp.c.md#main)

---

<a id="record"></a>

### `record`

`function` | [tools/mutate.sh:570](../../tools/mutate.sh#L570)

```bash
record()
```

---

<a id="find_index"></a>

### `find_index`

`function` | [tools/mutate.sh:576](../../tools/mutate.sh#L576)

```bash
find_index()
```

Locate a mutant by name.

---
