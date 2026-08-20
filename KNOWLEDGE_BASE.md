# Polyglot Codebase Knowledge Graph

> Generated offline by **readmenator**. Supports C, C++, Python, Go, Rust, JS/TS, Java, C#, Shell, PHP, Dart, GDScript, Nim, ASM, Ruby, Swift, Kotlin, Scala, Lua, Elixir.
> No LLMs. No tokens. Pure static analysis. See more [here](https://github.com/grisuno/ReadMenator)

**Total Files Parsed:** 49 | **Total Symbols Extracted:** 1105 | **Total Imports:** 96
 | **Resolved Imports:** 1

<!-- ranking_model: v1.0 | weights: {ppr:0.45,auth:0.2,test:0.15,doc:0.1,fresh:0.1} | alpha:0.85 | commit:75d209c | date:2026-07-18 -->


## Table of Contents

1. [Statistics Dashboard](#statistics-dashboard)
2. [Architectural Layers](#architectural-layers)
3. [Ranked Context](#ranked-context)
4. [God Nodes](#god-nodes)
5. [Community Analysis](#community-analysis)
6. [Surprising Connections](#surprising-connections)
7. [Suggested Questions](#suggested-questions)
8. [Taint Propagation Map](#taint-propagation-map)
9. [Hotspot Analysis](#hotspot-analysis)
10. [Change Impact Analysis](#change-impact-analysis)
11. [Suggested Linting Rules](#suggested-linting-rules)
12. [Orphans](#orphans)
13. [Query Recipes](#query-recipes)
14. [Structural Knowledge Map](#structural-knowledge-map)
15. [UML Class Diagram](#uml-class-diagram)
16. [Code Property Graph](#code-property-graph)
17. [Architecture Reference](#architecture-reference)
    - [C (20 files)](#c-20-files)
    - [H (7 files)](#h-7-files)
    - [PY (10 files)](#py-10-files)
    - [S (7 files)](#s-7-files)
    - [SH (5 files)](#sh-5-files)

---

## Statistics Dashboard

| Metric | Value |
|--------|-------|
| Total Files | 49 |
| Total Symbols | 1105 |
| Total Imports | 96 |
| Call Edges | 1398 |
| Inheritance Edges | 15 |
| Languages | 6 |
| Avg Symbols/File | 22.6 |
| Avg Imports/File | 2.0 |
| Resolved Imports | 1 |

### Top Files by Import Count (Fan-Out)

| File | Imports | Symbols | Language |
|------|---------|---------|----------|
| `test_minios_mcp.py` | 15 | 95 | py |
| `minios_mcp.py` | 11 | 48 | py |
| `tls_test.c` | 11 | 23 | c |
| `tls_test.py` | 10 | 16 | py |
| `tls_port.h` | 8 | 27 | h |
| `minios_addons.py` | 7 | 16 | py |
| `mcp_dbg_driver.py` | 6 | 6 | py |
| `mcp_dogfood.py` | 6 | 6 | py |
| `test_http_server.py` | 5 | 3 | py |
| `kernel.c` | 4 | 222 | c |

### Top Files by Imported-By Count (Fan-In)

| File | Imported By | Symbols | Language |
|------|-------------|---------|----------|
| `tls.h` | 5 | 42 | h |
| `tls_port.h` | 4 | 27 | h |
| `kernel.h` | 3 | 19 | h |
| `net.h` | 3 | 34 | h |
| `bootdefs.h` | 1 | 76 | h |
| `tls_roots.h` | 1 | 0 | h |
| `tls_test_roots.h` | 1 | 0 | h |

---

## Architectural Layers

Auto-detected from path patterns, naming conventions, and imported frameworks.

| Layer | Files |
|-------|-------|
| utility | 36 |
| testing | 8 |
| infrastructure | 2 |
| presentation | 2 |
| data_access | 1 |

### utility

- `app.py` (py, 0 symbols)
- `bootdefs.h` (h, 76 symbols)
- `bootloader.c` (c, 2 symbols)
- `cvm_host.c` (c, 45 symbols)
- `install.sh` (sh, 0 symbols)
- `kernel.c` (c, 222 symbols)
- `kernel.h` (h, 19 symbols)
- `__init__.py` (py, 0 symbols)
- `mcp_dogfood.py` (py, 6 symbols)
- `minios_addons.py` (py, 16 symbols)
- `minios_mcp.py` (py, 48 symbols)
- `mutate_mcp.sh` (sh, 1 symbols)
- `mkroots.sh` (sh, 0 symbols)
- `mutate.sh` (sh, 2 symbols)
- `net.c` (c, 84 symbols)
- *... and 21 more*

### infrastructure

- `mcp_dbg_driver.py` (py, 6 symbols)
- `mkramdisk.py` (py, 2 symbols)

### testing

- `test_minios_mcp.py` (py, 95 symbols)
- `ftest.c` (c, 1 symbols)
- `test.c` (c, 2 symbols)
- `test_bdd.sh` (sh, 9 symbols)
- `test_http_server.py` (py, 3 symbols)
- `tls_test.c` (c, 23 symbols)
- `tls_test.py` (py, 16 symbols)
- `tls_test_roots.h` (h, 0 symbols)

### presentation

- `http.c` (c, 2 symbols)
- `http.s` (s, 3 symbols)

### data_access

- `ramdisk_data.c` (c, 0 symbols)

---

## Ranked Context

Files ranked by composite score for the current query context. The ranking combines Personalized PageRank (query relevance), global authority, test coverage, documentation coverage, and code freshness. Model: v1.0.

| Rank | File | Composite | PPR | Authority | Test | Doc |
|------|------|-----------|-----|-----------|------|-----|
| 1 | `mutate_mcp.sh` | 0.2000 | 0.0000 | 0.0000 | 0.00 | 2.00 |
| 2 | `tls_roots.h` | 0.1363 | 0.0558 | 0.0558 | 0.00 | 1.00 |
| 3 | `tls_test_roots.h` | 0.1363 | 0.0558 | 0.0558 | 0.00 | 1.00 |
| 4 | `minios_addons.py` | 0.1085 | 0.0804 | 0.0804 | 0.00 | 0.56 |
| 5 | `app.py` | 0.1000 | 0.0000 | 0.0000 | 0.00 | 1.00 |
| 6 | `mkroots.sh` | 0.1000 | 0.0000 | 0.0000 | 0.00 | 1.00 |
| 7 | `ftest.c` | 0.1000 | 0.0000 | 0.0000 | 0.00 | 1.00 |
| 8 | `hello.c` | 0.1000 | 0.0000 | 0.0000 | 0.00 | 1.00 |
| 9 | `http.c` | 0.1000 | 0.0000 | 0.0000 | 0.00 | 1.00 |
| 10 | `tls_x509.c` | 0.0891 | 0.0435 | 0.0435 | 0.00 | 0.61 |

---

## God Nodes

Most architecturally central files ranked by combined import/export degree and symbol richness.

| File | Score | Connections | PageRank |
|------|-------|-------------|----------|
| `kernel.c` | 30.2 | | 0.0000 |
| `tls_port.h` | 14.7 | | 0.0000 |
| `tls.h` | 14.2 | | 0.0000 |
| `net.c` | 12.4 | | 0.0000 |
| `tls_crypto.c` | 11.6 | | 0.0000 |
| `bootdefs.h` | 9.6 | | 0.0000 |
| `test_minios_mcp.py` | 9.5 | | 0.0000 |
| `net.h` | 9.4 | | 0.0000 |
| `freedom.s` | 9.1 | | 0.0000 |
| `tls.c` | 8.5 | | 0.0000 |

---

## Community Analysis

Files grouped by import-based community detection. Cohesion measures how tightly connected each community is internally.

### root (Cohesion: 0.62)

**5 files** in this community:

- `bootdefs.h` (h, 76 symbols)
- `kernel.c` (c, 222 symbols)
- `kernel.h` (h, 19 symbols)
- `net.c` (c, 84 symbols)
- `net.h` (h, 34 symbols)

### mcp (Cohesion: 1.00)

**2 files** in this community:

- `minios_addons.py` (py, 16 symbols)
- `minios_mcp.py` (py, 48 symbols)

### root (Cohesion: 0.77)

**8 files** in this community:

- `tls.c` (c, 25 symbols)
- `tls.h` (h, 42 symbols)
- `tls_crypto.c` (c, 76 symbols)
- `tls_port.h` (h, 27 symbols)
- `tls_roots.h` (h, 0 symbols)
- `tls_test.c` (c, 23 symbols)
- `tls_test_roots.h` (h, 0 symbols)
- `tls_x509.c` (c, 23 symbols)

---

## Surprising Connections

Files in different communities connected through 3+ indirect hops.

- `bootdefs.h` <-> `tls_roots.h` (4 hops, across 2 communities)
- `bootdefs.h` <-> `tls_test_roots.h` (4 hops, across 2 communities)
- `net.c` <-> `tls_roots.h` (4 hops, across 2 communities)
- `net.c` <-> `tls_test_roots.h` (4 hops, across 2 communities)
- `bootdefs.h` <-> `tls.c` (3 hops, across 2 communities)

---

## Suggested Questions

Auto-generated exploration prompts based on graph structure:

- What does kernel.c depend on, and what depends on it? (4 connections)
- What does tls_port.h depend on, and what depends on it? (6 connections)
- What does tls.h depend on, and what depends on it? (5 connections)
- How are the 5 files in 'root' related to each other?
- Why are bootdefs.h and tls_roots.h connected through 4 hops across 2 communities?

---

## Taint Propagation Map

Taint analysis traces how dangerous imports propagate through the codebase via transitive dependencies. Source files import dangerous modules directly; sink files receive the danger indirectly.

**Taint Sources:** 6 | **Taint Sinks:** 6 | **Propagation Paths:** 7

- `mcp_dbg_driver.py` imports `subprocess` (0 hop to `mcp_dbg_driver.py`) [high]
  Path: mcp_dbg_driver.py
- `mcp_dogfood.py` imports `subprocess` (0 hop to `mcp_dogfood.py`) [high]
  Path: mcp_dogfood.py
- `minios_addons.py` imports `subprocess` (0 hop to `minios_addons.py`) [high]
  Path: minios_addons.py
- `minios_mcp.py` imports `subprocess` (0 hop to `minios_mcp.py`) [high]
  Path: minios_mcp.py
- `minios_mcp.py` imports `subprocess` (1 hop to `minios_addons.py`) [high]
  Path: minios_mcp.py -> minios_addons.py
- `test_minios_mcp.py` imports `subprocess` (0 hop to `test_minios_mcp.py`) [high]
  Path: test_minios_mcp.py
- `tls_test.py` imports `subprocess` (0 hop to `tls_test.py`) [high]
  Path: tls_test.py

---

## Hotspot Analysis

Files ranked by combined complexity (symbol count) and centrality (connection count). High-scoring files are architecturally critical and may need refactoring attention.

| File | Complexity | Centrality | Combined | Symbols | Connections |
|------|-----------|------------|----------|---------|-------------|
| `mutate_mcp.sh` | 0.004 | 0.000 | 0.002 | 1 | 0 |
| `tls_roots.h` | 0.000 | 0.067 | 0.040 | 0 | 1 |
| `tls_test_roots.h` | 0.000 | 0.067 | 0.040 | 0 | 1 |
| `minios_addons.py` | 0.072 | 0.533 | 0.349 | 16 | 8 |
| `app.py` | 0.000 | 0.000 | 0.000 | 0 | 0 |
| `mkroots.sh` | 0.000 | 0.000 | 0.000 | 0 | 0 |
| `ftest.c` | 0.004 | 0.000 | 0.002 | 1 | 0 |
| `hello.c` | 0.004 | 0.000 | 0.002 | 1 | 0 |
| `http.c` | 0.009 | 0.000 | 0.004 | 2 | 0 |
| `tls_x509.c` | 0.104 | 0.133 | 0.121 | 23 | 2 |
| `test_minios_mcp.py` | 0.428 | 1.000 | 0.771 | 95 | 15 |
| `minios_mcp.py` | 0.216 | 0.800 | 0.567 | 48 | 12 |
| `kernel.c` | 1.000 | 0.267 | 0.560 | 222 | 4 |
| `tls_port.h` | 0.122 | 0.800 | 0.529 | 27 | 12 |
| `tls_test.c` | 0.104 | 0.733 | 0.481 | 23 | 11 |

---

## Change Impact Analysis

Files sorted by how many other files would be affected if they changed. High-impact files should be changed with caution.

| File | Direct Dependents | Transitive Dependents | Total Impact |
|------|------------------|----------------------|--------------|
| `minios_addons.py` | 1 | 0 | 1 |
| `app.py` | 0 | 0 | 0 |
| `bootdefs.h` | 0 | 0 | 0 |
| `bootloader.c` | 0 | 0 | 0 |
| `cvm_host.c` | 0 | 0 | 0 |
| `install.sh` | 0 | 0 | 0 |
| `kernel.c` | 0 | 0 | 0 |
| `kernel.h` | 0 | 0 | 0 |
| `__init__.py` | 0 | 0 | 0 |
| `mcp_dbg_driver.py` | 0 | 0 | 0 |
| `mcp_dogfood.py` | 0 | 0 | 0 |
| `minios_mcp.py` | 0 | 0 | 0 |
| `mutate_mcp.sh` | 0 | 0 | 0 |
| `test_minios_mcp.py` | 0 | 0 | 0 |
| `mkramdisk.py` | 0 | 0 | 0 |

---

## Suggested Linting Rules

Automatically suggested linting and security rules based on patterns detected in the codebase. These can be exported as Semgrep rules using the `--export-rules` flag.

| Rule ID | Severity | Description | Language | Matches |
|---------|----------|-------------|----------|---------|
| `RM001` | info | Large number of functions in py: 169 total | py | 169 |
| `RM002` | info | Large number of functions in c: 446 total | c | 446 |
| `RM003` | info | Large number of functions in sh: 12 total | sh | 12 |
| `RM004` | info | Large number of functions in s: 101 total | s | 101 |
| `RM005` | info | Large number of functions in S: 38 total | S | 38 |
| `RM006` | info | Print statement found (consider logging instead) | python | 27 |

---

## Orphans

Files with no documentation or low connectivity. These are candidates for documentation investment or cleanup.

- `cvm_host.c` (45 symbols, no doc)
- `install.sh` (0 symbols, no doc)
- `__init__.py` (0 symbols, no doc)
- `mcp_dbg_driver.py` (6 symbols, no doc)
- `mcp_dogfood.py` (6 symbols, no doc)
- `mkramdisk.py` (2 symbols, no doc)
- `fib.c` (2 symbols, no doc)
- `fib.s` (3 symbols, no doc)
- `freedom.s` (91 symbols, no doc)
- `http.s` (3 symbols, no doc)
- `ldhello.c` (1 symbols, no doc)
- `ldhello.s` (2 symbols, no doc)
- `test.c` (2 symbols, no doc)
- `w1.c` (1 symbols, no doc)
- `w1.s` (2 symbols, no doc)
- `ramdisk_data.c` (0 symbols, no doc)
- `test_http_server.py` (3 symbols, no doc)
- `tls_test.py` (16 symbols, no doc)

---

## Query Recipes

Example queries you can run against this knowledge base using the ranking engine:

```
# Find files most relevant to a concept
readmenator query "Where is the import resolver implemented?"

# Rank files by relevance to a topic
readmenator query "How does documentation generation work?"

# Explain why a file ranks highly
readmenator query "explain readmenator/_documentation.py"

# Trace dependency paths with ranked context
readmenator query "path from CLI to exporter"
```

The ranking model uses the following signals:

- **Personalized PageRank** (45% weight): query-specific relevance via seed propagation
- **Global Authority** (20% weight): structural importance via standard PageRank
- **Test Coverage** (15% weight): fraction of symbols referenced in test files
- **Doc Coverage** (10% weight): presence of docstrings and file-level docs
- **Freshness** (10% weight): recent modification activity

Results include score decomposition and justification paths for each ranked item.

---

## Structural Knowledge Map

```mermaid
graph TD
    classDef mod fill:#1e1e1e,stroke:#ff6666,stroke-width:2px,color:#fff;
    classDef cls fill:#2d2d2d,stroke:#4ec9b0,stroke-width:2px,color:#fff;
    classDef fn fill:#333,stroke:#dcdcaa,stroke-width:1px,color:#dcdcaa;
    classDef ext fill:#111,stroke:#666,stroke-dasharray:5 5,color:#aaa;
    mcp_test_minios_mcp_py["test_minios_mcp.py (py)"]
    class mcp_test_minios_mcp_py mod;
    mcp_test_minios_mcp_py_load_module["load_module"]
    class mcp_test_minios_mcp_py_load_module fn;
    mcp_test_minios_mcp_py --> mcp_test_minios_mcp_py_load_module
    mcp_test_minios_mcp_py_have_qemu["have_qemu"]
    class mcp_test_minios_mcp_py_have_qemu fn;
    mcp_test_minios_mcp_py --> mcp_test_minios_mcp_py_have_qemu
    mcp_test_minios_mcp_py_MCPServer["MCPServer"]
    class mcp_test_minios_mcp_py_MCPServer cls;
    mcp_test_minios_mcp_py --> mcp_test_minios_mcp_py_MCPServer
    mcp_test_minios_mcp_py_TestProtocol["TestProtocol"]
    class mcp_test_minios_mcp_py_TestProtocol cls;
    mcp_test_minios_mcp_py --> mcp_test_minios_mcp_py_TestProtocol
    mcp_test_minios_mcp_py_TestValidation["TestValidation"]
    class mcp_test_minios_mcp_py_TestValidation cls;
    mcp_test_minios_mcp_py --> mcp_test_minios_mcp_py_TestValidation
    subgraph community_1 ["mcp"]
    mcp_minios_mcp_py["minios_mcp.py (py)"]
    class mcp_minios_mcp_py mod;
    end
    subgraph community_2 ["root"]
    tls_test_c["tls_test.c (c)"]
    class tls_test_c mod;
    tls_test_py["tls_test.py (py)"]
    class tls_test_py mod;
    tls_port_h["tls_port.h (h)"]
    class tls_port_h mod;
    mcp_minios_addons_py["minios_addons.py (py)"]
    class mcp_minios_addons_py mod;
    mcp_mcp_dbg_driver_py["mcp_dbg_driver.py (py)"]
    class mcp_mcp_dbg_driver_py mod;
    mcp_mcp_dogfood_py["mcp_dogfood.py (py)"]
    class mcp_mcp_dogfood_py mod;
    test_http_server_py["test_http_server.py (py)"]
    class test_http_server_py mod;
    end
    subgraph community_0 ["root"]
    kernel_c["kernel.c (c)"]
    class kernel_c mod;
    tls_c["tls.c (c)"]
    class tls_c mod;
    mkramdisk_py["mkramdisk.py (py)"]
    class mkramdisk_py mod;
    net_c["net.c (c)"]
    class net_c mod;
    tls_crypto_c["tls_crypto.c (c)"]
    class tls_crypto_c mod;
    tls_x509_c["tls_x509.c (c)"]
    class tls_x509_c mod;
    cvm_host_c["cvm_host.c (c)"]
    class cvm_host_c mod;
    progs_freedom_s["freedom.s (s)"]
    class progs_freedom_s mod;
    bootdefs_h["bootdefs.h (h)"]
    class bootdefs_h mod;
    tls_h["tls.h (h)"]
    class tls_h mod;
    progs_freedom_c["freedom.c (c)"]
    class progs_freedom_c mod;
    net_h["net.h (h)"]
    class net_h mod;
    stage2_S["stage2.S (S)"]
    class stage2_S mod;
    kernel_h["kernel.h (h)"]
    class kernel_h mod;
    stage1_S["stage1.S (S)"]
    class stage1_S mod;
    test_bdd_sh["test_bdd.sh (sh)"]
    class test_bdd_sh mod;
    progs_lxhello_c["lxhello.c (c)"]
    class progs_lxhello_c mod;
    progs_cpl_c["cpl.c (c)"]
    class progs_cpl_c mod;
    progs_fib_s["fib.s (s)"]
    class progs_fib_s mod;
    progs_http_s["http.s (s)"]
    class progs_http_s mod;
    progs_kmem_c["kmem.c (c)"]
    class progs_kmem_c mod;
    bootloader_c["bootloader.c (c)"]
    class bootloader_c mod;
    mutate_sh["mutate.sh (sh)"]
    class mutate_sh mod;
    progs_fib_c["fib.c (c)"]
    class progs_fib_c mod;
    progs_http_c["http.c (c)"]
    class progs_http_c mod;
    progs_ldhello_s["ldhello.s (s)"]
    class progs_ldhello_s mod;
    progs_test_c["test.c (c)"]
    class progs_test_c mod;
    progs_w1_s["w1.s (s)"]
    class progs_w1_s mod;
    mcp_mutate_mcp_sh["mutate_mcp.sh (sh)"]
    class mcp_mutate_mcp_sh mod;
    progs_ftest_c["ftest.c (c)"]
    class progs_ftest_c mod;
    progs_hello_c["hello.c (c)"]
    class progs_hello_c mod;
    progs_ldhello_c["ldhello.c (c)"]
    class progs_ldhello_c mod;
    progs_w1_c["w1.c (c)"]
    class progs_w1_c mod;
    app_py["app.py (py)"]
    class app_py mod;
    install_sh["install.sh (sh)"]
    class install_sh mod;
    mcp___init___py["__init__.py (py)"]
    class mcp___init___py mod;
    mkroots_sh["mkroots.sh (sh)"]
    class mkroots_sh mod;
    ramdisk_data_c["ramdisk_data.c (c)"]
    class ramdisk_data_c mod;
    tls_roots_h["tls_roots.h (h)"]
    class tls_roots_h mod;
    tls_test_roots_h["tls_test_roots.h (h)"]
    class tls_test_roots_h mod;
    end
    mcp_minios_mcp_py -- resolved_imports --> mcp_minios_addons_py
    ext_cvm_h["cvm.h"]
    class ext_cvm_h ext;
    cvm_host_c -.->|imports| ext_cvm_h
    ext_kernel_h["kernel.h"]
    class ext_kernel_h ext;
    kernel_c -.->|imports| ext_kernel_h
    ext_net_h["net.h"]
    class ext_net_h ext;
    kernel_c -.->|imports| ext_net_h
    ext_tls_h["tls.h"]
    class ext_tls_h ext;
    kernel_c -.->|imports| ext_tls_h
    ext_bootdefs_h["bootdefs.h"]
    class ext_bootdefs_h ext;
    kernel_c -.->|imports| ext_bootdefs_h
    ext_json["json"]
    class ext_json ext;
    mcp_mcp_dbg_driver_py -.->|imports| ext_json
    ext_os["os"]
    class ext_os ext;
    mcp_mcp_dbg_driver_py -.->|imports| ext_os
    ext_select["select"]
    class ext_select ext;
    mcp_mcp_dbg_driver_py -.->|imports| ext_select
    ext_subprocess["subprocess"]
    class ext_subprocess ext;
    mcp_mcp_dbg_driver_py -.->|imports| ext_subprocess
    ext_sys["sys"]
    class ext_sys ext;
    mcp_mcp_dbg_driver_py -.->|imports| ext_sys
    ext_time["time"]
    class ext_time ext;
    mcp_mcp_dbg_driver_py -.->|imports| ext_time
    mcp_mcp_dogfood_py -.->|imports| ext_json
    mcp_mcp_dogfood_py -.->|imports| ext_os
    mcp_mcp_dogfood_py -.->|imports| ext_select
    mcp_mcp_dogfood_py -.->|imports| ext_subprocess
    mcp_mcp_dogfood_py -.->|imports| ext_sys
    mcp_mcp_dogfood_py -.->|imports| ext_time
    mcp_minios_addons_py -.->|imports| ext_json
    mcp_minios_addons_py -.->|imports| ext_os
    ext_re["re"]
    class ext_re ext;
    mcp_minios_addons_py -.->|imports| ext_re
    ext_shutil["shutil"]
    class ext_shutil ext;
    mcp_minios_addons_py -.->|imports| ext_shutil
    mcp_minios_addons_py -.->|imports| ext_subprocess
    ext_tempfile["tempfile"]
    class ext_tempfile ext;
    mcp_minios_addons_py -.->|imports| ext_tempfile
    mcp_minios_addons_py -.->|imports| ext_time
    ext_atexit["atexit"]
    class ext_atexit ext;
    mcp_minios_mcp_py -.->|imports| ext_atexit
    mcp_minios_mcp_py -.->|imports| ext_json
    mcp_minios_mcp_py -.->|imports| ext_os
    ext_signal["signal"]
    class ext_signal ext;
    mcp_minios_mcp_py -.->|imports| ext_signal
    mcp_minios_mcp_py -.->|imports| ext_sys
    mcp_minios_mcp_py -.->|imports| ext_tempfile
    ext_threading["threading"]
    class ext_threading ext;
    mcp_minios_mcp_py -.->|imports| ext_threading
    mcp_minios_mcp_py -.->|imports| ext_time
    ext_tty["tty"]
    class ext_tty ext;
    mcp_minios_mcp_py -.->|imports| ext_tty
    ext_minios_addons["minios_addons"]
    class ext_minios_addons ext;
    mcp_minios_mcp_py -.->|imports| ext_minios_addons
    mcp_minios_mcp_py -.->|imports| ext_subprocess
    ext_importlib_util["importlib.util"]
    class ext_importlib_util ext;
    mcp_test_minios_mcp_py -.->|imports| ext_importlib_util
    mcp_test_minios_mcp_py -.->|imports| ext_json
    mcp_test_minios_mcp_py -.->|imports| ext_os
    mcp_test_minios_mcp_py -.->|imports| ext_select
    mcp_test_minios_mcp_py -.->|imports| ext_subprocess
    mcp_test_minios_mcp_py -.->|imports| ext_sys
    mcp_test_minios_mcp_py -.->|imports| ext_tempfile
    ext_unittest["unittest"]
    class ext_unittest ext;
    mcp_test_minios_mcp_py -.->|imports| ext_unittest
    mcp_test_minios_mcp_py -.->|imports| ext_shutil
    mcp_test_minios_mcp_py -.->|imports| ext_importlib_util
    mcp_test_minios_mcp_py -.->|imports| ext_importlib_util
    mcp_test_minios_mcp_py -.->|imports| ext_importlib_util
    mcp_test_minios_mcp_py -.->|imports| ext_shutil
    mcp_test_minios_mcp_py -.->|imports| ext_shutil
    mcp_test_minios_mcp_py -.->|imports| ext_shutil
    mkramdisk_py -.->|imports| ext_os
    ext_struct["struct"]
    class ext_struct ext;
    mkramdisk_py -.->|imports| ext_struct
    mkramdisk_py -.->|imports| ext_sys
    net_c -.->|imports| ext_kernel_h
    net_c -.->|imports| ext_net_h
    test_http_server_py -.->|imports| ext_sys
    test_http_server_py -.->|imports| ext_time
    ext_http_server["http.server"]
    class ext_http_server ext;
    test_http_server_py -.->|imports| ext_http_server
    ext_fcntl["fcntl"]
    class ext_fcntl ext;
    test_http_server_py -.->|imports| ext_fcntl
    test_http_server_py -.->|imports| ext_struct
    ext_tls_port_h["tls_port.h"]
    class ext_tls_port_h ext;
    tls_c -.->|imports| ext_tls_port_h
    tls_c -.->|imports| ext_tls_h
    ext_tls_roots_h["tls_roots.h"]
    class ext_tls_roots_h ext;
    tls_c -.->|imports| ext_tls_roots_h
    tls_crypto_c -.->|imports| ext_tls_port_h
    tls_crypto_c -.->|imports| ext_tls_h
    ext_stdio_h["stdio.h"]
    class ext_stdio_h ext;
    tls_port_h -.->|imports| ext_stdio_h
    ext_stdlib_h["stdlib.h"]
    class ext_stdlib_h ext;
    tls_port_h -.->|imports| ext_stdlib_h
    ext_string_h["string.h"]
    class ext_string_h ext;
    tls_port_h -.->|imports| ext_string_h
    ext_time_h["time.h"]
    class ext_time_h ext;
    tls_port_h -.->|imports| ext_time_h
    ext_unistd_h["unistd.h"]
    class ext_unistd_h ext;
    tls_port_h -.->|imports| ext_unistd_h
    ext_fcntl_h["fcntl.h"]
    class ext_fcntl_h ext;
    tls_port_h -.->|imports| ext_fcntl_h
    tls_port_h -.->|imports| ext_kernel_h
    tls_port_h -.->|imports| ext_net_h
    tls_test_c -.->|imports| ext_stdio_h
    tls_test_c -.->|imports| ext_stdlib_h
    tls_test_c -.->|imports| ext_string_h
    tls_test_c -.->|imports| ext_unistd_h
    ext_sys_socket_h["socket.h"]
    class ext_sys_socket_h ext;
    tls_test_c -.->|imports| ext_sys_socket_h
    ext_sys_select_h["select.h"]
    class ext_sys_select_h ext;
    tls_test_c -.->|imports| ext_sys_select_h
    ext_netinet_in_h["in.h"]
    class ext_netinet_in_h ext;
    tls_test_c -.->|imports| ext_netinet_in_h
    ext_arpa_inet_h["inet.h"]
    class ext_arpa_inet_h ext;
    tls_test_c -.->|imports| ext_arpa_inet_h
    tls_test_c -.->|imports| ext_tls_port_h
    tls_test_c -.->|imports| ext_tls_h
    ext_tls_test_roots_h["tls_test_roots.h"]
    class ext_tls_test_roots_h ext;
    tls_test_c -.->|imports| ext_tls_test_roots_h
    tls_test_py -.->|imports| ext_os
    tls_test_py -.->|imports| ext_re
    ext_shlex["shlex"]
    class ext_shlex ext;
    tls_test_py -.->|imports| ext_shlex
    ext_socket["socket"]
    class ext_socket ext;
    tls_test_py -.->|imports| ext_socket
    ext_ssl["ssl"]
    class ext_ssl ext;
    tls_test_py -.->|imports| ext_ssl
    tls_test_py -.->|imports| ext_subprocess
    tls_test_py -.->|imports| ext_sys
    tls_test_py -.->|imports| ext_threading
    tls_test_py -.->|imports| ext_time
    ext_datetime["datetime"]
    class ext_datetime ext;
    tls_test_py -.->|imports| ext_datetime
    tls_x509_c -.->|imports| ext_tls_port_h
    tls_x509_c -.->|imports| ext_tls_h
```

---

## UML Class Diagram

Auto-generated Mermaid class diagram from parsed class-level symbols. Shows classes, structs, interfaces, traits, and their methods with inheritance and dependency relationships.

```mermaid
classDiagram
  class kernel_c_Block {
    <<struct>>
    +outb(unsigned short port, unsigned char val)
    +inb(unsigned short port)
    +serial_tx_ready(void)
    +serial_rx_ready(void)
    +serial_putc(char c)
    +serial_puts(const char *s)
    +serial_available(void)
    +serial_getc(void)
    +vga_offset(int x, int y)
    +vga_clear(void)
  }
  class kernel_c_snctx {
    <<struct>>
    +outb(unsigned short port, unsigned char val)
    +inb(unsigned short port)
    +serial_tx_ready(void)
    +serial_rx_ready(void)
    +serial_putc(char c)
    +serial_puts(const char *s)
    +serial_available(void)
    +serial_getc(void)
    +vga_offset(int x, int y)
    +vga_clear(void)
  }
  class kernel_c_exec_range {
    <<struct>>
    +outb(unsigned short port, unsigned char val)
    +inb(unsigned short port)
    +serial_tx_ready(void)
    +serial_rx_ready(void)
    +serial_putc(char c)
    +serial_puts(const char *s)
    +serial_available(void)
    +serial_getc(void)
    +vga_offset(int x, int y)
    +vga_clear(void)
  }
  class kernel_c_kiovec {
    <<struct>>
    +outb(unsigned short port, unsigned char val)
    +inb(unsigned short port)
    +serial_tx_ready(void)
    +serial_rx_ready(void)
    +serial_putc(char c)
    +serial_puts(const char *s)
    +serial_available(void)
    +serial_getc(void)
    +vga_offset(int x, int y)
    +vga_clear(void)
  }
  class mcp_dbg_driver_py_Client {
    <<class>>
    +main()
    +__init__(self)
    +request(self, method, params)
    +tool(self, name, params)
    +close(self)
  }
  class mcp_dogfood_py_Client {
    <<class>>
    +main()
    +__init__(self, addons_dir)
    +request(self, method, params)
    +tool(self, name, params)
    +close(self)
  }
  class minios_addons_py_AddonError {
    <<class>>
    +_clean(s)
    +_unquote(v)
    +parse_addon_yaml(text)
    +validate_addon(addon, source)
    +validate_addon_path(path)
    +validate_shell_line(line)
    +load_addons_dir(addons_dir)
    +split_for_editor(text)
    +exit_code_of(text)
    +install_addon(session, addon, cfg)
  }
  class minios_addons_py_AddonState {
    <<class>>
    +_clean(s)
    +_unquote(v)
    +parse_addon_yaml(text)
    +validate_addon(addon, source)
    +validate_addon_path(path)
    +validate_shell_line(line)
    +load_addons_dir(addons_dir)
    +split_for_editor(text)
    +exit_code_of(text)
    +install_addon(session, addon, cfg)
  }
  class minios_mcp_py_ToolError {
    <<class>>
    +env_config()
    +clamp_timeout(ms)
    +validate_path(name)
    +validate_content(text)
    +subprocess_launch(cfg, slave_fd)
    +main()
    +__init__(self, code, message)
    +__init__(self, cap)
    +append(self, data)
    +bytes_from(self, pos)
  }
  class minios_mcp_py_RPCError {
    <<class>>
    +env_config()
    +clamp_timeout(ms)
    +validate_path(name)
    +validate_content(text)
    +subprocess_launch(cfg, slave_fd)
    +main()
    +__init__(self, code, message)
    +__init__(self, cap)
    +append(self, data)
    +bytes_from(self, pos)
  }
  class minios_mcp_py_LogBuffer {
    <<class>>
    +env_config()
    +clamp_timeout(ms)
    +validate_path(name)
    +validate_content(text)
    +subprocess_launch(cfg, slave_fd)
    +main()
    +__init__(self, code, message)
    +__init__(self, cap)
    +append(self, data)
    +bytes_from(self, pos)
  }
  class minios_mcp_py_MiniOSSession {
    <<class>>
    +env_config()
    +clamp_timeout(ms)
    +validate_path(name)
    +validate_content(text)
    +subprocess_launch(cfg, slave_fd)
    +main()
    +__init__(self, code, message)
    +__init__(self, cap)
    +append(self, data)
    +bytes_from(self, pos)
  }
  class minios_mcp_py_MCPServer {
    <<class>>
    +env_config()
    +clamp_timeout(ms)
    +validate_path(name)
    +validate_content(text)
    +subprocess_launch(cfg, slave_fd)
    +main()
    +__init__(self, code, message)
    +__init__(self, cap)
    +append(self, data)
    +bytes_from(self, pos)
  }
  class test_minios_mcp_py_MCPServer {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py_TestProtocol {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py_TestValidation {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py_TestLogBuffer {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py__ConsoleBDDBase {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py_TestMiniOSBDD {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py_TestAddonYaml {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py_TestAddonHelpers {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py_FakeOS {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py_TestAddonInstall {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py_TestAddonBDD {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class test_minios_mcp_py__toolerror {
    <<class>>
    +load_module()
    +have_qemu()
    +__init__(self, env_extra)
    +initialize(self)
    +request(self, method, params)
    +raw(self, line)
    +_read_response(self)
    +_roundtrip(self, msg)
    +tool(self, name, params)
    +close(self)
  }
  class net_c_net_arp_entry {
    <<struct>>
    +outb_port(unsigned short port, unsigned char val)
    +inb_port(unsigned short port)
    +outw_port(unsigned short port, unsigned short val)
    +outl_port(unsigned short port, unsigned int val)
    +inw_port(unsigned short port)
    +inl_port(unsigned short port)
    +net_reg8(unsigned short off)
    +net_reg8_w(unsigned short off, unsigned char v)
    +net_reg16(unsigned short off)
    +net_reg16_w(unsigned short off, unsigned short v)
  }
  class net_c_net_dns_state {
    <<struct>>
    +outb_port(unsigned short port, unsigned char val)
    +inb_port(unsigned short port)
    +outw_port(unsigned short port, unsigned short val)
    +outl_port(unsigned short port, unsigned int val)
    +inw_port(unsigned short port)
    +inl_port(unsigned short port)
    +net_reg8(unsigned short off)
    +net_reg8_w(unsigned short off, unsigned char v)
    +net_reg16(unsigned short off)
    +net_reg16_w(unsigned short off, unsigned short v)
  }
  class net_c_net_tcp_sock {
    <<struct>>
    +outb_port(unsigned short port, unsigned char val)
    +inb_port(unsigned short port)
    +outw_port(unsigned short port, unsigned short val)
    +outl_port(unsigned short port, unsigned int val)
    +inw_port(unsigned short port)
    +inl_port(unsigned short port)
    +net_reg8(unsigned short off)
    +net_reg8_w(unsigned short off, unsigned char v)
    +net_reg16(unsigned short off)
    +net_reg16_w(unsigned short off, unsigned short v)
  }
  class test_http_server_py_Handler {
    <<class>>
    +do_GET(self)
    +log_message(self, fmt)
  }
  class tls_h_tls_root {
    <<struct>>
  }
  class tls_h_sha256_ctx {
    <<struct>>
  }
  class tls_h_tls_pubkey {
    <<struct>>
  }
  class tls_h_tls_session {
    <<struct>>
  }
  class tls_crypto_c_mont_ctx {
    <<struct>>
    +sha256_rotr(unsigned x, unsigned n)
    +sha256_init(struct sha256_ctx *c)
    +sha256_block(struct sha256_ctx *c, const unsigned char *p)
    +sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len)
    +sha256_final(struct sha256_ctx *c, unsigned char out[32])
    +sha256(const unsigned char *data, unsigned len, unsigned char out[32])
    +hmac_sha256(const unsigned char *key, unsigned klen,
                 const unsigned char *d...
    +p_hash(const unsigned char *secret, unsigned secret_len,
                   const uns...
    +tls_prf(const unsigned char *secret, unsigned secret_len,
             const char *label, co...
    +aes_xtime(unsigned x)
  }
  class tls_crypto_c_ec_curve {
    <<struct>>
    +sha256_rotr(unsigned x, unsigned n)
    +sha256_init(struct sha256_ctx *c)
    +sha256_block(struct sha256_ctx *c, const unsigned char *p)
    +sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len)
    +sha256_final(struct sha256_ctx *c, unsigned char out[32])
    +sha256(const unsigned char *data, unsigned len, unsigned char out[32])
    +hmac_sha256(const unsigned char *key, unsigned klen,
                 const unsigned char *d...
    +p_hash(const unsigned char *secret, unsigned secret_len,
                   const uns...
    +tls_prf(const unsigned char *secret, unsigned secret_len,
             const char *label, co...
    +aes_xtime(unsigned x)
  }
  class tls_crypto_c_jpt {
    <<struct>>
    +sha256_rotr(unsigned x, unsigned n)
    +sha256_init(struct sha256_ctx *c)
    +sha256_block(struct sha256_ctx *c, const unsigned char *p)
    +sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len)
    +sha256_final(struct sha256_ctx *c, unsigned char out[32])
    +sha256(const unsigned char *data, unsigned len, unsigned char out[32])
    +hmac_sha256(const unsigned char *key, unsigned klen,
                 const unsigned char *d...
    +p_hash(const unsigned char *secret, unsigned secret_len,
                   const uns...
    +tls_prf(const unsigned char *secret, unsigned secret_len,
             const char *label, co...
    +aes_xtime(unsigned x)
  }
  class tls_test_py_Server {
    <<class>>
    +run(cmd)
    +check(cmd)
    +gen_certs()
    +der_bytes(pem_path)
    +rsa_params(key_path)
    +ec_pub(key_path)
    +c_bytes(data, name)
    +gen_header(p)
    +serve(cert, key)
    +serve_openssl(cert, key, chain)
  }
  class tls_x509_c_der_tlv {
    <<struct>>
    +oid_eq(const unsigned char *bytes, unsigned len,
                  const unsigned char...
    +der_next(const unsigned char *p, unsigned limit, unsigned *pos,
                    st...
    +der_container(const unsigned char *p, unsigned limit, unsigned *pos,
                 ...
    +days_from_civil(int y, int m, int d)
    +der_time_to_days(const struct der_tlv *t)
    +name_find_cn(const unsigned char *p, unsigned limit,
                        struct x5...
    +san_add(struct x509_sans *out, const unsigned char *v, unsigned len)
    +san_parse(const unsigned char *p, unsigned limit,
                      struct x509_s...
    +spki_parse(const unsigned char *p, unsigned limit,
                      struct tls_pu...
    +cert_parse(const unsigned char *der, unsigned len,
                      struct x509_c...
  }
  class tls_x509_c_x509_name {
    <<struct>>
    +oid_eq(const unsigned char *bytes, unsigned len,
                  const unsigned char...
    +der_next(const unsigned char *p, unsigned limit, unsigned *pos,
                    st...
    +der_container(const unsigned char *p, unsigned limit, unsigned *pos,
                 ...
    +days_from_civil(int y, int m, int d)
    +der_time_to_days(const struct der_tlv *t)
    +name_find_cn(const unsigned char *p, unsigned limit,
                        struct x5...
    +san_add(struct x509_sans *out, const unsigned char *v, unsigned len)
    +san_parse(const unsigned char *p, unsigned limit,
                      struct x509_s...
    +spki_parse(const unsigned char *p, unsigned limit,
                      struct tls_pu...
    +cert_parse(const unsigned char *der, unsigned len,
                      struct x509_c...
  }
  class tls_x509_c_x509_sans {
    <<struct>>
    +oid_eq(const unsigned char *bytes, unsigned len,
                  const unsigned char...
    +der_next(const unsigned char *p, unsigned limit, unsigned *pos,
                    st...
    +der_container(const unsigned char *p, unsigned limit, unsigned *pos,
                 ...
    +days_from_civil(int y, int m, int d)
    +der_time_to_days(const struct der_tlv *t)
    +name_find_cn(const unsigned char *p, unsigned limit,
                        struct x5...
    +san_add(struct x509_sans *out, const unsigned char *v, unsigned len)
    +san_parse(const unsigned char *p, unsigned limit,
                      struct x509_s...
    +spki_parse(const unsigned char *p, unsigned limit,
                      struct tls_pu...
    +cert_parse(const unsigned char *der, unsigned len,
                      struct x509_c...
  }
  class tls_x509_c_x509_cert {
    <<struct>>
    +oid_eq(const unsigned char *bytes, unsigned len,
                  const unsigned char...
    +der_next(const unsigned char *p, unsigned limit, unsigned *pos,
                    st...
    +der_container(const unsigned char *p, unsigned limit, unsigned *pos,
                 ...
    +days_from_civil(int y, int m, int d)
    +der_time_to_days(const struct der_tlv *t)
    +name_find_cn(const unsigned char *p, unsigned limit,
                        struct x5...
    +san_add(struct x509_sans *out, const unsigned char *v, unsigned len)
    +san_parse(const unsigned char *p, unsigned limit,
                      struct x509_s...
    +spki_parse(const unsigned char *p, unsigned limit,
                      struct tls_pu...
    +cert_parse(const unsigned char *der, unsigned len,
                      struct x509_c...
  }
  kernel_c_Block --> tls_h_sha256_ctx : uses
  kernel_c_Block --> tls_h_tls_pubkey : uses
  kernel_c_Block --> tls_h_tls_root : uses
  kernel_c_Block --> tls_h_tls_session : uses
  kernel_c_exec_range --> tls_h_sha256_ctx : uses
  kernel_c_exec_range --> tls_h_tls_pubkey : uses
  kernel_c_exec_range --> tls_h_tls_root : uses
  kernel_c_exec_range --> tls_h_tls_session : uses
  kernel_c_kiovec --> tls_h_sha256_ctx : uses
  kernel_c_kiovec --> tls_h_tls_pubkey : uses
  kernel_c_kiovec --> tls_h_tls_root : uses
  kernel_c_kiovec --> tls_h_tls_session : uses
  kernel_c_snctx --> tls_h_sha256_ctx : uses
  kernel_c_snctx --> tls_h_tls_pubkey : uses
  kernel_c_snctx --> tls_h_tls_root : uses
  kernel_c_snctx --> tls_h_tls_session : uses
  tls_crypto_c_ec_curve --> tls_h_sha256_ctx : uses
  tls_crypto_c_ec_curve --> tls_h_tls_pubkey : uses
  tls_crypto_c_ec_curve --> tls_h_tls_root : uses
  tls_crypto_c_ec_curve --> tls_h_tls_session : uses
  tls_crypto_c_jpt --> tls_h_sha256_ctx : uses
  tls_crypto_c_jpt --> tls_h_tls_pubkey : uses
  tls_crypto_c_jpt --> tls_h_tls_root : uses
  tls_crypto_c_jpt --> tls_h_tls_session : uses
  tls_crypto_c_mont_ctx --> tls_h_sha256_ctx : uses
  tls_crypto_c_mont_ctx --> tls_h_tls_pubkey : uses
  tls_crypto_c_mont_ctx --> tls_h_tls_root : uses
  tls_crypto_c_mont_ctx --> tls_h_tls_session : uses
  tls_x509_c_der_tlv --> tls_h_sha256_ctx : uses
  tls_x509_c_der_tlv --> tls_h_tls_pubkey : uses
  tls_x509_c_der_tlv --> tls_h_tls_root : uses
  tls_x509_c_der_tlv --> tls_h_tls_session : uses
  tls_x509_c_x509_cert --> tls_h_sha256_ctx : uses
  tls_x509_c_x509_cert --> tls_h_tls_pubkey : uses
  tls_x509_c_x509_cert --> tls_h_tls_root : uses
  tls_x509_c_x509_cert --> tls_h_tls_session : uses
  tls_x509_c_x509_name --> tls_h_sha256_ctx : uses
  tls_x509_c_x509_name --> tls_h_tls_pubkey : uses
  tls_x509_c_x509_name --> tls_h_tls_root : uses
  tls_x509_c_x509_name --> tls_h_tls_session : uses
  tls_x509_c_x509_sans --> tls_h_sha256_ctx : uses
  tls_x509_c_x509_sans --> tls_h_tls_pubkey : uses
  tls_x509_c_x509_sans --> tls_h_tls_root : uses
  tls_x509_c_x509_sans --> tls_h_tls_session : uses
```

---

## Code Property Graph

Machine-readable Code Property Graph (CPG) in JSON-LD format. This block allows AI agents to parse the full structural graph without additional file reads. Compatible with GraphRAG pipelines.

```json
{"@context": "https://schema.org", "analysis": {"communities": [{"cohesion": 0.625, "id": 0, "label": "root", "size": 5}, {"cohesion": 1.0, "id": 1, "label": "mcp", "size": 2}, {"cohesion": 0.769, "id": 2, "label": "root", "size": 8}], "god_nodes": [{"node_id": "kernel.c", "score": 30.2}, {"node_id": "tls_port.h", "score": 14.7}, {"node_id": "tls.h", "score": 14.2}, {"node_id": "net.c", "score": 12.4}, {"node_id": "tls_crypto.c", "score": 11.6}, {"node_id": "bootdefs.h", "score": 9.6}, {"node_id": "mcp/test_minios_mcp.py", "score": 9.5}, {"node_id": "net.h", "score": 9.4}, {"node_id": "progs/freedom.s", "score": 9.1}, {"node_id": "tls.c", "score": 8.5}], "surprising_connections": [{"hops": 4, "source": "bootdefs.h", "target": "tls_roots.h"}, {"hops": 4, "source": "bootdefs.h", "target": "tls_test_roots.h"}, {"hops": 4, "source": "net.c", "target": "tls_roots.h"}, {"hops": 4, "source": "net.c", "target": "tls_test_roots.h"}, {"hops": 3, "source": "bootdefs.h", "target": "tls.c"}]}, "edges": [{"confidence": "EXTRACTED", "relation": "imports", "source": "cvm_host.c", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "kernel.c", "target": "kernel.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "kernel.c", "target": "net.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "kernel.c", "target": "tls.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "kernel.c", "target": "bootdefs.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dbg_driver.py", "target": "json"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dbg_driver.py", "target": "os"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dbg_driver.py", "target": "select"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dbg_driver.py", "target": "subprocess"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dbg_driver.py", "target": "sys"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dbg_driver.py", "target": "time"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dogfood.py", "target": "json"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dogfood.py", "target": "os"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dogfood.py", "target": "select"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dogfood.py", "target": "subprocess"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dogfood.py", "target": "sys"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/mcp_dogfood.py", "target": "time"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_addons.py", "target": "json"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_addons.py", "target": "os"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_addons.py", "target": "re"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_addons.py", "target": "shutil"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_addons.py", "target": "subprocess"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_addons.py", "target": "tempfile"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_addons.py", "target": "time"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "atexit"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "json"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "os"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "signal"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "sys"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "tempfile"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "threading"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "time"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "tty"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "minios_addons"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/minios_mcp.py", "target": "subprocess"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "importlib.util"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "json"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "os"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "select"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "subprocess"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "sys"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "tempfile"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "unittest"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "shutil"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "importlib.util"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "importlib.util"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "importlib.util"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "shutil"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "shutil"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mcp/test_minios_mcp.py", "target": "shutil"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mkramdisk.py", "target": "os"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mkramdisk.py", "target": "struct"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "mkramdisk.py", "target": "sys"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "net.c", "target": "kernel.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "net.c", "target": "net.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "test_http_server.py", "target": "sys"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "test_http_server.py", "target": "time"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "test_http_server.py", "target": "http.server"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "test_http_server.py", "target": "fcntl"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "test_http_server.py", "target": "struct"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls.c", "target": "tls_port.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls.c", "target": "tls.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls.c", "target": "tls_roots.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_crypto.c", "target": "tls_port.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_crypto.c", "target": "tls.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_port.h", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_port.h", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_port.h", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_port.h", "target": "time.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_port.h", "target": "unistd.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_port.h", "target": "fcntl.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_port.h", "target": "kernel.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_port.h", "target": "net.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "unistd.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "sys/socket.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "sys/select.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "netinet/in.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "arpa/inet.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "tls_port.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "tls.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.c", "target": "tls_test_roots.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "os"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "re"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "shlex"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "socket"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "ssl"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "subprocess"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "sys"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "threading"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "time"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_test.py", "target": "datetime"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_x509.c", "target": "tls_port.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "tls_x509.c", "target": "tls.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "mcp/minios_mcp.py", "target": "mcp/minios_addons.py"}], "generator": "readmenator", "metadata": {"edge_count": 1510, "file_count": 49, "language_count": 6, "symbol_count": 1105}, "nodes": [{"doc": "_*_ coding: utf8 _*_", "id": "app.py", "kind": "module", "label": "app.py", "language": "py", "sha256": "57b21bdb023585b8", "symbol_count": 0, "symbols": []}, {"doc": "bootdefs.h - centralized configuration for the MiniOS two-stage boot path.", "id": "bootdefs.h", "kind": "module", "label": "bootdefs.h", "language": "h", "sha256": "c3b5f673f7207c4a", "symbol_count": 76, "symbols": [{"kind": "macro", "line": 29, "name": "BOOTDEFS_H"}, {"kind": "macro", "line": 30, "name": "SECTOR_BYTES"}, {"kind": "macro", "line": 32, "name": "SECTOR_PARAGRAPH_SHIFT"}, {"kind": "macro", "line": 33, "name": "SECTOR_DWORD_SHIFT"}, {"kind": "macro", "line": 34, "name": "BOOT_SIGNATURE"}, {"kind": "macro", "line": 36, "name": "BOOT_SIGNATURE_BYTES"}, {"kind": "macro", "line": 37, "name": "BOOT_SEG_NULL"}, {"kind": "macro", "line": 39, "name": "BOOT_STACK_TOP"}, {"kind": "macro", "line": 40, "name": "BOOT_DAP_ADDR"}, {"kind": "macro", "line": 42, "name": "BOOT_DAP_SIZE"}, {"kind": "macro", "line": 43, "name": "BOOT_DAP_OFF_COUNT"}, {"kind": "macro", "line": 44, "name": "BOOT_DAP_OFF_OFFSET"}, {"kind": "macro", "line": 45, "name": "BOOT_DAP_OFF_SEGMENT"}, {"kind": "macro", "line": 46, "name": "BOOT_DAP_OFF_LBA_LO"}, {"kind": "macro", "line": 47, "name": "BOOT_DAP_OFF_LBA_HI"}, {"kind": "macro", "line": 48, "name": "BOOT_DRIVE_ADDR"}, {"kind": "macro", "line": 49, "name": "BOOT_STAGE2_LBA"}, {"kind": "macro", "line": 51, "name": "BOOT_STAGE2_SECTORS"}, {"kind": "macro", "line": 52, "name": "BOOT_STAGE2_ADDR"}, {"kind": "macro", "line": 53, "name": "BOOT_STAGE2_SEG"}, {"kind": "macro", "line": 54, "name": "BOOT_KERNEL_LBA"}, {"kind": "macro", "line": 56, "name": "BOOT_KERNEL_BUF_ADDR"}, {"kind": "macro", "line": 57, "name": "BOOT_KERNEL_BUF_SEG"}, {"kind": "macro", "line": 58, "name": "BOOT_KERNEL_PHYS_ADDR"}, {"kind": "macro", "line": 59, "name": "BOOT_CHUNK_SECTORS"}, {"kind": "macro", "line": 61, "name": "BOOT_BIOS_MAX_SECTORS"}, {"kind": "macro", "line": 62, "name": "BOOT_PM_STACK_TOP"}, {"kind": "macro", "line": 64, "name": "BIOS_DISK_INT"}, {"kind": "macro", "line": 66, "name": "BIOS_DISK_EXT_CHECK"}, {"kind": "macro", "line": 67, "name": "BIOS_DISK_EXT_REQ_MAGIC"}, {"kind": "macro", "line": 68, "name": "BIOS_DISK_EXT_ACK_MAGIC"}, {"kind": "macro", "line": 69, "name": "BIOS_DISK_EXT_PACKET_BIT"}, {"kind": "macro", "line": 70, "name": "BIOS_DISK_READ_EXT"}, {"kind": "macro", "line": 71, "name": "BIOS_VIDEO_INT"}, {"kind": "macro", "line": 73, "name": "BIOS_VIDEO_TTY_WRITE"}, {"kind": "macro", "line": 74, "name": "BIOS_VIDEO_TTY_ATTR"}, {"kind": "macro", "line": 75, "name": "A20_CONTROL_PORT"}, {"kind": "macro", "line": 77, "name": "A20_ENABLE_BIT"}, {"kind": "macro", "line": 78, "name": "A20_RESET_CLEAR_MASK"}, {"kind": "macro", "line": 79, "name": "CR0_PE"}, {"kind": "macro", "line": 81, "name": "CR0_PE_CLEAR_MASK"}, {"kind": "macro", "line": 82, "name": "CR0_PG"}, {"kind": "macro", "line": 83, "name": "CR4_PAE"}, {"kind": "macro", "line": 84, "name": "MSR_EFER"}, {"kind": "macro", "line": 86, "name": "EFER_LME"}, {"kind": "macro", "line": 87, "name": "GDT32_CODE32_SEL"}, {"kind": "macro", "line": 89, "name": "GDT32_DATA32_SEL"}, {"kind": "macro", "line": 90, "name": "GDT32_CODE16_SEL"}, {"kind": "macro", "line": 91, "name": "GDT32_DATA16_SEL"}, {"kind": "macro", "line": 92, "name": "GDT32_DESC_NULL"}, {"kind": "macro", "line": 94, "name": "GDT32_DESC_CODE32"}, {"kind": "macro", "line": 95, "name": "GDT32_DESC_DATA32"}, {"kind": "macro", "line": 96, "name": "GDT32_DESC_CODE16"}, {"kind": "macro", "line": 97, "name": "GDT32_DESC_DATA16"}, {"kind": "macro", "line": 98, "name": "GDT64_ADDR"}, {"kind": "macro", "line": 100, "name": "GDT64_BYTES"}, {"kind": "macro", "line": 101, "name": "GDT64_CODE_SEL"}, {"kind": "macro", "line": 102, "name": "GDT64_DATA_SEL"}, {"kind": "macro", "line": 103, "name": "GDT64_USER_DATA_SEL"}, {"kind": "macro", "line": 104, "name": "GDT64_USER_CODE_SEL"}, {"kind": "macro", "line": 105, "name": "GDT64_DESC_NULL"}, {"kind": "macro", "line": 106, "name": "GDT64_DESC_CODE"}, {"kind": "macro", "line": 107, "name": "GDT64_DESC_DATA"}, {"kind": "macro", "line": 108, "name": "GDT64_DESC_UDATA"}, {"kind": "macro", "line": 109, "name": "GDT64_DESC_UCODE"}, {"kind": "macro", "line": 110, "name": "PT_PML4_ADDR"}, {"kind": "macro", "line": 112, "name": "PT_PDPT_ADDR"}, {"kind": "macro", "line": 113, "name": "PT_PD_ADDR"}, {"kind": "macro", "line": 114, "name": "PT_ZERO_DWORDS"}, {"kind": "macro", "line": 115, "name": "PT_FLAGS_PRESENT_RW"}, {"kind": "macro", "line": 116, "name": "PT_FLAGS_PRESENT_RW_PS"}, {"kind": "macro", "line": 117, "name": "PT_FLAGS_USER"}, {"kind": "macro", "line": 118, "name": "PT_PD_ENTRIES"}, {"kind": "macro", "line": 119, "name": "PT_PD_ENTRY_BYTES"}, {"kind": "macro", "line": 120, "name": "PT_PD_PAGE_BYTES"}, {"kind": "macro", "line": 121, "name": "PT_PD_INDEX_SHIFT"}]}, {"id": "bootloader.c", "kind": "module", "label": "bootloader.c", "language": "c", "sha256": "7bd57cae9f873eb1", "symbol_count": 2, "symbols": [{"doc": "\"gdt_start:\\n\" \"  .quad 0\\n\" \"  .quad 0x00CF9A000000FFFF\\n\" \"  .quad 0x00CF92000000FFFF\\n\" \"gdt_end:\\n\" \".global gdt32_ptr\\n\" \"gdt32_ptr:\\n\" \"  .word gdt_end - gdt_start - 1\\n\" \"  .long gdt_start\\n\" ); __asm__(\"boot_drive: .byte 0\\n\"); /* Number of 512-byte sectors of kernel to load from LBA 1 to phys 0x10000. define KSECTORS 508", "kind": "function", "line": 20, "name": "main", "signature": "void main(void)"}, {"kind": "macro", "line": 19, "name": "KSECTORS"}]}, {"id": "cvm_host.c", "kind": "module", "label": "cvm_host.c", "language": "c", "sha256": "78ca9036ed84aecc", "symbol_count": 45, "symbols": [{"kind": "function", "line": 18, "name": "n_strcmp", "signature": "static int64_t n_strcmp(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 24, "name": "n_strncmp", "signature": "static int64_t n_strncmp(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 31, "name": "n_strcpy", "signature": "static int64_t n_strcpy(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 37, "name": "n_strncpy", "signature": "static int64_t n_strncpy(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 44, "name": "n_memcpy", "signature": "static int64_t n_memcpy(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 51, "name": "n_memset", "signature": "static int64_t n_memset(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 57, "name": "n_memmove", "signature": "static int64_t n_memmove(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 64, "name": "n_memcmp", "signature": "static int64_t n_memcmp(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 71, "name": "n_strchr", "signature": "static int64_t n_strchr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 77, "name": "n_strstr", "signature": "static int64_t n_strstr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 84, "name": "n_malloc", "signature": "static int64_t n_malloc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 89, "name": "n_free", "signature": "static int64_t n_free(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 94, "name": "n_calloc", "signature": "static int64_t n_calloc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 102, "name": "n_realloc", "signature": "static int64_t n_realloc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 110, "name": "n_exit", "signature": "static int64_t n_exit(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 117, "name": "n_fopen", "signature": "static int64_t n_fopen(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 124, "name": "n_fclose", "signature": "static int64_t n_fclose(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 130, "name": "n_fread", "signature": "static int64_t n_fread(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 137, "name": "n_fwrite", "signature": "static int64_t n_fwrite(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 144, "name": "n_fseek", "signature": "static int64_t n_fseek(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 150, "name": "n_ftell", "signature": "static int64_t n_ftell(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 156, "name": "n_rewind", "signature": "static int64_t n_rewind(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 163, "name": "n_fputs", "signature": "static int64_t n_fputs(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 169, "name": "n_fputc", "signature": "static int64_t n_fputc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 175, "name": "n_fgetc", "signature": "static int64_t n_fgetc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 181, "name": "n_ungetc", "signature": "static int64_t n_ungetc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 187, "name": "n_fflush", "signature": "static int64_t n_fflush(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 193, "name": "n_putchar", "signature": "static int64_t n_putchar(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 200, "name": "n_write", "signature": "static int64_t n_write(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 209, "name": "n_read", "signature": "static int64_t n_read(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 224, "name": "n_puts", "signature": "static int64_t n_puts(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 232, "name": "n_atol", "signature": "static int64_t n_atol(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 245, "name": "n_strtol", "signature": "static int64_t n_strtol(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 258, "name": "n_stderr_addr", "signature": "static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 263, "name": "n_stdout_addr", "signature": "static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 268, "name": "n_stdin_addr", "signature": "static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 273, "name": "kout_char", "signature": "static void kout_char(void *ctx, char c)"}, {"kind": "function", "line": 279, "name": "kout_uint", "signature": "static void kout_uint(void *ctx, unsigned long long v, int base, int upper)"}, {"kind": "function", "line": 292, "name": "kformat", "signature": "static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)"}, {"kind": "function", "line": 358, "name": "n_fprintf", "signature": "static int64_t n_fprintf(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 365, "name": "n_printf", "signature": "static int64_t n_printf(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 372, "name": "n_sprintf", "signature": "static int64_t n_sprintf(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 380, "name": "n_snprintf", "signature": "static int64_t n_snprintf(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 388, "name": "register_host_natives", "signature": "static void register_host_natives(CvmState *vm)"}, {"kind": "function", "line": 433, "name": "cvm_main", "signature": "int cvm_main(int argc, char **argv)"}]}, {"id": "install.sh", "kind": "module", "label": "install.sh", "language": "sh", "sha256": "c907d80fd6734993", "symbol_count": 0, "symbols": []}, {"doc": "include \"kernel.h\" include \"net.h\" include \"tls.h\" include \"bootdefs.h\"  ================================================================", "id": "kernel.c", "kind": "module", "label": "kernel.c", "language": "c", "sha256": "b358af91cbe50191", "symbol_count": 222, "symbols": [{"kind": "struct", "line": 290, "name": "Block"}, {"kind": "struct", "line": 1190, "name": "snctx"}, {"kind": "struct", "line": 1392, "name": "exec_range"}, {"kind": "struct", "line": 1868, "name": "kiovec"}, {"doc": "================================================================ Port I/O helpers * ================================================================", "kind": "function", "line": 9, "name": "outb", "signature": "static inline void outb(unsigned short port, unsigned char val)"}, {"kind": "function", "line": 13, "name": "inb", "signature": "static inline unsigned char inb(unsigned short port)"}, {"kind": "function", "line": 34, "name": "serial_tx_ready", "signature": "static int serial_tx_ready(void)"}, {"kind": "function", "line": 36, "name": "serial_rx_ready", "signature": "static int serial_rx_ready(void)"}, {"kind": "function", "line": 37, "name": "serial_putc", "signature": "void serial_putc(char c)"}, {"kind": "function", "line": 42, "name": "serial_puts", "signature": "void serial_puts(const char *s)"}, {"kind": "function", "line": 43, "name": "serial_available", "signature": "int serial_available(void)"}, {"kind": "function", "line": 45, "name": "serial_getc", "signature": "int serial_getc(void)"}, {"doc": "================================================================ VGA driver * ================================================================ static int vga_x, vga_y; static char vga_color = 0x07; /* light grey on black", "kind": "function", "line": 55, "name": "vga_offset", "signature": "static inline unsigned vga_offset(int x, int y)"}, {"kind": "function", "line": 57, "name": "vga_clear", "signature": "void vga_clear(void)"}, {"kind": "function", "line": 67, "name": "vga_set_cursor", "signature": "void vga_set_cursor(int x, int y)"}, {"kind": "function", "line": 87, "name": "vga_scroll", "signature": "void vga_scroll(void)"}, {"kind": "function", "line": 105, "name": "vga_newline", "signature": "void vga_newline(void)"}, {"kind": "function", "line": 111, "name": "vga_raw_space", "signature": "static void vga_raw_space(void)"}, {"kind": "function", "line": 132, "name": "redir_grow", "signature": "static int redir_grow(void)"}, {"kind": "function", "line": 142, "name": "vga_putc", "signature": "void vga_putc(char c)"}, {"kind": "function", "line": 175, "name": "vga_puts", "signature": "void vga_puts(const char *s)"}, {"kind": "function", "line": 220, "name": "kbd_q_push", "signature": "static void kbd_q_push(unsigned char c)"}, {"kind": "function", "line": 227, "name": "kbd_q_empty", "signature": "static int kbd_q_empty(void)"}, {"kind": "function", "line": 229, "name": "kbd_q_pop", "signature": "static int kbd_q_pop(void)"}, {"kind": "function", "line": 236, "name": "kbd_q_peek", "signature": "static int kbd_q_peek(void)"}, {"kind": "function", "line": 241, "name": "kbd_available", "signature": "int kbd_available(void)"}, {"kind": "function", "line": 247, "name": "kbd_read", "signature": "int kbd_read(void)"}, {"doc": "Mark the user window [USER_LOAD_BASE, USER_LOAD_END) as user-accessible (U/S bit) in the 2 MB page directory built by the boot path. A ring-3 access requires U/S set at every level of the walk, so the PML4 and PDPT entries that cover the whole identity map are lifted too; the per-2 MB isolation then lives entirely in the PD leaf bits, and every other page — page tables, kernel image, heap, VGA, MMIO — stays supervisor, so a ring-3 program is stopped in hardware from reading or writing kernel * memory.", "kind": "function", "line": 335, "name": "mm_setup_protections", "signature": "static void mm_setup_protections(void)"}, {"kind": "function", "line": 347, "name": "kallocator_init", "signature": "void kallocator_init(void)"}, {"kind": "function", "line": 354, "name": "kmalloc", "signature": "void *kmalloc(unsigned long size)"}, {"kind": "function", "line": 391, "name": "kfree", "signature": "void kfree(void *ptr)"}, {"kind": "function", "line": 426, "name": "kcalloc", "signature": "void *kcalloc(unsigned long nmemb, unsigned long size)"}, {"kind": "function", "line": 433, "name": "krealloc", "signature": "void *krealloc(void *ptr, unsigned long size)"}, {"doc": "================================================================ String functions * ================================================================", "kind": "function", "line": 464, "name": "kstrlen", "signature": "unsigned long kstrlen(const char *s)"}, {"kind": "function", "line": 470, "name": "kstrcpy", "signature": "char *kstrcpy(char *dst, const char *src)"}, {"kind": "function", "line": 476, "name": "kstrncpy", "signature": "char *kstrncpy(char *dst, const char *src, unsigned long n)"}, {"kind": "function", "line": 482, "name": "kstrncat", "signature": "char *kstrncat(char *dst, const char *src, unsigned long n)"}, {"kind": "function", "line": 490, "name": "kstrcmp", "signature": "int kstrcmp(const char *a, const char *b)"}, {"kind": "function", "line": 495, "name": "kstrncmp", "signature": "int kstrncmp(const char *a, const char *b, unsigned long n)"}, {"kind": "function", "line": 500, "name": "kstrchr", "signature": "char *kstrchr(const char *s, int c)"}, {"kind": "function", "line": 505, "name": "kstrstr", "signature": "char *kstrstr(const char *hay, const char *ndl)"}, {"kind": "function", "line": 515, "name": "kmemcpy", "signature": "void *kmemcpy(void *dst, const void *src, unsigned long n)"}, {"kind": "function", "line": 522, "name": "kmemset", "signature": "void *kmemset(void *dst, int c, unsigned long n)"}, {"kind": "function", "line": 528, "name": "kmemcmp", "signature": "int kmemcmp(const void *a, const void *b, unsigned long n)"}, {"kind": "function", "line": 534, "name": "kmemmove", "signature": "void *kmemmove(void *dst, const void *src, unsigned long n)"}, {"doc": "const unsigned char *pa = a, *pb = b; while (n--) { if (*pa != *pb) return *pa - *pb; pa++; pb++; } return 0; } void *kmemmove(void *dst, const void *src, unsigned long n) { char *d = dst; const char *s = src; if (d < s) { while (n--) *d++ = *s++; } else       { d += n; s += n; while (n--) *--d = *--s; } return dst; } /* atoi helper", "kind": "function", "line": 544, "name": "katol", "signature": "static long katol(const char *s)"}, {"doc": "Reserve a data area of `want` bytes, clamped to the configured maximum. An existing area is kept when it is already large enough, otherwise the * live contents are carried over to the new one. Returns 1 on success.", "kind": "function", "line": 579, "name": "ramdisk_reserve", "signature": "static int ramdisk_reserve(unsigned long want)"}, {"doc": "Populate the ramdisk from a packed image. The image is validated in full before any entry is published, so a rejected image leaves the directory * untouched instead of advertising files whose data was never copied.", "kind": "function", "line": 596, "name": "ramdisk_setup_from", "signature": "void ramdisk_setup_from(void *data, unsigned size)"}, {"kind": "function", "line": 647, "name": "ramdisk_init", "signature": "void ramdisk_init(void)"}, {"kind": "function", "line": 664, "name": "ramdisk_open", "signature": "RDFile *ramdisk_open(const char *name)"}, {"kind": "function", "line": 674, "name": "ramdisk_read", "signature": "int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len)"}, {"kind": "function", "line": 682, "name": "ramdisk_write", "signature": "int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len)"}, {"kind": "function", "line": 690, "name": "ramdisk_create", "signature": "RDFile *ramdisk_create(const char *name, unsigned size)"}, {"doc": "Grow or shrink an existing file by relocating the data that follows it. Files are stored back to back in the data area; this moves every file * after `f` by the size delta. Returns 1 on success, 0 on overflow.", "kind": "function", "line": 708, "name": "ramdisk_resize", "signature": "int ramdisk_resize(RDFile *f, unsigned newsize)"}, {"kind": "function", "line": 744, "name": "ramdisk_list", "signature": "int ramdisk_list(RDFile **out, int max)"}, {"doc": "Remove an entry and compact the data area. Files after `f` are shifted left by f->size and the directory slot is dropped. Returns 1 on success, * 0 when the pointer is not a live entry.", "kind": "function", "line": 756, "name": "ramdisk_delete", "signature": "int ramdisk_delete(RDFile *f)"}, {"doc": "Resolve a path against the cwd into `out` (cap >= RAMDISK_FNAME_LEN). A leading '/' starts from the root, '..' pops one component, '.' and empty components are skipped. Returns 1 on success; a name that does * not fit is rejected like a missing file, never truncated.", "kind": "function", "line": 792, "name": "fs_resolve", "signature": "static int fs_resolve(const char *path, char *out, unsigned cap)"}, {"doc": "if (*p) p++; continue; } if (len + 1 + clen >= cap) return 0; if (len > 0 && out[len - 1] != '/') out[len++] = '/'; kmemcpy(out + len, start, clen); len += clen; out[len] = 0; if (*p) p++; } return 1; } /* Does the directory `dir` (ending in '/') exist? The root always does.", "kind": "function", "line": 826, "name": "fs_dir_exists", "signature": "static int fs_dir_exists(const char *dir)"}, {"doc": "Return 1 when the resolved name refers to a directory: a trailing '/' always does, otherwise the name denotes a directory when no exact file * entry exists and some entry starts with `<name>/`.", "kind": "function", "line": 837, "name": "fs_is_dir", "signature": "static int fs_is_dir(const char *resolved)"}, {"kind": "function", "line": 849, "name": "kfopen", "signature": "KFILE *kfopen(const char *path, const char *mode)"}, {"kind": "function", "line": 874, "name": "kfclose", "signature": "int kfclose(KFILE *f)"}, {"kind": "function", "line": 883, "name": "kfgetc", "signature": "int kfgetc(KFILE *f)"}, {"doc": "Read at most size-1 bytes up to and including the first newline. Returns * buf, or 0 when nothing could be read.", "kind": "function", "line": 900, "name": "kfgets", "signature": "char *kfgets(char *buf, int size, KFILE *f)"}, {"kind": "function", "line": 913, "name": "kfungetc", "signature": "int kfungetc(int c, KFILE *f)"}, {"kind": "function", "line": 919, "name": "kfread", "signature": "unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f)"}, {"kind": "function", "line": 934, "name": "kfwrite", "signature": "unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f)"}, {"kind": "function", "line": 962, "name": "kfseek", "signature": "int kfseek(KFILE *f, long offset, int whence)"}, {"kind": "function", "line": 975, "name": "kftell", "signature": "long kftell(KFILE *f)"}, {"kind": "function", "line": 979, "name": "kfflush", "signature": "int kfflush(KFILE *f)"}, {"kind": "function", "line": 990, "name": "kfputs", "signature": "int kfputs(const char *s, KFILE *f)"}, {"kind": "function", "line": 996, "name": "kfputc", "signature": "int kfputc(int c, KFILE *f)"}, {"kind": "function", "line": 1001, "name": "krewind", "signature": "void krewind(KFILE *f)"}, {"kind": "function", "line": 1013, "name": "kfile_stdin", "signature": "KFILE *kfile_stdin(void)"}, {"kind": "function", "line": 1015, "name": "kfile_stdout", "signature": "KFILE *kfile_stdout(void)"}, {"kind": "function", "line": 1016, "name": "kfile_stderr", "signature": "KFILE *kfile_stderr(void)"}, {"doc": "================================================================ printf family * ================================================================", "kind": "function", "line": 1022, "name": "putc_buf", "signature": "static void putc_buf(char c, void *ctx, int *written)"}, {"kind": "function", "line": 1028, "name": "putc_file", "signature": "static void putc_file(char c, void *ctx, int *written)"}, {"kind": "function", "line": 1034, "name": "putc_str", "signature": "static void putc_str(char c, void *ctx, int *written)"}, {"doc": "Emit a reverse-ordered digit buffer honouring width, left-justify and * zero-fill flags. buf holds `pos` digits least-significant first.", "kind": "function", "line": 1044, "name": "emit_num", "signature": "static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,\n                ..."}, {"kind": "function", "line": 1061, "name": "kformat", "signature": "static void kformat(void (*emit)(char, void *, int *), void *ctx,\n                    int *writte..."}, {"kind": "function", "line": 1160, "name": "kprintf", "signature": "int kprintf(const char *fmt, ...)"}, {"kind": "function", "line": 1169, "name": "kfprintf", "signature": "int kfprintf(KFILE *f, const char *fmt, ...)"}, {"kind": "function", "line": 1178, "name": "ksprintf", "signature": "int ksprintf(char *buf, const char *fmt, ...)"}, {"kind": "function", "line": 1191, "name": "putc_snbuf", "signature": "static void putc_snbuf(char c, void *ctx, int *written)"}, {"kind": "function", "line": 1196, "name": "ksnprintf", "signature": "int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)"}, {"kind": "function", "line": 1222, "name": "k_register_symbol", "signature": "void k_register_symbol(const char *name, void *addr)"}, {"kind": "function", "line": 1230, "name": "ksym_resolve", "signature": "void *ksym_resolve(const char *name)"}, {"kind": "function", "line": 1256, "name": "kprog_slot", "signature": "static KProg *kprog_slot(const char *name)"}, {"kind": "function", "line": 1264, "name": "k_register_program", "signature": "void k_register_program(const char *name, prog_entry_t entry)"}, {"kind": "function", "line": 1270, "name": "k_register_process", "signature": "void k_register_process(const char *name, void *proc_entry)"}, {"kind": "function", "line": 1276, "name": "k_spawn", "signature": "int k_spawn(const char *name, int argc, char **argv)"}, {"doc": "Copy a NUL-terminated name out of a string table without reading past the table's bounds; an out-of-range or unterminated name yields an * empty string, never a wild pointer into the kernel heap.", "kind": "function", "line": 1397, "name": "elf_name_copy", "signature": "static void elf_name_copy(char *out, unsigned out_cap, const char *tab,\n                         ..."}, {"doc": "Release a partially built relocatable image and report why it was * rejected. Used on every failure path of elf_load.", "kind": "function", "line": 1413, "name": "elf_load_fail", "signature": "static void elf_load_fail(void *base, void **sec_addrs, const char *why)"}, {"kind": "function", "line": 1418, "name": "elf_load", "signature": "void *elf_load(void *data, unsigned size)"}, {"doc": "================================================================ Linux ELF executable loader (ET_EXEC / ET_DYN) + process runtime  Loads program headers into the identity-mapped user region, applies RELATIVE / IRELATIVE / symbol relocations, sets up a System V initial stack (argc/argv/envp/auxv) and jumps to the ELF entry point.  The program talks back to the kernel through the x86-64 `syscall` instruction (see the syscall dispatcher below). * ================================================================ static unsigned long g_brk;        /* current program break static unsigned long g_brk_limit;  /* upper bound for brk growth static unsigned long user_mmap_cur; /* anonymous mmap cursor, grows down", "kind": "function", "line": 1645, "name": "apply_exec_relocs", "signature": "static void apply_exec_relocs(void *data, unsigned size, unsigned long base,\n                    ..."}, {"kind": "function", "line": 1728, "name": "load_exec_elf", "signature": "void *load_exec_elf(void *data, unsigned size)"}, {"doc": "if (dst + ph[i].p_memsz > max_end) max_end = dst + ph[i].p_memsz; } if (max_end == 0) return 0; apply_exec_relocs(data, size, base, xr, nxr); g_brk       = ALIGN_UP(max_end, 0x1000); g_brk_limit = USER_BRK_END; user_mmap_cur = USER_BRK_END; return (void *)(base + e->e_entry); } /* ---- MSR access + SYSCALL/SYSRET setup ----------------------------------", "kind": "function", "line": 1783, "name": "wrmsr", "signature": "static inline void wrmsr(unsigned msr, unsigned long val)"}, {"kind": "function", "line": 1788, "name": "rdmsr", "signature": "static inline unsigned long rdmsr(unsigned msr)"}, {"kind": "function", "line": 1803, "name": "syscall_init", "signature": "void syscall_init(void)"}, {"kind": "function", "line": 1879, "name": "syscall_trace_enabled", "signature": "long syscall_trace_enabled(void)"}, {"kind": "function", "line": 1881, "name": "syscall_trace_set", "signature": "void syscall_trace_set(int on)"}, {"kind": "function", "line": 1882, "name": "ksyscall", "signature": "long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)"}, {"doc": "--- User-pointer validation --------------------------------------------- The syscall boundary is the hardened edge between ring 3 and ring 0. Every pointer a Linux ABI program hands the kernel must lie inside the user window [USER_LOAD_BASE, USER_LOAD_END), because that is the only memory the page tables marked user-accessible. Anything else — kernel heap, kernel image, page tables, MMIO — must be rejected before a single * dereference. All arithmetic is overflow checked.", "kind": "function", "line": 1902, "name": "user_range_ok", "signature": "static int user_range_ok(unsigned long p, unsigned long len)"}, {"kind": "function", "line": 1908, "name": "user_str_ok", "signature": "static int user_str_ok(unsigned long p, unsigned long maxlen)"}, {"kind": "function", "line": 1916, "name": "ksyscall_dispatch", "signature": "static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)"}, {"doc": "\"  popq %r8\\n\" \"  popq %r9\\n\" \"  xchgq %rsp, syscall_kstack(%rip)\\n\" \"  cmpq $\" STR(USER_WIN_LO) \", %rsp\\n\" \"  jb 1f\\n\" \"  cmpq $\" STR(USER_WIN_HI) \", %rsp\\n\" \"  jae 1f\\n\" \"  sysretq\\n\" \"1:\\n\" \"  jmp *%rcx\\n\" ); /* ---- Build the SysV initial stack and jump to the ELF entry -------------", "kind": "function", "line": 2121, "name": "setup_user_stack", "signature": "static unsigned long *setup_user_stack(char *sbase, unsigned long ssize,\n                        ..."}, {"kind": "function", "line": 2152, "name": "k_exec_user", "signature": "int k_exec_user(void *entry, int argc, char **argv)"}, {"doc": "\"mov %%ax, %%ds\\n\" \"mov %%ax, %%es\\n\" \"mov %%ax, %%fs\\n\" \"mov %%ax, %%gs\\n\" \"mov %%ax, %%ss\\n\" :: [kdata] \"i\"(GDT64_DATA_SEL) : \"ax\", \"memory\"); wrmsr(MSR_FSBASE, 0); wrmsr(MSR_GSBASE, 0); syscall_kstack = SYS_KSTK_TOP; return exec_exit_code; } /* Run an ET_REL program as a plain function call, but catch a libc exit().", "kind": "function", "line": 2202, "name": "k_run_rel", "signature": "int k_run_rel(prog_entry_t entry, int argc, char **argv)"}, {"doc": "syscall_kstack = SYS_KSTK_TOP; return exec_exit_code; } /* Run an ET_REL program as a plain function call, but catch a libc exit(). int k_run_rel(prog_entry_t entry, int argc, char **argv) { exec_exit_code = 0; syscall_kstack = SYS_KSTK_TOP; if (ksetjmp(&exec_return) == 0) return entry(argc, argv); return exec_exit_code; } /* libc exit() for loaded programs: unwind back to the shell.", "kind": "function", "line": 2211, "name": "kexit", "signature": "void kexit(int code)"}, {"kind": "function", "line": 2236, "name": "shell_prompt", "signature": "static void shell_prompt(void)"}, {"doc": "#define SHELL_HIST_MAX 16 static char shell_hist[SHELL_HIST_MAX][CMD_BUF_SZ]; static int  shell_hist_count; static int  shell_hist_idx = -1; static char shell_line_saved[CMD_BUF_SZ]; static int  shell_line_saved_pos; static void shell_prompt(void) { vga_puts(\"\\nminiOS> \"); } static void shell_exec_builtin(int argc, char **argv); static int console_pushback = -1; /* Blocking read from either the PS/2 keyboard or COM1 serial line.", "kind": "function", "line": 2244, "name": "console_getc", "signature": "static int console_getc(void)"}, {"doc": "Next buffered byte without consuming it, or -1 when nothing is available right now. Used to tell an ESC prefix from a complete * escape sequence, which always arrives in one burst.", "kind": "function", "line": 2267, "name": "console_peek", "signature": "static int console_peek(void)"}, {"doc": "Read one line into buf (at most size-1 chars). Echoes input and * honours backspace. Shared by the shell prompt and the editor.", "kind": "function", "line": 2283, "name": "shell_readline_buf", "signature": "static void shell_readline_buf(char *buf, int size)"}, {"kind": "function", "line": 2309, "name": "shell_readline", "signature": "static void shell_readline(void)"}, {"doc": "Redraw the edit line with the recalled text: erase what is shown, * then write the replacement into buf and onto the console.", "kind": "function", "line": 2316, "name": "shell_hist_show", "signature": "static void shell_hist_show(char *buf, int size, int *pos, const char *text)"}, {"doc": "Move through the history ring: up recalls older entries, down moves * forward again and finally restores the live line.", "kind": "function", "line": 2332, "name": "shell_hist_nav", "signature": "static void shell_hist_nav(char *buf, int size, int *pos, int up)"}, {"kind": "function", "line": 2412, "name": "shell_parse", "signature": "static int shell_parse(char *line, char **argv, int max_args)"}, {"doc": "Shell status text must never land inside a redirected command's output: `cmd > file` captures what the command wrote, not what the shell reported * about it. These helpers lift a print out of the active capture.", "kind": "function", "line": 2430, "name": "redirect_suspend", "signature": "static int redirect_suspend(void)"}, {"kind": "function", "line": 2435, "name": "redirect_resume", "signature": "static void redirect_resume(int was)"}, {"kind": "function", "line": 2439, "name": "shell_report_exit", "signature": "static void shell_report_exit(int code)"}, {"kind": "function", "line": 2445, "name": "shell_report", "signature": "static void shell_report(const char *what, const char *detail)"}, {"doc": "int was = redirect_suspend(); kprintf(\"exit code: %d\\n\", code); redirect_resume(was); } static void shell_report(const char *what, const char *detail) { int was = redirect_suspend(); vga_puts(what); if (detail) vga_puts(detail); vga_putc('\\n'); redirect_resume(was); } /* Start capturing console output for a `> file` redirection.", "kind": "function", "line": 2455, "name": "redirect_begin", "signature": "static int redirect_begin(void)"}, {"doc": "Stop capturing and store the captured bytes in `path`. Returns 0 on success. The capture is released on every path so that a failure cannot * leave the console silently detached from the screen.", "kind": "function", "line": 2466, "name": "redirect_commit", "signature": "static int redirect_commit(const char *path, int append_mode)"}, {"doc": "Split a `> file` / `>> file` redirection off the end of a parsed command line. Returns 1 when a redirection was found, 0 when there was none and -1 when the syntax is incomplete. On success argc is trimmed to the * command and append_mode is set for `>>`.", "kind": "function", "line": 2487, "name": "shell_take_redirect", "signature": "static int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)"}, {"kind": "function", "line": 2509, "name": "shell_run", "signature": "void shell_run(void)"}, {"doc": "Load an ELF file from the ramdisk and register it under its filename stem. Returns 1 for an ET_REL program, 2 for an ET_EXEC/ET_DYN Linux process, * 0 on failure.  progname_out must hold at least 32 bytes.", "kind": "function", "line": 2548, "name": "shell_load", "signature": "static int shell_load(const char *fname, char *progname_out, void **entry_out)"}, {"kind": "function", "line": 2604, "name": "edit_alloc", "signature": "static EditBuf *edit_alloc(const char *fname)"}, {"kind": "function", "line": 2620, "name": "edit_free", "signature": "static void edit_free(EditBuf *e)"}, {"kind": "function", "line": 2626, "name": "edit_load", "signature": "static int edit_load(EditBuf *e)"}, {"kind": "function", "line": 2661, "name": "edit_save", "signature": "static int edit_save(EditBuf *e)"}, {"kind": "function", "line": 2675, "name": "edit_print", "signature": "static void edit_print(EditBuf *e, int idx)"}, {"kind": "function", "line": 2683, "name": "edit_list", "signature": "static void edit_list(EditBuf *e)"}, {"kind": "function", "line": 2692, "name": "edit_set_line", "signature": "static int edit_set_line(EditBuf *e, int idx, const char *text)"}, {"kind": "function", "line": 2701, "name": "edit_insert", "signature": "static int edit_insert(EditBuf *e, int idx, const char *text)"}, {"kind": "function", "line": 2711, "name": "edit_delete", "signature": "static int edit_delete(EditBuf *e, int idx)"}, {"kind": "function", "line": 2720, "name": "edit_usage", "signature": "static void edit_usage(void)"}, {"doc": "A buffer that did not hold the whole file must never be written back: * saving it would drop the part that was never loaded.", "kind": "function", "line": 2729, "name": "edit_refuse_save", "signature": "static int edit_refuse_save(EditBuf *e)"}, {"kind": "function", "line": 2734, "name": "edit_loop", "signature": "static void edit_loop(EditBuf *e)"}, {"kind": "function", "line": 2798, "name": "shell_cmd_edit", "signature": "static void shell_cmd_edit(int argc, char **argv)"}, {"kind": "function", "line": 2830, "name": "outw_port", "signature": "static inline void outw_port(unsigned short port, unsigned short val)"}, {"doc": "define QEMU_PM_PORT 0x604", "kind": "function", "line": 2836, "name": "shell_cmd_poweroff", "signature": "static void shell_cmd_poweroff(void)"}, {"doc": "Resolve a command through the bin path: load /bin/<cmd> (root-anchored, like Linux /bin, so the cwd never changes where commands are found) from the ramdisk as a Linux ELF and run it with the original argv. Returns * the exit code or -1 when the name is not eligible or no ELF exists.", "kind": "function", "line": 2847, "name": "shell_run_from_path", "signature": "static int shell_run_from_path(const char *cmd, int argc, char **argv)"}, {"kind": "function", "line": 2861, "name": "shell_exec_builtin", "signature": "static void shell_exec_builtin(int argc, char **argv)"}, {"doc": "================================================================ Libc symbol registration * ================================================================", "kind": "function", "line": 3121, "name": "register_libc_symbols", "signature": "static void register_libc_symbols(void)"}, {"kind": "function", "line": 3188, "name": "__attribute__", "signature": "__attribute__((section(\".init.text\")))\nvoid kmain(void)"}, {"kind": "macro", "line": 22, "name": "COM1"}, {"kind": "macro", "line": 124, "name": "REDIR_INITIAL_CAP"}, {"kind": "macro", "line": 125, "name": "REDIR_MAX_BYTES"}, {"kind": "macro", "line": 216, "name": "KBD_QUEUE_LEN"}, {"kind": "macro", "line": 285, "name": "ALLOC_MAGIC"}, {"kind": "macro", "line": 287, "name": "FREE_MAGIC"}, {"kind": "macro", "line": 288, "name": "ALIGN_UP"}, {"kind": "macro", "line": 295, "name": "BLOCK_HDR_SZ"}, {"kind": "macro", "line": 306, "name": "USER_LOAD_BASE"}, {"kind": "macro", "line": 307, "name": "USER_LOAD_END"}, {"kind": "macro", "line": 308, "name": "USER_STACK_SIZE"}, {"kind": "macro", "line": 309, "name": "USER_STACK_TOP"}, {"kind": "macro", "line": 310, "name": "USER_STACK_BASE"}, {"kind": "macro", "line": 311, "name": "USER_BRK_END"}, {"kind": "macro", "line": 312, "name": "SYS_KSTK_TOP"}, {"kind": "macro", "line": 313, "name": "SYS_KSTK_BASE"}, {"kind": "macro", "line": 314, "name": "HEAP_BASE"}, {"kind": "macro", "line": 315, "name": "HEAP_SIZE"}, {"kind": "macro", "line": 316, "name": "EFAULT"}, {"kind": "macro", "line": 322, "name": "USER_WIN_LO"}, {"kind": "macro", "line": 323, "name": "USER_WIN_HI"}, {"kind": "macro", "line": 324, "name": "STR_"}, {"kind": "macro", "line": 325, "name": "STR"}, {"kind": "macro", "line": 557, "name": "RD_MAGIC"}, {"kind": "macro", "line": 559, "name": "RD_HEADER_SIZE"}, {"kind": "macro", "line": 560, "name": "RD_ENTRY_SIZE"}, {"kind": "macro", "line": 561, "name": "RD_DATA_MIN"}, {"kind": "macro", "line": 562, "name": "RD_DATA_SPARE"}, {"kind": "macro", "line": 563, "name": "RD_DATA_MAX"}, {"kind": "macro", "line": 1212, "name": "KSYM_MAX"}, {"kind": "macro", "line": 1244, "name": "KPROG_MAX"}, {"kind": "macro", "line": 1296, "name": "EI_NIDENT"}, {"kind": "macro", "line": 1359, "name": "ELF64_R_SYM"}, {"kind": "macro", "line": 1361, "name": "ELF64_R_TYPE"}, {"kind": "macro", "line": 1362, "name": "SHN_UNDEF"}, {"kind": "macro", "line": 1363, "name": "SHT_SYMTAB"}, {"kind": "macro", "line": 1365, "name": "SHT_STRTAB"}, {"kind": "macro", "line": 1366, "name": "SHT_RELA"}, {"kind": "macro", "line": 1367, "name": "SHT_PROGBITS"}, {"kind": "macro", "line": 1368, "name": "SHT_NOBITS"}, {"kind": "macro", "line": 1369, "name": "SHF_ALLOC"}, {"kind": "macro", "line": 1370, "name": "SHF_EXECINSTR"}, {"kind": "macro", "line": 1371, "name": "ET_REL"}, {"kind": "macro", "line": 1373, "name": "ET_EXEC"}, {"kind": "macro", "line": 1374, "name": "ET_DYN"}, {"kind": "macro", "line": 1375, "name": "EM_X86_64"}, {"kind": "macro", "line": 1376, "name": "PT_LOAD"}, {"kind": "macro", "line": 1377, "name": "R_X86_64_64"}, {"kind": "macro", "line": 1379, "name": "R_X86_64_PC32"}, {"kind": "macro", "line": 1380, "name": "R_X86_64_PLT32"}, {"kind": "macro", "line": 1381, "name": "R_X86_64_GLOB_DAT"}, {"kind": "macro", "line": 1382, "name": "R_X86_64_JUMP_SLOT"}, {"kind": "macro", "line": 1383, "name": "R_X86_64_RELATIVE"}, {"kind": "macro", "line": 1384, "name": "R_X86_64_32"}, {"kind": "macro", "line": 1385, "name": "R_X86_64_32S"}, {"kind": "macro", "line": 1386, "name": "R_X86_64_IRELATIVE"}, {"kind": "macro", "line": 1387, "name": "PF_X"}, {"kind": "macro", "line": 1389, "name": "ELF_MAX_SEGMENTS"}, {"kind": "macro", "line": 1390, "name": "ELF_NAME_MAX"}, {"kind": "macro", "line": 1793, "name": "MSR_EFER"}, {"kind": "macro", "line": 1795, "name": "MSR_STAR"}, {"kind": "macro", "line": 1796, "name": "MSR_LSTAR"}, {"kind": "macro", "line": 1797, "name": "MSR_SFMASK"}, {"kind": "macro", "line": 1798, "name": "MSR_FSBASE"}, {"kind": "macro", "line": 1799, "name": "MSR_GSBASE"}, {"kind": "macro", "line": 1859, "name": "KFD_MAX"}, {"kind": "macro", "line": 1869, "name": "SYSCALL_TRACE"}, {"kind": "macro", "line": 2220, "name": "CMD_BUF_SZ"}, {"kind": "macro", "line": 2222, "name": "MAX_ARGS"}, {"kind": "macro", "line": 2223, "name": "SHELL_BIN_PATH"}, {"kind": "macro", "line": 2225, "name": "SHELL_BIN_PATH_LEN"}, {"kind": "macro", "line": 2226, "name": "SHELL_BIN_MAX_CMD"}, {"kind": "macro", "line": 2229, "name": "SHELL_HIST_MAX"}, {"kind": "macro", "line": 2587, "name": "EDIT_MAX_LINES"}, {"kind": "macro", "line": 2589, "name": "EDIT_LINE_MAX"}, {"kind": "macro", "line": 2590, "name": "EDIT_FILE_MAX"}, {"kind": "macro", "line": 2834, "name": "QEMU_PM_PORT"}]}, {"doc": "ifndef KERNEL_H define KERNEL_H  ========== VGA text mode ==========", "id": "kernel.h", "kind": "module", "label": "kernel.h", "language": "h", "sha256": "e6955a0b85fa8195", "symbol_count": 19, "symbols": [{"kind": "macro", "line": 2, "name": "KERNEL_H"}, {"kind": "macro", "line": 5, "name": "VGA_BASE"}, {"kind": "macro", "line": 6, "name": "VGA_COLS"}, {"kind": "macro", "line": 7, "name": "VGA_ROWS"}, {"kind": "macro", "line": 24, "name": "KEY_BACKSPACE"}, {"kind": "macro", "line": 25, "name": "KEY_ENTER"}, {"kind": "macro", "line": 26, "name": "KEY_LSHIFT"}, {"kind": "macro", "line": 27, "name": "KEY_RSHIFT"}, {"kind": "macro", "line": 28, "name": "KEY_CAPS"}, {"kind": "macro", "line": 29, "name": "KEY_E0"}, {"kind": "macro", "line": 30, "name": "KEY_UP"}, {"kind": "macro", "line": 31, "name": "KEY_DOWN"}, {"kind": "macro", "line": 32, "name": "KEY_ESC"}, {"kind": "macro", "line": 33, "name": "KEY_CSI"}, {"kind": "macro", "line": 34, "name": "KEY_ARR_UP"}, {"kind": "macro", "line": 35, "name": "KEY_ARR_DOWN"}, {"kind": "macro", "line": 48, "name": "RAMDISK_MAX_FILES"}, {"kind": "macro", "line": 49, "name": "RAMDISK_FNAME_LEN"}, {"kind": "macro", "line": 68, "name": "EOF"}]}, {"id": "mcp/__init__.py", "kind": "module", "label": "__init__.py", "language": "py", "sha256": "9a62779e844a15fa", "symbol_count": 0, "symbols": []}, {"id": "mcp/mcp_dbg_driver.py", "kind": "module", "label": "mcp_dbg_driver.py", "language": "py", "sha256": "d729864610ee717c", "symbol_count": 6, "symbols": [{"kind": "class", "line": 14, "name": "Client", "signature": "class Client"}, {"kind": "method", "line": 62, "name": "main", "signature": "def main()"}, {"kind": "method", "line": 15, "name": "__init__", "signature": "def __init__(self)"}, {"kind": "method", "line": 26, "name": "request", "signature": "def request(self, method, params)"}, {"kind": "method", "line": 44, "name": "tool", "signature": "def tool(self, name, params)"}, {"kind": "method", "line": 52, "name": "close", "signature": "def close(self)"}]}, {"id": "mcp/mcp_dogfood.py", "kind": "module", "label": "mcp_dogfood.py", "language": "py", "sha256": "0fca1f780714df8f", "symbol_count": 6, "symbols": [{"kind": "class", "line": 18, "name": "Client", "signature": "class Client"}, {"kind": "method", "line": 76, "name": "main", "signature": "def main()"}, {"kind": "method", "line": 19, "name": "__init__", "signature": "def __init__(self, addons_dir)"}, {"kind": "method", "line": 38, "name": "request", "signature": "def request(self, method, params)"}, {"kind": "method", "line": 56, "name": "tool", "signature": "def tool(self, name, params)"}, {"kind": "method", "line": 66, "name": "close", "signature": "def close(self)"}]}, {"id": "mcp/minios_addons.py", "kind": "module", "label": "minios_addons.py", "language": "py", "sha256": "26bc9344556d357f", "symbol_count": 16, "symbols": [{"doc": "Expected marketplace failure, reported to the client as isError.", "kind": "class", "line": 42, "name": "AddonError", "signature": "class AddonError(Exception)"}, {"kind": "method", "line": 48, "name": "_clean", "signature": "def _clean(s)"}, {"kind": "method", "line": 52, "name": "_unquote", "signature": "def _unquote(v)"}, {"doc": "Parse the strict YAML subset. Returns the addon dict.\n\nGrammar: flat `key: value` lines; `install:` opens an indented block\nwith `repo_url:`, a `files:` list of `- src:`/`dst:` pairs, and\n`build:` / `verify:` lists of `- ...` command lines (`verify` items\nmay carry a nested `exit_code:`). Everything else is a parse error\nwith its line number.", "kind": "method", "line": 59, "name": "parse_addon_yaml", "signature": "def parse_addon_yaml(text)"}, {"doc": "Check bounds and character sets. Raises AddonError.", "kind": "method", "line": 189, "name": "validate_addon", "signature": "def validate_addon(addon, source)"}, {"doc": "dst paths live on the ramdisk: relative, no '..', bounded charset.", "kind": "method", "line": 250, "name": "validate_addon_path", "signature": "def validate_addon_path(path)"}, {"doc": "Build/verify lines are single printable-ASCII shell commands.", "kind": "method", "line": 264, "name": "validate_shell_line", "signature": "def validate_shell_line(line)"}, {"doc": "Load every addon yaml; each entry is a dict or an error string.", "kind": "method", "line": 278, "name": "load_addons_dir", "signature": "def load_addons_dir(addons_dir)"}, {"doc": "Split a source into editor-sized chunks. Raises AddonError.", "kind": "method", "line": 302, "name": "split_for_editor", "signature": "def split_for_editor(text)"}, {"kind": "method", "line": 327, "name": "exit_code_of", "signature": "def exit_code_of(text)"}, {"doc": "Host-side record of installed addons (system temp dir).", "kind": "class", "line": 332, "name": "AddonState", "signature": "class AddonState"}, {"doc": "Install one validated addon into the booted MiniOS session.\n\nFailure at any step raises AddonError; upload parts are removed and\nnothing is recorded, so a half-installed package is never reported.", "kind": "method", "line": 356, "name": "install_addon", "signature": "def install_addon(session, addon, cfg)"}, {"kind": "method", "line": 69, "name": "fail", "signature": "def fail(lineno, why)"}, {"kind": "method", "line": 335, "name": "__init__", "signature": "def __init__(self, path)"}, {"kind": "method", "line": 338, "name": "load", "signature": "def load(self)"}, {"kind": "method", "line": 348, "name": "save", "signature": "def save(self, addons)"}]}, {"id": "mcp/minios_mcp.py", "kind": "module", "label": "minios_mcp.py", "language": "py", "sha256": "f9cc2728a96bf30d", "symbol_count": 48, "symbols": [{"doc": "Resolve the configuration: defaults overridden by the environment.", "kind": "function", "line": 68, "name": "env_config", "signature": "def env_config()"}, {"doc": "Clamp a requested wait to the bounded timeout range.", "kind": "function", "line": 86, "name": "clamp_timeout", "signature": "def clamp_timeout(ms)"}, {"doc": "Reject file names the ramdisk or the shell would mishandle.", "kind": "function", "line": 99, "name": "validate_path", "signature": "def validate_path(name)"}, {"doc": "Reject lines the kernel readline cannot carry (printable ASCII).", "kind": "function", "line": 115, "name": "validate_content", "signature": "def validate_content(text)"}, {"doc": "Expected tool failure, reported to the client as isError.", "kind": "class", "line": 128, "name": "ToolError", "signature": "class ToolError(Exception)"}, {"doc": "JSON-RPC level failure carrying a standard error code.", "kind": "class", "line": 134, "name": "RPCError", "signature": "class RPCError(Exception)"}, {"doc": "Bounded console log with absolute byte positions and waits.", "kind": "class", "line": 143, "name": "LogBuffer", "signature": "class LogBuffer"}, {"doc": "One QEMU child, one pty, one console log, one consume cursor.", "kind": "class", "line": 199, "name": "MiniOSSession", "signature": "class MiniOSSession"}, {"kind": "method", "line": 493, "name": "subprocess_launch", "signature": "def subprocess_launch(cfg, slave_fd)"}, {"doc": "JSON-RPC dispatch loop over stdio.", "kind": "class", "line": 605, "name": "MCPServer", "signature": "class MCPServer"}, {"kind": "method", "line": 743, "name": "main", "signature": "def main()"}, {"kind": "method", "line": 137, "name": "__init__", "signature": "def __init__(self, code, message)"}, {"kind": "method", "line": 146, "name": "__init__", "signature": "def __init__(self, cap)"}, {"kind": "method", "line": 152, "name": "append", "signature": "def append(self, data)"}, {"kind": "method", "line": 160, "name": "bytes_from", "signature": "def bytes_from(self, pos)"}, {"kind": "method", "line": 165, "name": "text_from", "signature": "def text_from(self, pos, end)"}, {"kind": "method", "line": 172, "name": "find", "signature": "def find(self, marker, start)"}, {"doc": "Block until marker appears at or after start; return position.", "kind": "method", "line": 176, "name": "wait_for", "signature": "def wait_for(self, marker, start, timeout_ms)"}, {"kind": "method", "line": 189, "name": "_find_locked", "signature": "def _find_locked(self, marker, start)"}, {"kind": "method", "line": 202, "name": "__init__", "signature": "def __init__(self, cfg)"}, {"kind": "method", "line": 213, "name": "booted", "signature": "def booted(self)"}, {"kind": "method", "line": 216, "name": "status", "signature": "def status(self)"}, {"kind": "method", "line": 225, "name": "_reap_stale", "signature": "def _reap_stale(self)"}, {"kind": "method", "line": 261, "name": "_drop_pidfile", "signature": "def _drop_pidfile(self)"}, {"kind": "method", "line": 267, "name": "boot", "signature": "def boot(self, timeout_ms)"}, {"kind": "method", "line": 302, "name": "_read_loop", "signature": "def _read_loop(self)"}, {"kind": "method", "line": 312, "name": "_close_pty", "signature": "def _close_pty(self)"}, {"kind": "method", "line": 322, "name": "_write_line", "signature": "def _write_line(self, line)"}, {"doc": "Editor content lines may be empty (blank lines in the file).", "kind": "method", "line": 331, "name": "_write_editor_line", "signature": "def _write_editor_line(self, line)"}, {"kind": "method", "line": 339, "name": "send", "signature": "def send(self, line, timeout_ms)"}, {"kind": "method", "line": 350, "name": "expect", "signature": "def expect(self, marker, timeout_ms)"}, {"kind": "method", "line": 364, "name": "snapshot", "signature": "def snapshot(self, max_bytes)"}, {"kind": "method", "line": 374, "name": "cat", "signature": "def cat(self, path)"}, {"doc": "Read a ramdisk file and return exactly its bytes.\n\nThe serial driver emits CRLF; the kernel cat appends one newline\nafter the content, so the body is extracted by stripping the echoed\ncommand line, the prompt and that single trailing newline.", "kind": "method", "line": 380, "name": "cat_body", "signature": "def cat_body(self, path, missing_ok)"}, {"kind": "method", "line": 406, "name": "_cleanup_parts", "signature": "def _cleanup_parts(self, parts)"}, {"kind": "method", "line": 413, "name": "write", "signature": "def write(self, path, content)"}, {"kind": "method", "line": 450, "name": "poweroff", "signature": "def poweroff(self, timeout_ms)"}, {"kind": "method", "line": 470, "name": "terminate", "signature": "def terminate(self)"}, {"kind": "method", "line": 489, "name": "close", "signature": "def close(self)"}, {"kind": "method", "line": 608, "name": "__init__", "signature": "def __init__(self, cfg)"}, {"kind": "method", "line": 612, "name": "run", "signature": "def run(self)"}, {"kind": "method", "line": 620, "name": "_handle", "signature": "def _handle(self, line)"}, {"kind": "method", "line": 646, "name": "_initialize", "signature": "def _initialize(self, params)"}, {"kind": "method", "line": 653, "name": "_call", "signature": "def _call(self, params)"}, {"kind": "method", "line": 670, "name": "_dispatch", "signature": "def _dispatch(self, name, args)"}, {"kind": "method", "line": 697, "name": "_addons_list", "signature": "def _addons_list(self)"}, {"kind": "method", "line": 718, "name": "_addon_install", "signature": "def _addon_install(self, args)"}, {"kind": "method", "line": 739, "name": "_reply", "signature": "def _reply(self, msg)"}]}, {"doc": "Mutation testing for the MiniOS MCP bridge. Every mutant is injected into a private copy of minios_mcp.py and run against the unit and BDD suite. A mutant that survives (suite fully green) exposes a test gap.  Suites run in parallel (one worker per core, MUTATE_JOBS to override); each mutant gets its own pid file and addon state so the runs stay independent.  Mutation format: \"name | sed -i expression | file\"", "id": "mcp/mutate_mcp.sh", "kind": "module", "label": "mutate_mcp.sh", "language": "sh", "sha256": "fff886f5090d023d", "symbol_count": 1, "symbols": [{"doc": "Each mutant runs the suite in its own directory with its own pid file and addon state, so the runs are independent and may execute in parallel. The worker writes the exit code; the loop below maps it onto the verdict.", "kind": "function", "line": 115, "name": "run_one"}]}, {"id": "mcp/test_minios_mcp.py", "kind": "module", "label": "test_minios_mcp.py", "language": "py", "sha256": "2d3a02511a702c8d", "symbol_count": 95, "symbols": [{"kind": "function", "line": 29, "name": "load_module", "signature": "def load_module()"}, {"kind": "function", "line": 49, "name": "have_qemu", "signature": "def have_qemu()"}, {"doc": "Child process running minios_mcp.py, driven over stdio JSON-RPC.", "kind": "class", "line": 55, "name": "MCPServer", "signature": "class MCPServer"}, {"kind": "class", "line": 138, "name": "TestProtocol", "signature": "class TestProtocol(TestCase)"}, {"kind": "class", "line": 193, "name": "TestValidation", "signature": "class TestValidation(TestCase)"}, {"kind": "class", "line": 242, "name": "TestLogBuffer", "signature": "class TestLogBuffer(TestCase)"}, {"doc": "Fail-fast for QEMU-backed classes: once a tool call has hit a\nconsole wait timeout the bridge is stuck (a mutated marker, a hung\nshell) and every remaining test would only burn its own timeout, so\nthey are skipped instead.", "kind": "class", "line": 274, "name": "_ConsoleBDDBase", "signature": "class _ConsoleBDDBase(TestCase)"}, {"kind": "class", "line": 310, "name": "TestMiniOSBDD", "signature": "class TestMiniOSBDD(_ConsoleBDDBase)"}, {"kind": "class", "line": 412, "name": "TestAddonYaml", "signature": "class TestAddonYaml(TestCase)"}, {"kind": "class", "line": 474, "name": "TestAddonHelpers", "signature": "class TestAddonHelpers(TestCase)"}, {"doc": "In-memory stand-in for the MiniOS session (no QEMU).", "kind": "class", "line": 514, "name": "FakeOS", "signature": "class FakeOS"}, {"kind": "class", "line": 580, "name": "TestAddonInstall", "signature": "class TestAddonInstall(TestCase)"}, {"doc": "Install a fixture addon from a local git repo into the real OS.", "kind": "class", "line": 715, "name": "TestAddonBDD", "signature": "class TestAddonBDD(_ConsoleBDDBase)"}, {"kind": "method", "line": 58, "name": "__init__", "signature": "def __init__(self, env_extra)"}, {"kind": "method", "line": 77, "name": "initialize", "signature": "def initialize(self)"}, {"kind": "method", "line": 81, "name": "request", "signature": "def request(self, method, params)"}, {"kind": "method", "line": 88, "name": "raw", "signature": "def raw(self, line)"}, {"kind": "method", "line": 93, "name": "_read_response", "signature": "def _read_response(self)"}, {"kind": "method", "line": 99, "name": "_roundtrip", "signature": "def _roundtrip(self, msg)"}, {"kind": "method", "line": 107, "name": "tool", "signature": "def tool(self, name, params)"}, {"kind": "method", "line": 117, "name": "close", "signature": "def close(self)"}, {"kind": "method", "line": 140, "name": "setUpClass", "signature": "def setUpClass(cls)"}, {"kind": "method", "line": 146, "name": "tearDownClass", "signature": "def tearDownClass(cls)"}, {"kind": "method", "line": 149, "name": "test_initialize", "signature": "def test_initialize(self)"}, {"kind": "method", "line": 155, "name": "test_tools_list", "signature": "def test_tools_list(self)"}, {"kind": "method", "line": 163, "name": "test_ping", "signature": "def test_ping(self)"}, {"kind": "method", "line": 167, "name": "test_unknown_method", "signature": "def test_unknown_method(self)"}, {"kind": "method", "line": 171, "name": "test_malformed_json", "signature": "def test_malformed_json(self)"}, {"kind": "method", "line": 175, "name": "test_unknown_tool", "signature": "def test_unknown_tool(self)"}, {"kind": "method", "line": 180, "name": "test_send_not_booted", "signature": "def test_send_not_booted(self)"}, {"kind": "method", "line": 186, "name": "test_send_empty_line_rejected", "signature": "def test_send_empty_line_rejected(self)"}, {"kind": "method", "line": 195, "name": "setUpClass", "signature": "def setUpClass(cls)"}, {"kind": "method", "line": 200, "name": "test_path_accepts_plain_names", "signature": "def test_path_accepts_plain_names(self)"}, {"kind": "method", "line": 204, "name": "test_path_rejects_unsafe", "signature": "def test_path_rejects_unsafe(self)"}, {"kind": "method", "line": 208, "name": "test_path_rejects_long", "signature": "def test_path_rejects_long(self)"}, {"kind": "method", "line": 211, "name": "test_content_accepts_ascii", "signature": "def test_content_accepts_ascii(self)"}, {"kind": "method", "line": 214, "name": "test_content_rejects_non_printable", "signature": "def test_content_rejects_non_printable(self)"}, {"kind": "method", "line": 218, "name": "test_timeout_clamped", "signature": "def test_timeout_clamped(self)"}, {"kind": "method", "line": 222, "name": "test_write_rejects_line_too_long", "signature": "def test_write_rejects_line_too_long(self)"}, {"kind": "method", "line": 231, "name": "test_write_rejects_too_many_lines", "signature": "def test_write_rejects_too_many_lines(self)"}, {"kind": "method", "line": 244, "name": "setUpClass", "signature": "def setUpClass(cls)"}, {"kind": "method", "line": 249, "name": "test_bounds", "signature": "def test_bounds(self)"}, {"kind": "method", "line": 256, "name": "test_find_and_total", "signature": "def test_find_and_total(self)"}, {"kind": "method", "line": 263, "name": "test_cursor_prevents_stale_match", "signature": "def test_cursor_prevents_stale_match(self)"}, {"kind": "method", "line": 283, "name": "guard_server", "signature": "def guard_server(cls)"}, {"kind": "method", "line": 304, "name": "setUp", "signature": "def setUp(self)"}, {"kind": "method", "line": 312, "name": "setUpClass", "signature": "def setUpClass(cls)"}, {"kind": "method", "line": 319, "name": "tearDownClass", "signature": "def tearDownClass(cls)"}, {"kind": "method", "line": 323, "name": "test_t01_boot", "signature": "def test_t01_boot(self)"}, {"kind": "method", "line": 333, "name": "test_t02_expect", "signature": "def test_t02_expect(self)"}, {"kind": "method", "line": 340, "name": "test_t03_write_and_cat", "signature": "def test_t03_write_and_cat(self)"}, {"kind": "method", "line": 350, "name": "test_t04_toolchain_elf", "signature": "def test_t04_toolchain_elf(self)"}, {"kind": "method", "line": 361, "name": "test_t05_toolchain_cvm", "signature": "def test_t05_toolchain_cvm(self)"}, {"kind": "method", "line": 371, "name": "test_t06_selfhosted_compiler", "signature": "def test_t06_selfhosted_compiler(self)"}, {"kind": "method", "line": 377, "name": "test_t07_bin_command_path", "signature": "def test_t07_bin_command_path(self)"}, {"kind": "method", "line": 385, "name": "test_t08_poweroff_and_reboot", "signature": "def test_t08_poweroff_and_reboot(self)"}, {"kind": "method", "line": 414, "name": "setUpClass", "signature": "def setUpClass(cls)"}, {"kind": "method", "line": 424, "name": "test_parse_valid", "signature": "def test_parse_valid(self)"}, {"kind": "method", "line": 434, "name": "test_validate_accepts_valid", "signature": "def test_validate_accepts_valid(self)"}, {"kind": "method", "line": 438, "name": "test_unknown_key_rejected", "signature": "def test_unknown_key_rejected(self)"}, {"kind": "method", "line": 442, "name": "test_bad_indent_rejected", "signature": "def test_bad_indent_rejected(self)"}, {"kind": "method", "line": 446, "name": "test_validate_rejects_bad_dst", "signature": "def test_validate_rejects_bad_dst(self)"}, {"kind": "method", "line": 451, "name": "test_validate_rejects_missing_name", "signature": "def test_validate_rejects_missing_name(self)"}, {"kind": "method", "line": 455, "name": "test_validate_rejects_long_build_line", "signature": "def test_validate_rejects_long_build_line(self)"}, {"kind": "method", "line": 463, "name": "test_validate_rejects_control_chars", "signature": "def test_validate_rejects_control_chars(self)"}, {"kind": "method", "line": 468, "name": "test_validate_rejects_empty_files", "signature": "def test_validate_rejects_empty_files(self)"}, {"kind": "method", "line": 476, "name": "setUpClass", "signature": "def setUpClass(cls)"}, {"kind": "method", "line": 486, "name": "test_split_for_editor_chunks", "signature": "def test_split_for_editor_chunks(self)"}, {"kind": "method", "line": 493, "name": "test_split_rejects_long_line", "signature": "def test_split_rejects_long_line(self)"}, {"kind": "method", "line": 497, "name": "test_split_rejects_non_ascii", "signature": "def test_split_rejects_non_ascii(self)"}, {"kind": "method", "line": 501, "name": "test_exit_code_of", "signature": "def test_exit_code_of(self)"}, {"kind": "method", "line": 506, "name": "test_state_roundtrip", "signature": "def test_state_roundtrip(self)"}, {"kind": "method", "line": 517, "name": "__init__", "signature": "def __init__(self, exit_codes)"}, {"kind": "method", "line": 524, "name": "booted", "signature": "def booted(self)"}, {"kind": "method", "line": 527, "name": "boot", "signature": "def boot(self, timeout_ms)"}, {"kind": "method", "line": 531, "name": "write", "signature": "def write(self, path, content)"}, {"kind": "method", "line": 538, "name": "send", "signature": "def send(self, line, timeout_ms)"}, {"kind": "method", "line": 562, "name": "cat_body", "signature": "def cat_body(self, path, missing_ok)"}, {"kind": "class", "line": 569, "name": "_toolerror", "signature": "class _toolerror(Exception)"}, {"kind": "method", "line": 574, "name": "_cleanup_parts", "signature": "def _cleanup_parts(self, parts)"}, {"kind": "method", "line": 582, "name": "setUpClass", "signature": "def setUpClass(cls)"}, {"kind": "method", "line": 614, "name": "tearDownClass", "signature": "def tearDownClass(cls)"}, {"kind": "method", "line": 619, "name": "make_addon", "signature": "def make_addon(self)"}, {"kind": "method", "line": 641, "name": "test_install_success", "signature": "def test_install_success(self)"}, {"kind": "method", "line": 654, "name": "test_install_mismatch_aborts_and_cleans", "signature": "def test_install_mismatch_aborts_and_cleans(self)"}, {"kind": "method", "line": 668, "name": "test_install_multi_chunk_reassembly", "signature": "def test_install_multi_chunk_reassembly(self)"}, {"kind": "method", "line": 699, "name": "test_install_verify_failure_aborts", "signature": "def test_install_verify_failure_aborts(self)"}, {"kind": "method", "line": 706, "name": "test_install_build_failure_aborts", "signature": "def test_install_build_failure_aborts(self)"}, {"kind": "method", "line": 719, "name": "setUpClass", "signature": "def setUpClass(cls)"}, {"kind": "method", "line": 756, "name": "tearDownClass", "signature": "def tearDownClass(cls)"}, {"kind": "method", "line": 764, "name": "test_addons_list", "signature": "def test_addons_list(self)"}, {"kind": "method", "line": 770, "name": "test_install_fixture", "signature": "def test_install_fixture(self)"}, {"kind": "method", "line": 779, "name": "test_install_unknown_addon_fails", "signature": "def test_install_unknown_addon_fails(self)"}, {"kind": "method", "line": 286, "name": "guarded", "signature": "def guarded(name, params)"}, {"kind": "method", "line": 658, "name": "broken_cat", "signature": "def broken_cat(path, missing_ok)"}]}, {"id": "mkramdisk.py", "kind": "module", "label": "mkramdisk.py", "language": "py", "sha256": "e890ba2ab94eb112", "symbol_count": 2, "symbols": [{"kind": "function", "line": 20, "name": "pack_name", "signature": "def pack_name(path, common)"}, {"kind": "function", "line": 30, "name": "main", "signature": "def main()"}]}, {"doc": "mkroots.sh - regenerate tls_roots.h from the DER files in tls_roots_src/.  Provenance of each root (2026 web PKI reality; everything a real site chains to is one of these):  isrg_root_x1.der          Let's Encrypt ISRG Root X1 (RSA, older chains) https://letsencrypt.org/certs/isrg-root-x1.pem isrg_root_x2.der          Let's Encrypt ISRG Root X2 (ECDSA P-384, current) https://letsencrypt.org/certs/isrg-root-x2.pem digicert_global_root_g2.der  DigiCert Global Root G2 (RSA) https://cacerts.digicert.com/DigiCertGlobalRootG2.crt globalsign_root_r3.der    GlobalSign Root CA R3 (RSA) https://secure.globalsign.com/cacert/root-r3.crt gts_root_r4.der           Google Trust Services Root R4 (ECDSA P-384) https://pki.goog/repo/certs/gtsr4.pem sslcom_ecc_2022.der       SSL.com TLS ECC Root CA 2022 (Cloudflare ECC chains) sslcom_rsa_2022.der       SSL.com TLS RSA Root CA 2022 (Cloudflare RSA chains)  The two SSL.com roots have no stable public URL; they are extracted from the certificate chain example.com serves (openssl s_client -showcerts, ECDHE-ECDSA and ECDHE-RSA respectively). The build never runs this script: tls_roots.h is a committed input, regenerated only when the root set changes.", "id": "mkroots.sh", "kind": "module", "label": "mkroots.sh", "language": "sh", "sha256": "785077624212c370", "symbol_count": 0, "symbols": []}, {"doc": "Mutation testing for MiniOS.  Each mutation is applied to the source in place, the disk image is rebuilt and the behavioural suite is run in fail-fast mode. A mutant that survives a full green suite exposes a gap that must be closed by adding a scenario, never by deleting the mutant.  The sources are backed up before the first mutation and restored on every exit path, including interrupts. A mutation whose expression matches nothing is reported as broken rather than surviving: `sed -i` exits zero when it changes nothing, which would otherwise rebuild pristine sources and look like a test gap.  Mutation format: \"name | sed -i expression | file\"", "id": "mutate.sh", "kind": "module", "label": "mutate.sh", "language": "sh", "sha256": "a01bc09d995ea4ee", "symbol_count": 2, "symbols": [{"kind": "function", "line": 24, "name": "restore_sources"}, {"kind": "function", "line": 31, "name": "cleanup"}]}, {"doc": "MiniOS network stack: rtl8139 under QEMU slirp user networking.", "id": "net.c", "kind": "module", "label": "net.c", "language": "c", "sha256": "0b8a0adc86d17617", "symbol_count": 84, "symbols": [{"kind": "struct", "line": 250, "name": "net_arp_entry"}, {"kind": "struct", "line": 376, "name": "net_dns_state"}, {"kind": "struct", "line": 544, "name": "net_tcp_sock"}, {"kind": "function", "line": 24, "name": "outb_port", "signature": "static void outb_port(unsigned short port, unsigned char val)"}, {"kind": "function", "line": 28, "name": "inb_port", "signature": "static unsigned char inb_port(unsigned short port)"}, {"kind": "function", "line": 34, "name": "outw_port", "signature": "static void outw_port(unsigned short port, unsigned short val)"}, {"kind": "function", "line": 38, "name": "outl_port", "signature": "static void outl_port(unsigned short port, unsigned int val)"}, {"kind": "function", "line": 42, "name": "inw_port", "signature": "static unsigned short inw_port(unsigned short port)"}, {"kind": "function", "line": 48, "name": "inl_port", "signature": "static unsigned int inl_port(unsigned short port)"}, {"kind": "function", "line": 54, "name": "net_reg8", "signature": "static unsigned char net_reg8(unsigned short off)"}, {"kind": "function", "line": 56, "name": "net_reg8_w", "signature": "static void net_reg8_w(unsigned short off, unsigned char v)"}, {"kind": "function", "line": 57, "name": "net_reg16", "signature": "static unsigned short net_reg16(unsigned short off)"}, {"kind": "function", "line": 58, "name": "net_reg16_w", "signature": "static void net_reg16_w(unsigned short off, unsigned short v)"}, {"kind": "function", "line": 59, "name": "net_reg32", "signature": "static unsigned int net_reg32(unsigned short off)"}, {"kind": "function", "line": 60, "name": "net_reg32_w", "signature": "static void net_reg32_w(unsigned short off, unsigned int v)"}, {"doc": "define NET_REG_CR      0x37 define NET_REG_TSD0    0x10 define NET_REG_TSAD0   0x20 define NET_REG_RBSTART 0x30 define NET_REG_CAPR    0x38 define NET_REG_CBR     0x3A define NET_REG_9346CR  0x50", "kind": "function", "line": 69, "name": "pci_read32", "signature": "static unsigned int pci_read32(unsigned bus, unsigned dev, unsigned func, unsigned reg)"}, {"kind": "function", "line": 74, "name": "pci_write32", "signature": "static void pci_write32(unsigned bus, unsigned dev, unsigned func, unsigned reg, unsigned int val)"}, {"doc": "#define NET_REG_CBR     0x3A #define NET_REG_9346CR  0x50 static unsigned int pci_read32(unsigned bus, unsigned dev, unsigned func, unsigned reg) { outl_port(0xCF8, 0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC)); return inl_port(0xCFC); } static void pci_write32(unsigned bus, unsigned dev, unsigned func, unsigned reg, unsigned int val) { outl_port(0xCF8, 0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC)); outl_port(0xCFC, val); } /* Find the rtl8139 and return its I/O base, 0 when absent.", "kind": "function", "line": 81, "name": "net_find_rtl8139", "signature": "static unsigned short net_find_rtl8139(void)"}, {"kind": "function", "line": 99, "name": "net_rdtsc", "signature": "static unsigned long net_rdtsc(void)"}, {"kind": "function", "line": 105, "name": "net_time_init", "signature": "static void net_time_init(void)"}, {"kind": "function", "line": 119, "name": "net_time_ms", "signature": "unsigned long net_time_ms(void)"}, {"kind": "function", "line": 136, "name": "net_rtl_reset", "signature": "static void net_rtl_reset(void)"}, {"kind": "function", "line": 145, "name": "net_rtl_init", "signature": "static void net_rtl_init(void)"}, {"kind": "function", "line": 177, "name": "net_tx_frame", "signature": "static int net_tx_frame(const unsigned char *frame, unsigned len)"}, {"doc": "================================================================ Byte helpers * ================================================================", "kind": "function", "line": 211, "name": "net_put16", "signature": "static void net_put16(unsigned char *p, unsigned short v)"}, {"kind": "function", "line": 216, "name": "net_put32", "signature": "static void net_put32(unsigned char *p, unsigned int v)"}, {"kind": "function", "line": 223, "name": "net_get16", "signature": "static unsigned short net_get16(const unsigned char *p)"}, {"kind": "function", "line": 227, "name": "net_get32", "signature": "static unsigned int net_get32(const unsigned char *p)"}, {"kind": "function", "line": 232, "name": "net_checksum", "signature": "static unsigned short net_checksum(const void *data, unsigned len)"}, {"kind": "function", "line": 257, "name": "net_arp_store", "signature": "static void net_arp_store(const unsigned char *ip, const unsigned char *mac)"}, {"kind": "function", "line": 272, "name": "net_arp_lookup", "signature": "static int net_arp_lookup(const unsigned char *ip, unsigned char *mac_out)"}, {"kind": "function", "line": 283, "name": "net_arp_request", "signature": "static void net_arp_request(const unsigned char *ip)"}, {"doc": "kmemcpy(frame + 6, net_mac, NET_ETH_ALEN); net_put16(frame + 12, NET_ETHERTYPE_ARP); net_put16(frame + 14, 1);                 /* ethernet net_put16(frame + 16, 0x0800);            /* IPv4 frame[18] = 6; frame[19] = 4; net_put16(frame + 20, NET_ARP_REQUEST); kmemcpy(frame + 22, net_mac, NET_ETH_ALEN); kmemcpy(frame + 28, net_our_ip, 4); kmemcpy(frame + 38, ip, 4); net_tx_frame(frame, 42); } /* Resolve an IP on the 10.0.2.0/24 link. Retries, bounded timeout.", "kind": "function", "line": 302, "name": "net_arp_resolve", "signature": "static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out)"}, {"doc": "================================================================ IPv4 / ICMP / UDP / DNS * ================================================================ static unsigned short net_ip_id; static unsigned short net_icmp_id = 0x4D49; static unsigned short net_udp_port = NET_EPHEMERAL_MIN; static unsigned int   net_tx_bytes; static unsigned int   net_rx_bytes; /* Send a frame on the link: dst IP decides the destination MAC.", "kind": "function", "line": 327, "name": "net_ip_send", "signature": "static int net_ip_send(const unsigned char *dip, unsigned char proto,\n                       cons..."}, {"kind": "function", "line": 362, "name": "net_udp_send", "signature": "static int net_udp_send(const unsigned char *dip, unsigned short sport,\n                        u..."}, {"doc": "net_put16(pkt + 6, 0);                    /* checksum optional for UDP kmemcpy(pkt + 8, data, len); return net_ip_send(dip, NET_PROTO_UDP, pkt, total); } struct net_dns_state { unsigned short id; unsigned char  ip[4]; int            done; }; static struct net_dns_state net_dns; /* Parse a DNS response for the first A record.", "kind": "function", "line": 385, "name": "net_dns_parse", "signature": "static void net_dns_parse(const unsigned char *data, unsigned len)"}, {"doc": "rtype = net_get16(data + pos); rdlen = net_get16(data + pos + 8); pos += 10; if (pos + rdlen > len) return; if (rtype == 1 && rdlen == 4) { kmemcpy(net_dns.ip, data + pos, 4); net_dns.done = 1; return; } pos += rdlen; } } /* Blocking A-record lookup against NET_DNS.", "kind": "function", "line": 421, "name": "net_dns_resolve", "signature": "static int net_dns_resolve(const char *host, unsigned char ip_out[4])"}, {"kind": "function", "line": 477, "name": "net_udp_send", "signature": "net_udp_send((const unsigned char[])"}, {"kind": "function", "line": 491, "name": "net_icmp_rx", "signature": "static void net_icmp_rx(const unsigned char *ip, unsigned len)"}, {"kind": "function", "line": 514, "name": "net_ping", "signature": "static int net_ping(const unsigned char ip[4])"}, {"kind": "function", "line": 566, "name": "net_sock_alloc", "signature": "static struct net_tcp_sock *net_sock_alloc(void)"}, {"kind": "function", "line": 579, "name": "net_sock_index", "signature": "static int net_sock_index(const struct net_tcp_sock *s)"}, {"doc": "return &net_sockets[i]; } } return 0; } static int net_sock_index(const struct net_tcp_sock *s) { int i; for (i = 0; i < NET_SOCKETS; i++) if (&net_sockets[i] == s) return i; return -1; } /* Compute the TCP checksum over a pseudo header + segment.", "kind": "function", "line": 588, "name": "net_tcp_checksum", "signature": "static unsigned short net_tcp_checksum(const unsigned char *src, const unsigned char *dst,\n      ..."}, {"doc": "const unsigned char *seg, unsigned len) { unsigned char buf[NET_TX_MAX + 12]; unsigned total = 12 + len; kmemcpy(buf, src, 4); kmemcpy(buf + 4, dst, 4); buf[8] = 0; buf[9] = NET_PROTO_TCP; net_put16(buf + 10, (unsigned short)len); kmemcpy(buf + 12, seg, len); if (total & 1) buf[total++] = 0; return net_checksum(buf, total); } /* UDP checksum over pseudo header + datagram (may be 0 = not computed).", "kind": "function", "line": 604, "name": "net_udp_checksum_ok", "signature": "static int net_udp_checksum_ok(const unsigned char *src, const unsigned char *dst,\n              ..."}, {"kind": "function", "line": 619, "name": "net_tcp_xmit", "signature": "static int net_tcp_xmit(struct net_tcp_sock *s, unsigned flags,\n                        const uns..."}, {"doc": "seg[21] = 0x04;                       /* len 4 net_put16(seg + 22, NET_TCP_MSS); } else { seg[12] = 0x50; } kmemcpy(seg + hlen, data, len); net_put16(seg + 16, net_tcp_checksum(net_our_ip, s->dip, s->sport, s->dport, seg, hlen + len)); if (!net_ip_send(s->dip, NET_PROTO_TCP, seg, hlen + len)) return 0; if (fresh && (flags & (0x02 | 0x08 | 0x01))) s->seq += len + ((flags & (0x02 | 0x01)) ? 1 : 0); return 1; } /* Process one received TCP segment.", "kind": "function", "line": 651, "name": "net_tcp_rx", "signature": "static void net_tcp_rx(const unsigned char *ip, unsigned len)"}, {"doc": "} if (flags & 0x10) {                   /* ACK: peer acks our data if (s->tx_pending && (int)(ack - (s->tx_seq + s->tx_len)) >= 0) { s->tx_pending = 0; } if (s->state == NET_TCP_FIN_SENT && (int)(ack - (s->seq)) >= 0) { s->state = NET_TCP_DEAD; } } } } /* Blocking connect of an allocated socket to an IPv4 address.", "kind": "function", "line": 737, "name": "net_tcp_connect_into", "signature": "static int net_tcp_connect_into(struct net_tcp_sock *s, const unsigned char ip[4],\n              ..."}, {"doc": "unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry && s->state == NET_TCP_SYN_SENT) net_poll_rx(); if (s->state == NET_TCP_SYN_SENT) net_tcp_xmit(s, 0x02, 0, 0, 0); } if (s->state != NET_TCP_ESTABLISHED) { s->in_use = 0; s->state = NET_TCP_CLOSED; return 0; } return 1; } /* Blocking send (stop-and-wait, one outstanding segment).", "kind": "function", "line": 764, "name": "net_tcp_send", "signature": "static int net_tcp_send(struct net_tcp_sock *s, const char *buf, int len)"}, {"doc": "net_time_ms() < deadline) { unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry && s->tx_pending) net_poll_rx(); if (s->tx_pending) net_tcp_xmit(s, 0x18, s->tx_buf, chunk, 0); } if (s->tx_pending || s->state != NET_TCP_ESTABLISHED) return sent ? sent : -1; buf += chunk; len -= (int)chunk; sent += (int)chunk; } return sent; } /* Blocking receive; 0 = EOF (FIN).", "kind": "function", "line": 790, "name": "net_tcp_recv", "signature": "static int net_tcp_recv(struct net_tcp_sock *s, char *buf, int len)"}, {"kind": "function", "line": 827, "name": "net_tcp_close", "signature": "static void net_tcp_close(struct net_tcp_sock *s)"}, {"doc": "================================================================ Receive path: NIC -> ethernet -> ARP/IP -> demux * ================================================================", "kind": "function", "line": 847, "name": "net_rx_handle_frame", "signature": "static void net_rx_handle_frame(const unsigned char *frame, unsigned len)"}, {"kind": "function", "line": 916, "name": "net_poll_rx", "signature": "void net_poll_rx(void)"}, {"doc": "================================================================ Public libc-style API * ================================================================", "kind": "function", "line": 956, "name": "net_open", "signature": "int net_open(void)"}, {"kind": "function", "line": 962, "name": "net_connect", "signature": "int net_connect(const char *host, unsigned short port)"}, {"kind": "function", "line": 971, "name": "net_send", "signature": "int net_send(int fd, const char *buf, int len)"}, {"kind": "function", "line": 976, "name": "net_recv", "signature": "int net_recv(int fd, char *buf, int len)"}, {"kind": "function", "line": 981, "name": "net_recv_timeout", "signature": "int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms)"}, {"kind": "function", "line": 986, "name": "net_close", "signature": "void net_close(int fd)"}, {"doc": "================================================================ Linux syscall ABI * ================================================================", "kind": "function", "line": 995, "name": "net_sys_socket", "signature": "long net_sys_socket(long a1, long a2, long a3)"}, {"kind": "function", "line": 1004, "name": "net_sys_connect", "signature": "long net_sys_connect(long fd, long sockaddr, long addrlen)"}, {"kind": "function", "line": 1017, "name": "net_sys_sendto", "signature": "long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen)"}, {"kind": "function", "line": 1027, "name": "net_sys_recvfrom", "signature": "long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen)"}, {"kind": "function", "line": 1037, "name": "net_sys_shutdown", "signature": "long net_sys_shutdown(long fd, long how)"}, {"kind": "function", "line": 1044, "name": "net_sys_close", "signature": "long net_sys_close(long fd)"}, {"kind": "function", "line": 1051, "name": "net_sys_poll", "signature": "long net_sys_poll(long fds, long nfds, long timeout_ms)"}, {"doc": "MiniOS syscall 200: resolve a hostname, returned as a network-order * 32-bit address (like inet_addr), or -1 on failure.", "kind": "function", "line": 1082, "name": "net_sys_dns", "signature": "long net_sys_dns(long host)"}, {"doc": "================================================================ Shell commands * ================================================================", "kind": "function", "line": 1092, "name": "net_parse_ip", "signature": "static int net_parse_ip(const char *text, unsigned char ip[4])"}, {"kind": "function", "line": 1117, "name": "net_cmd_status", "signature": "void net_cmd_status(void)"}, {"kind": "function", "line": 1131, "name": "net_cmd_ping", "signature": "void net_cmd_ping(const char *ip_text)"}, {"kind": "function", "line": 1142, "name": "net_cmd_dns", "signature": "void net_cmd_dns(const char *host)"}, {"doc": "================================================================ Init and symbol registration * ================================================================", "kind": "function", "line": 1155, "name": "net_register_symbols", "signature": "void net_register_symbols(void)"}, {"kind": "function", "line": 1163, "name": "net_init", "signature": "void net_init(void)"}, {"kind": "macro", "line": 61, "name": "NET_REG_CR"}, {"kind": "macro", "line": 63, "name": "NET_REG_TSD0"}, {"kind": "macro", "line": 64, "name": "NET_REG_TSAD0"}, {"kind": "macro", "line": 65, "name": "NET_REG_RBSTART"}, {"kind": "macro", "line": 66, "name": "NET_REG_CAPR"}, {"kind": "macro", "line": 67, "name": "NET_REG_CBR"}, {"kind": "macro", "line": 68, "name": "NET_REG_9346CR"}, {"kind": "macro", "line": 537, "name": "NET_TCP_CLOSED"}, {"kind": "macro", "line": 539, "name": "NET_TCP_SYN_SENT"}, {"kind": "macro", "line": 540, "name": "NET_TCP_ESTABLISHED"}, {"kind": "macro", "line": 541, "name": "NET_TCP_FIN_SENT"}, {"kind": "macro", "line": 542, "name": "NET_TCP_DEAD"}]}, {"doc": "ifndef NET_H define NET_H  ========== Fixed slirp configuration (QEMU -nic user) ==========", "id": "net.h", "kind": "module", "label": "net.h", "language": "h", "sha256": "c29117c3ace6d14a", "symbol_count": 34, "symbols": [{"kind": "macro", "line": 2, "name": "NET_H"}, {"kind": "macro", "line": 5, "name": "NET_IP_ADDR"}, {"kind": "macro", "line": 6, "name": "NET_NETMASK"}, {"kind": "macro", "line": 7, "name": "NET_GATEWAY"}, {"kind": "macro", "line": 8, "name": "NET_DNS"}, {"kind": "macro", "line": 11, "name": "NET_PCI_VENDOR"}, {"kind": "macro", "line": 12, "name": "NET_PCI_DEVICE"}, {"kind": "macro", "line": 18, "name": "NET_RX_BUF_LEN"}, {"kind": "macro", "line": 19, "name": "NET_RX_ALIGN"}, {"kind": "macro", "line": 22, "name": "NET_RCR"}, {"kind": "macro", "line": 23, "name": "NET_MAX_FRAME"}, {"kind": "macro", "line": 24, "name": "NET_TX_SLOTS"}, {"kind": "macro", "line": 27, "name": "NET_ETH_ALEN"}, {"kind": "macro", "line": 28, "name": "NET_ETHERTYPE_IP"}, {"kind": "macro", "line": 29, "name": "NET_ETHERTYPE_ARP"}, {"kind": "macro", "line": 32, "name": "NET_PROTO_ICMP"}, {"kind": "macro", "line": 33, "name": "NET_PROTO_TCP"}, {"kind": "macro", "line": 34, "name": "NET_PROTO_UDP"}, {"kind": "macro", "line": 37, "name": "NET_ARP_CACHE"}, {"kind": "macro", "line": 38, "name": "NET_ARP_REQUEST"}, {"kind": "macro", "line": 39, "name": "NET_ARP_REPLY"}, {"kind": "macro", "line": 42, "name": "NET_TCP_MSS"}, {"kind": "macro", "line": 43, "name": "NET_TCP_WINDOW"}, {"kind": "macro", "line": 46, "name": "NET_SOCK_RX_BUF"}, {"kind": "macro", "line": 47, "name": "NET_RX_RING_SIZE"}, {"kind": "macro", "line": 48, "name": "NET_SOCKETS"}, {"kind": "macro", "line": 49, "name": "NET_DNS_PORT"}, {"kind": "macro", "line": 50, "name": "NET_EPHEMERAL_MIN"}, {"kind": "macro", "line": 51, "name": "NET_DNS_TRIES"}, {"kind": "macro", "line": 52, "name": "NET_DNS_TMO_MS"}, {"kind": "macro", "line": 53, "name": "NET_CONNECT_TMO_S"}, {"kind": "macro", "line": 54, "name": "NET_RETRY_MS"}, {"kind": "macro", "line": 55, "name": "NET_TX_MAX"}, {"kind": "macro", "line": 58, "name": "NET_FD_BASE"}]}, {"doc": "Ring-3 privilege probe. Reads the CS selector at runtime and exits with", "id": "progs/cpl.c", "kind": "module", "label": "cpl.c", "language": "c", "sha256": "b467d1f0f88c6622", "symbol_count": 3, "symbols": [{"doc": "Ring-3 privilege probe. Reads the CS selector at runtime and exits with the CPL it is executing at. Under the isolation contract a Linux ELF runs at ring 3, so CS is the user code selector (0x23) and the exit code is 3; a regression to ring-0 execution would report 0. Built as a * static Linux ELF like lxhello.elf and run through the syscall ABI.", "kind": "function", "line": 6, "name": "read_cpl", "signature": "static long read_cpl(void)"}, {"kind": "function", "line": 11, "name": "exit_now", "signature": "static void exit_now(long code)"}, {"kind": "function", "line": 15, "name": "_start", "signature": "void _start(void)"}]}, {"id": "progs/fib.c", "kind": "module", "label": "fib.c", "language": "c", "sha256": "3c508f69b636e39e", "symbol_count": 2, "symbols": [{"kind": "function", "line": 1, "name": "fib", "signature": "int fib(int n)"}, {"kind": "function", "line": 5, "name": "main", "signature": "int main(void)"}]}, {"id": "progs/fib.s", "kind": "module", "label": "fib.s", "language": "s", "sha256": "6a2ccc0a38580f79", "symbol_count": 3, "symbols": [{"kind": "function", "line": 3, "name": "fib"}, {"kind": "function", "line": 61, "name": "main"}, {"kind": "function", "line": 82, "name": "_start"}]}, {"doc": "freedom - a headless text browser for MiniOS.", "id": "progs/freedom.c", "kind": "module", "label": "freedom.c", "language": "c", "sha256": "116b418d73acca8e", "symbol_count": 41, "symbols": [{"doc": "static char f_dom[FREEDOM_DOM_BUF]; static int  f_domlen; static char f_css[FREEDOM_CSS_BUF]; static int  f_csslen; static char f_linkhost[FREEDOM_CSS_MAX][64]; static char f_linkpath[FREEDOM_CSS_MAX][128]; static int  f_linkn; static int  f_cstage; static int  f_csize; static int  f_crem; static int  f_bdone; /* Decimal string to int (the ld stub set has no atol).", "kind": "function", "line": 127, "name": "atoi", "signature": "static int atoi(char *s)"}, {"doc": "Append src to dst at pos; returns the new length or -1 when it does * not fit.", "kind": "function", "line": 140, "name": "append", "signature": "static int append(char *dst, int pos, char *src, int cap)"}, {"kind": "function", "line": 148, "name": "ci_lower", "signature": "static int ci_lower(int c)"}, {"doc": "int n; n = strlen(src); if (pos + n >= cap) return -1; memcpy(dst + pos, src, n); dst[pos + n] = 0; return pos + n; } static int ci_lower(int c) { if (c >= 'A' && c <= 'Z') return c + ('a' - 'A'); return c; } /* Case-insensitive starts-with.", "kind": "function", "line": 155, "name": "ci_starts", "signature": "static int ci_starts(char *s, char *pre)"}, {"doc": "} /* Case-insensitive starts-with. static int ci_starts(char *s, char *pre) { while (*pre) { if (!*s) return 0; if (ci_lower(*s) != ci_lower(*pre)) return 0; s++; pre++; } return 1; } /* Case-insensitive equality.", "kind": "function", "line": 166, "name": "ci_eq", "signature": "static int ci_eq(char *a, char *b)"}, {"doc": "return 1; } /* Case-insensitive equality. static int ci_eq(char *a, char *b) { while (*a && *b) { if (ci_lower(*a) != ci_lower(*b)) return 0; a++; b++; } return *a == 0 && *b == 0; } /* Case-insensitive index of needle in haystack, or -1.", "kind": "function", "line": 176, "name": "ci_index", "signature": "static int ci_index(char *s, char *needle)"}, {"doc": "} return *a == 0 && *b == 0; } /* Case-insensitive index of needle in haystack, or -1. static int ci_index(char *s, char *needle) { int i; for (i = 0; s[i]; i++) { if (ci_starts(s + i, needle)) return i; } return -1; } /* Does the input look like an URL (no spaces, contains a dot)?", "kind": "function", "line": 185, "name": "looks_like_url", "signature": "static int looks_like_url(char *s)"}, {"doc": "Does s begin with \"<scheme>:\" per RFC 3986 (ALPHA *(ALPHA/DIGIT/+/-/.) \":\")? Any such prefix makes the string a scheme, * and the omnibox policy is: only http:// and https:// are executed.", "kind": "function", "line": 199, "name": "has_scheme", "signature": "static int has_scheme(char *s)"}, {"doc": "char c; c = s[0]; if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) return 0; for (i = 1; s[i]; i++) { c = s[i]; if (c == ':') return 1; if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '+' || c == '-' || c == '.')) return 0; } return 0; } /* Encode a query for the DuckDuckGo HTML endpoint (no-JS).", "kind": "function", "line": 215, "name": "make_search", "signature": "static void make_search(char *out, char *query, int cap)"}, {"doc": "Split an http:// or https:// URL into f_host, f_path, f_port and f_secure. Returns 0 on failure. The input buffer is never modified: the parse is index-only, so it stays valid when the compiler widens * dereferenced stores.", "kind": "function", "line": 239, "name": "split_url", "signature": "static int split_url(char *url)"}, {"doc": "Recompute f_host/f_path/f_port/f_secure from the last Location value. Returns 1 when the chase may continue, 0 when it must stop * (diagnostic already printed).", "kind": "function", "line": 286, "name": "resolve_redirect", "signature": "static int resolve_redirect(void)"}, {"doc": "if (l + 1 >= 128) return 0; f_path[0] = '/'; memcpy(f_path + 1, loc, l); f_path[l + 1] = 0; } else { if (last + 1 + l >= 128) return 0; memcpy(f_path + last + 1, loc, l); f_path[last + 1 + l] = 0; } } return 1; } /* --- HTML filter --------------------------------------------------", "kind": "function", "line": 338, "name": "put_ws", "signature": "static void put_ws(void)"}, {"doc": "Print one text byte through the UTF-8 gate. Remote pages are hostile data: bytes outside a valid UTF-8 sequence (overlong, surrogate, out of range) are replaced with '?' (FreeDom policy). * Sequence state is kept in f_utbuf/f_utlen/f_utrem.", "kind": "function", "line": 350, "name": "put_utf", "signature": "static void put_utf(int c)"}, {"doc": "Print one text byte: whitespace collapses, everything else goes * through the UTF-8 gate. Dump modes suppress the page text.", "kind": "function", "line": 400, "name": "put_text", "signature": "static void put_text(int c)"}, {"doc": "} else if (v >= 2048 && v < 65536) { put_text(224 | (v >> 12)); put_text(128 | ((v >> 6) & 63)); put_text(128 | (v & 63)); } } else { int k; put_text('&'); for (k = 0; e[k]; k++) put_text(e[k]); put_text(';'); } } /* --- dump capture helpers ------------------------------------------", "kind": "function", "line": 455, "name": "css_append", "signature": "static void css_append(char *s, int n)"}, {"kind": "function", "line": 461, "name": "css_line", "signature": "static void css_line(char *s)"}, {"kind": "function", "line": 466, "name": "dom_append", "signature": "static void dom_append(char *s, int n)"}, {"kind": "function", "line": 472, "name": "dom_space", "signature": "static void dom_space(void)"}, {"kind": "function", "line": 476, "name": "dom_nl", "signature": "static void dom_nl(void)"}, {"doc": "int i; for (i = 0; i < n && f_domlen < FREEDOM_DOM_BUF - 1; i++) f_dom[f_domlen++] = s[i]; } static void dom_space(void) { if (f_domlen < FREEDOM_DOM_BUF - 1) f_dom[f_domlen++] = ' '; } static void dom_nl(void) { if (f_domlen < FREEDOM_DOM_BUF - 1) f_dom[f_domlen++] = '\\n'; } /* Record the finished attribute in its place.", "kind": "function", "line": 482, "name": "record_attr", "signature": "static void record_attr(void)"}, {"doc": "f_hreflen = f_vallen < 127 ? f_vallen : 127; memcpy(f_href, f_val, f_hreflen); f_href[f_hreflen] = 0; } else if (ci_eq(f_attr, \"style\")) { f_stylelen = f_vallen < (FREEDOM_ATTR_MAX - 1) ? f_vallen : (FREEDOM_ATTR_MAX - 1); memcpy(f_styleattr, f_val, f_stylelen); f_styleattr[f_stylelen] = 0; } else if (ci_eq(f_attr, \"rel\")) { f_rel_ss = ci_index(f_val, \"stylesheet\") >= 0; } } /* Is tagname a void element (no closing tag, no children)?", "kind": "function", "line": 507, "name": "is_void_tag", "signature": "static int is_void_tag(void)"}, {"doc": "A tag was fully collected into f_tagn (+ attributes). Decide what it * does to the stream and the dumps.", "kind": "function", "line": 519, "name": "classify_tag", "signature": "static void classify_tag(void)"}, {"doc": "} dom_nl(); if (!is_void_tag()) f_depth++; } if (ci_eq(f_tagn, \"br\") || ci_eq(f_tagn, \"p\") || ci_eq(f_tagn, \"div\") || ci_eq(f_tagn, \"h1\") || ci_eq(f_tagn, \"h2\") || ci_eq(f_tagn, \"h3\") || ci_eq(f_tagn, \"h4\") || ci_eq(f_tagn, \"h5\") || ci_eq(f_tagn, \"h6\") || ci_eq(f_tagn, \"li\") || ci_eq(f_tagn, \"tr\")) { if (f_mode == 0) putchar('\\n'); f_ws = 1; } } /* Feed one body byte into the filter.", "kind": "function", "line": 604, "name": "body_byte", "signature": "static void body_byte(int c)"}, {"doc": "f_rel_ss = 0; return; } if (c == '&') { f_entlen = 1; f_ent[0] = 0; return; } put_text(c); } /* --- HTTP ---------------------------------------------------------- /* Classify one header line (NUL-terminated).", "kind": "function", "line": 769, "name": "head_line", "signature": "static void head_line(char *line)"}, {"doc": "Parse the collected header block f_hdr[0..f_hlen-1] (the last four * bytes are the terminating CRLF CRLF).", "kind": "function", "line": 794, "name": "parse_head", "signature": "static void parse_head(void)"}, {"doc": "f_hdr[lend] = 0; if (i == 0) { char *sp; sp = strchr(f_hdr, ' '); if (sp) f_status = atoi(sp + 1); } else if (lend > i) { head_line(f_hdr + i); } f_hdr[lend] = '\\r'; i = lend + 2; } } /* Receive body bytes: TLS for f_secure, plain TCP otherwise.", "kind": "function", "line": 816, "name": "recv_body", "signature": "static int recv_body(int fd, char *buf, int len)"}, {"doc": "head_line(f_hdr + i); } f_hdr[lend] = '\\r'; i = lend + 2; } } /* Receive body bytes: TLS for f_secure, plain TCP otherwise. static int recv_body(int fd, char *buf, int len) { if (f_secure) return tls_recv(fd, buf, len); return recvfrom(fd, buf, len, 0, 0, 0); } /* Send the whole request: TLS for f_secure, plain TCP otherwise.", "kind": "function", "line": 822, "name": "send_all", "signature": "static int send_all(int fd, char *buf, int len)"}, {"doc": "Send one HTTP request and process the response body. Returns the status code, or 0 on transport failure. Sets f_redir when a * Location header was seen.", "kind": "function", "line": 833, "name": "fetch", "signature": "static int fetch(char *host, char *path, int port)"}, {"doc": "Fetch a linked stylesheet and print its raw body (through the UTF-8 * gate). No redirect chasing: the bound is one request.", "kind": "function", "line": 993, "name": "fetch_css", "signature": "static void fetch_css(char *host, char *path)"}, {"doc": "} continue; } f_ws = 0; put_utf(c); got++; } } close(fd); putchar('\\n'); printf(\"freedom: %s (%d bytes)\\n\", host, got); } /* Print the collected CSS dump.", "kind": "function", "line": 1071, "name": "print_css_dump", "signature": "static void print_css_dump(void)"}, {"doc": "putchar('\\n'); printf(\"freedom: %s (%d bytes)\\n\", host, got); } /* Print the collected CSS dump. static void print_css_dump(void) { int i; puts(\"=== freedom css ===\"); for (i = 0; i < f_csslen; i++) put_utf(f_css[i]); if (f_csslen == 0) puts(\"(no css)\"); if (f_linkn > 0) putchar('\\n'); } /* Print the collected DOM outline.", "kind": "function", "line": 1080, "name": "print_dom_dump", "signature": "static void print_dom_dump(void)"}, {"kind": "function", "line": 1086, "name": "main", "signature": "int main(int argc, char **argv)"}, {"kind": "macro", "line": 49, "name": "FREEDOM_HOPS_MAX"}, {"kind": "macro", "line": 51, "name": "FREEDOM_HDR_MAX"}, {"kind": "macro", "line": 52, "name": "FREEDOM_BUF"}, {"kind": "macro", "line": 53, "name": "FREEDOM_CHUNK_MAX"}, {"kind": "macro", "line": 54, "name": "FREEDOM_CSS_MAX"}, {"kind": "macro", "line": 55, "name": "FREEDOM_CSS_BUF"}, {"kind": "macro", "line": 56, "name": "FREEDOM_DOM_BUF"}, {"kind": "macro", "line": 57, "name": "FREEDOM_ATTR_MAX"}, {"kind": "macro", "line": 58, "name": "FREEDOM_LINE_MAX"}]}, {"id": "progs/freedom.s", "kind": "module", "label": "freedom.s", "language": "s", "sha256": "2e63fd888fd84e2b", "symbol_count": 91, "symbols": [{"kind": "function", "line": 3, "name": "f_host"}, {"kind": "function", "line": 7, "name": "f_path"}, {"kind": "function", "line": 11, "name": "f_port"}, {"kind": "function", "line": 15, "name": "f_secure"}, {"kind": "function", "line": 19, "name": "f_loc"}, {"kind": "function", "line": 23, "name": "f_redir"}, {"kind": "function", "line": 27, "name": "f_status"}, {"kind": "function", "line": 31, "name": "f_clen"}, {"kind": "function", "line": 35, "name": "f_has_clen"}, {"kind": "function", "line": 39, "name": "f_chunked"}, {"kind": "function", "line": 43, "name": "f_hdr"}, {"kind": "function", "line": 47, "name": "f_hlen"}, {"kind": "function", "line": 51, "name": "f_tag"}, {"kind": "function", "line": 55, "name": "f_suppress"}, {"kind": "function", "line": 59, "name": "f_comment"}, {"kind": "function", "line": 63, "name": "f_cmdash"}, {"kind": "function", "line": 67, "name": "f_tagn"}, {"kind": "function", "line": 71, "name": "f_tagnlen"}, {"kind": "function", "line": 75, "name": "f_ent"}, {"kind": "function", "line": 79, "name": "f_entlen"}, {"kind": "function", "line": 83, "name": "f_ws"}, {"kind": "function", "line": 87, "name": "f_utbuf"}, {"kind": "function", "line": 91, "name": "f_utlen"}, {"kind": "function", "line": 95, "name": "f_utrem"}, {"kind": "function", "line": 99, "name": "f_attr_on"}, {"kind": "function", "line": 103, "name": "f_waitq"}, {"kind": "function", "line": 107, "name": "f_inval"}, {"kind": "function", "line": 111, "name": "f_inval2"}, {"kind": "function", "line": 115, "name": "f_attr"}, {"kind": "function", "line": 119, "name": "f_attrlen"}, {"kind": "function", "line": 123, "name": "f_val"}, {"kind": "function", "line": 127, "name": "f_vallen"}, {"kind": "function", "line": 131, "name": "f_id"}, {"kind": "function", "line": 135, "name": "f_idlen"}, {"kind": "function", "line": 139, "name": "f_cls"}, {"kind": "function", "line": 143, "name": "f_clslen"}, {"kind": "function", "line": 147, "name": "f_href"}, {"kind": "function", "line": 151, "name": "f_hreflen"}, {"kind": "function", "line": 155, "name": "f_rel_ss"}, {"kind": "function", "line": 159, "name": "f_styleattr"}, {"kind": "function", "line": 163, "name": "f_stylelen"}, {"kind": "function", "line": 167, "name": "f_dump_css"}, {"kind": "function", "line": 171, "name": "f_dump_dom"}, {"kind": "function", "line": 175, "name": "f_mode"}, {"kind": "function", "line": 179, "name": "f_rawcap"}, {"kind": "function", "line": 183, "name": "f_depth"}, {"kind": "function", "line": 187, "name": "f_dom"}, {"kind": "function", "line": 191, "name": "f_domlen"}, {"kind": "function", "line": 195, "name": "f_css"}, {"kind": "function", "line": 199, "name": "f_csslen"}, {"kind": "function", "line": 203, "name": "f_linkhost"}, {"kind": "function", "line": 207, "name": "f_linkpath"}, {"kind": "function", "line": 211, "name": "f_linkn"}, {"kind": "function", "line": 215, "name": "f_cstage"}, {"kind": "function", "line": 219, "name": "f_csize"}, {"kind": "function", "line": 223, "name": "f_crem"}, {"kind": "function", "line": 227, "name": "f_bdone"}, {"kind": "function", "line": 231, "name": "atoi"}, {"kind": "function", "line": 317, "name": "append"}, {"kind": "function", "line": 402, "name": "ci_lower"}, {"kind": "function", "line": 451, "name": "ci_starts"}, {"kind": "function", "line": 524, "name": "ci_eq"}, {"kind": "function", "line": 621, "name": "ci_index"}, {"kind": "function", "line": 681, "name": "looks_like_url"}, {"kind": "function", "line": 755, "name": "has_scheme"}, {"kind": "function", "line": 1030, "name": "make_search"}, {"kind": "function", "line": 1266, "name": "split_url"}, {"kind": "function", "line": 1781, "name": "resolve_redirect"}, {"kind": "function", "line": 2306, "name": "put_ws"}, {"kind": "function", "line": 2352, "name": "put_utf"}, {"kind": "function", "line": 2888, "name": "put_text"}, {"kind": "function", "line": 2991, "name": "put_entity"}, {"kind": "function", "line": 3828, "name": "css_append"}, {"kind": "function", "line": 3899, "name": "css_line"}, {"kind": "function", "line": 3958, "name": "dom_append"}, {"kind": "function", "line": 4029, "name": "dom_space"}, {"kind": "function", "line": 4063, "name": "dom_nl"}, {"kind": "function", "line": 4097, "name": "record_attr"}, {"kind": "function", "line": 4435, "name": "is_void_tag"}, {"kind": "function", "line": 4757, "name": "classify_tag"}, {"kind": "function", "line": 5994, "name": "body_byte"}, {"kind": "function", "line": 7239, "name": "head_line"}, {"kind": "function", "line": 7500, "name": "parse_head"}, {"kind": "function", "line": 7717, "name": "recv_body"}, {"kind": "function", "line": 7778, "name": "send_all"}, {"kind": "function", "line": 7853, "name": "fetch"}, {"kind": "function", "line": 9331, "name": "fetch_css"}, {"kind": "function", "line": 10143, "name": "print_css_dump"}, {"kind": "function", "line": 10243, "name": "print_dom_dump"}, {"kind": "function", "line": 10322, "name": "main"}, {"kind": "function", "line": 11800, "name": "_start"}]}, {"doc": "Exercises the kernel libc surface used by loaded .o programs: fprintf to stdout/stderr, snprintf into a buffer, and exit().", "id": "progs/ftest.c", "kind": "module", "label": "ftest.c", "language": "c", "sha256": "81ebab6590f07af1", "symbol_count": 1, "symbols": [{"kind": "function", "line": 9, "name": "main", "signature": "int main(int argc, char **argv)"}]}, {"doc": "MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader", "id": "progs/hello.c", "kind": "module", "label": "hello.c", "language": "c", "sha256": "d3bfdc30c4039b11", "symbol_count": 1, "symbols": [{"kind": "function", "line": 3, "name": "main", "signature": "int main(int argc, char **argv)"}]}, {"doc": "Minimal HTTP/1.0 GET through the Linux socket syscalls.", "id": "progs/http.c", "kind": "module", "label": "http.c", "language": "c", "sha256": "6e928a938b6ac83c", "symbol_count": 2, "symbols": [{"doc": "int socket(int domain, int type, int proto); int connect(int fd, void *addr, int addrlen); int sendto(int fd, char *buf, int len, int flags, void *to, int tolen); int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen); int shutdown(int fd, int how); int close(int fd); int net_dns_resolve(char *host); int puts(char *s); int printf(char *fmt, ...); int strlen(char *s); int putchar(int c); /* Decimal string to int (the ld stub set has no atol).", "kind": "function", "line": 18, "name": "atoi", "signature": "int atoi(char *s)"}, {"kind": "function", "line": 28, "name": "main", "signature": "int main(int argc, char **argv)"}]}, {"id": "progs/http.s", "kind": "module", "label": "http.s", "language": "s", "sha256": "3c456efc0500a72e", "symbol_count": 3, "symbols": [{"kind": "function", "line": 3, "name": "atoi"}, {"kind": "function", "line": 89, "name": "main"}, {"kind": "function", "line": 698, "name": "_start"}]}, {"doc": "Kernel-pointer rejection probe. Passes a kernel-heap address (0x2000000,", "id": "progs/kmem.c", "kind": "module", "label": "kmem.c", "language": "c", "sha256": "9b9364f5e56025a7", "symbol_count": 3, "symbols": [{"doc": "Kernel-pointer rejection probe. Passes a kernel-heap address (0x2000000, a supervisor page) to write(2). The hardened syscall boundary must reject it with -EFAULT; the program exits 0 when the write was refused and 1 when the kernel wrongly dereferenced a kernel pointer on its behalf. * Built as a static Linux ELF like lxhello.elf.", "kind": "function", "line": 6, "name": "syscall3", "signature": "static long syscall3(long n, long a1, long a2, long a3)"}, {"kind": "function", "line": 12, "name": "exit_now", "signature": "static void exit_now(long code)"}, {"kind": "function", "line": 16, "name": "_start", "signature": "void _start(void)"}]}, {"id": "progs/ldhello.c", "kind": "module", "label": "ldhello.c", "language": "c", "sha256": "736a16ff3f36af1f", "symbol_count": 1, "symbols": [{"kind": "function", "line": 1, "name": "main", "signature": "int main(void)"}]}, {"id": "progs/ldhello.s", "kind": "module", "label": "ldhello.s", "language": "s", "sha256": "62a6a7c58a95f2e9", "symbol_count": 2, "symbols": [{"kind": "function", "line": 3, "name": "main"}, {"kind": "function", "line": 14, "name": "_start"}]}, {"id": "progs/lxhello.c", "kind": "module", "label": "lxhello.c", "language": "c", "sha256": "4098c132f2f71cd9", "symbol_count": 7, "symbols": [{"doc": "lxhello — a genuine Linux x86-64 ELF executable.  Built with `gcc -static -no-pie -nostdlib` so it links as ET_EXEC at 0x400000 with a hand-written _start.  It never uses libc: it reads argc/argv straight off the SysV initial stack and talks to the kernel exclusively through the `syscall` instruction.  If MiniOS runs this and prints the message, its ELF loader + Linux syscall ABI are working.", "kind": "function", "line": 10, "name": "lx_syscall3", "signature": "static long lx_syscall3(long n, long a1, long a2, long a3)"}, {"doc": "define SYS_write 1 define SYS_exit  60", "kind": "function", "line": 22, "name": "lx_strlen", "signature": "static unsigned long lx_strlen(const char *s)"}, {"kind": "function", "line": 28, "name": "lx_write", "signature": "static void lx_write(const char *s)"}, {"kind": "function", "line": 32, "name": "lx_write_int", "signature": "static void lx_write_int(long v)"}, {"doc": "static void lx_write_int(long v) { char buf[24]; int i = (int)sizeof(buf); int neg = 0; buf[--i] = 0; if (v < 0) { neg = 1; v = -v; } if (v == 0) buf[--i] = '0'; while (v > 0 && i > 0) { buf[--i] = (char)('0' + v % 10); v /= 10; } if (neg && i > 0) buf[--i] = '-'; lx_write(&buf[i]); } /* Entry called by _start with the real argc/argv pulled off the stack.", "kind": "function", "line": 46, "name": "lmain", "signature": "int lmain(long argc, char **argv)"}, {"kind": "macro", "line": 19, "name": "SYS_write"}, {"kind": "macro", "line": 21, "name": "SYS_exit"}]}, {"id": "progs/test.c", "kind": "module", "label": "test.c", "language": "c", "sha256": "fadd75bd1d9dc132", "symbol_count": 2, "symbols": [{"kind": "function", "line": 1, "name": "add", "signature": "int add(int a, int b)"}, {"kind": "function", "line": 2, "name": "main", "signature": "int main(void)"}]}, {"id": "progs/w1.c", "kind": "module", "label": "w1.c", "language": "c", "sha256": "ed14d3aee26b599f", "symbol_count": 1, "symbols": [{"kind": "function", "line": 2, "name": "main", "signature": "int main(void)"}]}, {"id": "progs/w1.s", "kind": "module", "label": "w1.s", "language": "s", "sha256": "df9d6e432fea580e", "symbol_count": 2, "symbols": [{"kind": "function", "line": 3, "name": "main"}, {"kind": "function", "line": 37, "name": "_start"}]}, {"id": "ramdisk_data.c", "kind": "module", "label": "ramdisk_data.c", "language": "c", "sha256": "d0e1e915c7b2e722", "symbol_count": 0, "symbols": []}, {"doc": "stage1.S - MiniOS boot sector.", "id": "stage1.S", "kind": "module", "label": "stage1.S", "language": "S", "sha256": "fa8c3c211038292f", "symbol_count": 11, "symbols": [{"kind": "function", "line": 21, "name": "main"}, {"kind": "function", "line": 25, "name": "normalize"}, {"kind": "function", "line": 59, "name": "no_extensions"}, {"kind": "function", "line": 63, "name": "read_failed"}, {"kind": "function", "line": 66, "name": "fail"}, {"kind": "function", "line": 69, "name": "halt"}, {"kind": "function", "line": 74, "name": "puts"}, {"kind": "function", "line": 78, "name": "puts_next"}, {"kind": "function", "line": 84, "name": "puts_done"}, {"kind": "function", "line": 88, "name": "msg_no_lba"}, {"kind": "function", "line": 90, "name": "msg_read"}]}, {"doc": "stage2.S - MiniOS second-stage loader.", "id": "stage2.S", "kind": "module", "label": "stage2.S", "language": "S", "sha256": "40954166a62e2fb8", "symbol_count": 27, "symbols": [{"kind": "function", "line": 39, "name": "stage2_main"}, {"kind": "function", "line": 54, "name": "a20_ready"}, {"kind": "function", "line": 61, "name": "load_chunk"}, {"kind": "function", "line": 66, "name": "chunk_size_ready"}, {"kind": "function", "line": 73, "name": "read_piece"}, {"kind": "function", "line": 78, "name": "piece_size_ready"}, {"kind": "function", "line": 110, "name": "chunk_copy"}, {"kind": "function", "line": 123, "name": "chunk_leave_pm"}, {"kind": "function", "line": 133, "name": "chunk_resume"}, {"kind": "function", "line": 152, "name": "enter_long_mode"}, {"kind": "function", "line": 172, "name": "fill_page_directory"}, {"kind": "function", "line": 201, "name": "read_failed"}, {"kind": "function", "line": 205, "name": "halt"}, {"kind": "function", "line": 210, "name": "puts"}, {"kind": "function", "line": 214, "name": "puts_next"}, {"kind": "function", "line": 220, "name": "puts_done"}, {"kind": "function", "line": 224, "name": "msg_read"}, {"kind": "function", "line": 228, "name": "gdt32_start"}, {"kind": "function", "line": 234, "name": "gdt32_end"}, {"kind": "function", "line": 235, "name": "gdt32_ptr"}, {"kind": "function", "line": 240, "name": "gdt64_image"}, {"kind": "function", "line": 246, "name": "gdt64_ptr"}, {"kind": "function", "line": 250, "name": "saved_gdtr"}, {"kind": "function", "line": 253, "name": "sectors_left"}, {"kind": "function", "line": 255, "name": "chunk_sectors"}, {"kind": "function", "line": 257, "name": "next_lba"}, {"kind": "function", "line": 259, "name": "dest_addr"}]}, {"doc": "BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the serial console (COM1). Every scenario sends a script of shell commands, then asserts that the expected markers appear in the console log.  The guest powers itself off through the ACPI port at the end of each scenario, which makes QEMU exit; the timeout is only a safety net for hangs. A stale-qemu guard prevents image-lock cascades between runs.  Environment overrides: QEMU, TMO (per-scenario timeout), KEEP_LOG=1 to keep the console log of the last scenario for inspection.", "id": "test_bdd.sh", "kind": "module", "label": "test_bdd.sh", "language": "sh", "sha256": "da770bf5135ac399", "symbol_count": 9, "symbols": [{"kind": "function", "line": 30, "name": "cleanup_stale_qemu"}, {"doc": "scenario <name> <script of shell commands>", "kind": "function", "line": 41, "name": "scenario"}, {"doc": "expect <marker>", "kind": "function", "line": 59, "name": "expect"}, {"doc": "expect_count <count> <marker>: the marker must appear exactly that many times in the log. Used where a single occurrence would also match the echoed command line, so only the output can prove the behaviour.", "kind": "function", "line": 80, "name": "expect_count"}, {"doc": "refute <marker>: the marker must NOT appear (suppressed hostile content).", "kind": "function", "line": 102, "name": "refute"}, {"kind": "function", "line": 326, "name": "http_server_start"}, {"kind": "function", "line": 333, "name": "http_server_stop"}, {"kind": "function", "line": 338, "name": "http_fixture_start"}, {"kind": "function", "line": 345, "name": "http_fixture_stop"}]}, {"id": "test_http_server.py", "kind": "module", "label": "test_http_server.py", "language": "py", "sha256": "c0e76ad90608e77a", "symbol_count": 3, "symbols": [{"kind": "class", "line": 21, "name": "Handler", "signature": "class Handler(BaseHTTPRequestHandler)"}, {"kind": "method", "line": 24, "name": "do_GET", "signature": "def do_GET(self)"}, {"kind": "method", "line": 114, "name": "log_message", "signature": "def log_message(self, fmt)"}]}, {"doc": "tls.c - TLS 1.2 client sessions for MiniOS.", "id": "tls.c", "kind": "module", "label": "tls.c", "language": "c", "sha256": "9fb81c61de171b94", "symbol_count": 25, "symbols": [{"doc": "Diagnostics are `freedom: tls: <stage>: <reason>` lines (freedom is the only consumer of the TLS syscalls).  #include \"tls_port.h\" #include \"tls.h\" #ifndef TLS_TEST #include \"tls_roots.h\" #endif static struct tls_session *tls_sessions[TLS_FD_MAX]; /* ---- diagnostics and teardown ----", "kind": "function", "line": 24, "name": "tls_fail", "signature": "static void tls_fail(struct tls_session *s, const char *stage, const char *reason)"}, {"kind": "function", "line": 32, "name": "tls_fd_of", "signature": "static int tls_fd_of(const struct tls_session *s)"}, {"kind": "function", "line": 39, "name": "tls_free_fd", "signature": "void tls_free_fd(int fd)"}, {"doc": "Build the TLS 1.2 AEAD additional data: seq(8) || type || 0303 || * TLSCompressed.length (the plaintext length, RFC 5288 section 3).", "kind": "function", "line": 52, "name": "tls_aad", "signature": "static void tls_aad(unsigned char aad[13], int type, unsigned long long seq,\n                    ..."}, {"doc": "Send one record: header || nonce_explicit(8) || ciphertext || tag. The nonce_explicit is the sequence number (RFC 5288 allows it and * OpenSSL uses it); the nonce is salt || nonce_explicit.", "kind": "function", "line": 66, "name": "tls_send_record", "signature": "static int tls_send_record(struct tls_session *s, int type,\n                           const unsi..."}, {"doc": "for (i = 0; i < 8; i++) buf[5 + i] = (unsigned char)(s->cli_seq >> (56 - i * 8)); TLS_MEMCPY(nonce, s->cli_salt, 4); TLS_MEMCPY(nonce + 4, buf + 5, 8); if (aes128_gcm_seal_core(s->cli_key, nonce, aad, 13, payload, (unsigned)len, buf + 5 + 8, buf + 5 + 8 + len) != 0) return -1; s->cli_seq++; if (TLS_SEND(tls_fd_of(s), (const char *)buf, total) != total) return -1; return 0; } /* Send one plaintext record (ChangeCipherSpec is never encrypted).", "kind": "function", "line": 95, "name": "tls_send_raw_record", "signature": "static int tls_send_raw_record(struct tls_session *s, int type,\n                               co..."}, {"doc": "Read one record: header into s->rec_hdr, payload into s->rec. Returns: 1 = record ready, 0 = clean TCP EOF, -1 = torn record or bad header, -2 = timeout. A non-positive deadline blocks forever * (application-data reads behave like plain TCP).", "kind": "function", "line": 114, "name": "tls_read_record", "signature": "static int tls_read_record(struct tls_session *s, int fd, int deadline_ms)"}, {"kind": "function", "line": 173, "name": "exchange", "signature": "* key exchange (ClientHello, ClientKeyExchange) go out in plaintext\n * records, as TLS 1.2 requir..."}, {"doc": "const unsigned char *body, int len) { if (len < 0 || len > 1024) return -1; s->pt[0] = (unsigned char)type; s->pt[1] = (unsigned char)(len >> 16); s->pt[2] = (unsigned char)(len >> 8); s->pt[3] = (unsigned char)len; TLS_MEMCPY(s->pt + 4, body, (unsigned)len); sha256_update(&s->hs_hash, s->pt, (unsigned)(len + 4)); if (!s->keys_ready) return tls_send_raw_record(s, TLS_CT_HANDSHAKE, s->pt, len + 4); return tls_send_record(s, TLS_CT_HANDSHAKE, s->pt, len + 4); } /* ClientHello body (without the handshake header). Returns length.", "kind": "function", "line": 190, "name": "build_client_hello", "signature": "static int build_client_hello(struct tls_session *s, unsigned char *out)"}, {"doc": "out[pos++] = 0x00; out[pos++] = 0x06; out[pos++] = 0x04; out[pos++] = 0x01;   /* rsa_pkcs1_sha256 out[pos++] = 0x04; out[pos++] = 0x03;   /* ecdsa_p256_sha256 out[pos++] = 0x05; out[pos++] = 0x03;   /* ecdsa_p384_sha384 { int extlen = pos - ext_start - 2; out[ext_start] = (unsigned char)(extlen >> 8); out[ext_start + 1] = (unsigned char)extlen; } } return pos; } /* Derive all keys and send ClientKeyExchange, CCS, Finished.", "kind": "function", "line": 244, "name": "client_finish_flight", "signature": "static int client_finish_flight(struct tls_session *s)"}, {"doc": "sha256_final(&hcopy, hash); } tls_prf(s->master, 48, \"client finished\", hash, 32, verify, 12); TLS_MEMCPY(finished + 4, verify, 12); if (tls_send_record(s, TLS_CT_HANDSHAKE, finished, 16) != 0) { tls_fail(s, \"send\", \"client finished\"); return -1; } /* the server Finished covers the transcript including our Finished sha256_update(&s->hs_hash, finished, 16); return 0; } /* ---- handshake message parsers ----", "kind": "function", "line": 339, "name": "parse_server_hello", "signature": "static int parse_server_hello(struct tls_session *s,\n                              const unsigned..."}, {"kind": "function", "line": 369, "name": "parse_certificate", "signature": "static int parse_certificate(struct tls_session *s,\n                             const unsigned c..."}, {"kind": "function", "line": 400, "name": "parse_server_key_exchange", "signature": "static int parse_server_key_exchange(struct tls_session *s,\n                                     ..."}, {"doc": "sha256(data, 64 + params_len, digest); return ecdsa_verify(0, s->leaf_pk.qx, s->leaf_pk.qy, digest, 32, m + pos, sig_len); } if (sig_alg == TLS_SIG_ECDSA_P384_SHA384) { if (s->leaf_pk.kind != 2) return -1; sha384(data, 64 + params_len, digest); return ecdsa_verify(1, s->leaf_pk.qx, s->leaf_pk.qy, digest, 48, m + pos, sig_len); } return -1; } /* ---- handshake driver ----", "kind": "function", "line": 465, "name": "tls_handshake", "signature": "int tls_handshake(int fd, const char *host)"}, {"doc": "pre-Finished is refused tls_fail(s, \"handshake\", \"unexpected message\"); tls_sessions[fd] = 0; return -1; } } s->hs_msg_len = 0; s->hs_msg_want = 0; } } } } /* ---- application data ----", "kind": "function", "line": 686, "name": "tls_send", "signature": "int tls_send(int fd, const char *buf, int len)"}, {"kind": "function", "line": 695, "name": "tls_recv", "signature": "int tls_recv(int fd, char *buf, int len)"}, {"doc": "ifndef TLS_TEST", "kind": "function", "line": 772, "name": "tls_sys_handshake", "signature": "long tls_sys_handshake(long fd, long host)"}, {"kind": "function", "line": 776, "name": "tls_sys_send", "signature": "long tls_sys_send(long fd, long buf, long len)"}, {"kind": "function", "line": 781, "name": "tls_sys_recv", "signature": "long tls_sys_recv(long fd, long buf, long len)"}, {"doc": "return tls_handshake((int)(fd - NET_FD_BASE), (const char *)host); } long tls_sys_send(long fd, long buf, long len) { if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS || !buf) return -1; return tls_send((int)(fd - NET_FD_BASE), (const char *)buf, (int)len); } long tls_sys_recv(long fd, long buf, long len) { if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS || !buf) return -1; return tls_recv((int)(fd - NET_FD_BASE), (char *)buf, (int)len); } /* ---- kernel entropy and clock ----", "kind": "function", "line": 788, "name": "tls_rdtsc", "signature": "static inline unsigned long long tls_rdtsc(void)"}, {"kind": "function", "line": 794, "name": "tls_random", "signature": "void tls_random(unsigned char *out, unsigned len)"}, {"doc": "void tls_random(unsigned char *out, unsigned len) { unsigned long long seed = tls_rdtsc() ^ ((unsigned long long)net_time_ms() << 33); unsigned i; static unsigned long long counter = 0x6D696E69544C53ULL; counter ^= seed; for (i = 0; i < len; i++) { seed = seed * 6364136223846793005ULL + 1442695040888963407ULL; out[i] = (unsigned char)((seed >> 33) ^ (counter >> (i & 7) * 8)); counter = counter * 6364136223846793005ULL + 1; } } /* The port helpers in net.c are static; these live here for the RTC.", "kind": "function", "line": 808, "name": "outb", "signature": "static inline void outb(unsigned short port, unsigned char v)"}, {"kind": "function", "line": 811, "name": "inb", "signature": "static inline unsigned char inb(unsigned short port)"}, {"doc": "} } /* The port helpers in net.c are static; these live here for the RTC. static inline void outb(unsigned short port, unsigned char v) { __asm__ volatile(\"outb %0, %1\" : : \"a\"(v), \"Nd\"(port)); } static inline unsigned char inb(unsigned short port) { unsigned char v; __asm__ volatile(\"inb %1, %0\" : \"=a\"(v) : \"Nd\"(port)); return v; } /* CMOS RTC -> days since epoch. Registers are BCD.", "kind": "function", "line": 818, "name": "cmos_read", "signature": "static inline unsigned char cmos_read(unsigned char reg)"}, {"kind": "function", "line": 822, "name": "tls_now_days", "signature": "long tls_now_days(void)"}]}, {"doc": "ifndef TLS_H define TLS_H  ========== TLS 1.2 client (RFC 5246) ==========", "id": "tls.h", "kind": "module", "label": "tls.h", "language": "h", "sha256": "d969b76b49a0aea0", "symbol_count": 42, "symbols": [{"kind": "struct", "line": 70, "name": "tls_root"}, {"kind": "struct", "line": 79, "name": "sha256_ctx"}, {"kind": "struct", "line": 85, "name": "tls_pubkey"}, {"kind": "struct", "line": 95, "name": "tls_session"}, {"kind": "macro", "line": 2, "name": "TLS_H"}, {"kind": "macro", "line": 7, "name": "TLS_CT_CCS"}, {"kind": "macro", "line": 8, "name": "TLS_CT_ALERT"}, {"kind": "macro", "line": 9, "name": "TLS_CT_HANDSHAKE"}, {"kind": "macro", "line": 10, "name": "TLS_CT_APPDATA"}, {"kind": "macro", "line": 11, "name": "TLS_REC_HEADER"}, {"kind": "macro", "line": 12, "name": "TLS_REC_MAX"}, {"kind": "macro", "line": 13, "name": "TLS_MSG_MAX"}, {"kind": "macro", "line": 14, "name": "TLS_PLAIN_MAX"}, {"kind": "macro", "line": 15, "name": "TLS_VERSION_TLS12"}, {"kind": "macro", "line": 16, "name": "TLS_VERSION_TLS10"}, {"kind": "macro", "line": 19, "name": "TLS_HS_CLIENT_HELLO"}, {"kind": "macro", "line": 20, "name": "TLS_HS_SERVER_HELLO"}, {"kind": "macro", "line": 21, "name": "TLS_HS_CERTIFICATE"}, {"kind": "macro", "line": 22, "name": "TLS_HS_SERVER_KEY_EXCHANGE"}, {"kind": "macro", "line": 23, "name": "TLS_HS_SERVER_HELLO_DONE"}, {"kind": "macro", "line": 24, "name": "TLS_HS_CLIENT_KEY_EXCHANGE"}, {"kind": "macro", "line": 25, "name": "TLS_HS_FINISHED"}, {"kind": "macro", "line": 28, "name": "TLS_CSUITE_ECDHE_RSA_AES128GCM"}, {"kind": "macro", "line": 29, "name": "TLS_CSUITE_ECDHE_ECDSA_AES128GCM"}, {"kind": "macro", "line": 32, "name": "TLS_SIG_RSA_PKCS1_SHA256"}, {"kind": "macro", "line": 33, "name": "TLS_SIG_ECDSA_P256_SHA256"}, {"kind": "macro", "line": 34, "name": "TLS_SIG_ECDSA_P384_SHA384"}, {"kind": "macro", "line": 37, "name": "TLS_GROUP_SECP256R1"}, {"kind": "macro", "line": 40, "name": "TLS_EXT_SERVER_NAME"}, {"kind": "macro", "line": 41, "name": "TLS_EXT_SUPPORTED_GROUPS"}, {"kind": "macro", "line": 42, "name": "TLS_EXT_EC_POINT_FORMATS"}, {"kind": "macro", "line": 43, "name": "TLS_EXT_SIGNATURE_ALGS"}, {"kind": "macro", "line": 46, "name": "TLS_ALERT_LEVEL_WARNING"}, {"kind": "macro", "line": 47, "name": "TLS_ALERT_LEVEL_FATAL"}, {"kind": "macro", "line": 50, "name": "TLS_HS_TIMEOUT_MS"}, {"kind": "macro", "line": 51, "name": "TLS_READ_TIMEOUT_MS"}, {"kind": "macro", "line": 54, "name": "TLS_HOST_MAX"}, {"kind": "macro", "line": 57, "name": "TLS_CHAIN_MAX"}, {"kind": "macro", "line": 58, "name": "TLS_CERT_MAX"}, {"kind": "macro", "line": 62, "name": "TLS_BN_4096_WORDS"}, {"kind": "macro", "line": 63, "name": "TLS_BN_384_WORDS"}, {"kind": "macro", "line": 68, "name": "TLS_ROOT_COUNT"}]}, {"doc": "tls_crypto.c - the crypto behind the kernel TLS 1.2 client.", "id": "tls_crypto.c", "kind": "module", "label": "tls_crypto.c", "language": "c", "sha256": "0f26b30700677070", "symbol_count": 76, "symbols": [{"kind": "struct", "line": 655, "name": "mont_ctx"}, {"kind": "struct", "line": 838, "name": "ec_curve"}, {"doc": "Jacobian point: three coordinates in Montgomery domain, nw words each. * The point at infinity has Z = 0.", "kind": "struct", "line": 859, "name": "jpt"}, {"kind": "function", "line": 32, "name": "sha256_rotr", "signature": "static unsigned sha256_rotr(unsigned x, unsigned n)"}, {"kind": "function", "line": 36, "name": "sha256_init", "signature": "void sha256_init(struct sha256_ctx *c)"}, {"kind": "function", "line": 49, "name": "sha256_block", "signature": "static void sha256_block(struct sha256_ctx *c, const unsigned char *p)"}, {"kind": "function", "line": 79, "name": "sha256_update", "signature": "void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len)"}, {"kind": "function", "line": 104, "name": "sha256_final", "signature": "void sha256_final(struct sha256_ctx *c, unsigned char out[32])"}, {"kind": "function", "line": 125, "name": "sha256", "signature": "void sha256(const unsigned char *data, unsigned len, unsigned char out[32])"}, {"doc": "out[i * 4 + 1] = (unsigned char)(c->state[i] >> 16); out[i * 4 + 2] = (unsigned char)(c->state[i] >> 8); out[i * 4 + 3] = (unsigned char)(c->state[i]); } } void sha256(const unsigned char *data, unsigned len, unsigned char out[32]) { struct sha256_ctx c; sha256_init(&c); sha256_update(&c, data, len); sha256_final(&c, out); } /* ========== HMAC-SHA256 ==========", "kind": "function", "line": 134, "name": "hmac_sha256", "signature": "void hmac_sha256(const unsigned char *key, unsigned klen,\n                 const unsigned char *d..."}, {"doc": "opad[i] = k[i] ^ 0x5c; } sha256_init(&c); sha256_update(&c, ipad, 64); sha256_update(&c, data, dlen); sha256_final(&c, inner); sha256_init(&c); sha256_update(&c, opad, 64); sha256_update(&c, inner, 32); sha256_final(&c, out); } /* ========== TLS 1.2 PRF (P_SHA256) ==========", "kind": "function", "line": 164, "name": "p_hash", "signature": "static void p_hash(const unsigned char *secret, unsigned secret_len,\n                   const uns..."}, {"kind": "function", "line": 187, "name": "tls_prf", "signature": "void tls_prf(const unsigned char *secret, unsigned secret_len,\n             const char *label, co..."}, {"kind": "function", "line": 229, "name": "aes_xtime", "signature": "static unsigned aes_xtime(unsigned x)"}, {"kind": "function", "line": 234, "name": "aes_key_expand", "signature": "static void aes_key_expand(const unsigned char key[16], unsigned rk[44])"}, {"kind": "function", "line": 252, "name": "aes_mixcol", "signature": "static void aes_mixcol(unsigned a0, unsigned a1, unsigned a2, unsigned a3,\n                      ..."}, {"kind": "function", "line": 262, "name": "aes128_encrypt_block", "signature": "void aes128_encrypt_block(const unsigned char key[16],\n                          const unsigned c..."}, {"kind": "function", "line": 320, "name": "gf_shift_right", "signature": "static gf128 gf_shift_right(gf128 v)"}, {"doc": "z = z * h, in GF(2^128), MSB-first. Branches on z bits (public: * AAD/ciphertext), never on h bits (secret).", "kind": "function", "line": 334, "name": "gf_mul", "signature": "static gf128 gf_mul(gf128 z, gf128 h)"}, {"kind": "function", "line": 350, "name": "gf_put", "signature": "static gf128 gf_put(const unsigned char *p)"}, {"kind": "function", "line": 360, "name": "ghash_blocks", "signature": "static gf128 ghash_blocks(gf128 z, gf128 h, const unsigned char *data, unsigned len)"}, {"doc": "if (len > 0) { unsigned char pad[16]; gf128 b; TLS_MEMSET(pad, 0, 16); TLS_MEMCPY(pad, data, len); b = gf_put(pad); z.lo ^= b.lo; z.hi ^= b.hi; z = gf_mul(z, h); } return z; } /* Compute GCM tag for aad || ct (ct already ciphertext).", "kind": "function", "line": 384, "name": "gcm_tag_core", "signature": "static void gcm_tag_core(const unsigned char key[16],\n                         const unsigned cha..."}, {"kind": "function", "line": 426, "name": "gcm_ctr_core", "signature": "static void gcm_ctr_core(const unsigned char key[16],\n                         const unsigned cha..."}, {"doc": "TLS_MEMCPY(blk, nonce, 12); blk[12] = (unsigned char)(ctr >> 24); blk[13] = (unsigned char)(ctr >> 16); blk[14] = (unsigned char)(ctr >> 8); blk[15] = (unsigned char)(ctr); aes128_encrypt_block(key, blk, crypt); if (take > 16) take = 16; for (i = 0; i < (int)take; i++) out[off + i] = in[off + i] ^ crypt[i]; off += take; ctr++; } } /* TLS nonce: 4-byte implicit salt || 8-byte sequence number.", "kind": "function", "line": 450, "name": "tls_nonce", "signature": "static void tls_nonce(const unsigned char salt[4], unsigned long long seq,\n                      ..."}, {"kind": "function", "line": 456, "name": "gcm_tag", "signature": "static void gcm_tag(const unsigned char key[16], const unsigned char salt[4],\n                   ..."}, {"kind": "function", "line": 466, "name": "gcm_ctr", "signature": "static void gcm_ctr(const unsigned char key[16], const unsigned char salt[4],\n                   ..."}, {"kind": "function", "line": 474, "name": "aes128_gcm_seal", "signature": "int aes128_gcm_seal(const unsigned char key[16],\n                    const unsigned char salt[4],..."}, {"kind": "function", "line": 486, "name": "aes128_gcm_open", "signature": "int aes128_gcm_open(const unsigned char key[16],\n                    const unsigned char salt[4],..."}, {"kind": "function", "line": 504, "name": "aes128_gcm_seal_core", "signature": "int aes128_gcm_seal_core(const unsigned char key[16],\n                         const unsigned cha..."}, {"kind": "function", "line": 515, "name": "aes128_gcm_open_core", "signature": "int aes128_gcm_open_core(const unsigned char key[16],\n                         const unsigned cha..."}, {"doc": "unsigned char want[16]; unsigned char diff = 0; int i; if (ct_len > TLS_REC_MAX) return -1; gcm_tag_core(key, nonce, aad, aad_len, ct, ct_len, want); for (i = 0; i < 16; i++) diff |= want[i] ^ tag[i]; if (diff) return -1; gcm_ctr_core(key, nonce, ct, pt, ct_len); return 0; } /* ========== Big integers (32-bit limbs, little-endian) ========== #define TLS_BN_WORDS 128   /* 4096 bits", "kind": "function", "line": 536, "name": "bn_zero", "signature": "static void bn_zero(unsigned *a, int nw)"}, {"kind": "function", "line": 541, "name": "bn_is_zero", "signature": "static int bn_is_zero(const unsigned *a, int nw)"}, {"kind": "function", "line": 548, "name": "bn_cmp", "signature": "static int bn_cmp(const unsigned *a, const unsigned *b, int nw)"}, {"doc": "for (i = 0; i < nw; i++) v |= a[i]; return v == 0; } static int bn_cmp(const unsigned *a, const unsigned *b, int nw) { int i; for (i = nw - 1; i >= 0; i--) { if (a[i] < b[i]) return -1; if (a[i] > b[i]) return 1; } return 0; } /* r = a + b; returns carry out.", "kind": "function", "line": 559, "name": "bn_add", "signature": "static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw)"}, {"doc": "/* r = a + b; returns carry out. static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw) { unsigned long long carry = 0; int i; for (i = 0; i < nw; i++) { unsigned long long t = (unsigned long long)a[i] + b[i] + carry; r[i] = (unsigned)t; carry = t >> 32; } return (unsigned)carry; } /* r = a - b; a must be >= b; returns borrow (0 = fine).", "kind": "function", "line": 571, "name": "bn_sub", "signature": "static unsigned bn_sub(const unsigned *a, const unsigned *b, unsigned *r, int nw)"}, {"doc": "r = 2a mod n, for a < n. v = 2^(32nw) mod n = 2^(32nw) - n (the * Montgomery \"one\"): 2a + carry means 2a - 2^(32nw) + v = 2a - n < n.", "kind": "function", "line": 584, "name": "bn_dbl_mod", "signature": "static void bn_dbl_mod(const unsigned *a, const unsigned *n, const unsigned *v,\n                 ..."}, {"doc": "Montgomery multiplication. n is odd, n0inv = -n^(-1) mod 2^32. r = a*b*R^-1 mod n, R = 2^(32nw). * a, b < n.", "kind": "function", "line": 596, "name": "bn_mont_mul", "signature": "static void bn_mont_mul(const unsigned *a, const unsigned *b, const unsigned *n,\n                ..."}, {"doc": "carry = v >> 32; } s = (unsigned long long)t[nw] + carry; t[nw - 1] = (unsigned)s; t[nw] = t[nw + 1] + (unsigned)(s >> 32); } if (t[nw] || bn_cmp(t, n, nw) >= 0) { bn_sub(t, n, r, nw); } else { for (i = 0; i < nw; i++) r[i] = t[i]; } } /* -n^(-1) mod 2^32 via Newton iteration (n0 must be odd).", "kind": "function", "line": 635, "name": "bn_mont_n0inv", "signature": "static unsigned bn_mont_n0inv(unsigned n0)"}, {"doc": "} else { for (i = 0; i < nw; i++) r[i] = t[i]; } } /* -n^(-1) mod 2^32 via Newton iteration (n0 must be odd). static unsigned bn_mont_n0inv(unsigned n0) { unsigned inv = 1; int i; for (i = 0; i < 5; i++) inv *= 2 - n0 * inv; return 0 - inv; } /* R^2 mod n, R = 2^(32nw): 64*nw doublings from 1.", "kind": "function", "line": 643, "name": "bn_mont_r2", "signature": "static void bn_mont_r2(const unsigned *n, const unsigned *v, int nw,\n                       unsig..."}, {"kind": "function", "line": 662, "name": "bn_from_be", "signature": "static void bn_from_be(const unsigned char *bytes, unsigned len,\n                       unsigned ..."}, {"kind": "function", "line": 670, "name": "bn_to_be", "signature": "static void bn_to_be(const unsigned *a, unsigned char *out, unsigned len)"}, {"kind": "function", "line": 676, "name": "mont_init", "signature": "static void mont_init(struct mont_ctx *m, const unsigned char *p_bytes,\n                      uns..."}, {"kind": "function", "line": 688, "name": "mont_to", "signature": "static void mont_to(struct mont_ctx *m, const unsigned *a, unsigned *r)"}, {"kind": "function", "line": 692, "name": "mont_from", "signature": "static void mont_from(struct mont_ctx *m, const unsigned *a, unsigned *r)"}, {"kind": "function", "line": 699, "name": "mont_mul", "signature": "static void mont_mul(struct mont_ctx *m, const unsigned *a, const unsigned *b,\n                  ..."}, {"kind": "function", "line": 704, "name": "mont_sqr", "signature": "static void mont_sqr(struct mont_ctx *m, const unsigned *a, unsigned *r)"}, {"doc": "Field add/sub over the mont modulus (in Montgomery domain). The carry of a+b is corrected with one = 2^(32nw) - n, and a - b < 0 is * p - (b - a); neither path can overflow one word.", "kind": "function", "line": 712, "name": "mont_add", "signature": "static void mont_add(struct mont_ctx *m, const unsigned *a, const unsigned *b,\n                  ..."}, {"kind": "function", "line": 720, "name": "mont_sub", "signature": "static void mont_sub(struct mont_ctx *m, const unsigned *a, const unsigned *b,\n                  ..."}, {"doc": "Field inverse via Fermat: a^(p-2) mod p (a in Montgomery domain; * the result stays in Montgomery domain).", "kind": "function", "line": 736, "name": "mont_inv", "signature": "static void mont_inv(struct mont_ctx *m, const unsigned *a, unsigned *r)"}, {"kind": "function", "line": 847, "name": "ec_init", "signature": "static void ec_init(struct ec_curve *c, const unsigned char *p,\n                    const unsigne..."}, {"kind": "function", "line": 864, "name": "jpt_is_inf", "signature": "static int jpt_is_inf(const struct jpt *p, int nw)"}, {"kind": "function", "line": 868, "name": "jpt_set_inf", "signature": "static void jpt_set_inf(struct jpt *p, int nw)"}, {"kind": "function", "line": 874, "name": "jpt_copy", "signature": "static void jpt_copy(struct jpt *d, const struct jpt *s, int nw)"}, {"doc": "bn_zero(p->y, nw); bn_zero(p->z, nw); } static void jpt_copy(struct jpt *d, const struct jpt *s, int nw) { int i; for (i = 0; i < nw; i++) { d->x[i] = s->x[i]; d->y[i] = s->y[i]; d->z[i] = s->z[i]; } } /* Constant-time swap of two points on a 0/~0 mask.", "kind": "function", "line": 885, "name": "jpt_cswap", "signature": "static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask, int nw)"}, {"doc": "} /* Constant-time swap of two points on a 0/~0 mask. static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask, int nw) { int i; for (i = 0; i < nw; i++) { unsigned t; t = (a->x[i] ^ b->x[i]) & mask; a->x[i] ^= t; b->x[i] ^= t; t = (a->y[i] ^ b->y[i]) & mask; a->y[i] ^= t; b->y[i] ^= t; t = (a->z[i] ^ b->z[i]) & mask; a->z[i] ^= t; b->z[i] ^= t; } } /* P3 = 2 * P1 (a = p - 3: E = 3(A - Z1^4)).", "kind": "function", "line": 896, "name": "jpt_dbl", "signature": "static void jpt_dbl(struct ec_curve *c, const struct jpt *p1, struct jpt *p3)"}, {"doc": "mont_sqr(m, E, F); mont_add(m, D, D, t);          /* 2D mont_sub(m, F, t, p3->x);      /* X3 = F - 2D mont_sub(m, D, p3->x, t); mont_mul(m, E, t, t2); mont_add(m, C, C, t); mont_add(m, t, t, t); mont_add(m, t, t, t);          /* 8C mont_sub(m, t2, t, p3->y);     /* Y3 = E(D-X3) - 8C mont_mul(m, p1->y, p1->z, YZ); mont_add(m, YZ, YZ, p3->z);    /* Z3 = 2YZ } /* P3 = P1 + P2 (generic Jacobian add).", "kind": "function", "line": 936, "name": "jpt_add", "signature": "static void jpt_add(struct ec_curve *c, const struct jpt *p1, const struct jpt *p2,\n             ..."}, {"doc": "Constant-iteration scalar multiplication: the classic ladder. * Fixed iteration count, no table lookups indexed by secret bits.", "kind": "function", "line": 980, "name": "jpt_scalar_mult", "signature": "static void jpt_scalar_mult(struct ec_curve *c, const struct jpt *base,\n                         ..."}, {"doc": "Affine from Jacobian: x = X/Z^2, y = Y/Z^3. Bytes out are big-endian. * y_out may be NULL when only the x coordinate is wanted.", "kind": "function", "line": 1007, "name": "jpt_to_affine", "signature": "static void jpt_to_affine(struct ec_curve *c, const struct jpt *p,\n                          unsi..."}, {"doc": "Affine from bytes with on-curve validation. Returns 0 when the point * is valid and not the point at infinity.", "kind": "function", "line": 1032, "name": "jpt_from_affine", "signature": "static int jpt_from_affine(struct ec_curve *c, const unsigned char *x_bytes,\n                    ..."}, {"kind": "function", "line": 1075, "name": "ec_curve_by_id", "signature": "static struct ec_curve *ec_curve_by_id(int curve)"}, {"kind": "function", "line": 1079, "name": "ec_boot", "signature": "static void ec_boot(void)"}, {"kind": "function", "line": 1087, "name": "p256_scalar_mult", "signature": "int p256_scalar_mult(const unsigned char scalar[32],\n                     const unsigned char qx[..."}, {"kind": "function", "line": 1100, "name": "p384_scalar_mult", "signature": "int p384_scalar_mult(const unsigned char scalar[48],\n                     const unsigned char qx[..."}, {"kind": "function", "line": 1113, "name": "p256_ecdh", "signature": "int p256_ecdh(const unsigned char priv[32],\n              const unsigned char peer_x[32], const u..."}, {"doc": "int p256_ecdh(const unsigned char priv[32], const unsigned char peer_x[32], const unsigned char peer_y[32], unsigned char z[32]) { struct ec_curve *c; struct jpt base, out; ec_boot(); c = &ec_p256; if (jpt_from_affine(c, peer_x, peer_y, &base) != 0) return -1; jpt_scalar_mult(c, &base, priv, &out); jpt_to_affine(c, &out, z, 0); return 0; } /* ========== ECDSA verify ==========", "kind": "function", "line": 1128, "name": "der_parse_sig", "signature": "static int der_parse_sig(const unsigned char *sig, unsigned sig_len,\n                         con..."}, {"kind": "function", "line": 1162, "name": "ecdsa_verify", "signature": "int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[],\n           ..."}, {"doc": "EMSA-PKCS1-v1_5 DigestInfo check for an arbitrary hash: the encoding is 00 01 FF.. 00 <prefix><digest>. Constant-time: every byte of the * encoding contributes to the diff.", "kind": "function", "line": 1261, "name": "rsa_verify_digestinfo", "signature": "static int rsa_verify_digestinfo(const unsigned char *em, unsigned em_len,\n                      ..."}, {"doc": "diff |= em[i] ^ 0xff; } if (i >= em_len) return -1;         /* no separator if (i < 10) return -1;              /* padding too short (RFC 8017) i++; if (em_len - i != prefix_len + digest_len) return -1; for (i = 0; i < prefix_len; i++) diff |= em[em_len - prefix_len - digest_len + i] ^ prefix[i]; for (i = 0; i < digest_len; i++) diff |= em[em_len - digest_len + i] ^ digest[i]; return diff ? -1 : 0; } /* Shared RSA PKCS#1 v1.5 core: m^e mod n, EMSA-PKCS1-v1_5 in em.", "kind": "function", "line": 1285, "name": "rsa_pkcs1_verify_raw", "signature": "static int rsa_pkcs1_verify_raw(const unsigned char *n, unsigned n_len,\n                         ..."}, {"kind": "function", "line": 1325, "name": "rsa_pkcs1_verify_sha256", "signature": "int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len,\n                            c..."}, {"kind": "function", "line": 1339, "name": "rsa_pkcs1_verify_sha384", "signature": "int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len,\n                            c..."}, {"kind": "function", "line": 1385, "name": "sha384_rotr", "signature": "static unsigned long long sha384_rotr(unsigned long long x, unsigned n)"}, {"kind": "function", "line": 1389, "name": "sha384_raw", "signature": "static void sha384_raw(const unsigned char *data, unsigned len,\n                       unsigned c..."}, {"kind": "function", "line": 1505, "name": "sha384", "signature": "void sha384(const unsigned char *data, unsigned len, unsigned char out[48])"}, {"doc": "out[i * 8 + 2] = (unsigned char)(state[i] >> 40); out[i * 8 + 3] = (unsigned char)(state[i] >> 32); out[i * 8 + 4] = (unsigned char)(state[i] >> 24); out[i * 8 + 5] = (unsigned char)(state[i] >> 16); out[i * 8 + 6] = (unsigned char)(state[i] >> 8); out[i * 8 + 7] = (unsigned char)state[i]; } } void sha384(const unsigned char *data, unsigned len, unsigned char out[48]) { sha384_raw(data, len, out); } /* ========== P-256 helpers for the handshake ==========", "kind": "function", "line": 1511, "name": "p256_point_valid", "signature": "int p256_point_valid(const unsigned char x[32], const unsigned char y[32])"}, {"kind": "function", "line": 1519, "name": "p256_pub", "signature": "int p256_pub(const unsigned char priv[32],\n             unsigned char x[32], unsigned char y[32])"}, {"kind": "function", "line": 1538, "name": "p256_scalar_valid", "signature": "int p256_scalar_valid(const unsigned char scalar[32])"}, {"kind": "macro", "line": 534, "name": "TLS_BN_WORDS"}]}, {"doc": "ifndef TLS_PORT_H define TLS_PORT_H  Portability shim between the MiniOS kernel and the host-side test", "id": "tls_port.h", "kind": "module", "label": "tls_port.h", "language": "h", "sha256": "9c1747e836963cb4", "symbol_count": 27, "symbols": [{"doc": "define TLS_SEND           tls_test_send define TLS_RECV           tls_test_recv define TLS_RECV_TIMEOUT   tls_test_recv_timeout define TLS_CLOSE          tls_test_close", "kind": "function", "line": 39, "name": "tls_now_days", "signature": "static inline long tls_now_days(void)"}, {"kind": "function", "line": 43, "name": "tls_random", "signature": "static inline void tls_random(unsigned char *out, unsigned len)"}, {"kind": "macro", "line": 2, "name": "TLS_PORT_H"}, {"kind": "macro", "line": 17, "name": "TLS_FD_MAX"}, {"kind": "macro", "line": 19, "name": "TLS_PRINTF"}, {"kind": "macro", "line": 21, "name": "TLS_MALLOC"}, {"kind": "macro", "line": 22, "name": "TLS_FREE"}, {"kind": "macro", "line": 23, "name": "TLS_MEMCPY"}, {"kind": "macro", "line": 24, "name": "TLS_MEMSET"}, {"kind": "macro", "line": 25, "name": "TLS_MEMCMP"}, {"kind": "macro", "line": 26, "name": "TLS_STRLEN"}, {"kind": "macro", "line": 34, "name": "TLS_SEND"}, {"kind": "macro", "line": 36, "name": "TLS_RECV"}, {"kind": "macro", "line": 37, "name": "TLS_RECV_TIMEOUT"}, {"kind": "macro", "line": 38, "name": "TLS_CLOSE"}, {"kind": "macro", "line": 62, "name": "TLS_PRINTF"}, {"kind": "macro", "line": 64, "name": "TLS_MALLOC"}, {"kind": "macro", "line": 65, "name": "TLS_FREE"}, {"kind": "macro", "line": 66, "name": "TLS_MEMCPY"}, {"kind": "macro", "line": 67, "name": "TLS_MEMSET"}, {"kind": "macro", "line": 68, "name": "TLS_MEMCMP"}, {"kind": "macro", "line": 69, "name": "TLS_STRLEN"}, {"kind": "macro", "line": 70, "name": "TLS_SEND"}, {"kind": "macro", "line": 72, "name": "TLS_RECV"}, {"kind": "macro", "line": 73, "name": "TLS_RECV_TIMEOUT"}, {"kind": "macro", "line": 74, "name": "TLS_CLOSE"}, {"kind": "macro", "line": 75, "name": "TLS_FD_MAX"}]}, {"doc": "tls_roots.h - embedded CA roots (DER), generated by mkroots.sh.", "id": "tls_roots.h", "kind": "module", "label": "tls_roots.h", "language": "h", "sha256": "9762a8bc430995a5", "symbol_count": 0, "symbols": []}, {"doc": "tls_test.c - host-side tests for the kernel TLS stack.", "id": "tls_test.c", "kind": "module", "label": "tls_test.c", "language": "c", "sha256": "6972eec88c754a8c", "symbol_count": 23, "symbols": [{"doc": "#include <stdio.h> #include <stdlib.h> #include <string.h> #include <unistd.h> #include <sys/socket.h> #include <sys/select.h> #include <netinet/in.h> #include <arpa/inet.h> #include \"tls_port.h\" #include \"tls.h\" #include \"tls_test_roots.h\" /* ---- transport: the TLS stack talks to POSIX sockets here ----", "kind": "function", "line": 25, "name": "tls_test_send", "signature": "int tls_test_send(int fd, const char *buf, int len)"}, {"kind": "function", "line": 35, "name": "tls_test_recv", "signature": "int tls_test_recv(int fd, char *buf, int len)"}, {"kind": "function", "line": 40, "name": "tls_test_recv_timeout", "signature": "int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms)"}, {"kind": "function", "line": 53, "name": "tls_test_close", "signature": "void tls_test_close(int fd)"}, {"kind": "function", "line": 66, "name": "hexdigit", "signature": "static int hexdigit(int c)"}, {"kind": "function", "line": 73, "name": "unhex", "signature": "static void unhex(const char *hex, unsigned char *out, int n)"}, {"kind": "function", "line": 79, "name": "bytes_eq", "signature": "static int bytes_eq(const unsigned char *a, const unsigned char *b, int n)"}, {"doc": "static void unhex(const char *hex, unsigned char *out, int n) { int i; for (i = 0; i < n; i++) out[i] = (unsigned char)((hexdigit(hex[2 * i]) << 4) | hexdigit(hex[2 * i + 1])); } static int bytes_eq(const unsigned char *a, const unsigned char *b, int n) { int i, d = 0; for (i = 0; i < n; i++) d |= a[i] ^ b[i]; return d == 0; } /* ---- fixed vectors ----", "kind": "function", "line": 87, "name": "test_sha256", "signature": "static void test_sha256(void)"}, {"kind": "function", "line": 102, "name": "test_sha384", "signature": "static void test_sha384(void)"}, {"kind": "function", "line": 113, "name": "test_gcm", "signature": "static void test_gcm(void)"}, {"kind": "function", "line": 153, "name": "test_p256", "signature": "static void test_p256(void)"}, {"kind": "function", "line": 199, "name": "test_rsa_ecdsa_vectors", "signature": "static void test_rsa_ecdsa_vectors(void)"}, {"doc": "ok = ecdsa_verify(0, test_ec_x, test_ec_y, digest, 32, test_ec_sig, sizeof(test_ec_sig)) == 0; CHECK(\"ecdsa p256 sha256 verify\", ok); { unsigned char bad[256]; memcpy(bad, test_ec_sig, sizeof(test_ec_sig)); bad[2] ^= 0x01; ok = ecdsa_verify(0, test_ec_x, test_ec_y, digest, 32, bad, sizeof(test_ec_sig)) == -1; CHECK(\"ecdsa rejects tampered sig\", ok); } } /* ---- network scenarios ----", "kind": "function", "line": 248, "name": "tcp_connect", "signature": "static int tcp_connect(int port)"}, {"doc": "int fd = socket(AF_INET, SOCK_STREAM, 0); if (fd < 0) return -1; memset(&sa, 0, sizeof(sa)); sa.sin_family = AF_INET; sa.sin_port = htons((unsigned short)port); sa.sin_addr.s_addr = htonl(0x7f000001UL); if (connect(fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) { close(fd); return -1; } return fd; } /* Full handshake + one HTTP round trip. Returns 0 on success.", "kind": "function", "line": 265, "name": "http_over_tls", "signature": "static int http_over_tls(int port, const char *host)"}, {"kind": "function", "line": 289, "name": "scenario_good", "signature": "static int scenario_good(int port)"}, {"doc": "total += n; printed = 1; } tls_free_fd(fd); close(fd); if (!printed) return -1; return 0; } static int scenario_good(int port) { return http_over_tls(port, \"localhost\") == 0 ? 0 : -1; } /* \"*.example.com\" matches exactly one label.", "kind": "function", "line": 295, "name": "scenario_wild_good", "signature": "static int scenario_wild_good(int port)"}, {"kind": "function", "line": 298, "name": "scenario_wild_root", "signature": "static int scenario_wild_root(int port)"}, {"kind": "function", "line": 308, "name": "scenario_wild_deep", "signature": "static int scenario_wild_deep(int port)"}, {"kind": "function", "line": 318, "name": "scenario_bad_host", "signature": "static int scenario_bad_host(int port)"}, {"kind": "function", "line": 328, "name": "scenario_bad_ca", "signature": "static int scenario_bad_ca(int port)"}, {"kind": "function", "line": 338, "name": "scenario_expired", "signature": "static int scenario_expired(int port)"}, {"kind": "function", "line": 348, "name": "main", "signature": "int main(int argc, char **argv)"}, {"kind": "macro", "line": 61, "name": "CHECK"}]}, {"id": "tls_test.py", "kind": "module", "label": "tls_test.py", "language": "py", "sha256": "28b68a956762c4e1", "symbol_count": 16, "symbols": [{"kind": "function", "line": 26, "name": "run", "signature": "def run(cmd)"}, {"kind": "function", "line": 30, "name": "check", "signature": "def check(cmd)"}, {"kind": "function", "line": 37, "name": "gen_certs", "signature": "def gen_certs()"}, {"kind": "function", "line": 154, "name": "der_bytes", "signature": "def der_bytes(pem_path)"}, {"kind": "function", "line": 162, "name": "rsa_params", "signature": "def rsa_params(key_path)"}, {"kind": "function", "line": 172, "name": "ec_pub", "signature": "def ec_pub(key_path)"}, {"kind": "function", "line": 183, "name": "c_bytes", "signature": "def c_bytes(data, name)"}, {"kind": "function", "line": 191, "name": "gen_header", "signature": "def gen_header(p)"}, {"kind": "class", "line": 241, "name": "Server", "signature": "class Server(Thread)"}, {"kind": "method", "line": 280, "name": "serve", "signature": "def serve(cert, key)"}, {"kind": "method", "line": 288, "name": "serve_openssl", "signature": "def serve_openssl(cert, key, chain)"}, {"kind": "method", "line": 306, "name": "expect", "signature": "def expect(bin_path, args, want_zero, marker)"}, {"kind": "method", "line": 319, "name": "main", "signature": "def main()"}, {"kind": "method", "line": 61, "name": "server_cert", "signature": "def server_cert(name, algo, curve, ca_name, ca_algo, curve_ca, extra, subj)"}, {"kind": "method", "line": 242, "name": "__init__", "signature": "def __init__(self, cert, key, tls13_ok)"}, {"kind": "method", "line": 248, "name": "run", "signature": "def run(self)"}]}, {"doc": "tls_test_roots.h - generated by tls_test.py; never built into the kernel. The test root replaces the production table.", "id": "tls_test_roots.h", "kind": "module", "label": "tls_test_roots.h", "language": "h", "sha256": "7e3cb05140c67238", "symbol_count": 0, "symbols": []}, {"doc": "tls_x509.c - minimal X.509 DER parsing and chain verification.", "id": "tls_x509.c", "kind": "module", "label": "tls_x509.c", "language": "c", "sha256": "8cb5a4de9f742a13", "symbol_count": 23, "symbols": [{"kind": "struct", "line": 43, "name": "der_tlv"}, {"kind": "struct", "line": 129, "name": "x509_name"}, {"kind": "struct", "line": 172, "name": "x509_sans"}, {"kind": "struct", "line": 265, "name": "x509_cert"}, {"kind": "function", "line": 35, "name": "oid_eq", "signature": "static int oid_eq(const unsigned char *bytes, unsigned len,\n                  const unsigned char..."}, {"doc": "Parse the TLV at p[pos]; advances pos to the first byte after it. * Returns 0 on success, -1 on any bound violation.", "kind": "function", "line": 51, "name": "der_next", "signature": "static int der_next(const unsigned char *p, unsigned limit, unsigned *pos,\n                    st..."}, {"doc": "len = (len << 8) | p[(*pos)++]; } } else { len = p[(*pos)++]; } if (len > limit - *pos) return -1; out->val = p + *pos; out->len = len; out->tag = tag; pos += len; return 0; } /* A constructed SEQUENCE/SET whose content must parse as children.", "kind": "function", "line": 82, "name": "der_container", "signature": "static int der_container(const unsigned char *p, unsigned limit, unsigned *pos,\n                 ..."}, {"doc": "} /* A constructed SEQUENCE/SET whose content must parse as children. static int der_container(const unsigned char *p, unsigned limit, unsigned *pos, const unsigned char **val, unsigned *len) { struct der_tlv t; if (der_next(p, limit, pos, &t) != 0) return -1; if (t.tag != 0x30) return -1; val = t.val; len = t.len; return 0; } /* ---- Time ----", "kind": "function", "line": 93, "name": "days_from_civil", "signature": "static long days_from_civil(int y, int m, int d)"}, {"doc": "/* ---- Time ---- static long days_from_civil(int y, int m, int d) { long era, doe, yoe; int doy; y -= m <= 2 ? 1 : 0; era = (y >= 0 ? y : y - 399) / 400; yoe = y - (int)era * 400; doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; doe = (long)yoe * 365 + yoe / 4 - yoe / 100 + doy; return era * 146097 + doe - 719468; } /* UTCTime / GeneralizedTime \"....Z\" -> days since epoch, or -1.", "kind": "function", "line": 106, "name": "der_time_to_days", "signature": "static long der_time_to_days(const struct der_tlv *t)"}, {"doc": "} if (mon < 1 || mon > 12 || day < 1 || day > 31 || year < 1970 || year > 2100) return -1; return days_from_civil(year, mon, day); } /* ---- Name / extensions ---- struct x509_name { unsigned char cn[64]; unsigned cn_len; }; /* Find the first CN in an RDNSequence. Returns 0 when found.", "kind": "function", "line": 135, "name": "name_find_cn", "signature": "static int name_find_cn(const unsigned char *p, unsigned limit,\n                        struct x5..."}, {"kind": "function", "line": 177, "name": "san_add", "signature": "static void san_add(struct x509_sans *out, const unsigned char *v, unsigned len)"}, {"doc": "struct x509_sans { unsigned char dns[TLS_SAN_MAX][64]; unsigned      len[TLS_SAN_MAX]; int           count; }; static void san_add(struct x509_sans *out, const unsigned char *v, unsigned len) { if (out->count >= TLS_SAN_MAX || len >= 64) return; TLS_MEMCPY(out->dns[out->count], v, len); out->len[out->count] = len; out->count++; } /* Walk the SAN extension (2.5.29.17) OCTET STRING body.", "kind": "function", "line": 186, "name": "san_parse", "signature": "static void san_parse(const unsigned char *p, unsigned limit,\n                      struct x509_s..."}, {"doc": "unsigned seq_len, pos = 0; out->count = 0; if (der_container(p, limit, &pos, &seq, &seq_len) != 0) return; pos = 0; while (pos < seq_len) { struct der_tlv t; if (der_next(seq, seq_len, &pos, &t) != 0) return; if (t.tag == 0x82) san_add(out, t.val, t.len); /* dNSName } } /* ---- Public key ---- /* SPKI SEQUENCE content: { alg SEQUENCE { OID, params }, BIT STRING }.", "kind": "function", "line": 203, "name": "spki_parse", "signature": "static int spki_parse(const unsigned char *p, unsigned limit,\n                      struct tls_pu..."}, {"kind": "function", "line": 278, "name": "cert_parse", "signature": "static int cert_parse(const unsigned char *der, unsigned len,\n                      struct x509_c..."}, {"doc": "unsigned bpos = e2pos; if (der_next(ext, ext_len, &bpos, &body) != 0) break; if (oid_eq(eoid, eoid_len, oid_san, sizeof(oid_san))) san_parse(body.val, body.len, &out->sans), out->has_san = 1; } } } } } return 0; } /* ---- Hostname matching ----", "kind": "function", "line": 391, "name": "ascii_lower", "signature": "static int ascii_lower(int c)"}, {"doc": "} } } } return 0; } /* ---- Hostname matching ---- static int ascii_lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; } /* Exact match, ASCII case-insensitive.", "kind": "function", "line": 397, "name": "host_match_exact", "signature": "static int host_match_exact(const char *host, const unsigned char *name,\n                        ..."}, {"doc": "Wildcard: \"*.example.com\" matches exactly one label (\"a.example.com\", * never \"a.b.example.com\" nor \"example.com\").", "kind": "function", "line": 410, "name": "host_match_wildcard", "signature": "static int host_match_wildcard(const char *host, const unsigned char *name,\n                     ..."}, {"kind": "function", "line": 430, "name": "host_matches", "signature": "static int host_matches(const char *host, const struct x509_cert *leaf)"}, {"doc": "return 1; } return 0;   /* SAN present and nothing matched: fail closed } if (leaf->subject.cn_len) { return host_match_exact(host, leaf->subject.cn, leaf->subject.cn_len) || host_match_wildcard(host, leaf->subject.cn, leaf->subject.cn_len); } return 0; } /* ---- Signature verification ---- /* ========== Public API ==========", "kind": "function", "line": 451, "name": "tls_x509_parse_pubkey", "signature": "int tls_x509_parse_pubkey(const unsigned char *der, unsigned len,\n                          struc..."}, {"doc": "Trust anchors are matched by public key, not by self-signature: a presented root is often a cross-signed copy (signed by a legacy root, e.g. the SSL.com 2022 roots are signed by Comodo AAA), so checking its signature against its own key would reject a perfectly valid anchor. Key equality is safe because every link above the top is still signature-verified: an attacker cannot present a top cert carrying an embedded root's public key unless the chain below it was signed with * that root's private key.", "kind": "function", "line": 468, "name": "pubkey_equal", "signature": "static int pubkey_equal(const struct tls_pubkey *a, const struct tls_pubkey *b)"}, {"doc": "signature-verified: an attacker cannot present a top cert carrying an embedded root's public key unless the chain below it was signed with * that root's private key. static int pubkey_equal(const struct tls_pubkey *a, const struct tls_pubkey *b) { if (a->kind != b->kind) return 0; if (a->kind == 0) return a->n_len == b->n_len && a->e_len == b->e_len && TLS_MEMCMP(a->n, b->n, a->n_len) == 0 && TLS_MEMCMP(a->e, b->e, a->e_len) == 0; return TLS_MEMCMP(a->qx, b->qx, 48) == 0 && TLS_MEMCMP(a->qy, b->qy, 48) == 0; } /* Verify one certificate's signature with an issuer public key.", "kind": "function", "line": 479, "name": "cert_verify_signature", "signature": "static int cert_verify_signature(const struct x509_cert *cert,\n                                 c..."}, {"kind": "function", "line": 520, "name": "tls_x509_verify_chain", "signature": "int tls_x509_verify_chain(const unsigned char *chain, unsigned chain_len,\n                       ..."}, {"kind": "macro", "line": 170, "name": "TLS_SAN_MAX"}]}], "type": "CodePropertyGraph", "version": "1.0"}
```

---

## Architecture Reference

### C (20 files)

#### `bootloader.c`
**Path:** `bootloader.c`

**Functions:**
- `main` (line 20) `void main(void)` - *"gdt_start:\n" "  .quad 0\n" "  .quad 0x00CF9A000000FFFF\n" "  .quad 0x00CF92000000FFFF\n" "gdt_end:\n" ".global gdt32_ptr\n" "gdt32_ptr:\n" "  .word gdt_end - gdt_start - 1\n" "  .long gdt_start\n" ); __asm__("boot_drive: .byte 0\n"); /* Number of 512-byte sectors of kernel to load from LBA 1 to phys 0x10000. define KSECTORS 508*

**Macros:**
- `KSECTORS` (line 19)

#### `cvm_host.c`
**Path:** `cvm_host.c`

**Functions:**
- `n_strcmp` (line 18) `static int64_t n_strcmp(void *vm, int ac, uint64_t *av)`
- `n_strncmp` (line 24) `static int64_t n_strncmp(void *vm, int ac, uint64_t *av)`
- `n_strcpy` (line 31) `static int64_t n_strcpy(void *vm, int ac, uint64_t *av)`
- `n_strncpy` (line 37) `static int64_t n_strncpy(void *vm, int ac, uint64_t *av)`
- `n_memcpy` (line 44) `static int64_t n_memcpy(void *vm, int ac, uint64_t *av)`
- `n_memset` (line 51) `static int64_t n_memset(void *vm, int ac, uint64_t *av)`
- `n_memmove` (line 57) `static int64_t n_memmove(void *vm, int ac, uint64_t *av)`
- `n_memcmp` (line 64) `static int64_t n_memcmp(void *vm, int ac, uint64_t *av)`
- `n_strchr` (line 71) `static int64_t n_strchr(void *vm, int ac, uint64_t *av)`
- `n_strstr` (line 77) `static int64_t n_strstr(void *vm, int ac, uint64_t *av)`
- `n_malloc` (line 84) `static int64_t n_malloc(void *vm, int ac, uint64_t *av)`
- `n_free` (line 89) `static int64_t n_free(void *vm, int ac, uint64_t *av)`
- `n_calloc` (line 94) `static int64_t n_calloc(void *vm, int ac, uint64_t *av)`
- `n_realloc` (line 102) `static int64_t n_realloc(void *vm, int ac, uint64_t *av)`
- `n_exit` (line 110) `static int64_t n_exit(void *vm, int ac, uint64_t *av)`
- `n_fopen` (line 117) `static int64_t n_fopen(void *vm, int ac, uint64_t *av)`
- `n_fclose` (line 124) `static int64_t n_fclose(void *vm, int ac, uint64_t *av)`
- `n_fread` (line 130) `static int64_t n_fread(void *vm, int ac, uint64_t *av)`
- `n_fwrite` (line 137) `static int64_t n_fwrite(void *vm, int ac, uint64_t *av)`
- `n_fseek` (line 144) `static int64_t n_fseek(void *vm, int ac, uint64_t *av)`
- `n_ftell` (line 150) `static int64_t n_ftell(void *vm, int ac, uint64_t *av)`
- `n_rewind` (line 156) `static int64_t n_rewind(void *vm, int ac, uint64_t *av)`
- `n_fputs` (line 163) `static int64_t n_fputs(void *vm, int ac, uint64_t *av)`
- `n_fputc` (line 169) `static int64_t n_fputc(void *vm, int ac, uint64_t *av)`
- `n_fgetc` (line 175) `static int64_t n_fgetc(void *vm, int ac, uint64_t *av)`
- `n_ungetc` (line 181) `static int64_t n_ungetc(void *vm, int ac, uint64_t *av)`
- `n_fflush` (line 187) `static int64_t n_fflush(void *vm, int ac, uint64_t *av)`
- `n_putchar` (line 193) `static int64_t n_putchar(void *vm, int ac, uint64_t *av)`
- `n_write` (line 200) `static int64_t n_write(void *vm, int ac, uint64_t *av)`
- `n_read` (line 209) `static int64_t n_read(void *vm, int ac, uint64_t *av)`
- `n_puts` (line 224) `static int64_t n_puts(void *vm, int ac, uint64_t *av)`
- `n_atol` (line 232) `static int64_t n_atol(void *vm, int ac, uint64_t *av)`
- `n_strtol` (line 245) `static int64_t n_strtol(void *vm, int ac, uint64_t *av)`
- `n_stderr_addr` (line 258) `static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)`
- `n_stdout_addr` (line 263) `static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)`
- `n_stdin_addr` (line 268) `static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)`
- `kout_char` (line 273) `static void kout_char(void *ctx, char c)`
- `kout_uint` (line 279) `static void kout_uint(void *ctx, unsigned long long v, int base, int upper)`
- `kformat` (line 292) `static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)`
- `n_fprintf` (line 358) `static int64_t n_fprintf(void *vm, int ac, uint64_t *av)`
- `n_printf` (line 365) `static int64_t n_printf(void *vm, int ac, uint64_t *av)`
- `n_sprintf` (line 372) `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)`
- `n_snprintf` (line 380) `static int64_t n_snprintf(void *vm, int ac, uint64_t *av)`
- `register_host_natives` (line 388) `static void register_host_natives(CvmState *vm)`
- `cvm_main` (line 433) `int cvm_main(int argc, char **argv)`

#### `kernel.c`
**Path:** `kernel.c`
**File Doc:** *include "kernel.h" include "net.h" include "tls.h" include "bootdefs.h"  ================================================================*

**Functions:**
- `outb` (line 9) `static inline void outb(unsigned short port, unsigned char val)` - *================================================================ Port I/O helpers * ================================================================*
- `inb` (line 13) `static inline unsigned char inb(unsigned short port)`
- `serial_tx_ready` (line 34) `static int serial_tx_ready(void)`
- `serial_rx_ready` (line 36) `static int serial_rx_ready(void)`
- `serial_putc` (line 37) `void serial_putc(char c)`
- `serial_puts` (line 42) `void serial_puts(const char *s)`
- `serial_available` (line 43) `int serial_available(void)`
- `serial_getc` (line 45) `int serial_getc(void)`
- `vga_offset` (line 55) `static inline unsigned vga_offset(int x, int y)` - *================================================================ VGA driver * ================================================================ static int vga_x, vga_y; static char vga_color = 0x07; /* light grey on black*
- `vga_clear` (line 57) `void vga_clear(void)`
- `vga_set_cursor` (line 67) `void vga_set_cursor(int x, int y)`
- `vga_scroll` (line 87) `void vga_scroll(void)`
- `vga_newline` (line 105) `void vga_newline(void)`
- `vga_raw_space` (line 111) `static void vga_raw_space(void)`
- `redir_grow` (line 132) `static int redir_grow(void)`
- `vga_putc` (line 142) `void vga_putc(char c)`
- `vga_puts` (line 175) `void vga_puts(const char *s)`
- `kbd_q_push` (line 220) `static void kbd_q_push(unsigned char c)`
- `kbd_q_empty` (line 227) `static int kbd_q_empty(void)`
- `kbd_q_pop` (line 229) `static int kbd_q_pop(void)`
- `kbd_q_peek` (line 236) `static int kbd_q_peek(void)`
- `kbd_available` (line 241) `int kbd_available(void)`
- `kbd_read` (line 247) `int kbd_read(void)`
- `mm_setup_protections` (line 335) `static void mm_setup_protections(void)` - *Mark the user window [USER_LOAD_BASE, USER_LOAD_END) as user-accessible (U/S bit) in the 2 MB page directory built by the boot path. A ring-3 access requires U/S set at every level of the walk, so the PML4 and PDPT entries that cover the whole identity map are lifted too; the per-2 MB isolation then lives entirely in the PD leaf bits, and every other page — page tables, kernel image, heap, VGA, MMIO — stays supervisor, so a ring-3 program is stopped in hardware from reading or writing kernel * memory.*
- `kallocator_init` (line 347) `void kallocator_init(void)`
- `kmalloc` (line 354) `void *kmalloc(unsigned long size)`
- `kfree` (line 391) `void kfree(void *ptr)`
- `kcalloc` (line 426) `void *kcalloc(unsigned long nmemb, unsigned long size)`
- `krealloc` (line 433) `void *krealloc(void *ptr, unsigned long size)`
- `kstrlen` (line 464) `unsigned long kstrlen(const char *s)` - *================================================================ String functions * ================================================================*
- `kstrcpy` (line 470) `char *kstrcpy(char *dst, const char *src)`
- `kstrncpy` (line 476) `char *kstrncpy(char *dst, const char *src, unsigned long n)`
- `kstrncat` (line 482) `char *kstrncat(char *dst, const char *src, unsigned long n)`
- `kstrcmp` (line 490) `int kstrcmp(const char *a, const char *b)`
- `kstrncmp` (line 495) `int kstrncmp(const char *a, const char *b, unsigned long n)`
- `kstrchr` (line 500) `char *kstrchr(const char *s, int c)`
- `kstrstr` (line 505) `char *kstrstr(const char *hay, const char *ndl)`
- `kmemcpy` (line 515) `void *kmemcpy(void *dst, const void *src, unsigned long n)`
- `kmemset` (line 522) `void *kmemset(void *dst, int c, unsigned long n)`
- `kmemcmp` (line 528) `int kmemcmp(const void *a, const void *b, unsigned long n)`
- `kmemmove` (line 534) `void *kmemmove(void *dst, const void *src, unsigned long n)`
- `katol` (line 544) `static long katol(const char *s)` - *const unsigned char *pa = a, *pb = b; while (n--) { if (*pa != *pb) return *pa - *pb; pa++; pb++; } return 0; } void *kmemmove(void *dst, const void *src, unsigned long n) { char *d = dst; const char *s = src; if (d < s) { while (n--) *d++ = *s++; } else       { d += n; s += n; while (n--) *--d = *--s; } return dst; } /* atoi helper*
- `ramdisk_reserve` (line 579) `static int ramdisk_reserve(unsigned long want)` - *Reserve a data area of `want` bytes, clamped to the configured maximum. An existing area is kept when it is already large enough, otherwise the * live contents are carried over to the new one. Returns 1 on success.*
- `ramdisk_setup_from` (line 596) `void ramdisk_setup_from(void *data, unsigned size)` - *Populate the ramdisk from a packed image. The image is validated in full before any entry is published, so a rejected image leaves the directory * untouched instead of advertising files whose data was never copied.*
- `ramdisk_init` (line 647) `void ramdisk_init(void)`
- `ramdisk_open` (line 664) `RDFile *ramdisk_open(const char *name)`
- `ramdisk_read` (line 674) `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len)`
- `ramdisk_write` (line 682) `int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len)`
- `ramdisk_create` (line 690) `RDFile *ramdisk_create(const char *name, unsigned size)`
- `ramdisk_resize` (line 708) `int ramdisk_resize(RDFile *f, unsigned newsize)` - *Grow or shrink an existing file by relocating the data that follows it. Files are stored back to back in the data area; this moves every file * after `f` by the size delta. Returns 1 on success, 0 on overflow.*
- `ramdisk_list` (line 744) `int ramdisk_list(RDFile **out, int max)`
- `ramdisk_delete` (line 756) `int ramdisk_delete(RDFile *f)` - *Remove an entry and compact the data area. Files after `f` are shifted left by f->size and the directory slot is dropped. Returns 1 on success, * 0 when the pointer is not a live entry.*
- `fs_resolve` (line 792) `static int fs_resolve(const char *path, char *out, unsigned cap)` - *Resolve a path against the cwd into `out` (cap >= RAMDISK_FNAME_LEN). A leading '/' starts from the root, '..' pops one component, '.' and empty components are skipped. Returns 1 on success; a name that does * not fit is rejected like a missing file, never truncated.*
- `fs_dir_exists` (line 826) `static int fs_dir_exists(const char *dir)` - *if (*p) p++; continue; } if (len + 1 + clen >= cap) return 0; if (len > 0 && out[len - 1] != '/') out[len++] = '/'; kmemcpy(out + len, start, clen); len += clen; out[len] = 0; if (*p) p++; } return 1; } /* Does the directory `dir` (ending in '/') exist? The root always does.*
- `fs_is_dir` (line 837) `static int fs_is_dir(const char *resolved)` - *Return 1 when the resolved name refers to a directory: a trailing '/' always does, otherwise the name denotes a directory when no exact file * entry exists and some entry starts with `<name>/`.*
- `kfopen` (line 849) `KFILE *kfopen(const char *path, const char *mode)`
- `kfclose` (line 874) `int kfclose(KFILE *f)`
- `kfgetc` (line 883) `int kfgetc(KFILE *f)`
- `kfgets` (line 900) `char *kfgets(char *buf, int size, KFILE *f)` - *Read at most size-1 bytes up to and including the first newline. Returns * buf, or 0 when nothing could be read.*
- `kfungetc` (line 913) `int kfungetc(int c, KFILE *f)`
- `kfread` (line 919) `unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f)`
- `kfwrite` (line 934) `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f)`
- `kfseek` (line 962) `int kfseek(KFILE *f, long offset, int whence)`
- `kftell` (line 975) `long kftell(KFILE *f)`
- `kfflush` (line 979) `int kfflush(KFILE *f)`
- `kfputs` (line 990) `int kfputs(const char *s, KFILE *f)`
- `kfputc` (line 996) `int kfputc(int c, KFILE *f)`
- `krewind` (line 1001) `void krewind(KFILE *f)`
- `kfile_stdin` (line 1013) `KFILE *kfile_stdin(void)`
- `kfile_stdout` (line 1015) `KFILE *kfile_stdout(void)`
- `kfile_stderr` (line 1016) `KFILE *kfile_stderr(void)`
- `putc_buf` (line 1022) `static void putc_buf(char c, void *ctx, int *written)` - *================================================================ printf family * ================================================================*
- `putc_file` (line 1028) `static void putc_file(char c, void *ctx, int *written)`
- `putc_str` (line 1034) `static void putc_str(char c, void *ctx, int *written)`
- `emit_num` (line 1044) `static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,
                ...` - *Emit a reverse-ordered digit buffer honouring width, left-justify and * zero-fill flags. buf holds `pos` digits least-significant first.*
- `kformat` (line 1061) `static void kformat(void (*emit)(char, void *, int *), void *ctx,
                    int *writte...`
- `kprintf` (line 1160) `int kprintf(const char *fmt, ...)`
- `kfprintf` (line 1169) `int kfprintf(KFILE *f, const char *fmt, ...)`
- `ksprintf` (line 1178) `int ksprintf(char *buf, const char *fmt, ...)`
- `putc_snbuf` (line 1191) `static void putc_snbuf(char c, void *ctx, int *written)`
- `ksnprintf` (line 1196) `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)`
- `k_register_symbol` (line 1222) `void k_register_symbol(const char *name, void *addr)`
- `ksym_resolve` (line 1230) `void *ksym_resolve(const char *name)`
- `kprog_slot` (line 1256) `static KProg *kprog_slot(const char *name)`
- `k_register_program` (line 1264) `void k_register_program(const char *name, prog_entry_t entry)`
- `k_register_process` (line 1270) `void k_register_process(const char *name, void *proc_entry)`
- `k_spawn` (line 1276) `int k_spawn(const char *name, int argc, char **argv)`
- `elf_name_copy` (line 1397) `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,
                         ...` - *Copy a NUL-terminated name out of a string table without reading past the table's bounds; an out-of-range or unterminated name yields an * empty string, never a wild pointer into the kernel heap.*
- `elf_load_fail` (line 1413) `static void elf_load_fail(void *base, void **sec_addrs, const char *why)` - *Release a partially built relocatable image and report why it was * rejected. Used on every failure path of elf_load.*
- `elf_load` (line 1418) `void *elf_load(void *data, unsigned size)`
- `apply_exec_relocs` (line 1645) `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,
                    ...` - *================================================================ Linux ELF executable loader (ET_EXEC / ET_DYN) + process runtime  Loads program headers into the identity-mapped user region, applies RELATIVE / IRELATIVE / symbol relocations, sets up a System V initial stack (argc/argv/envp/auxv) and jumps to the ELF entry point.  The program talks back to the kernel through the x86-64 `syscall` instruction (see the syscall dispatcher below). * ================================================================ static unsigned long g_brk;        /* current program break static unsigned long g_brk_limit;  /* upper bound for brk growth static unsigned long user_mmap_cur; /* anonymous mmap cursor, grows down*
- `load_exec_elf` (line 1728) `void *load_exec_elf(void *data, unsigned size)`
- `wrmsr` (line 1783) `static inline void wrmsr(unsigned msr, unsigned long val)` - *if (dst + ph[i].p_memsz > max_end) max_end = dst + ph[i].p_memsz; } if (max_end == 0) return 0; apply_exec_relocs(data, size, base, xr, nxr); g_brk       = ALIGN_UP(max_end, 0x1000); g_brk_limit = USER_BRK_END; user_mmap_cur = USER_BRK_END; return (void *)(base + e->e_entry); } /* ---- MSR access + SYSCALL/SYSRET setup ----------------------------------*
- `rdmsr` (line 1788) `static inline unsigned long rdmsr(unsigned msr)`
- `syscall_init` (line 1803) `void syscall_init(void)`
- `syscall_trace_enabled` (line 1879) `long syscall_trace_enabled(void)`
- `syscall_trace_set` (line 1881) `void syscall_trace_set(int on)`
- `ksyscall` (line 1882) `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- `user_range_ok` (line 1902) `static int user_range_ok(unsigned long p, unsigned long len)` - *--- User-pointer validation --------------------------------------------- The syscall boundary is the hardened edge between ring 3 and ring 0. Every pointer a Linux ABI program hands the kernel must lie inside the user window [USER_LOAD_BASE, USER_LOAD_END), because that is the only memory the page tables marked user-accessible. Anything else — kernel heap, kernel image, page tables, MMIO — must be rejected before a single * dereference. All arithmetic is overflow checked.*
- `user_str_ok` (line 1908) `static int user_str_ok(unsigned long p, unsigned long maxlen)`
- `ksyscall_dispatch` (line 1916) `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- `setup_user_stack` (line 2121) `static unsigned long *setup_user_stack(char *sbase, unsigned long ssize,
                        ...` - *"  popq %r8\n" "  popq %r9\n" "  xchgq %rsp, syscall_kstack(%rip)\n" "  cmpq $" STR(USER_WIN_LO) ", %rsp\n" "  jb 1f\n" "  cmpq $" STR(USER_WIN_HI) ", %rsp\n" "  jae 1f\n" "  sysretq\n" "1:\n" "  jmp *%rcx\n" ); /* ---- Build the SysV initial stack and jump to the ELF entry -------------*
- `k_exec_user` (line 2152) `int k_exec_user(void *entry, int argc, char **argv)`
- `k_run_rel` (line 2202) `int k_run_rel(prog_entry_t entry, int argc, char **argv)` - *"mov %%ax, %%ds\n" "mov %%ax, %%es\n" "mov %%ax, %%fs\n" "mov %%ax, %%gs\n" "mov %%ax, %%ss\n" :: [kdata] "i"(GDT64_DATA_SEL) : "ax", "memory"); wrmsr(MSR_FSBASE, 0); wrmsr(MSR_GSBASE, 0); syscall_kstack = SYS_KSTK_TOP; return exec_exit_code; } /* Run an ET_REL program as a plain function call, but catch a libc exit().*
- `kexit` (line 2211) `void kexit(int code)` - *syscall_kstack = SYS_KSTK_TOP; return exec_exit_code; } /* Run an ET_REL program as a plain function call, but catch a libc exit(). int k_run_rel(prog_entry_t entry, int argc, char **argv) { exec_exit_code = 0; syscall_kstack = SYS_KSTK_TOP; if (ksetjmp(&exec_return) == 0) return entry(argc, argv); return exec_exit_code; } /* libc exit() for loaded programs: unwind back to the shell.*
- `shell_prompt` (line 2236) `static void shell_prompt(void)`
- `console_getc` (line 2244) `static int console_getc(void)` - *#define SHELL_HIST_MAX 16 static char shell_hist[SHELL_HIST_MAX][CMD_BUF_SZ]; static int  shell_hist_count; static int  shell_hist_idx = -1; static char shell_line_saved[CMD_BUF_SZ]; static int  shell_line_saved_pos; static void shell_prompt(void) { vga_puts("\nminiOS> "); } static void shell_exec_builtin(int argc, char **argv); static int console_pushback = -1; /* Blocking read from either the PS/2 keyboard or COM1 serial line.*
- `console_peek` (line 2267) `static int console_peek(void)` - *Next buffered byte without consuming it, or -1 when nothing is available right now. Used to tell an ESC prefix from a complete * escape sequence, which always arrives in one burst.*
- `shell_readline_buf` (line 2283) `static void shell_readline_buf(char *buf, int size)` - *Read one line into buf (at most size-1 chars). Echoes input and * honours backspace. Shared by the shell prompt and the editor.*
- `shell_readline` (line 2309) `static void shell_readline(void)`
- `shell_hist_show` (line 2316) `static void shell_hist_show(char *buf, int size, int *pos, const char *text)` - *Redraw the edit line with the recalled text: erase what is shown, * then write the replacement into buf and onto the console.*
- `shell_hist_nav` (line 2332) `static void shell_hist_nav(char *buf, int size, int *pos, int up)` - *Move through the history ring: up recalls older entries, down moves * forward again and finally restores the live line.*
- `shell_parse` (line 2412) `static int shell_parse(char *line, char **argv, int max_args)`
- `redirect_suspend` (line 2430) `static int redirect_suspend(void)` - *Shell status text must never land inside a redirected command's output: `cmd > file` captures what the command wrote, not what the shell reported * about it. These helpers lift a print out of the active capture.*
- `redirect_resume` (line 2435) `static void redirect_resume(int was)`
- `shell_report_exit` (line 2439) `static void shell_report_exit(int code)`
- `shell_report` (line 2445) `static void shell_report(const char *what, const char *detail)`
- `redirect_begin` (line 2455) `static int redirect_begin(void)` - *int was = redirect_suspend(); kprintf("exit code: %d\n", code); redirect_resume(was); } static void shell_report(const char *what, const char *detail) { int was = redirect_suspend(); vga_puts(what); if (detail) vga_puts(detail); vga_putc('\n'); redirect_resume(was); } /* Start capturing console output for a `> file` redirection.*
- `redirect_commit` (line 2466) `static int redirect_commit(const char *path, int append_mode)` - *Stop capturing and store the captured bytes in `path`. Returns 0 on success. The capture is released on every path so that a failure cannot * leave the console silently detached from the screen.*
- `shell_take_redirect` (line 2487) `static int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)` - *Split a `> file` / `>> file` redirection off the end of a parsed command line. Returns 1 when a redirection was found, 0 when there was none and -1 when the syntax is incomplete. On success argc is trimmed to the * command and append_mode is set for `>>`.*
- `shell_run` (line 2509) `void shell_run(void)`
- `shell_load` (line 2548) `static int shell_load(const char *fname, char *progname_out, void **entry_out)` - *Load an ELF file from the ramdisk and register it under its filename stem. Returns 1 for an ET_REL program, 2 for an ET_EXEC/ET_DYN Linux process, * 0 on failure.  progname_out must hold at least 32 bytes.*
- `edit_alloc` (line 2604) `static EditBuf *edit_alloc(const char *fname)`
- `edit_free` (line 2620) `static void edit_free(EditBuf *e)`
- `edit_load` (line 2626) `static int edit_load(EditBuf *e)`
- `edit_save` (line 2661) `static int edit_save(EditBuf *e)`
- `edit_print` (line 2675) `static void edit_print(EditBuf *e, int idx)`
- `edit_list` (line 2683) `static void edit_list(EditBuf *e)`
- `edit_set_line` (line 2692) `static int edit_set_line(EditBuf *e, int idx, const char *text)`
- `edit_insert` (line 2701) `static int edit_insert(EditBuf *e, int idx, const char *text)`
- `edit_delete` (line 2711) `static int edit_delete(EditBuf *e, int idx)`
- `edit_usage` (line 2720) `static void edit_usage(void)`
- `edit_refuse_save` (line 2729) `static int edit_refuse_save(EditBuf *e)` - *A buffer that did not hold the whole file must never be written back: * saving it would drop the part that was never loaded.*
- `edit_loop` (line 2734) `static void edit_loop(EditBuf *e)`
- `shell_cmd_edit` (line 2798) `static void shell_cmd_edit(int argc, char **argv)`
- `outw_port` (line 2830) `static inline void outw_port(unsigned short port, unsigned short val)`
- `shell_cmd_poweroff` (line 2836) `static void shell_cmd_poweroff(void)` - *define QEMU_PM_PORT 0x604*
- `shell_run_from_path` (line 2847) `static int shell_run_from_path(const char *cmd, int argc, char **argv)` - *Resolve a command through the bin path: load /bin/<cmd> (root-anchored, like Linux /bin, so the cwd never changes where commands are found) from the ramdisk as a Linux ELF and run it with the original argv. Returns * the exit code or -1 when the name is not eligible or no ELF exists.*
- `shell_exec_builtin` (line 2861) `static void shell_exec_builtin(int argc, char **argv)`
- `register_libc_symbols` (line 3121) `static void register_libc_symbols(void)` - *================================================================ Libc symbol registration * ================================================================*
- `__attribute__` (line 3188) `__attribute__((section(".init.text")))
void kmain(void)`

**Macros:**
- `COM1` (line 22)
- `REDIR_INITIAL_CAP` (line 124)
- `REDIR_MAX_BYTES` (line 125)
- `KBD_QUEUE_LEN` (line 216)
- `ALLOC_MAGIC` (line 285)
- `FREE_MAGIC` (line 287)
- `ALIGN_UP` (line 288)
- `BLOCK_HDR_SZ` (line 295)
- `USER_LOAD_BASE` (line 306)
- `USER_LOAD_END` (line 307)
- `USER_STACK_SIZE` (line 308)
- `USER_STACK_TOP` (line 309)
- `USER_STACK_BASE` (line 310)
- `USER_BRK_END` (line 311)
- `SYS_KSTK_TOP` (line 312)
- `SYS_KSTK_BASE` (line 313)
- `HEAP_BASE` (line 314)
- `HEAP_SIZE` (line 315)
- `EFAULT` (line 316)
- `USER_WIN_LO` (line 322)
- `USER_WIN_HI` (line 323)
- `STR_` (line 324)
- `STR` (line 325)
- `RD_MAGIC` (line 557)
- `RD_HEADER_SIZE` (line 559)
- `RD_ENTRY_SIZE` (line 560)
- `RD_DATA_MIN` (line 561)
- `RD_DATA_SPARE` (line 562)
- `RD_DATA_MAX` (line 563)
- `KSYM_MAX` (line 1212)
- `KPROG_MAX` (line 1244)
- `EI_NIDENT` (line 1296)
- `ELF64_R_SYM` (line 1359)
- `ELF64_R_TYPE` (line 1361)
- `SHN_UNDEF` (line 1362)
- `SHT_SYMTAB` (line 1363)
- `SHT_STRTAB` (line 1365)
- `SHT_RELA` (line 1366)
- `SHT_PROGBITS` (line 1367)
- `SHT_NOBITS` (line 1368)
- `SHF_ALLOC` (line 1369)
- `SHF_EXECINSTR` (line 1370)
- `ET_REL` (line 1371)
- `ET_EXEC` (line 1373)
- `ET_DYN` (line 1374)
- `EM_X86_64` (line 1375)
- `PT_LOAD` (line 1376)
- `R_X86_64_64` (line 1377)
- `R_X86_64_PC32` (line 1379)
- `R_X86_64_PLT32` (line 1380)
- `R_X86_64_GLOB_DAT` (line 1381)
- `R_X86_64_JUMP_SLOT` (line 1382)
- `R_X86_64_RELATIVE` (line 1383)
- `R_X86_64_32` (line 1384)
- `R_X86_64_32S` (line 1385)
- `R_X86_64_IRELATIVE` (line 1386)
- `PF_X` (line 1387)
- `ELF_MAX_SEGMENTS` (line 1389)
- `ELF_NAME_MAX` (line 1390)
- `MSR_EFER` (line 1793)
- `MSR_STAR` (line 1795)
- `MSR_LSTAR` (line 1796)
- `MSR_SFMASK` (line 1797)
- `MSR_FSBASE` (line 1798)
- `MSR_GSBASE` (line 1799)
- `KFD_MAX` (line 1859)
- `SYSCALL_TRACE` (line 1869)
- `CMD_BUF_SZ` (line 2220)
- `MAX_ARGS` (line 2222)
- `SHELL_BIN_PATH` (line 2223)
- `SHELL_BIN_PATH_LEN` (line 2225)
- `SHELL_BIN_MAX_CMD` (line 2226)
- `SHELL_HIST_MAX` (line 2229)
- `EDIT_MAX_LINES` (line 2587)
- `EDIT_LINE_MAX` (line 2589)
- `EDIT_FILE_MAX` (line 2590)
- `QEMU_PM_PORT` (line 2834)

**Structs:**
- `Block` (line 290)
- `snctx` (line 1190)
- `exec_range` (line 1392)
- `kiovec` (line 1868)

#### `net.c`
**Path:** `net.c`
**File Doc:** *MiniOS network stack: rtl8139 under QEMU slirp user networking.*

**Functions:**
- `outb_port` (line 24) `static void outb_port(unsigned short port, unsigned char val)`
- `inb_port` (line 28) `static unsigned char inb_port(unsigned short port)`
- `outw_port` (line 34) `static void outw_port(unsigned short port, unsigned short val)`
- `outl_port` (line 38) `static void outl_port(unsigned short port, unsigned int val)`
- `inw_port` (line 42) `static unsigned short inw_port(unsigned short port)`
- `inl_port` (line 48) `static unsigned int inl_port(unsigned short port)`
- `net_reg8` (line 54) `static unsigned char net_reg8(unsigned short off)`
- `net_reg8_w` (line 56) `static void net_reg8_w(unsigned short off, unsigned char v)`
- `net_reg16` (line 57) `static unsigned short net_reg16(unsigned short off)`
- `net_reg16_w` (line 58) `static void net_reg16_w(unsigned short off, unsigned short v)`
- `net_reg32` (line 59) `static unsigned int net_reg32(unsigned short off)`
- `net_reg32_w` (line 60) `static void net_reg32_w(unsigned short off, unsigned int v)`
- `pci_read32` (line 69) `static unsigned int pci_read32(unsigned bus, unsigned dev, unsigned func, unsigned reg)` - *define NET_REG_CR      0x37 define NET_REG_TSD0    0x10 define NET_REG_TSAD0   0x20 define NET_REG_RBSTART 0x30 define NET_REG_CAPR    0x38 define NET_REG_CBR     0x3A define NET_REG_9346CR  0x50*
- `pci_write32` (line 74) `static void pci_write32(unsigned bus, unsigned dev, unsigned func, unsigned reg, unsigned int val)`
- `net_find_rtl8139` (line 81) `static unsigned short net_find_rtl8139(void)` - *#define NET_REG_CBR     0x3A #define NET_REG_9346CR  0x50 static unsigned int pci_read32(unsigned bus, unsigned dev, unsigned func, unsigned reg) { outl_port(0xCF8, 0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC)); return inl_port(0xCFC); } static void pci_write32(unsigned bus, unsigned dev, unsigned func, unsigned reg, unsigned int val) { outl_port(0xCF8, 0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC)); outl_port(0xCFC, val); } /* Find the rtl8139 and return its I/O base, 0 when absent.*
- `net_rdtsc` (line 99) `static unsigned long net_rdtsc(void)`
- `net_time_init` (line 105) `static void net_time_init(void)`
- `net_time_ms` (line 119) `unsigned long net_time_ms(void)`
- `net_rtl_reset` (line 136) `static void net_rtl_reset(void)`
- `net_rtl_init` (line 145) `static void net_rtl_init(void)`
- `net_tx_frame` (line 177) `static int net_tx_frame(const unsigned char *frame, unsigned len)`
- `net_put16` (line 211) `static void net_put16(unsigned char *p, unsigned short v)` - *================================================================ Byte helpers * ================================================================*
- `net_put32` (line 216) `static void net_put32(unsigned char *p, unsigned int v)`
- `net_get16` (line 223) `static unsigned short net_get16(const unsigned char *p)`
- `net_get32` (line 227) `static unsigned int net_get32(const unsigned char *p)`
- `net_checksum` (line 232) `static unsigned short net_checksum(const void *data, unsigned len)`
- `net_arp_store` (line 257) `static void net_arp_store(const unsigned char *ip, const unsigned char *mac)`
- `net_arp_lookup` (line 272) `static int net_arp_lookup(const unsigned char *ip, unsigned char *mac_out)`
- `net_arp_request` (line 283) `static void net_arp_request(const unsigned char *ip)`
- `net_arp_resolve` (line 302) `static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out)` - *kmemcpy(frame + 6, net_mac, NET_ETH_ALEN); net_put16(frame + 12, NET_ETHERTYPE_ARP); net_put16(frame + 14, 1);                 /* ethernet net_put16(frame + 16, 0x0800);            /* IPv4 frame[18] = 6; frame[19] = 4; net_put16(frame + 20, NET_ARP_REQUEST); kmemcpy(frame + 22, net_mac, NET_ETH_ALEN); kmemcpy(frame + 28, net_our_ip, 4); kmemcpy(frame + 38, ip, 4); net_tx_frame(frame, 42); } /* Resolve an IP on the 10.0.2.0/24 link. Retries, bounded timeout.*
- `net_ip_send` (line 327) `static int net_ip_send(const unsigned char *dip, unsigned char proto,
                       cons...` - *================================================================ IPv4 / ICMP / UDP / DNS * ================================================================ static unsigned short net_ip_id; static unsigned short net_icmp_id = 0x4D49; static unsigned short net_udp_port = NET_EPHEMERAL_MIN; static unsigned int   net_tx_bytes; static unsigned int   net_rx_bytes; /* Send a frame on the link: dst IP decides the destination MAC.*
- `net_udp_send` (line 362) `static int net_udp_send(const unsigned char *dip, unsigned short sport,
                        u...`
- `net_dns_parse` (line 385) `static void net_dns_parse(const unsigned char *data, unsigned len)` - *net_put16(pkt + 6, 0);                    /* checksum optional for UDP kmemcpy(pkt + 8, data, len); return net_ip_send(dip, NET_PROTO_UDP, pkt, total); } struct net_dns_state { unsigned short id; unsigned char  ip[4]; int            done; }; static struct net_dns_state net_dns; /* Parse a DNS response for the first A record.*
- `net_dns_resolve` (line 421) `static int net_dns_resolve(const char *host, unsigned char ip_out[4])` - *rtype = net_get16(data + pos); rdlen = net_get16(data + pos + 8); pos += 10; if (pos + rdlen > len) return; if (rtype == 1 && rdlen == 4) { kmemcpy(net_dns.ip, data + pos, 4); net_dns.done = 1; return; } pos += rdlen; } } /* Blocking A-record lookup against NET_DNS.*
- `net_udp_send` (line 477) `net_udp_send((const unsigned char[])`
- `net_icmp_rx` (line 491) `static void net_icmp_rx(const unsigned char *ip, unsigned len)`
- `net_ping` (line 514) `static int net_ping(const unsigned char ip[4])`
- `net_sock_alloc` (line 566) `static struct net_tcp_sock *net_sock_alloc(void)`
- `net_sock_index` (line 579) `static int net_sock_index(const struct net_tcp_sock *s)`
- `net_tcp_checksum` (line 588) `static unsigned short net_tcp_checksum(const unsigned char *src, const unsigned char *dst,
      ...` - *return &net_sockets[i]; } } return 0; } static int net_sock_index(const struct net_tcp_sock *s) { int i; for (i = 0; i < NET_SOCKETS; i++) if (&net_sockets[i] == s) return i; return -1; } /* Compute the TCP checksum over a pseudo header + segment.*
- `net_udp_checksum_ok` (line 604) `static int net_udp_checksum_ok(const unsigned char *src, const unsigned char *dst,
              ...` - *const unsigned char *seg, unsigned len) { unsigned char buf[NET_TX_MAX + 12]; unsigned total = 12 + len; kmemcpy(buf, src, 4); kmemcpy(buf + 4, dst, 4); buf[8] = 0; buf[9] = NET_PROTO_TCP; net_put16(buf + 10, (unsigned short)len); kmemcpy(buf + 12, seg, len); if (total & 1) buf[total++] = 0; return net_checksum(buf, total); } /* UDP checksum over pseudo header + datagram (may be 0 = not computed).*
- `net_tcp_xmit` (line 619) `static int net_tcp_xmit(struct net_tcp_sock *s, unsigned flags,
                        const uns...`
- `net_tcp_rx` (line 651) `static void net_tcp_rx(const unsigned char *ip, unsigned len)` - *seg[21] = 0x04;                       /* len 4 net_put16(seg + 22, NET_TCP_MSS); } else { seg[12] = 0x50; } kmemcpy(seg + hlen, data, len); net_put16(seg + 16, net_tcp_checksum(net_our_ip, s->dip, s->sport, s->dport, seg, hlen + len)); if (!net_ip_send(s->dip, NET_PROTO_TCP, seg, hlen + len)) return 0; if (fresh && (flags & (0x02 | 0x08 | 0x01))) s->seq += len + ((flags & (0x02 | 0x01)) ? 1 : 0); return 1; } /* Process one received TCP segment.*
- `net_tcp_connect_into` (line 737) `static int net_tcp_connect_into(struct net_tcp_sock *s, const unsigned char ip[4],
              ...` - *} if (flags & 0x10) {                   /* ACK: peer acks our data if (s->tx_pending && (int)(ack - (s->tx_seq + s->tx_len)) >= 0) { s->tx_pending = 0; } if (s->state == NET_TCP_FIN_SENT && (int)(ack - (s->seq)) >= 0) { s->state = NET_TCP_DEAD; } } } } /* Blocking connect of an allocated socket to an IPv4 address.*
- `net_tcp_send` (line 764) `static int net_tcp_send(struct net_tcp_sock *s, const char *buf, int len)` - *unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry && s->state == NET_TCP_SYN_SENT) net_poll_rx(); if (s->state == NET_TCP_SYN_SENT) net_tcp_xmit(s, 0x02, 0, 0, 0); } if (s->state != NET_TCP_ESTABLISHED) { s->in_use = 0; s->state = NET_TCP_CLOSED; return 0; } return 1; } /* Blocking send (stop-and-wait, one outstanding segment).*
- `net_tcp_recv` (line 790) `static int net_tcp_recv(struct net_tcp_sock *s, char *buf, int len)` - *net_time_ms() < deadline) { unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry && s->tx_pending) net_poll_rx(); if (s->tx_pending) net_tcp_xmit(s, 0x18, s->tx_buf, chunk, 0); } if (s->tx_pending || s->state != NET_TCP_ESTABLISHED) return sent ? sent : -1; buf += chunk; len -= (int)chunk; sent += (int)chunk; } return sent; } /* Blocking receive; 0 = EOF (FIN).*
- `net_tcp_close` (line 827) `static void net_tcp_close(struct net_tcp_sock *s)`
- `net_rx_handle_frame` (line 847) `static void net_rx_handle_frame(const unsigned char *frame, unsigned len)` - *================================================================ Receive path: NIC -> ethernet -> ARP/IP -> demux * ================================================================*
- `net_poll_rx` (line 916) `void net_poll_rx(void)`
- `net_open` (line 956) `int net_open(void)` - *================================================================ Public libc-style API * ================================================================*
- `net_connect` (line 962) `int net_connect(const char *host, unsigned short port)`
- `net_send` (line 971) `int net_send(int fd, const char *buf, int len)`
- `net_recv` (line 976) `int net_recv(int fd, char *buf, int len)`
- `net_recv_timeout` (line 981) `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms)`
- `net_close` (line 986) `void net_close(int fd)`
- `net_sys_socket` (line 995) `long net_sys_socket(long a1, long a2, long a3)` - *================================================================ Linux syscall ABI * ================================================================*
- `net_sys_connect` (line 1004) `long net_sys_connect(long fd, long sockaddr, long addrlen)`
- `net_sys_sendto` (line 1017) `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen)`
- `net_sys_recvfrom` (line 1027) `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen)`
- `net_sys_shutdown` (line 1037) `long net_sys_shutdown(long fd, long how)`
- `net_sys_close` (line 1044) `long net_sys_close(long fd)`
- `net_sys_poll` (line 1051) `long net_sys_poll(long fds, long nfds, long timeout_ms)`
- `net_sys_dns` (line 1082) `long net_sys_dns(long host)` - *MiniOS syscall 200: resolve a hostname, returned as a network-order * 32-bit address (like inet_addr), or -1 on failure.*
- `net_parse_ip` (line 1092) `static int net_parse_ip(const char *text, unsigned char ip[4])` - *================================================================ Shell commands * ================================================================*
- `net_cmd_status` (line 1117) `void net_cmd_status(void)`
- `net_cmd_ping` (line 1131) `void net_cmd_ping(const char *ip_text)`
- `net_cmd_dns` (line 1142) `void net_cmd_dns(const char *host)`
- `net_register_symbols` (line 1155) `void net_register_symbols(void)` - *================================================================ Init and symbol registration * ================================================================*
- `net_init` (line 1163) `void net_init(void)`

**Macros:**
- `NET_REG_CR` (line 61)
- `NET_REG_TSD0` (line 63)
- `NET_REG_TSAD0` (line 64)
- `NET_REG_RBSTART` (line 65)
- `NET_REG_CAPR` (line 66)
- `NET_REG_CBR` (line 67)
- `NET_REG_9346CR` (line 68)
- `NET_TCP_CLOSED` (line 537)
- `NET_TCP_SYN_SENT` (line 539)
- `NET_TCP_ESTABLISHED` (line 540)
- `NET_TCP_FIN_SENT` (line 541)
- `NET_TCP_DEAD` (line 542)

**Structs:**
- `net_arp_entry` (line 250)
- `net_dns_state` (line 376)
- `net_tcp_sock` (line 544)

#### `cpl.c`
**Path:** `progs/cpl.c`
**File Doc:** *Ring-3 privilege probe. Reads the CS selector at runtime and exits with*

**Functions:**
- `read_cpl` (line 6) `static long read_cpl(void)` - *Ring-3 privilege probe. Reads the CS selector at runtime and exits with the CPL it is executing at. Under the isolation contract a Linux ELF runs at ring 3, so CS is the user code selector (0x23) and the exit code is 3; a regression to ring-0 execution would report 0. Built as a * static Linux ELF like lxhello.elf and run through the syscall ABI.*
- `exit_now` (line 11) `static void exit_now(long code)`
- `_start` (line 15) `void _start(void)`

#### `fib.c`
**Path:** `progs/fib.c`

**Functions:**
- `fib` (line 1) `int fib(int n)`
- `main` (line 5) `int main(void)`

#### `freedom.c`
**Path:** `progs/freedom.c`
**File Doc:** *freedom - a headless text browser for MiniOS.*

**Functions:**
- `atoi` (line 127) `static int atoi(char *s)` - *static char f_dom[FREEDOM_DOM_BUF]; static int  f_domlen; static char f_css[FREEDOM_CSS_BUF]; static int  f_csslen; static char f_linkhost[FREEDOM_CSS_MAX][64]; static char f_linkpath[FREEDOM_CSS_MAX][128]; static int  f_linkn; static int  f_cstage; static int  f_csize; static int  f_crem; static int  f_bdone; /* Decimal string to int (the ld stub set has no atol).*
- `append` (line 140) `static int append(char *dst, int pos, char *src, int cap)` - *Append src to dst at pos; returns the new length or -1 when it does * not fit.*
- `ci_lower` (line 148) `static int ci_lower(int c)`
- `ci_starts` (line 155) `static int ci_starts(char *s, char *pre)` - *int n; n = strlen(src); if (pos + n >= cap) return -1; memcpy(dst + pos, src, n); dst[pos + n] = 0; return pos + n; } static int ci_lower(int c) { if (c >= 'A' && c <= 'Z') return c + ('a' - 'A'); return c; } /* Case-insensitive starts-with.*
- `ci_eq` (line 166) `static int ci_eq(char *a, char *b)` - *} /* Case-insensitive starts-with. static int ci_starts(char *s, char *pre) { while (*pre) { if (!*s) return 0; if (ci_lower(*s) != ci_lower(*pre)) return 0; s++; pre++; } return 1; } /* Case-insensitive equality.*
- `ci_index` (line 176) `static int ci_index(char *s, char *needle)` - *return 1; } /* Case-insensitive equality. static int ci_eq(char *a, char *b) { while (*a && *b) { if (ci_lower(*a) != ci_lower(*b)) return 0; a++; b++; } return *a == 0 && *b == 0; } /* Case-insensitive index of needle in haystack, or -1.*
- `looks_like_url` (line 185) `static int looks_like_url(char *s)` - *} return *a == 0 && *b == 0; } /* Case-insensitive index of needle in haystack, or -1. static int ci_index(char *s, char *needle) { int i; for (i = 0; s[i]; i++) { if (ci_starts(s + i, needle)) return i; } return -1; } /* Does the input look like an URL (no spaces, contains a dot)?*
- `has_scheme` (line 199) `static int has_scheme(char *s)` - *Does s begin with "<scheme>:" per RFC 3986 (ALPHA *(ALPHA/DIGIT/+/-/.) ":")? Any such prefix makes the string a scheme, * and the omnibox policy is: only http:// and https:// are executed.*
- `make_search` (line 215) `static void make_search(char *out, char *query, int cap)` - *char c; c = s[0]; if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) return 0; for (i = 1; s[i]; i++) { c = s[i]; if (c == ':') return 1; if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '+' || c == '-' || c == '.')) return 0; } return 0; } /* Encode a query for the DuckDuckGo HTML endpoint (no-JS).*
- `split_url` (line 239) `static int split_url(char *url)` - *Split an http:// or https:// URL into f_host, f_path, f_port and f_secure. Returns 0 on failure. The input buffer is never modified: the parse is index-only, so it stays valid when the compiler widens * dereferenced stores.*
- `resolve_redirect` (line 286) `static int resolve_redirect(void)` - *Recompute f_host/f_path/f_port/f_secure from the last Location value. Returns 1 when the chase may continue, 0 when it must stop * (diagnostic already printed).*
- `put_ws` (line 338) `static void put_ws(void)` - *if (l + 1 >= 128) return 0; f_path[0] = '/'; memcpy(f_path + 1, loc, l); f_path[l + 1] = 0; } else { if (last + 1 + l >= 128) return 0; memcpy(f_path + last + 1, loc, l); f_path[last + 1 + l] = 0; } } return 1; } /* --- HTML filter --------------------------------------------------*
- `put_utf` (line 350) `static void put_utf(int c)` - *Print one text byte through the UTF-8 gate. Remote pages are hostile data: bytes outside a valid UTF-8 sequence (overlong, surrogate, out of range) are replaced with '?' (FreeDom policy). * Sequence state is kept in f_utbuf/f_utlen/f_utrem.*
- `put_text` (line 400) `static void put_text(int c)` - *Print one text byte: whitespace collapses, everything else goes * through the UTF-8 gate. Dump modes suppress the page text.*
- `css_append` (line 455) `static void css_append(char *s, int n)` - *} else if (v >= 2048 && v < 65536) { put_text(224 | (v >> 12)); put_text(128 | ((v >> 6) & 63)); put_text(128 | (v & 63)); } } else { int k; put_text('&'); for (k = 0; e[k]; k++) put_text(e[k]); put_text(';'); } } /* --- dump capture helpers ------------------------------------------*
- `css_line` (line 461) `static void css_line(char *s)`
- `dom_append` (line 466) `static void dom_append(char *s, int n)`
- `dom_space` (line 472) `static void dom_space(void)`
- `dom_nl` (line 476) `static void dom_nl(void)`
- `record_attr` (line 482) `static void record_attr(void)` - *int i; for (i = 0; i < n && f_domlen < FREEDOM_DOM_BUF - 1; i++) f_dom[f_domlen++] = s[i]; } static void dom_space(void) { if (f_domlen < FREEDOM_DOM_BUF - 1) f_dom[f_domlen++] = ' '; } static void dom_nl(void) { if (f_domlen < FREEDOM_DOM_BUF - 1) f_dom[f_domlen++] = '\n'; } /* Record the finished attribute in its place.*
- `is_void_tag` (line 507) `static int is_void_tag(void)` - *f_hreflen = f_vallen < 127 ? f_vallen : 127; memcpy(f_href, f_val, f_hreflen); f_href[f_hreflen] = 0; } else if (ci_eq(f_attr, "style")) { f_stylelen = f_vallen < (FREEDOM_ATTR_MAX - 1) ? f_vallen : (FREEDOM_ATTR_MAX - 1); memcpy(f_styleattr, f_val, f_stylelen); f_styleattr[f_stylelen] = 0; } else if (ci_eq(f_attr, "rel")) { f_rel_ss = ci_index(f_val, "stylesheet") >= 0; } } /* Is tagname a void element (no closing tag, no children)?*
- `classify_tag` (line 519) `static void classify_tag(void)` - *A tag was fully collected into f_tagn (+ attributes). Decide what it * does to the stream and the dumps.*
- `body_byte` (line 604) `static void body_byte(int c)` - *} dom_nl(); if (!is_void_tag()) f_depth++; } if (ci_eq(f_tagn, "br") || ci_eq(f_tagn, "p") || ci_eq(f_tagn, "div") || ci_eq(f_tagn, "h1") || ci_eq(f_tagn, "h2") || ci_eq(f_tagn, "h3") || ci_eq(f_tagn, "h4") || ci_eq(f_tagn, "h5") || ci_eq(f_tagn, "h6") || ci_eq(f_tagn, "li") || ci_eq(f_tagn, "tr")) { if (f_mode == 0) putchar('\n'); f_ws = 1; } } /* Feed one body byte into the filter.*
- `head_line` (line 769) `static void head_line(char *line)` - *f_rel_ss = 0; return; } if (c == '&') { f_entlen = 1; f_ent[0] = 0; return; } put_text(c); } /* --- HTTP ---------------------------------------------------------- /* Classify one header line (NUL-terminated).*
- `parse_head` (line 794) `static void parse_head(void)` - *Parse the collected header block f_hdr[0..f_hlen-1] (the last four * bytes are the terminating CRLF CRLF).*
- `recv_body` (line 816) `static int recv_body(int fd, char *buf, int len)` - *f_hdr[lend] = 0; if (i == 0) { char *sp; sp = strchr(f_hdr, ' '); if (sp) f_status = atoi(sp + 1); } else if (lend > i) { head_line(f_hdr + i); } f_hdr[lend] = '\r'; i = lend + 2; } } /* Receive body bytes: TLS for f_secure, plain TCP otherwise.*
- `send_all` (line 822) `static int send_all(int fd, char *buf, int len)` - *head_line(f_hdr + i); } f_hdr[lend] = '\r'; i = lend + 2; } } /* Receive body bytes: TLS for f_secure, plain TCP otherwise. static int recv_body(int fd, char *buf, int len) { if (f_secure) return tls_recv(fd, buf, len); return recvfrom(fd, buf, len, 0, 0, 0); } /* Send the whole request: TLS for f_secure, plain TCP otherwise.*
- `fetch` (line 833) `static int fetch(char *host, char *path, int port)` - *Send one HTTP request and process the response body. Returns the status code, or 0 on transport failure. Sets f_redir when a * Location header was seen.*
- `fetch_css` (line 993) `static void fetch_css(char *host, char *path)` - *Fetch a linked stylesheet and print its raw body (through the UTF-8 * gate). No redirect chasing: the bound is one request.*
- `print_css_dump` (line 1071) `static void print_css_dump(void)` - *} continue; } f_ws = 0; put_utf(c); got++; } } close(fd); putchar('\n'); printf("freedom: %s (%d bytes)\n", host, got); } /* Print the collected CSS dump.*
- `print_dom_dump` (line 1080) `static void print_dom_dump(void)` - *putchar('\n'); printf("freedom: %s (%d bytes)\n", host, got); } /* Print the collected CSS dump. static void print_css_dump(void) { int i; puts("=== freedom css ==="); for (i = 0; i < f_csslen; i++) put_utf(f_css[i]); if (f_csslen == 0) puts("(no css)"); if (f_linkn > 0) putchar('\n'); } /* Print the collected DOM outline.*
- `main` (line 1086) `int main(int argc, char **argv)`

**Macros:**
- `FREEDOM_HOPS_MAX` (line 49)
- `FREEDOM_HDR_MAX` (line 51)
- `FREEDOM_BUF` (line 52)
- `FREEDOM_CHUNK_MAX` (line 53)
- `FREEDOM_CSS_MAX` (line 54)
- `FREEDOM_CSS_BUF` (line 55)
- `FREEDOM_DOM_BUF` (line 56)
- `FREEDOM_ATTR_MAX` (line 57)
- `FREEDOM_LINE_MAX` (line 58)

#### `ftest.c`
**Path:** `progs/ftest.c`
**File Doc:** *Exercises the kernel libc surface used by loaded .o programs: fprintf to stdout/stderr, snprintf into a buffer, and exit().*

**Functions:**
- `main` (line 9) `int main(int argc, char **argv)`

#### `hello.c`
**Path:** `progs/hello.c`
**File Doc:** *MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader*

**Functions:**
- `main` (line 3) `int main(int argc, char **argv)`

#### `http.c`
**Path:** `progs/http.c`
**File Doc:** *Minimal HTTP/1.0 GET through the Linux socket syscalls.*

**Functions:**
- `atoi` (line 18) `int atoi(char *s)` - *int socket(int domain, int type, int proto); int connect(int fd, void *addr, int addrlen); int sendto(int fd, char *buf, int len, int flags, void *to, int tolen); int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen); int shutdown(int fd, int how); int close(int fd); int net_dns_resolve(char *host); int puts(char *s); int printf(char *fmt, ...); int strlen(char *s); int putchar(int c); /* Decimal string to int (the ld stub set has no atol).*
- `main` (line 28) `int main(int argc, char **argv)`

#### `kmem.c`
**Path:** `progs/kmem.c`
**File Doc:** *Kernel-pointer rejection probe. Passes a kernel-heap address (0x2000000,*

**Functions:**
- `syscall3` (line 6) `static long syscall3(long n, long a1, long a2, long a3)` - *Kernel-pointer rejection probe. Passes a kernel-heap address (0x2000000, a supervisor page) to write(2). The hardened syscall boundary must reject it with -EFAULT; the program exits 0 when the write was refused and 1 when the kernel wrongly dereferenced a kernel pointer on its behalf. * Built as a static Linux ELF like lxhello.elf.*
- `exit_now` (line 12) `static void exit_now(long code)`
- `_start` (line 16) `void _start(void)`

#### `ldhello.c`
**Path:** `progs/ldhello.c`

**Functions:**
- `main` (line 1) `int main(void)`

#### `lxhello.c`
**Path:** `progs/lxhello.c`

**Functions:**
- `lx_syscall3` (line 10) `static long lx_syscall3(long n, long a1, long a2, long a3)` - *lxhello — a genuine Linux x86-64 ELF executable.  Built with `gcc -static -no-pie -nostdlib` so it links as ET_EXEC at 0x400000 with a hand-written _start.  It never uses libc: it reads argc/argv straight off the SysV initial stack and talks to the kernel exclusively through the `syscall` instruction.  If MiniOS runs this and prints the message, its ELF loader + Linux syscall ABI are working.*
- `lx_strlen` (line 22) `static unsigned long lx_strlen(const char *s)` - *define SYS_write 1 define SYS_exit  60*
- `lx_write` (line 28) `static void lx_write(const char *s)`
- `lx_write_int` (line 32) `static void lx_write_int(long v)`
- `lmain` (line 46) `int lmain(long argc, char **argv)` - *static void lx_write_int(long v) { char buf[24]; int i = (int)sizeof(buf); int neg = 0; buf[--i] = 0; if (v < 0) { neg = 1; v = -v; } if (v == 0) buf[--i] = '0'; while (v > 0 && i > 0) { buf[--i] = (char)('0' + v % 10); v /= 10; } if (neg && i > 0) buf[--i] = '-'; lx_write(&buf[i]); } /* Entry called by _start with the real argc/argv pulled off the stack.*

**Macros:**
- `SYS_write` (line 19)
- `SYS_exit` (line 21)

#### `test.c`
**Path:** `progs/test.c`

**Functions:**
- `add` (line 1) `int add(int a, int b)`
- `main` (line 2) `int main(void)`

#### `w1.c`
**Path:** `progs/w1.c`

**Functions:**
- `main` (line 2) `int main(void)`

#### `ramdisk_data.c`
**Path:** `ramdisk_data.c`

*No symbols extracted*

#### `tls.c`
**Path:** `tls.c`
**File Doc:** *tls.c - TLS 1.2 client sessions for MiniOS.*

**Functions:**
- `tls_fail` (line 24) `static void tls_fail(struct tls_session *s, const char *stage, const char *reason)` - *Diagnostics are `freedom: tls: <stage>: <reason>` lines (freedom is the only consumer of the TLS syscalls).  #include "tls_port.h" #include "tls.h" #ifndef TLS_TEST #include "tls_roots.h" #endif static struct tls_session *tls_sessions[TLS_FD_MAX]; /* ---- diagnostics and teardown ----*
- `tls_fd_of` (line 32) `static int tls_fd_of(const struct tls_session *s)`
- `tls_free_fd` (line 39) `void tls_free_fd(int fd)`
- `tls_aad` (line 52) `static void tls_aad(unsigned char aad[13], int type, unsigned long long seq,
                    ...` - *Build the TLS 1.2 AEAD additional data: seq(8) || type || 0303 || * TLSCompressed.length (the plaintext length, RFC 5288 section 3).*
- `tls_send_record` (line 66) `static int tls_send_record(struct tls_session *s, int type,
                           const unsi...` - *Send one record: header || nonce_explicit(8) || ciphertext || tag. The nonce_explicit is the sequence number (RFC 5288 allows it and * OpenSSL uses it); the nonce is salt || nonce_explicit.*
- `tls_send_raw_record` (line 95) `static int tls_send_raw_record(struct tls_session *s, int type,
                               co...` - *for (i = 0; i < 8; i++) buf[5 + i] = (unsigned char)(s->cli_seq >> (56 - i * 8)); TLS_MEMCPY(nonce, s->cli_salt, 4); TLS_MEMCPY(nonce + 4, buf + 5, 8); if (aes128_gcm_seal_core(s->cli_key, nonce, aad, 13, payload, (unsigned)len, buf + 5 + 8, buf + 5 + 8 + len) != 0) return -1; s->cli_seq++; if (TLS_SEND(tls_fd_of(s), (const char *)buf, total) != total) return -1; return 0; } /* Send one plaintext record (ChangeCipherSpec is never encrypted).*
- `tls_read_record` (line 114) `static int tls_read_record(struct tls_session *s, int fd, int deadline_ms)` - *Read one record: header into s->rec_hdr, payload into s->rec. Returns: 1 = record ready, 0 = clean TCP EOF, -1 = torn record or bad header, -2 = timeout. A non-positive deadline blocks forever * (application-data reads behave like plain TCP).*
- `exchange` (line 173) `* key exchange (ClientHello, ClientKeyExchange) go out in plaintext
 * records, as TLS 1.2 requir...`
- `build_client_hello` (line 190) `static int build_client_hello(struct tls_session *s, unsigned char *out)` - *const unsigned char *body, int len) { if (len < 0 || len > 1024) return -1; s->pt[0] = (unsigned char)type; s->pt[1] = (unsigned char)(len >> 16); s->pt[2] = (unsigned char)(len >> 8); s->pt[3] = (unsigned char)len; TLS_MEMCPY(s->pt + 4, body, (unsigned)len); sha256_update(&s->hs_hash, s->pt, (unsigned)(len + 4)); if (!s->keys_ready) return tls_send_raw_record(s, TLS_CT_HANDSHAKE, s->pt, len + 4); return tls_send_record(s, TLS_CT_HANDSHAKE, s->pt, len + 4); } /* ClientHello body (without the handshake header). Returns length.*
- `client_finish_flight` (line 244) `static int client_finish_flight(struct tls_session *s)` - *out[pos++] = 0x00; out[pos++] = 0x06; out[pos++] = 0x04; out[pos++] = 0x01;   /* rsa_pkcs1_sha256 out[pos++] = 0x04; out[pos++] = 0x03;   /* ecdsa_p256_sha256 out[pos++] = 0x05; out[pos++] = 0x03;   /* ecdsa_p384_sha384 { int extlen = pos - ext_start - 2; out[ext_start] = (unsigned char)(extlen >> 8); out[ext_start + 1] = (unsigned char)extlen; } } return pos; } /* Derive all keys and send ClientKeyExchange, CCS, Finished.*
- `parse_server_hello` (line 339) `static int parse_server_hello(struct tls_session *s,
                              const unsigned...` - *sha256_final(&hcopy, hash); } tls_prf(s->master, 48, "client finished", hash, 32, verify, 12); TLS_MEMCPY(finished + 4, verify, 12); if (tls_send_record(s, TLS_CT_HANDSHAKE, finished, 16) != 0) { tls_fail(s, "send", "client finished"); return -1; } /* the server Finished covers the transcript including our Finished sha256_update(&s->hs_hash, finished, 16); return 0; } /* ---- handshake message parsers ----*
- `parse_certificate` (line 369) `static int parse_certificate(struct tls_session *s,
                             const unsigned c...`
- `parse_server_key_exchange` (line 400) `static int parse_server_key_exchange(struct tls_session *s,
                                     ...`
- `tls_handshake` (line 465) `int tls_handshake(int fd, const char *host)` - *sha256(data, 64 + params_len, digest); return ecdsa_verify(0, s->leaf_pk.qx, s->leaf_pk.qy, digest, 32, m + pos, sig_len); } if (sig_alg == TLS_SIG_ECDSA_P384_SHA384) { if (s->leaf_pk.kind != 2) return -1; sha384(data, 64 + params_len, digest); return ecdsa_verify(1, s->leaf_pk.qx, s->leaf_pk.qy, digest, 48, m + pos, sig_len); } return -1; } /* ---- handshake driver ----*
- `tls_send` (line 686) `int tls_send(int fd, const char *buf, int len)` - *pre-Finished is refused tls_fail(s, "handshake", "unexpected message"); tls_sessions[fd] = 0; return -1; } } s->hs_msg_len = 0; s->hs_msg_want = 0; } } } } /* ---- application data ----*
- `tls_recv` (line 695) `int tls_recv(int fd, char *buf, int len)`
- `tls_sys_handshake` (line 772) `long tls_sys_handshake(long fd, long host)` - *ifndef TLS_TEST*
- `tls_sys_send` (line 776) `long tls_sys_send(long fd, long buf, long len)`
- `tls_sys_recv` (line 781) `long tls_sys_recv(long fd, long buf, long len)`
- `tls_rdtsc` (line 788) `static inline unsigned long long tls_rdtsc(void)` - *return tls_handshake((int)(fd - NET_FD_BASE), (const char *)host); } long tls_sys_send(long fd, long buf, long len) { if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS || !buf) return -1; return tls_send((int)(fd - NET_FD_BASE), (const char *)buf, (int)len); } long tls_sys_recv(long fd, long buf, long len) { if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS || !buf) return -1; return tls_recv((int)(fd - NET_FD_BASE), (char *)buf, (int)len); } /* ---- kernel entropy and clock ----*
- `tls_random` (line 794) `void tls_random(unsigned char *out, unsigned len)`
- `outb` (line 808) `static inline void outb(unsigned short port, unsigned char v)` - *void tls_random(unsigned char *out, unsigned len) { unsigned long long seed = tls_rdtsc() ^ ((unsigned long long)net_time_ms() << 33); unsigned i; static unsigned long long counter = 0x6D696E69544C53ULL; counter ^= seed; for (i = 0; i < len; i++) { seed = seed * 6364136223846793005ULL + 1442695040888963407ULL; out[i] = (unsigned char)((seed >> 33) ^ (counter >> (i & 7) * 8)); counter = counter * 6364136223846793005ULL + 1; } } /* The port helpers in net.c are static; these live here for the RTC.*
- `inb` (line 811) `static inline unsigned char inb(unsigned short port)`
- `cmos_read` (line 818) `static inline unsigned char cmos_read(unsigned char reg)` - *} } /* The port helpers in net.c are static; these live here for the RTC. static inline void outb(unsigned short port, unsigned char v) { __asm__ volatile("outb %0, %1" : : "a"(v), "Nd"(port)); } static inline unsigned char inb(unsigned short port) { unsigned char v; __asm__ volatile("inb %1, %0" : "=a"(v) : "Nd"(port)); return v; } /* CMOS RTC -> days since epoch. Registers are BCD.*
- `tls_now_days` (line 822) `long tls_now_days(void)`

#### `tls_crypto.c`
**Path:** `tls_crypto.c`
**File Doc:** *tls_crypto.c - the crypto behind the kernel TLS 1.2 client.*

**Functions:**
- `sha256_rotr` (line 32) `static unsigned sha256_rotr(unsigned x, unsigned n)`
- `sha256_init` (line 36) `void sha256_init(struct sha256_ctx *c)`
- `sha256_block` (line 49) `static void sha256_block(struct sha256_ctx *c, const unsigned char *p)`
- `sha256_update` (line 79) `void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len)`
- `sha256_final` (line 104) `void sha256_final(struct sha256_ctx *c, unsigned char out[32])`
- `sha256` (line 125) `void sha256(const unsigned char *data, unsigned len, unsigned char out[32])`
- `hmac_sha256` (line 134) `void hmac_sha256(const unsigned char *key, unsigned klen,
                 const unsigned char *d...` - *out[i * 4 + 1] = (unsigned char)(c->state[i] >> 16); out[i * 4 + 2] = (unsigned char)(c->state[i] >> 8); out[i * 4 + 3] = (unsigned char)(c->state[i]); } } void sha256(const unsigned char *data, unsigned len, unsigned char out[32]) { struct sha256_ctx c; sha256_init(&c); sha256_update(&c, data, len); sha256_final(&c, out); } /* ========== HMAC-SHA256 ==========*
- `p_hash` (line 164) `static void p_hash(const unsigned char *secret, unsigned secret_len,
                   const uns...` - *opad[i] = k[i] ^ 0x5c; } sha256_init(&c); sha256_update(&c, ipad, 64); sha256_update(&c, data, dlen); sha256_final(&c, inner); sha256_init(&c); sha256_update(&c, opad, 64); sha256_update(&c, inner, 32); sha256_final(&c, out); } /* ========== TLS 1.2 PRF (P_SHA256) ==========*
- `tls_prf` (line 187) `void tls_prf(const unsigned char *secret, unsigned secret_len,
             const char *label, co...`
- `aes_xtime` (line 229) `static unsigned aes_xtime(unsigned x)`
- `aes_key_expand` (line 234) `static void aes_key_expand(const unsigned char key[16], unsigned rk[44])`
- `aes_mixcol` (line 252) `static void aes_mixcol(unsigned a0, unsigned a1, unsigned a2, unsigned a3,
                      ...`
- `aes128_encrypt_block` (line 262) `void aes128_encrypt_block(const unsigned char key[16],
                          const unsigned c...`
- `gf_shift_right` (line 320) `static gf128 gf_shift_right(gf128 v)`
- `gf_mul` (line 334) `static gf128 gf_mul(gf128 z, gf128 h)` - *z = z * h, in GF(2^128), MSB-first. Branches on z bits (public: * AAD/ciphertext), never on h bits (secret).*
- `gf_put` (line 350) `static gf128 gf_put(const unsigned char *p)`
- `ghash_blocks` (line 360) `static gf128 ghash_blocks(gf128 z, gf128 h, const unsigned char *data, unsigned len)`
- `gcm_tag_core` (line 384) `static void gcm_tag_core(const unsigned char key[16],
                         const unsigned cha...` - *if (len > 0) { unsigned char pad[16]; gf128 b; TLS_MEMSET(pad, 0, 16); TLS_MEMCPY(pad, data, len); b = gf_put(pad); z.lo ^= b.lo; z.hi ^= b.hi; z = gf_mul(z, h); } return z; } /* Compute GCM tag for aad || ct (ct already ciphertext).*
- `gcm_ctr_core` (line 426) `static void gcm_ctr_core(const unsigned char key[16],
                         const unsigned cha...`
- `tls_nonce` (line 450) `static void tls_nonce(const unsigned char salt[4], unsigned long long seq,
                      ...` - *TLS_MEMCPY(blk, nonce, 12); blk[12] = (unsigned char)(ctr >> 24); blk[13] = (unsigned char)(ctr >> 16); blk[14] = (unsigned char)(ctr >> 8); blk[15] = (unsigned char)(ctr); aes128_encrypt_block(key, blk, crypt); if (take > 16) take = 16; for (i = 0; i < (int)take; i++) out[off + i] = in[off + i] ^ crypt[i]; off += take; ctr++; } } /* TLS nonce: 4-byte implicit salt || 8-byte sequence number.*
- `gcm_tag` (line 456) `static void gcm_tag(const unsigned char key[16], const unsigned char salt[4],
                   ...`
- `gcm_ctr` (line 466) `static void gcm_ctr(const unsigned char key[16], const unsigned char salt[4],
                   ...`
- `aes128_gcm_seal` (line 474) `int aes128_gcm_seal(const unsigned char key[16],
                    const unsigned char salt[4],...`
- `aes128_gcm_open` (line 486) `int aes128_gcm_open(const unsigned char key[16],
                    const unsigned char salt[4],...`
- `aes128_gcm_seal_core` (line 504) `int aes128_gcm_seal_core(const unsigned char key[16],
                         const unsigned cha...`
- `aes128_gcm_open_core` (line 515) `int aes128_gcm_open_core(const unsigned char key[16],
                         const unsigned cha...`
- `bn_zero` (line 536) `static void bn_zero(unsigned *a, int nw)` - *unsigned char want[16]; unsigned char diff = 0; int i; if (ct_len > TLS_REC_MAX) return -1; gcm_tag_core(key, nonce, aad, aad_len, ct, ct_len, want); for (i = 0; i < 16; i++) diff |= want[i] ^ tag[i]; if (diff) return -1; gcm_ctr_core(key, nonce, ct, pt, ct_len); return 0; } /* ========== Big integers (32-bit limbs, little-endian) ========== #define TLS_BN_WORDS 128   /* 4096 bits*
- `bn_is_zero` (line 541) `static int bn_is_zero(const unsigned *a, int nw)`
- `bn_cmp` (line 548) `static int bn_cmp(const unsigned *a, const unsigned *b, int nw)`
- `bn_add` (line 559) `static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw)` - *for (i = 0; i < nw; i++) v |= a[i]; return v == 0; } static int bn_cmp(const unsigned *a, const unsigned *b, int nw) { int i; for (i = nw - 1; i >= 0; i--) { if (a[i] < b[i]) return -1; if (a[i] > b[i]) return 1; } return 0; } /* r = a + b; returns carry out.*
- `bn_sub` (line 571) `static unsigned bn_sub(const unsigned *a, const unsigned *b, unsigned *r, int nw)` - */* r = a + b; returns carry out. static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw) { unsigned long long carry = 0; int i; for (i = 0; i < nw; i++) { unsigned long long t = (unsigned long long)a[i] + b[i] + carry; r[i] = (unsigned)t; carry = t >> 32; } return (unsigned)carry; } /* r = a - b; a must be >= b; returns borrow (0 = fine).*
- `bn_dbl_mod` (line 584) `static void bn_dbl_mod(const unsigned *a, const unsigned *n, const unsigned *v,
                 ...` - *r = 2a mod n, for a < n. v = 2^(32nw) mod n = 2^(32nw) - n (the * Montgomery "one"): 2a + carry means 2a - 2^(32nw) + v = 2a - n < n.*
- `bn_mont_mul` (line 596) `static void bn_mont_mul(const unsigned *a, const unsigned *b, const unsigned *n,
                ...` - *Montgomery multiplication. n is odd, n0inv = -n^(-1) mod 2^32. r = a*b*R^-1 mod n, R = 2^(32nw). * a, b < n.*
- `bn_mont_n0inv` (line 635) `static unsigned bn_mont_n0inv(unsigned n0)` - *carry = v >> 32; } s = (unsigned long long)t[nw] + carry; t[nw - 1] = (unsigned)s; t[nw] = t[nw + 1] + (unsigned)(s >> 32); } if (t[nw] || bn_cmp(t, n, nw) >= 0) { bn_sub(t, n, r, nw); } else { for (i = 0; i < nw; i++) r[i] = t[i]; } } /* -n^(-1) mod 2^32 via Newton iteration (n0 must be odd).*
- `bn_mont_r2` (line 643) `static void bn_mont_r2(const unsigned *n, const unsigned *v, int nw,
                       unsig...` - *} else { for (i = 0; i < nw; i++) r[i] = t[i]; } } /* -n^(-1) mod 2^32 via Newton iteration (n0 must be odd). static unsigned bn_mont_n0inv(unsigned n0) { unsigned inv = 1; int i; for (i = 0; i < 5; i++) inv *= 2 - n0 * inv; return 0 - inv; } /* R^2 mod n, R = 2^(32nw): 64*nw doublings from 1.*
- `bn_from_be` (line 662) `static void bn_from_be(const unsigned char *bytes, unsigned len,
                       unsigned ...`
- `bn_to_be` (line 670) `static void bn_to_be(const unsigned *a, unsigned char *out, unsigned len)`
- `mont_init` (line 676) `static void mont_init(struct mont_ctx *m, const unsigned char *p_bytes,
                      uns...`
- `mont_to` (line 688) `static void mont_to(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- `mont_from` (line 692) `static void mont_from(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- `mont_mul` (line 699) `static void mont_mul(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
- `mont_sqr` (line 704) `static void mont_sqr(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- `mont_add` (line 712) `static void mont_add(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...` - *Field add/sub over the mont modulus (in Montgomery domain). The carry of a+b is corrected with one = 2^(32nw) - n, and a - b < 0 is * p - (b - a); neither path can overflow one word.*
- `mont_sub` (line 720) `static void mont_sub(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
- `mont_inv` (line 736) `static void mont_inv(struct mont_ctx *m, const unsigned *a, unsigned *r)` - *Field inverse via Fermat: a^(p-2) mod p (a in Montgomery domain; * the result stays in Montgomery domain).*
- `ec_init` (line 847) `static void ec_init(struct ec_curve *c, const unsigned char *p,
                    const unsigne...`
- `jpt_is_inf` (line 864) `static int jpt_is_inf(const struct jpt *p, int nw)`
- `jpt_set_inf` (line 868) `static void jpt_set_inf(struct jpt *p, int nw)`
- `jpt_copy` (line 874) `static void jpt_copy(struct jpt *d, const struct jpt *s, int nw)`
- `jpt_cswap` (line 885) `static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask, int nw)` - *bn_zero(p->y, nw); bn_zero(p->z, nw); } static void jpt_copy(struct jpt *d, const struct jpt *s, int nw) { int i; for (i = 0; i < nw; i++) { d->x[i] = s->x[i]; d->y[i] = s->y[i]; d->z[i] = s->z[i]; } } /* Constant-time swap of two points on a 0/~0 mask.*
- `jpt_dbl` (line 896) `static void jpt_dbl(struct ec_curve *c, const struct jpt *p1, struct jpt *p3)` - *} /* Constant-time swap of two points on a 0/~0 mask. static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask, int nw) { int i; for (i = 0; i < nw; i++) { unsigned t; t = (a->x[i] ^ b->x[i]) & mask; a->x[i] ^= t; b->x[i] ^= t; t = (a->y[i] ^ b->y[i]) & mask; a->y[i] ^= t; b->y[i] ^= t; t = (a->z[i] ^ b->z[i]) & mask; a->z[i] ^= t; b->z[i] ^= t; } } /* P3 = 2 * P1 (a = p - 3: E = 3(A - Z1^4)).*
- `jpt_add` (line 936) `static void jpt_add(struct ec_curve *c, const struct jpt *p1, const struct jpt *p2,
             ...` - *mont_sqr(m, E, F); mont_add(m, D, D, t);          /* 2D mont_sub(m, F, t, p3->x);      /* X3 = F - 2D mont_sub(m, D, p3->x, t); mont_mul(m, E, t, t2); mont_add(m, C, C, t); mont_add(m, t, t, t); mont_add(m, t, t, t);          /* 8C mont_sub(m, t2, t, p3->y);     /* Y3 = E(D-X3) - 8C mont_mul(m, p1->y, p1->z, YZ); mont_add(m, YZ, YZ, p3->z);    /* Z3 = 2YZ } /* P3 = P1 + P2 (generic Jacobian add).*
- `jpt_scalar_mult` (line 980) `static void jpt_scalar_mult(struct ec_curve *c, const struct jpt *base,
                         ...` - *Constant-iteration scalar multiplication: the classic ladder. * Fixed iteration count, no table lookups indexed by secret bits.*
- `jpt_to_affine` (line 1007) `static void jpt_to_affine(struct ec_curve *c, const struct jpt *p,
                          unsi...` - *Affine from Jacobian: x = X/Z^2, y = Y/Z^3. Bytes out are big-endian. * y_out may be NULL when only the x coordinate is wanted.*
- `jpt_from_affine` (line 1032) `static int jpt_from_affine(struct ec_curve *c, const unsigned char *x_bytes,
                    ...` - *Affine from bytes with on-curve validation. Returns 0 when the point * is valid and not the point at infinity.*
- `ec_curve_by_id` (line 1075) `static struct ec_curve *ec_curve_by_id(int curve)`
- `ec_boot` (line 1079) `static void ec_boot(void)`
- `p256_scalar_mult` (line 1087) `int p256_scalar_mult(const unsigned char scalar[32],
                     const unsigned char qx[...`
- `p384_scalar_mult` (line 1100) `int p384_scalar_mult(const unsigned char scalar[48],
                     const unsigned char qx[...`
- `p256_ecdh` (line 1113) `int p256_ecdh(const unsigned char priv[32],
              const unsigned char peer_x[32], const u...`
- `der_parse_sig` (line 1128) `static int der_parse_sig(const unsigned char *sig, unsigned sig_len,
                         con...` - *int p256_ecdh(const unsigned char priv[32], const unsigned char peer_x[32], const unsigned char peer_y[32], unsigned char z[32]) { struct ec_curve *c; struct jpt base, out; ec_boot(); c = &ec_p256; if (jpt_from_affine(c, peer_x, peer_y, &base) != 0) return -1; jpt_scalar_mult(c, &base, priv, &out); jpt_to_affine(c, &out, z, 0); return 0; } /* ========== ECDSA verify ==========*
- `ecdsa_verify` (line 1162) `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[],
           ...`
- `rsa_verify_digestinfo` (line 1261) `static int rsa_verify_digestinfo(const unsigned char *em, unsigned em_len,
                      ...` - *EMSA-PKCS1-v1_5 DigestInfo check for an arbitrary hash: the encoding is 00 01 FF.. 00 <prefix><digest>. Constant-time: every byte of the * encoding contributes to the diff.*
- `rsa_pkcs1_verify_raw` (line 1285) `static int rsa_pkcs1_verify_raw(const unsigned char *n, unsigned n_len,
                         ...` - *diff |= em[i] ^ 0xff; } if (i >= em_len) return -1;         /* no separator if (i < 10) return -1;              /* padding too short (RFC 8017) i++; if (em_len - i != prefix_len + digest_len) return -1; for (i = 0; i < prefix_len; i++) diff |= em[em_len - prefix_len - digest_len + i] ^ prefix[i]; for (i = 0; i < digest_len; i++) diff |= em[em_len - digest_len + i] ^ digest[i]; return diff ? -1 : 0; } /* Shared RSA PKCS#1 v1.5 core: m^e mod n, EMSA-PKCS1-v1_5 in em.*
- `rsa_pkcs1_verify_sha256` (line 1325) `int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len,
                            c...`
- `rsa_pkcs1_verify_sha384` (line 1339) `int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len,
                            c...`
- `sha384_rotr` (line 1385) `static unsigned long long sha384_rotr(unsigned long long x, unsigned n)`
- `sha384_raw` (line 1389) `static void sha384_raw(const unsigned char *data, unsigned len,
                       unsigned c...`
- `sha384` (line 1505) `void sha384(const unsigned char *data, unsigned len, unsigned char out[48])`
- `p256_point_valid` (line 1511) `int p256_point_valid(const unsigned char x[32], const unsigned char y[32])` - *out[i * 8 + 2] = (unsigned char)(state[i] >> 40); out[i * 8 + 3] = (unsigned char)(state[i] >> 32); out[i * 8 + 4] = (unsigned char)(state[i] >> 24); out[i * 8 + 5] = (unsigned char)(state[i] >> 16); out[i * 8 + 6] = (unsigned char)(state[i] >> 8); out[i * 8 + 7] = (unsigned char)state[i]; } } void sha384(const unsigned char *data, unsigned len, unsigned char out[48]) { sha384_raw(data, len, out); } /* ========== P-256 helpers for the handshake ==========*
- `p256_pub` (line 1519) `int p256_pub(const unsigned char priv[32],
             unsigned char x[32], unsigned char y[32])`
- `p256_scalar_valid` (line 1538) `int p256_scalar_valid(const unsigned char scalar[32])`

**Macros:**
- `TLS_BN_WORDS` (line 534)

**Structs:**
- `mont_ctx` (line 655)
- `ec_curve` (line 838)
- `jpt` (line 859) - *Jacobian point: three coordinates in Montgomery domain, nw words each. * The point at infinity has Z = 0.*

#### `tls_test.c`
**Path:** `tls_test.c`
**File Doc:** *tls_test.c - host-side tests for the kernel TLS stack.*

**Functions:**
- `tls_test_send` (line 25) `int tls_test_send(int fd, const char *buf, int len)` - *#include <stdio.h> #include <stdlib.h> #include <string.h> #include <unistd.h> #include <sys/socket.h> #include <sys/select.h> #include <netinet/in.h> #include <arpa/inet.h> #include "tls_port.h" #include "tls.h" #include "tls_test_roots.h" /* ---- transport: the TLS stack talks to POSIX sockets here ----*
- `tls_test_recv` (line 35) `int tls_test_recv(int fd, char *buf, int len)`
- `tls_test_recv_timeout` (line 40) `int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms)`
- `tls_test_close` (line 53) `void tls_test_close(int fd)`
- `hexdigit` (line 66) `static int hexdigit(int c)`
- `unhex` (line 73) `static void unhex(const char *hex, unsigned char *out, int n)`
- `bytes_eq` (line 79) `static int bytes_eq(const unsigned char *a, const unsigned char *b, int n)`
- `test_sha256` (line 87) `static void test_sha256(void)` - *static void unhex(const char *hex, unsigned char *out, int n) { int i; for (i = 0; i < n; i++) out[i] = (unsigned char)((hexdigit(hex[2 * i]) << 4) | hexdigit(hex[2 * i + 1])); } static int bytes_eq(const unsigned char *a, const unsigned char *b, int n) { int i, d = 0; for (i = 0; i < n; i++) d |= a[i] ^ b[i]; return d == 0; } /* ---- fixed vectors ----*
- `test_sha384` (line 102) `static void test_sha384(void)`
- `test_gcm` (line 113) `static void test_gcm(void)`
- `test_p256` (line 153) `static void test_p256(void)`
- `test_rsa_ecdsa_vectors` (line 199) `static void test_rsa_ecdsa_vectors(void)`
- `tcp_connect` (line 248) `static int tcp_connect(int port)` - *ok = ecdsa_verify(0, test_ec_x, test_ec_y, digest, 32, test_ec_sig, sizeof(test_ec_sig)) == 0; CHECK("ecdsa p256 sha256 verify", ok); { unsigned char bad[256]; memcpy(bad, test_ec_sig, sizeof(test_ec_sig)); bad[2] ^= 0x01; ok = ecdsa_verify(0, test_ec_x, test_ec_y, digest, 32, bad, sizeof(test_ec_sig)) == -1; CHECK("ecdsa rejects tampered sig", ok); } } /* ---- network scenarios ----*
- `http_over_tls` (line 265) `static int http_over_tls(int port, const char *host)` - *int fd = socket(AF_INET, SOCK_STREAM, 0); if (fd < 0) return -1; memset(&sa, 0, sizeof(sa)); sa.sin_family = AF_INET; sa.sin_port = htons((unsigned short)port); sa.sin_addr.s_addr = htonl(0x7f000001UL); if (connect(fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) { close(fd); return -1; } return fd; } /* Full handshake + one HTTP round trip. Returns 0 on success.*
- `scenario_good` (line 289) `static int scenario_good(int port)`
- `scenario_wild_good` (line 295) `static int scenario_wild_good(int port)` - *total += n; printed = 1; } tls_free_fd(fd); close(fd); if (!printed) return -1; return 0; } static int scenario_good(int port) { return http_over_tls(port, "localhost") == 0 ? 0 : -1; } /* "*.example.com" matches exactly one label.*
- `scenario_wild_root` (line 298) `static int scenario_wild_root(int port)`
- `scenario_wild_deep` (line 308) `static int scenario_wild_deep(int port)`
- `scenario_bad_host` (line 318) `static int scenario_bad_host(int port)`
- `scenario_bad_ca` (line 328) `static int scenario_bad_ca(int port)`
- `scenario_expired` (line 338) `static int scenario_expired(int port)`
- `main` (line 348) `int main(int argc, char **argv)`

**Macros:**
- `CHECK` (line 61)

#### `tls_x509.c`
**Path:** `tls_x509.c`
**File Doc:** *tls_x509.c - minimal X.509 DER parsing and chain verification.*

**Functions:**
- `oid_eq` (line 35) `static int oid_eq(const unsigned char *bytes, unsigned len,
                  const unsigned char...`
- `der_next` (line 51) `static int der_next(const unsigned char *p, unsigned limit, unsigned *pos,
                    st...` - *Parse the TLV at p[pos]; advances pos to the first byte after it. * Returns 0 on success, -1 on any bound violation.*
- `der_container` (line 82) `static int der_container(const unsigned char *p, unsigned limit, unsigned *pos,
                 ...` - *len = (len << 8) | p[(*pos)++]; } } else { len = p[(*pos)++]; } if (len > limit - *pos) return -1; out->val = p + *pos; out->len = len; out->tag = tag; pos += len; return 0; } /* A constructed SEQUENCE/SET whose content must parse as children.*
- `days_from_civil` (line 93) `static long days_from_civil(int y, int m, int d)` - *} /* A constructed SEQUENCE/SET whose content must parse as children. static int der_container(const unsigned char *p, unsigned limit, unsigned *pos, const unsigned char **val, unsigned *len) { struct der_tlv t; if (der_next(p, limit, pos, &t) != 0) return -1; if (t.tag != 0x30) return -1; val = t.val; len = t.len; return 0; } /* ---- Time ----*
- `der_time_to_days` (line 106) `static long der_time_to_days(const struct der_tlv *t)` - */* ---- Time ---- static long days_from_civil(int y, int m, int d) { long era, doe, yoe; int doy; y -= m <= 2 ? 1 : 0; era = (y >= 0 ? y : y - 399) / 400; yoe = y - (int)era * 400; doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; doe = (long)yoe * 365 + yoe / 4 - yoe / 100 + doy; return era * 146097 + doe - 719468; } /* UTCTime / GeneralizedTime "....Z" -> days since epoch, or -1.*
- `name_find_cn` (line 135) `static int name_find_cn(const unsigned char *p, unsigned limit,
                        struct x5...` - *} if (mon < 1 || mon > 12 || day < 1 || day > 31 || year < 1970 || year > 2100) return -1; return days_from_civil(year, mon, day); } /* ---- Name / extensions ---- struct x509_name { unsigned char cn[64]; unsigned cn_len; }; /* Find the first CN in an RDNSequence. Returns 0 when found.*
- `san_add` (line 177) `static void san_add(struct x509_sans *out, const unsigned char *v, unsigned len)`
- `san_parse` (line 186) `static void san_parse(const unsigned char *p, unsigned limit,
                      struct x509_s...` - *struct x509_sans { unsigned char dns[TLS_SAN_MAX][64]; unsigned      len[TLS_SAN_MAX]; int           count; }; static void san_add(struct x509_sans *out, const unsigned char *v, unsigned len) { if (out->count >= TLS_SAN_MAX || len >= 64) return; TLS_MEMCPY(out->dns[out->count], v, len); out->len[out->count] = len; out->count++; } /* Walk the SAN extension (2.5.29.17) OCTET STRING body.*
- `spki_parse` (line 203) `static int spki_parse(const unsigned char *p, unsigned limit,
                      struct tls_pu...` - *unsigned seq_len, pos = 0; out->count = 0; if (der_container(p, limit, &pos, &seq, &seq_len) != 0) return; pos = 0; while (pos < seq_len) { struct der_tlv t; if (der_next(seq, seq_len, &pos, &t) != 0) return; if (t.tag == 0x82) san_add(out, t.val, t.len); /* dNSName } } /* ---- Public key ---- /* SPKI SEQUENCE content: { alg SEQUENCE { OID, params }, BIT STRING }.*
- `cert_parse` (line 278) `static int cert_parse(const unsigned char *der, unsigned len,
                      struct x509_c...`
- `ascii_lower` (line 391) `static int ascii_lower(int c)` - *unsigned bpos = e2pos; if (der_next(ext, ext_len, &bpos, &body) != 0) break; if (oid_eq(eoid, eoid_len, oid_san, sizeof(oid_san))) san_parse(body.val, body.len, &out->sans), out->has_san = 1; } } } } } return 0; } /* ---- Hostname matching ----*
- `host_match_exact` (line 397) `static int host_match_exact(const char *host, const unsigned char *name,
                        ...` - *} } } } return 0; } /* ---- Hostname matching ---- static int ascii_lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; } /* Exact match, ASCII case-insensitive.*
- `host_match_wildcard` (line 410) `static int host_match_wildcard(const char *host, const unsigned char *name,
                     ...` - *Wildcard: "*.example.com" matches exactly one label ("a.example.com", * never "a.b.example.com" nor "example.com").*
- `host_matches` (line 430) `static int host_matches(const char *host, const struct x509_cert *leaf)`
- `tls_x509_parse_pubkey` (line 451) `int tls_x509_parse_pubkey(const unsigned char *der, unsigned len,
                          struc...` - *return 1; } return 0;   /* SAN present and nothing matched: fail closed } if (leaf->subject.cn_len) { return host_match_exact(host, leaf->subject.cn, leaf->subject.cn_len) || host_match_wildcard(host, leaf->subject.cn, leaf->subject.cn_len); } return 0; } /* ---- Signature verification ---- /* ========== Public API ==========*
- `pubkey_equal` (line 468) `static int pubkey_equal(const struct tls_pubkey *a, const struct tls_pubkey *b)` - *Trust anchors are matched by public key, not by self-signature: a presented root is often a cross-signed copy (signed by a legacy root, e.g. the SSL.com 2022 roots are signed by Comodo AAA), so checking its signature against its own key would reject a perfectly valid anchor. Key equality is safe because every link above the top is still signature-verified: an attacker cannot present a top cert carrying an embedded root's public key unless the chain below it was signed with * that root's private key.*
- `cert_verify_signature` (line 479) `static int cert_verify_signature(const struct x509_cert *cert,
                                 c...` - *signature-verified: an attacker cannot present a top cert carrying an embedded root's public key unless the chain below it was signed with * that root's private key. static int pubkey_equal(const struct tls_pubkey *a, const struct tls_pubkey *b) { if (a->kind != b->kind) return 0; if (a->kind == 0) return a->n_len == b->n_len && a->e_len == b->e_len && TLS_MEMCMP(a->n, b->n, a->n_len) == 0 && TLS_MEMCMP(a->e, b->e, a->e_len) == 0; return TLS_MEMCMP(a->qx, b->qx, 48) == 0 && TLS_MEMCMP(a->qy, b->qy, 48) == 0; } /* Verify one certificate's signature with an issuer public key.*
- `tls_x509_verify_chain` (line 520) `int tls_x509_verify_chain(const unsigned char *chain, unsigned chain_len,
                       ...`

**Macros:**
- `TLS_SAN_MAX` (line 170)

**Structs:**
- `der_tlv` (line 43)
- `x509_name` (line 129)
- `x509_sans` (line 172)
- `x509_cert` (line 265)

### H (7 files)

#### `bootdefs.h`
**Path:** `bootdefs.h`
**File Doc:** *bootdefs.h - centralized configuration for the MiniOS two-stage boot path.*

**Imported by:** `kernel.c`

**Macros:**
- `BOOTDEFS_H` (line 29)
- `SECTOR_BYTES` (line 30)
- `SECTOR_PARAGRAPH_SHIFT` (line 32)
- `SECTOR_DWORD_SHIFT` (line 33)
- `BOOT_SIGNATURE` (line 34)
- `BOOT_SIGNATURE_BYTES` (line 36)
- `BOOT_SEG_NULL` (line 37)
- `BOOT_STACK_TOP` (line 39)
- `BOOT_DAP_ADDR` (line 40)
- `BOOT_DAP_SIZE` (line 42)
- `BOOT_DAP_OFF_COUNT` (line 43)
- `BOOT_DAP_OFF_OFFSET` (line 44)
- `BOOT_DAP_OFF_SEGMENT` (line 45)
- `BOOT_DAP_OFF_LBA_LO` (line 46)
- `BOOT_DAP_OFF_LBA_HI` (line 47)
- `BOOT_DRIVE_ADDR` (line 48)
- `BOOT_STAGE2_LBA` (line 49)
- `BOOT_STAGE2_SECTORS` (line 51)
- `BOOT_STAGE2_ADDR` (line 52)
- `BOOT_STAGE2_SEG` (line 53)
- `BOOT_KERNEL_LBA` (line 54)
- `BOOT_KERNEL_BUF_ADDR` (line 56)
- `BOOT_KERNEL_BUF_SEG` (line 57)
- `BOOT_KERNEL_PHYS_ADDR` (line 58)
- `BOOT_CHUNK_SECTORS` (line 59)
- `BOOT_BIOS_MAX_SECTORS` (line 61)
- `BOOT_PM_STACK_TOP` (line 62)
- `BIOS_DISK_INT` (line 64)
- `BIOS_DISK_EXT_CHECK` (line 66)
- `BIOS_DISK_EXT_REQ_MAGIC` (line 67)
- `BIOS_DISK_EXT_ACK_MAGIC` (line 68)
- `BIOS_DISK_EXT_PACKET_BIT` (line 69)
- `BIOS_DISK_READ_EXT` (line 70)
- `BIOS_VIDEO_INT` (line 71)
- `BIOS_VIDEO_TTY_WRITE` (line 73)
- `BIOS_VIDEO_TTY_ATTR` (line 74)
- `A20_CONTROL_PORT` (line 75)
- `A20_ENABLE_BIT` (line 77)
- `A20_RESET_CLEAR_MASK` (line 78)
- `CR0_PE` (line 79)
- `CR0_PE_CLEAR_MASK` (line 81)
- `CR0_PG` (line 82)
- `CR4_PAE` (line 83)
- `MSR_EFER` (line 84)
- `EFER_LME` (line 86)
- `GDT32_CODE32_SEL` (line 87)
- `GDT32_DATA32_SEL` (line 89)
- `GDT32_CODE16_SEL` (line 90)
- `GDT32_DATA16_SEL` (line 91)
- `GDT32_DESC_NULL` (line 92)
- `GDT32_DESC_CODE32` (line 94)
- `GDT32_DESC_DATA32` (line 95)
- `GDT32_DESC_CODE16` (line 96)
- `GDT32_DESC_DATA16` (line 97)
- `GDT64_ADDR` (line 98)
- `GDT64_BYTES` (line 100)
- `GDT64_CODE_SEL` (line 101)
- `GDT64_DATA_SEL` (line 102)
- `GDT64_USER_DATA_SEL` (line 103)
- `GDT64_USER_CODE_SEL` (line 104)
- `GDT64_DESC_NULL` (line 105)
- `GDT64_DESC_CODE` (line 106)
- `GDT64_DESC_DATA` (line 107)
- `GDT64_DESC_UDATA` (line 108)
- `GDT64_DESC_UCODE` (line 109)
- `PT_PML4_ADDR` (line 110)
- `PT_PDPT_ADDR` (line 112)
- `PT_PD_ADDR` (line 113)
- `PT_ZERO_DWORDS` (line 114)
- `PT_FLAGS_PRESENT_RW` (line 115)
- `PT_FLAGS_PRESENT_RW_PS` (line 116)
- `PT_FLAGS_USER` (line 117)
- `PT_PD_ENTRIES` (line 118)
- `PT_PD_ENTRY_BYTES` (line 119)
- `PT_PD_PAGE_BYTES` (line 120)
- `PT_PD_INDEX_SHIFT` (line 121)

#### `kernel.h`
**Path:** `kernel.h`
**File Doc:** *ifndef KERNEL_H define KERNEL_H  ========== VGA text mode ==========*

**Imported by:** `kernel.c`, `net.c`, `tls_port.h`

**Macros:**
- `KERNEL_H` (line 2)
- `VGA_BASE` (line 5)
- `VGA_COLS` (line 6)
- `VGA_ROWS` (line 7)
- `KEY_BACKSPACE` (line 24)
- `KEY_ENTER` (line 25)
- `KEY_LSHIFT` (line 26)
- `KEY_RSHIFT` (line 27)
- `KEY_CAPS` (line 28)
- `KEY_E0` (line 29)
- `KEY_UP` (line 30)
- `KEY_DOWN` (line 31)
- `KEY_ESC` (line 32)
- `KEY_CSI` (line 33)
- `KEY_ARR_UP` (line 34)
- `KEY_ARR_DOWN` (line 35)
- `RAMDISK_MAX_FILES` (line 48)
- `RAMDISK_FNAME_LEN` (line 49)
- `EOF` (line 68)

#### `net.h`
**Path:** `net.h`
**File Doc:** *ifndef NET_H define NET_H  ========== Fixed slirp configuration (QEMU -nic user) ==========*

**Imported by:** `kernel.c`, `net.c`, `tls_port.h`

**Macros:**
- `NET_H` (line 2)
- `NET_IP_ADDR` (line 5)
- `NET_NETMASK` (line 6)
- `NET_GATEWAY` (line 7)
- `NET_DNS` (line 8)
- `NET_PCI_VENDOR` (line 11)
- `NET_PCI_DEVICE` (line 12)
- `NET_RX_BUF_LEN` (line 18)
- `NET_RX_ALIGN` (line 19)
- `NET_RCR` (line 22)
- `NET_MAX_FRAME` (line 23)
- `NET_TX_SLOTS` (line 24)
- `NET_ETH_ALEN` (line 27)
- `NET_ETHERTYPE_IP` (line 28)
- `NET_ETHERTYPE_ARP` (line 29)
- `NET_PROTO_ICMP` (line 32)
- `NET_PROTO_TCP` (line 33)
- `NET_PROTO_UDP` (line 34)
- `NET_ARP_CACHE` (line 37)
- `NET_ARP_REQUEST` (line 38)
- `NET_ARP_REPLY` (line 39)
- `NET_TCP_MSS` (line 42)
- `NET_TCP_WINDOW` (line 43)
- `NET_SOCK_RX_BUF` (line 46)
- `NET_RX_RING_SIZE` (line 47)
- `NET_SOCKETS` (line 48)
- `NET_DNS_PORT` (line 49)
- `NET_EPHEMERAL_MIN` (line 50)
- `NET_DNS_TRIES` (line 51)
- `NET_DNS_TMO_MS` (line 52)
- `NET_CONNECT_TMO_S` (line 53)
- `NET_RETRY_MS` (line 54)
- `NET_TX_MAX` (line 55)
- `NET_FD_BASE` (line 58)

#### `tls.h`
**Path:** `tls.h`
**File Doc:** *ifndef TLS_H define TLS_H  ========== TLS 1.2 client (RFC 5246) ==========*

**Imported by:** `kernel.c`, `tls.c`, `tls_crypto.c`, `tls_test.c`, `tls_x509.c`

**Macros:**
- `TLS_H` (line 2)
- `TLS_CT_CCS` (line 7)
- `TLS_CT_ALERT` (line 8)
- `TLS_CT_HANDSHAKE` (line 9)
- `TLS_CT_APPDATA` (line 10)
- `TLS_REC_HEADER` (line 11)
- `TLS_REC_MAX` (line 12)
- `TLS_MSG_MAX` (line 13)
- `TLS_PLAIN_MAX` (line 14)
- `TLS_VERSION_TLS12` (line 15)
- `TLS_VERSION_TLS10` (line 16)
- `TLS_HS_CLIENT_HELLO` (line 19)
- `TLS_HS_SERVER_HELLO` (line 20)
- `TLS_HS_CERTIFICATE` (line 21)
- `TLS_HS_SERVER_KEY_EXCHANGE` (line 22)
- `TLS_HS_SERVER_HELLO_DONE` (line 23)
- `TLS_HS_CLIENT_KEY_EXCHANGE` (line 24)
- `TLS_HS_FINISHED` (line 25)
- `TLS_CSUITE_ECDHE_RSA_AES128GCM` (line 28)
- `TLS_CSUITE_ECDHE_ECDSA_AES128GCM` (line 29)
- `TLS_SIG_RSA_PKCS1_SHA256` (line 32)
- `TLS_SIG_ECDSA_P256_SHA256` (line 33)
- `TLS_SIG_ECDSA_P384_SHA384` (line 34)
- `TLS_GROUP_SECP256R1` (line 37)
- `TLS_EXT_SERVER_NAME` (line 40)
- `TLS_EXT_SUPPORTED_GROUPS` (line 41)
- `TLS_EXT_EC_POINT_FORMATS` (line 42)
- `TLS_EXT_SIGNATURE_ALGS` (line 43)
- `TLS_ALERT_LEVEL_WARNING` (line 46)
- `TLS_ALERT_LEVEL_FATAL` (line 47)
- `TLS_HS_TIMEOUT_MS` (line 50)
- `TLS_READ_TIMEOUT_MS` (line 51)
- `TLS_HOST_MAX` (line 54)
- `TLS_CHAIN_MAX` (line 57)
- `TLS_CERT_MAX` (line 58)
- `TLS_BN_4096_WORDS` (line 62)
- `TLS_BN_384_WORDS` (line 63)
- `TLS_ROOT_COUNT` (line 68)

**Structs:**
- `tls_root` (line 70)
- `sha256_ctx` (line 79)
- `tls_pubkey` (line 85)
- `tls_session` (line 95)

#### `tls_port.h`
**Path:** `tls_port.h`
**File Doc:** *ifndef TLS_PORT_H define TLS_PORT_H  Portability shim between the MiniOS kernel and the host-side test*

**Imported by:** `tls.c`, `tls_crypto.c`, `tls_test.c`, `tls_x509.c`

**Functions:**
- `tls_now_days` (line 39) `static inline long tls_now_days(void)` - *define TLS_SEND           tls_test_send define TLS_RECV           tls_test_recv define TLS_RECV_TIMEOUT   tls_test_recv_timeout define TLS_CLOSE          tls_test_close*
- `tls_random` (line 43) `static inline void tls_random(unsigned char *out, unsigned len)`

**Macros:**
- `TLS_PORT_H` (line 2)
- `TLS_FD_MAX` (line 17)
- `TLS_PRINTF` (line 19)
- `TLS_MALLOC` (line 21)
- `TLS_FREE` (line 22)
- `TLS_MEMCPY` (line 23)
- `TLS_MEMSET` (line 24)
- `TLS_MEMCMP` (line 25)
- `TLS_STRLEN` (line 26)
- `TLS_SEND` (line 34)
- `TLS_RECV` (line 36)
- `TLS_RECV_TIMEOUT` (line 37)
- `TLS_CLOSE` (line 38)
- `TLS_PRINTF` (line 62)
- `TLS_MALLOC` (line 64)
- `TLS_FREE` (line 65)
- `TLS_MEMCPY` (line 66)
- `TLS_MEMSET` (line 67)
- `TLS_MEMCMP` (line 68)
- `TLS_STRLEN` (line 69)
- `TLS_SEND` (line 70)
- `TLS_RECV` (line 72)
- `TLS_RECV_TIMEOUT` (line 73)
- `TLS_CLOSE` (line 74)
- `TLS_FD_MAX` (line 75)

#### `tls_roots.h`
**Path:** `tls_roots.h`
**File Doc:** *tls_roots.h - embedded CA roots (DER), generated by mkroots.sh.*

**Imported by:** `tls.c`

*No symbols extracted*

#### `tls_test_roots.h`
**Path:** `tls_test_roots.h`
**File Doc:** *tls_test_roots.h - generated by tls_test.py; never built into the kernel. The test root replaces the production table.*

**Imported by:** `tls_test.c`

*No symbols extracted*

### PY (10 files)

#### `app.py`
**Path:** `app.py`
**File Doc:** *_*_ coding: utf8 _*_*

*No symbols extracted*

#### `__init__.py`
**Path:** `mcp/__init__.py`

*No symbols extracted*

#### `mcp_dbg_driver.py`
**Path:** `mcp/mcp_dbg_driver.py`

**Classes:**
- `Client` (line 14) `class Client`

**Methods:**
- `main` (line 62) `def main()`
- `__init__` (line 15) `def __init__(self)`
- `request` (line 26) `def request(self, method, params)`
- `tool` (line 44) `def tool(self, name, params)`
- `close` (line 52) `def close(self)`

#### `mcp_dogfood.py`
**Path:** `mcp/mcp_dogfood.py`

**Classes:**
- `Client` (line 18) `class Client`

**Methods:**
- `main` (line 76) `def main()`
- `__init__` (line 19) `def __init__(self, addons_dir)`
- `request` (line 38) `def request(self, method, params)`
- `tool` (line 56) `def tool(self, name, params)`
- `close` (line 66) `def close(self)`

#### `minios_addons.py`
**Path:** `mcp/minios_addons.py`

**Classes:**
- `AddonError` (line 42) `class AddonError(Exception)` - *Expected marketplace failure, reported to the client as isError.*
- `AddonState` (line 332) `class AddonState` - *Host-side record of installed addons (system temp dir).*

**Methods:**
- `_clean` (line 48) `def _clean(s)`
- `_unquote` (line 52) `def _unquote(v)`
- `parse_addon_yaml` (line 59) `def parse_addon_yaml(text)` - *Parse the strict YAML subset. Returns the addon dict.

Grammar: flat `key: value` lines; `install:` opens an indented block
with `repo_url:`, a `files:` list of `- src:`/`dst:` pairs, and
`build:` / `verify:` lists of `- ...` command lines (`verify` items
may carry a nested `exit_code:`). Everything else is a parse error
with its line number.*
- `validate_addon` (line 189) `def validate_addon(addon, source)` - *Check bounds and character sets. Raises AddonError.*
- `validate_addon_path` (line 250) `def validate_addon_path(path)` - *dst paths live on the ramdisk: relative, no '..', bounded charset.*
- `validate_shell_line` (line 264) `def validate_shell_line(line)` - *Build/verify lines are single printable-ASCII shell commands.*
- `load_addons_dir` (line 278) `def load_addons_dir(addons_dir)` - *Load every addon yaml; each entry is a dict or an error string.*
- `split_for_editor` (line 302) `def split_for_editor(text)` - *Split a source into editor-sized chunks. Raises AddonError.*
- `exit_code_of` (line 327) `def exit_code_of(text)`
- `install_addon` (line 356) `def install_addon(session, addon, cfg)` - *Install one validated addon into the booted MiniOS session.

Failure at any step raises AddonError; upload parts are removed and
nothing is recorded, so a half-installed package is never reported.*
- `fail` (line 69) `def fail(lineno, why)`
- `__init__` (line 335) `def __init__(self, path)`
- `load` (line 338) `def load(self)`
- `save` (line 348) `def save(self, addons)`

#### `minios_mcp.py`
**Path:** `mcp/minios_mcp.py`

**Classes:**
- `ToolError` (line 128) `class ToolError(Exception)` - *Expected tool failure, reported to the client as isError.*
- `RPCError` (line 134) `class RPCError(Exception)` - *JSON-RPC level failure carrying a standard error code.*
- `LogBuffer` (line 143) `class LogBuffer` - *Bounded console log with absolute byte positions and waits.*
- `MiniOSSession` (line 199) `class MiniOSSession` - *One QEMU child, one pty, one console log, one consume cursor.*
- `MCPServer` (line 605) `class MCPServer` - *JSON-RPC dispatch loop over stdio.*

**Functions:**
- `env_config` (line 68) `def env_config()` - *Resolve the configuration: defaults overridden by the environment.*
- `clamp_timeout` (line 86) `def clamp_timeout(ms)` - *Clamp a requested wait to the bounded timeout range.*
- `validate_path` (line 99) `def validate_path(name)` - *Reject file names the ramdisk or the shell would mishandle.*
- `validate_content` (line 115) `def validate_content(text)` - *Reject lines the kernel readline cannot carry (printable ASCII).*

**Methods:**
- `subprocess_launch` (line 493) `def subprocess_launch(cfg, slave_fd)`
- `main` (line 743) `def main()`
- `__init__` (line 137) `def __init__(self, code, message)`
- `__init__` (line 146) `def __init__(self, cap)`
- `append` (line 152) `def append(self, data)`
- `bytes_from` (line 160) `def bytes_from(self, pos)`
- `text_from` (line 165) `def text_from(self, pos, end)`
- `find` (line 172) `def find(self, marker, start)`
- `wait_for` (line 176) `def wait_for(self, marker, start, timeout_ms)` - *Block until marker appears at or after start; return position.*
- `_find_locked` (line 189) `def _find_locked(self, marker, start)`
- `__init__` (line 202) `def __init__(self, cfg)`
- `booted` (line 213) `def booted(self)`
- `status` (line 216) `def status(self)`
- `_reap_stale` (line 225) `def _reap_stale(self)`
- `_drop_pidfile` (line 261) `def _drop_pidfile(self)`
- `boot` (line 267) `def boot(self, timeout_ms)`
- `_read_loop` (line 302) `def _read_loop(self)`
- `_close_pty` (line 312) `def _close_pty(self)`
- `_write_line` (line 322) `def _write_line(self, line)`
- `_write_editor_line` (line 331) `def _write_editor_line(self, line)` - *Editor content lines may be empty (blank lines in the file).*
- `send` (line 339) `def send(self, line, timeout_ms)`
- `expect` (line 350) `def expect(self, marker, timeout_ms)`
- `snapshot` (line 364) `def snapshot(self, max_bytes)`
- `cat` (line 374) `def cat(self, path)`
- `cat_body` (line 380) `def cat_body(self, path, missing_ok)` - *Read a ramdisk file and return exactly its bytes.

The serial driver emits CRLF; the kernel cat appends one newline
after the content, so the body is extracted by stripping the echoed
command line, the prompt and that single trailing newline.*
- `_cleanup_parts` (line 406) `def _cleanup_parts(self, parts)`
- `write` (line 413) `def write(self, path, content)`
- `poweroff` (line 450) `def poweroff(self, timeout_ms)`
- `terminate` (line 470) `def terminate(self)`
- `close` (line 489) `def close(self)`
- `__init__` (line 608) `def __init__(self, cfg)`
- `run` (line 612) `def run(self)`
- `_handle` (line 620) `def _handle(self, line)`
- `_initialize` (line 646) `def _initialize(self, params)`
- `_call` (line 653) `def _call(self, params)`
- `_dispatch` (line 670) `def _dispatch(self, name, args)`
- `_addons_list` (line 697) `def _addons_list(self)`
- `_addon_install` (line 718) `def _addon_install(self, args)`
- `_reply` (line 739) `def _reply(self, msg)`

#### `test_minios_mcp.py`
**Path:** `mcp/test_minios_mcp.py`

**Classes:**
- `MCPServer` (line 55) `class MCPServer` - *Child process running minios_mcp.py, driven over stdio JSON-RPC.*
- `TestProtocol` (line 138) `class TestProtocol(TestCase)`
- `TestValidation` (line 193) `class TestValidation(TestCase)`
- `TestLogBuffer` (line 242) `class TestLogBuffer(TestCase)`
- `_ConsoleBDDBase` (line 274) `class _ConsoleBDDBase(TestCase)` - *Fail-fast for QEMU-backed classes: once a tool call has hit a
console wait timeout the bridge is stuck (a mutated marker, a hung
shell) and every remaining test would only burn its own timeout, so
they are skipped instead.*
- `TestMiniOSBDD` (line 310) `class TestMiniOSBDD(_ConsoleBDDBase)`
- `TestAddonYaml` (line 412) `class TestAddonYaml(TestCase)`
- `TestAddonHelpers` (line 474) `class TestAddonHelpers(TestCase)`
- `FakeOS` (line 514) `class FakeOS` - *In-memory stand-in for the MiniOS session (no QEMU).*
- `TestAddonInstall` (line 580) `class TestAddonInstall(TestCase)`
- `TestAddonBDD` (line 715) `class TestAddonBDD(_ConsoleBDDBase)` - *Install a fixture addon from a local git repo into the real OS.*
- `_toolerror` (line 569) `class _toolerror(Exception)`

**Functions:**
- `load_module` (line 29) `def load_module()`
- `have_qemu` (line 49) `def have_qemu()`

**Methods:**
- `__init__` (line 58) `def __init__(self, env_extra)`
- `initialize` (line 77) `def initialize(self)`
- `request` (line 81) `def request(self, method, params)`
- `raw` (line 88) `def raw(self, line)`
- `_read_response` (line 93) `def _read_response(self)`
- `_roundtrip` (line 99) `def _roundtrip(self, msg)`
- `tool` (line 107) `def tool(self, name, params)`
- `close` (line 117) `def close(self)`
- `setUpClass` (line 140) `def setUpClass(cls)`
- `tearDownClass` (line 146) `def tearDownClass(cls)`
- `test_initialize` (line 149) `def test_initialize(self)`
- `test_tools_list` (line 155) `def test_tools_list(self)`
- `test_ping` (line 163) `def test_ping(self)`
- `test_unknown_method` (line 167) `def test_unknown_method(self)`
- `test_malformed_json` (line 171) `def test_malformed_json(self)`
- `test_unknown_tool` (line 175) `def test_unknown_tool(self)`
- `test_send_not_booted` (line 180) `def test_send_not_booted(self)`
- `test_send_empty_line_rejected` (line 186) `def test_send_empty_line_rejected(self)`
- `setUpClass` (line 195) `def setUpClass(cls)`
- `test_path_accepts_plain_names` (line 200) `def test_path_accepts_plain_names(self)`
- `test_path_rejects_unsafe` (line 204) `def test_path_rejects_unsafe(self)`
- `test_path_rejects_long` (line 208) `def test_path_rejects_long(self)`
- `test_content_accepts_ascii` (line 211) `def test_content_accepts_ascii(self)`
- `test_content_rejects_non_printable` (line 214) `def test_content_rejects_non_printable(self)`
- `test_timeout_clamped` (line 218) `def test_timeout_clamped(self)`
- `test_write_rejects_line_too_long` (line 222) `def test_write_rejects_line_too_long(self)`
- `test_write_rejects_too_many_lines` (line 231) `def test_write_rejects_too_many_lines(self)`
- `setUpClass` (line 244) `def setUpClass(cls)`
- `test_bounds` (line 249) `def test_bounds(self)`
- `test_find_and_total` (line 256) `def test_find_and_total(self)`
- `test_cursor_prevents_stale_match` (line 263) `def test_cursor_prevents_stale_match(self)`
- `guard_server` (line 283) `def guard_server(cls)`
- `setUp` (line 304) `def setUp(self)`
- `setUpClass` (line 312) `def setUpClass(cls)`
- `tearDownClass` (line 319) `def tearDownClass(cls)`
- `test_t01_boot` (line 323) `def test_t01_boot(self)`
- `test_t02_expect` (line 333) `def test_t02_expect(self)`
- `test_t03_write_and_cat` (line 340) `def test_t03_write_and_cat(self)`
- `test_t04_toolchain_elf` (line 350) `def test_t04_toolchain_elf(self)`
- `test_t05_toolchain_cvm` (line 361) `def test_t05_toolchain_cvm(self)`
- `test_t06_selfhosted_compiler` (line 371) `def test_t06_selfhosted_compiler(self)`
- `test_t07_bin_command_path` (line 377) `def test_t07_bin_command_path(self)`
- `test_t08_poweroff_and_reboot` (line 385) `def test_t08_poweroff_and_reboot(self)`
- `setUpClass` (line 414) `def setUpClass(cls)`
- `test_parse_valid` (line 424) `def test_parse_valid(self)`
- `test_validate_accepts_valid` (line 434) `def test_validate_accepts_valid(self)`
- `test_unknown_key_rejected` (line 438) `def test_unknown_key_rejected(self)`
- `test_bad_indent_rejected` (line 442) `def test_bad_indent_rejected(self)`
- `test_validate_rejects_bad_dst` (line 446) `def test_validate_rejects_bad_dst(self)`
- `test_validate_rejects_missing_name` (line 451) `def test_validate_rejects_missing_name(self)`
- `test_validate_rejects_long_build_line` (line 455) `def test_validate_rejects_long_build_line(self)`
- `test_validate_rejects_control_chars` (line 463) `def test_validate_rejects_control_chars(self)`
- `test_validate_rejects_empty_files` (line 468) `def test_validate_rejects_empty_files(self)`
- `setUpClass` (line 476) `def setUpClass(cls)`
- `test_split_for_editor_chunks` (line 486) `def test_split_for_editor_chunks(self)`
- `test_split_rejects_long_line` (line 493) `def test_split_rejects_long_line(self)`
- `test_split_rejects_non_ascii` (line 497) `def test_split_rejects_non_ascii(self)`
- `test_exit_code_of` (line 501) `def test_exit_code_of(self)`
- `test_state_roundtrip` (line 506) `def test_state_roundtrip(self)`
- `__init__` (line 517) `def __init__(self, exit_codes)`
- `booted` (line 524) `def booted(self)`
- `boot` (line 527) `def boot(self, timeout_ms)`
- `write` (line 531) `def write(self, path, content)`
- `send` (line 538) `def send(self, line, timeout_ms)`
- `cat_body` (line 562) `def cat_body(self, path, missing_ok)`
- `_cleanup_parts` (line 574) `def _cleanup_parts(self, parts)`
- `setUpClass` (line 582) `def setUpClass(cls)`
- `tearDownClass` (line 614) `def tearDownClass(cls)`
- `make_addon` (line 619) `def make_addon(self)`
- `test_install_success` (line 641) `def test_install_success(self)`
- `test_install_mismatch_aborts_and_cleans` (line 654) `def test_install_mismatch_aborts_and_cleans(self)`
- `test_install_multi_chunk_reassembly` (line 668) `def test_install_multi_chunk_reassembly(self)`
- `test_install_verify_failure_aborts` (line 699) `def test_install_verify_failure_aborts(self)`
- `test_install_build_failure_aborts` (line 706) `def test_install_build_failure_aborts(self)`
- `setUpClass` (line 719) `def setUpClass(cls)`
- `tearDownClass` (line 756) `def tearDownClass(cls)`
- `test_addons_list` (line 764) `def test_addons_list(self)`
- `test_install_fixture` (line 770) `def test_install_fixture(self)`
- `test_install_unknown_addon_fails` (line 779) `def test_install_unknown_addon_fails(self)`
- `guarded` (line 286) `def guarded(name, params)`
- `broken_cat` (line 658) `def broken_cat(path, missing_ok)`

#### `mkramdisk.py`
**Path:** `mkramdisk.py`

**Functions:**
- `pack_name` (line 20) `def pack_name(path, common)`
- `main` (line 30) `def main()`

#### `test_http_server.py`
**Path:** `test_http_server.py`

**Classes:**
- `Handler` (line 21) `class Handler(BaseHTTPRequestHandler)`

**Methods:**
- `do_GET` (line 24) `def do_GET(self)`
- `log_message` (line 114) `def log_message(self, fmt)`

#### `tls_test.py`
**Path:** `tls_test.py`

**Classes:**
- `Server` (line 241) `class Server(Thread)`

**Functions:**
- `run` (line 26) `def run(cmd)`
- `check` (line 30) `def check(cmd)`
- `gen_certs` (line 37) `def gen_certs()`
- `der_bytes` (line 154) `def der_bytes(pem_path)`
- `rsa_params` (line 162) `def rsa_params(key_path)`
- `ec_pub` (line 172) `def ec_pub(key_path)`
- `c_bytes` (line 183) `def c_bytes(data, name)`
- `gen_header` (line 191) `def gen_header(p)`

**Methods:**
- `serve` (line 280) `def serve(cert, key)`
- `serve_openssl` (line 288) `def serve_openssl(cert, key, chain)`
- `expect` (line 306) `def expect(bin_path, args, want_zero, marker)`
- `main` (line 319) `def main()`
- `server_cert` (line 61) `def server_cert(name, algo, curve, ca_name, ca_algo, curve_ca, extra, subj)`
- `__init__` (line 242) `def __init__(self, cert, key, tls13_ok)`
- `run` (line 248) `def run(self)`

### S (7 files)

#### `fib.s`
**Path:** `progs/fib.s`

**Functions:**
- `fib` (line 3)
- `main` (line 61)
- `_start` (line 82)

#### `freedom.s`
**Path:** `progs/freedom.s`

**Functions:**
- `f_host` (line 3)
- `f_path` (line 7)
- `f_port` (line 11)
- `f_secure` (line 15)
- `f_loc` (line 19)
- `f_redir` (line 23)
- `f_status` (line 27)
- `f_clen` (line 31)
- `f_has_clen` (line 35)
- `f_chunked` (line 39)
- `f_hdr` (line 43)
- `f_hlen` (line 47)
- `f_tag` (line 51)
- `f_suppress` (line 55)
- `f_comment` (line 59)
- `f_cmdash` (line 63)
- `f_tagn` (line 67)
- `f_tagnlen` (line 71)
- `f_ent` (line 75)
- `f_entlen` (line 79)
- `f_ws` (line 83)
- `f_utbuf` (line 87)
- `f_utlen` (line 91)
- `f_utrem` (line 95)
- `f_attr_on` (line 99)
- `f_waitq` (line 103)
- `f_inval` (line 107)
- `f_inval2` (line 111)
- `f_attr` (line 115)
- `f_attrlen` (line 119)
- `f_val` (line 123)
- `f_vallen` (line 127)
- `f_id` (line 131)
- `f_idlen` (line 135)
- `f_cls` (line 139)
- `f_clslen` (line 143)
- `f_href` (line 147)
- `f_hreflen` (line 151)
- `f_rel_ss` (line 155)
- `f_styleattr` (line 159)
- `f_stylelen` (line 163)
- `f_dump_css` (line 167)
- `f_dump_dom` (line 171)
- `f_mode` (line 175)
- `f_rawcap` (line 179)
- `f_depth` (line 183)
- `f_dom` (line 187)
- `f_domlen` (line 191)
- `f_css` (line 195)
- `f_csslen` (line 199)
- `f_linkhost` (line 203)
- `f_linkpath` (line 207)
- `f_linkn` (line 211)
- `f_cstage` (line 215)
- `f_csize` (line 219)
- `f_crem` (line 223)
- `f_bdone` (line 227)
- `atoi` (line 231)
- `append` (line 317)
- `ci_lower` (line 402)
- `ci_starts` (line 451)
- `ci_eq` (line 524)
- `ci_index` (line 621)
- `looks_like_url` (line 681)
- `has_scheme` (line 755)
- `make_search` (line 1030)
- `split_url` (line 1266)
- `resolve_redirect` (line 1781)
- `put_ws` (line 2306)
- `put_utf` (line 2352)
- `put_text` (line 2888)
- `put_entity` (line 2991)
- `css_append` (line 3828)
- `css_line` (line 3899)
- `dom_append` (line 3958)
- `dom_space` (line 4029)
- `dom_nl` (line 4063)
- `record_attr` (line 4097)
- `is_void_tag` (line 4435)
- `classify_tag` (line 4757)
- `body_byte` (line 5994)
- `head_line` (line 7239)
- `parse_head` (line 7500)
- `recv_body` (line 7717)
- `send_all` (line 7778)
- `fetch` (line 7853)
- `fetch_css` (line 9331)
- `print_css_dump` (line 10143)
- `print_dom_dump` (line 10243)
- `main` (line 10322)
- `_start` (line 11800)

#### `http.s`
**Path:** `progs/http.s`

**Functions:**
- `atoi` (line 3)
- `main` (line 89)
- `_start` (line 698)

#### `ldhello.s`
**Path:** `progs/ldhello.s`

**Functions:**
- `main` (line 3)
- `_start` (line 14)

#### `w1.s`
**Path:** `progs/w1.s`

**Functions:**
- `main` (line 3)
- `_start` (line 37)

#### `stage1.S`
**Path:** `stage1.S`
**File Doc:** *stage1.S - MiniOS boot sector.*

**Functions:**
- `main` (line 21)
- `normalize` (line 25)
- `no_extensions` (line 59)
- `read_failed` (line 63)
- `fail` (line 66)
- `halt` (line 69)
- `puts` (line 74)
- `puts_next` (line 78)
- `puts_done` (line 84)
- `msg_no_lba` (line 88)
- `msg_read` (line 90)

#### `stage2.S`
**Path:** `stage2.S`
**File Doc:** *stage2.S - MiniOS second-stage loader.*

**Functions:**
- `stage2_main` (line 39)
- `a20_ready` (line 54)
- `load_chunk` (line 61)
- `chunk_size_ready` (line 66)
- `read_piece` (line 73)
- `piece_size_ready` (line 78)
- `chunk_copy` (line 110)
- `chunk_leave_pm` (line 123)
- `chunk_resume` (line 133)
- `enter_long_mode` (line 152)
- `fill_page_directory` (line 172)
- `read_failed` (line 201)
- `halt` (line 205)
- `puts` (line 210)
- `puts_next` (line 214)
- `puts_done` (line 220)
- `msg_read` (line 224)
- `gdt32_start` (line 228)
- `gdt32_end` (line 234)
- `gdt32_ptr` (line 235)
- `gdt64_image` (line 240)
- `gdt64_ptr` (line 246)
- `saved_gdtr` (line 250)
- `sectors_left` (line 253)
- `chunk_sectors` (line 255)
- `next_lba` (line 257)
- `dest_addr` (line 259)

### SH (5 files)

#### `install.sh`
**Path:** `install.sh`

*No symbols extracted*

#### `mutate_mcp.sh`
**Path:** `mcp/mutate_mcp.sh`
**File Doc:** *Mutation testing for the MiniOS MCP bridge. Every mutant is injected into a private copy of minios_mcp.py and run against the unit and BDD suite. A mutant that survives (suite fully green) exposes a test gap.  Suites run in parallel (one worker per core, MUTATE_JOBS to override); each mutant gets its own pid file and addon state so the runs stay independent.  Mutation format: "name | sed -i expression | file"*

**Functions:**
- `run_one` (line 115) - *Each mutant runs the suite in its own directory with its own pid file and addon state, so the runs are independent and may execute in parallel. The worker writes the exit code; the loop below maps it onto the verdict.*

#### `mkroots.sh`
**Path:** `mkroots.sh`
**File Doc:** *mkroots.sh - regenerate tls_roots.h from the DER files in tls_roots_src/.  Provenance of each root (2026 web PKI reality; everything a real site chains to is one of these):  isrg_root_x1.der          Let's Encrypt ISRG Root X1 (RSA, older chains) https://letsencrypt.org/certs/isrg-root-x1.pem isrg_root_x2.der          Let's Encrypt ISRG Root X2 (ECDSA P-384, current) https://letsencrypt.org/certs/isrg-root-x2.pem digicert_global_root_g2.der  DigiCert Global Root G2 (RSA) https://cacerts.digicert.com/DigiCertGlobalRootG2.crt globalsign_root_r3.der    GlobalSign Root CA R3 (RSA) https://secure.globalsign.com/cacert/root-r3.crt gts_root_r4.der           Google Trust Services Root R4 (ECDSA P-384) https://pki.goog/repo/certs/gtsr4.pem sslcom_ecc_2022.der       SSL.com TLS ECC Root CA 2022 (Cloudflare ECC chains) sslcom_rsa_2022.der       SSL.com TLS RSA Root CA 2022 (Cloudflare RSA chains)  The two SSL.com roots have no stable public URL; they are extracted from the certificate chain example.com serves (openssl s_client -showcerts, ECDHE-ECDSA and ECDHE-RSA respectively). The build never runs this script: tls_roots.h is a committed input, regenerated only when the root set changes.*

*No symbols extracted*

#### `mutate.sh`
**Path:** `mutate.sh`
**File Doc:** *Mutation testing for MiniOS.  Each mutation is applied to the source in place, the disk image is rebuilt and the behavioural suite is run in fail-fast mode. A mutant that survives a full green suite exposes a gap that must be closed by adding a scenario, never by deleting the mutant.  The sources are backed up before the first mutation and restored on every exit path, including interrupts. A mutation whose expression matches nothing is reported as broken rather than surviving: `sed -i` exits zero when it changes nothing, which would otherwise rebuild pristine sources and look like a test gap.  Mutation format: "name | sed -i expression | file"*

**Functions:**
- `restore_sources` (line 24)
- `cleanup` (line 31)

#### `test_bdd.sh`
**Path:** `test_bdd.sh`
**File Doc:** *BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the serial console (COM1). Every scenario sends a script of shell commands, then asserts that the expected markers appear in the console log.  The guest powers itself off through the ACPI port at the end of each scenario, which makes QEMU exit; the timeout is only a safety net for hangs. A stale-qemu guard prevents image-lock cascades between runs.  Environment overrides: QEMU, TMO (per-scenario timeout), KEEP_LOG=1 to keep the console log of the last scenario for inspection.*

**Functions:**
- `cleanup_stale_qemu` (line 30)
- `scenario` (line 41) - *scenario <name> <script of shell commands>*
- `expect` (line 59) - *expect <marker>*
- `expect_count` (line 80) - *expect_count <count> <marker>: the marker must appear exactly that many times in the log. Used where a single occurrence would also match the echoed command line, so only the output can prove the behaviour.*
- `refute` (line 102) - *refute <marker>: the marker must NOT appear (suppressed hostile content).*
- `http_server_start` (line 326)
- `http_server_stop` (line 333)
- `http_fixture_start` (line 338)
- `http_fixture_stop` (line 345)
