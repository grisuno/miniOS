#!/bin/bash
# host_codecs.sh - reusable host-side verification for the in-OS codec tools.
#
# The miniGCC-compiled tools are static Linux ELFs (the kernel runs Linux
# binaries unmodified), so they execute on the host too.  This script drives
# them with a host file: roundtrip, fail-closed rejection, and (for lzss)
# bidirectional interop against the reference Okumura codec in
# $LZSS_REF_SRC.  LZ4 cannot interop on the host because it goes through
# MiniOS syscalls 216/217, so only its lzss-style roundtrip + reject paths
# are exercised here; the kernel LZ4 roundtrip is covered by test_lz4_kernel.
#
# Usage: host_codecs.sh <progs_dir>
#   <progs_dir>  the miniOS progs/ dir containing bin/lzss, bin/unlzss, ...
# Environment: LZSS_REF_SRC (default ../../CompressLoader/lzss.c)
set -u

PROGS="${1:?usage: host_codecs.sh <progs_dir>}"
WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT
PASS=0
FAIL=0
ok() { echo "  PASS  $1"; PASS=$((PASS+1)); }
bad() { echo "  FAIL  $1"; FAIL=$((FAIL+1)); }

"$PROGS/bin/lzss" >/dev/null 2>&1; chmod +x "$PROGS"/bin/lzss "$PROGS"/bin/unlzss "$PROGS"/bin/lz4 "$PROGS"/bin/unlz4 2>/dev/null

gen_input() {  # write compressible data
    python3 -c "open('$WORK/in.txt','w').write(('the quick brown fox jumps over the lazy dog\n')*40)"
}

roundtrip() {  # <lzss|unlzss-style binary pair> <in> <compressed> <out> <compressor> <decompressor>
    local comp="$1" dec="$2" in="$3" cz="$4" out="$5"
    "$comp" "$in" "$cz" >/dev/null || { bad "encode $comp"; return; }
    chmod 644 "$cz" 2>/dev/null
    "$dec" "$cz" "$out" >/dev/null || { bad "decode $dec"; return; }
    chmod 644 "$out" 2>/dev/null
    cmp -s "$in" "$out" && ok "roundtrip ($comp/$dec)" || bad "roundtrip mismatch ($comp/$dec)"
}

reject() {  # <decoder> <input-file> <expect-marker>
    local dec="$1" f="$2" marker="$3"
    local out
    out=$("$dec" "$f" "$WORK/o.bin" 2>&1)
    if echo "$out" | grep -qF "$marker"; then ok "reject $marker ($dec)"; else bad "reject $marker ($dec): $out"; fi
}

echo "=== lzss roundtrip + fail-closed (host) ==="
gen_input
roundtrip "$PROGS/bin/lzss" "$PROGS/bin/unlzss" "$WORK/in.txt" "$WORK/in.lzs" "$WORK/in.out"
printf 'LZS1' > "$WORK/trunc.lzs"
reject "$PROGS/bin/unlzss" "$WORK/trunc.lzs" "truncated header"
printf 'XXXXXXXX-not-lzs1-here-anyway' > "$WORK/bad.lzs"
reject "$PROGS/bin/unlzss" "$WORK/bad.lzs" "bad magic"
printf 'LZS1\xff\xff\xff\x7f' > "$WORK/huge.lzs"
reject "$PROGS/bin/unlzss" "$WORK/huge.lzs" "declared size out of range"

echo "=== lzss interop vs reference Okumura (host) ==="
LZSS_REF="${LZSS_REF_SRC:-$HOME/src_note/c/CompressLoader/lzss.c}"
if [ -f "$LZSS_REF" ]; then
    cat > "$WORK/refmain.c" <<'EOF'
#include <stdio.h>
extern FILE *infile, *outfile;
int encode(void); int decode(void);
int main(int argc, char **argv) {
    if (argc != 4) return 2;
    if (argv[1][0] == 'e') { infile=fopen(argv[2],"rb"); outfile=fopen(argv[3],"wb"); encode(); }
    else { infile=fopen(argv[2],"rb"); outfile=fopen(argv[3],"wb"); decode(); }
    fclose(infile); fclose(outfile); return 0;
}
EOF
    gcc -w -O1 -o "$WORK/ref" "$WORK/refmain.c" "$LZSS_REF" 2>/dev/null || { bad "reference build"; }
    if [ -x "$WORK/ref" ]; then
        "$WORK/ref" e "$WORK/in.txt" "$WORK/ref.lzs"
        dd if="$WORK/in.lzs" of="$WORK/in.pure" bs=1 skip=8 status=none
        "$WORK/ref" d "$WORK/in.pure" "$WORK/refdec.out"
        cmp -s "$WORK/in.txt" "$WORK/refdec.out" && ok "my-lzss -> reference decode" || bad "my-lzss -> reference decode"
        printf 'LZS1' > "$WORK/wrapped.lzs"
        python3 -c "import struct,sys; open('$WORK/wrapped.lzs','ab').write(struct.pack('<I',$(stat -c%s "$WORK/in.txt")))" 
        cat "$WORK/ref.lzs" >> "$WORK/wrapped.lzs"
        chmod 644 "$WORK/wrapped.lzs"
        "$PROGS/bin/unlzss" "$WORK/wrapped.lzs" "$WORK/mydec.out" >/dev/null 2>&1
        chmod 644 "$WORK/mydec.out" 2>/dev/null
        cmp -s "$WORK/in.txt" "$WORK/mydec.out" && ok "reference-lzss -> my decode" || bad "reference-lzss -> my decode"
    fi
else
    echo "  (skip interop: reference not found at $LZSS_REF)"
fi

echo "=== lz4 fail-closed (host; roundtrip needs MiniOS syscalls 216/217) ==="
printf 'AAAA' > "$WORK/aaa.lz4"
reject "$PROGS/bin/unlz4" "$WORK/aaa.lz4" "implausible size"

echo ""
echo "summary: $PASS passed, $FAIL failed"
[ "$FAIL" -eq 0 ]
