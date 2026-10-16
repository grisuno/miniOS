# `mcp/mutate_mcp.sh`

> Source: [mcp/mutate_mcp.sh:1](../../mcp/mutate_mcp.sh#L1) | language `sh` | coverage 100.0% | [API index](../index.md)

Mutation testing for the MiniOS MCP bridge.

Every mutant is injected into a private copy of minios_mcp.py and run against the unit and BDD suite. A mutant that survives (suite fully green) exposes a test gap.  Suites run in parallel (one worker per core, MUTATE_JOBS to override); each mutant gets its own pid file and addon state so the runs stay independent.  Mutation format: "name | sed -i expression | file"

## Contents

- **Functions:** [`run_one`](#run_one)

## Functions

<a id="run_one"></a>

### `run_one`

`function` | [mcp/mutate_mcp.sh:116](../../mcp/mutate_mcp.sh#L116)

```bash
run_one()
```

Each mutant runs the suite in its own directory with its own pid file and addon state, so the runs are independent and may execute in parallel.

The worker writes the exit code; the loop below maps it onto the verdict.

---
