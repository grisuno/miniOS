# TopoGPT3 on MiniOS

A 24.5M-parameter complex-valued autoregressive language model for code,
running as a ring-3 static Linux ELF inside MiniOS.

### Project

[TopoGPT3](https://github.com/grisuno/TopoGPT3) is a 24.5M-parameter
complex-valued autoregressive language model for code, built with
quaternion-inspired spectral operators and a Mixture-of-Experts
transformer. MiniOS ships it as a static Linux ELF at ring 3, built by the
host toolchain and loaded by the ordinary `ET_EXEC` loader, so it needs no
translation layer.

### Engine (`progs/topogpt3/topogpt3.c`)

The inference engine is a self-contained single-file C implementation
(1,999 lines) that loads flat binary weight files and runs the full
forward pass. It has no dependency beyond libc: when `stdio.h` is not
available it declares the few libc entry points it needs and talks to the
`ld` stubs, and it carries its own `sqrt`/`exp` so the math does not depend
on libm either.

Architecture constants (`progs/topogpt3/topogpt3.c:65-98`): `D_MODEL` 256,
`N_HEADS` 8, `N_KV_HEADS` 2 (GQA groups 4), `D_HEAD` 32, `N_LAYERS` 6,
`N_EXPERTS` 4 with `MOE_TOP_K` 2, `D_QUAT` 64, `N_SPECTRAL_LAYERS` 2,
`SPECTRAL_LATENT_DIM` 128, a 2x4 torus grid, `MAX_SEQ_LEN` 512,
`MAX_TOKENS` 1024, `MAX_PROMPT_LEN` 4096, `VOCAB_SIZE` 50,257 and EOS
token 50,256.

The forward pass is GQA attention with RoPE on Q and K, a causal mask and
a 128-token sliding window, RMSNorm, SwiGLU MoE with top-2 routing, and
the quaternion torus spectral layers.

### Command line

| Flag | Meaning | Default |
|------|---------|---------|
| `-p "prompt"` | headless: generate from one prompt | - |
| `-i` | interactive REPL | - |
| `-f file.txt` | headless: read the prompt from a file | - |
| `-T tokens.bin` | headless: read pre-tokenized binary ids (`TKID` magic) | - |
| `-w FILE` | weight file | `topogpt3.weights` |
| `-v FILE` | vocabulary file | `vocab.bin` |
| `-n NUM` | max new tokens | 256 |
| `-t NUM` | temperature | 0.3 |
| `-k NUM` | top-k | 50 |
| `-r NUM` | repetition penalty | 1.1 |
| `-h` | help | - |

With only `-w` given, the mode falls back to interactive
(`progs/topogpt3/topogpt3.c:1947-1950`). The shipped weight file is
`topogpt3.fp16`, so `-w topogpt3.fp16` is mandatory in practice.

### Interactive commands

| Command | Purpose |
|---------|---------|
| `/help` | show available commands |
| `/quit` | exit interactive mode |
| `/clear` | clear the prompt buffer |
| `/temp N` | set temperature |
| `/topk N` | set top-k |
| `/rep N` | set repetition penalty |
| `/newtokens N` | set max new tokens |
| `/status` | show current settings |

`/status` prints `temp=<f> top_k=<n> rep=<f> max_new=<n> prompt_len=<n>`
(`progs/topogpt3/topogpt3.c:1793-1796`).

### Weight and vocabulary formats

Weight loading auto-detects the format from the file magic: `TG16`
(float16, converted to float32 on load) and `TG3W` (float32). The float16
format halves the footprint (47 MB against 94 MB), which is why MiniOS
uses it. The `TG16` header carries a version and a tensor count, and the
loader prints `Loading <n> tensors (fp16 v<version>)...` before
`Weights loaded successfully (fp16).` (`progs/topogpt3/topogpt3.c:1452-1593`).

The shipped assets are `topogpt3.fp16` (48,930,967 bytes, `TG16` version
2, 380 tensors) and `vocab.bin` (421,349 bytes, `VOCB` magic, the 50,257
GPT-2 BPE tokens). The vocabulary is not required in git: the build
rebuilds it on demand from the canonical GPT-2 `encoder.json` with
`tools/mkvocab.py` (`Makefile:1548-1563`).

### Build and run

```
make progs/bin/topogpt3.elf    # compile the C engine
make minifs.bin                 # rebuild MiniFS with weights + vocab
make os.img                     # rebuild the full disk image
```

The engine is built with the host toolchain (`gcc -static -no-pie -O2`,
linked with `-lm`) and placed at `bin/topogpt3.elf` on the MiniFS, with a
bare-name copy so `topogpt3` resolves without the suffix. The weights and
the vocabulary ship on the MiniFS next to it.

`convert_weights_minios.py`, in the TopoGPT3 repository, converts
safetensors checkpoints into the float16 binary format; the engine names
it in its own error message when the weight file cannot be loaded.

### Measured throughput

| Platform | Speed |
|----------|-------|
| Linux host (KVM) | 17-29 tok/s |
| MiniOS QEMU (no KVM) | 0.80 tok/s |
| MiniOS QEMU (with KVM) | 17-29 tok/s |

