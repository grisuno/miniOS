# `progs/pokemon/fetch.sh`

> Source: [progs/pokemon/fetch.sh:1](../../progs/pokemon/fetch.sh#L1) | language `sh` | coverage 100.0% | [API index](../index.md)

fetch.sh - clone the gb-recompiled tool into progs/pokemon/upstream.

The upstream project ships the recompiler + runtime, but no ROMs and no pre-generated game code (see its README). You generate a project from a ROM you legally own, then point the MiniOS build at it. See README.md.  Usage: ./fetch.sh   (safe to re-run; never touches an existing checkout)
