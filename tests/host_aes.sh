#!/bin/bash
# host_aes.sh - host-side verification for the AES-256-CTR command tools.
#
# The miniGCC-built tools are static Linux ELFs, so they run on the host.
# This script checks the cipher core against two independent references
# (NIST SP 800-38A F.5.5 CTR-AES256 and OpenSSL) plus roundtrip, dispatch,
# empty input and the fail-closed rejection paths.
#
# Usage: tests/host_aes.sh <progs_dir>
set -u

PROGS="${1:?usage: host_aes.sh <progs_dir>}"
PROGS="$(cd "$(dirname "$PROGS")" && pwd)/$(basename "$PROGS")"
WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT
chmod +x "$PROGS"/bin/aes "$PROGS"/bin/unaes 2>/dev/null
AES="$PROGS/bin/aes"
UNAES="$PROGS/bin/unaes"
KEY="603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4"
NONCE="f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"
PASS=0
FAIL=0
ok() { echo "  PASS  $1"; PASS=$((PASS+1)); }
bad() { echo "  FAIL  $1"; FAIL=$((FAIL+1)); }
rd() { chmod 644 "$1" 2>/dev/null; true; }

python3 - <<'EOF'
open('nist.bin','wb').write(bytes.fromhex('6bc1bee22e409f96e93d7e117393172a'))
open('big.bin','wb').write(bytes(range(256)) * 16)
EOF
cd "$WORK" || exit 1
cp "$OLDPWD/nist.bin" . 2>/dev/null; cp "$OLDPWD/big.bin" .

echo "=== NIST SP 800-38A CTR-AES256 known answer ==="
"$AES" "$KEY" "$NONCE" nist.bin n.aes >/dev/null && rd n.aes
got="$(dd if=n.aes bs=1 skip=8 count=16 status=none | xxd -p | tr -d '\n')"
[ "$got" = "601ec313775789a5b7a7f504bbf3d228" ] && ok "F.5.5 block 1 ciphertext" || bad "KAT got $got"

echo "=== OpenSSL interop (multi-block counter stream) ==="
if command -v openssl >/dev/null; then
    openssl enc -aes-256-ctr -K "$KEY" -iv "$NONCE" -in big.bin -out ref.bin 2>/dev/null
    "$AES" "$KEY" "$NONCE" big.bin big.aes >/dev/null && rd big.aes
    dd if=big.aes of=body.bin bs=1 skip=8 status=none
    cmp -s body.bin ref.bin && ok "ciphertext == openssl byte-for-byte" || bad "ciphertext mismatch"
    "$UNAES" "$KEY" "$NONCE" big.aes big.out >/dev/null && rd big.out
    cmp -s big.bin big.out && ok "roundtrip 4096 bytes" || bad "roundtrip"
else
    echo "  (skip: openssl not found)"
fi

echo "=== reverse direction and dispatch ==="
openssl enc -aes-256-ctr -K "$KEY" -iv "$NONCE" -in nist.bin -out r16.bin 2>/dev/null
python3 -c "import struct; d=open('r16.bin','rb').read(); open('w.aes','wb').write(b'AES1'+struct.pack('<I',len(d))+d)"
rd w.aes
"$UNAES" "$KEY" "$NONCE" w.aes w.out >/dev/null && rd w.out
cmp -s nist.bin w.out && ok "openssl -> unaes" || bad "openssl -> unaes"
cp "$UNAES" ./unaes-tool && chmod +x ./unaes-tool
./unaes-tool "$KEY" "$NONCE" w.aes d.out >/dev/null && rd d.out
cmp -s nist.bin d.out && ok "argv[0] contains unaes -> decode" || bad "argv[0] dispatch"
"$AES" -d "$KEY" "$NONCE" w.aes dd.out >/dev/null && rd dd.out
cmp -s nist.bin dd.out && ok "-d forces decode on aes name" || bad "-d flag"

echo "=== fail-closed ==="
out="$("$AES" short "$NONCE" big.bin x.aes 2>&1)"; echo "$out" | grep -q "key must be" && ok "short key rejected" || bad "short key: $out"
out="$("$AES" "$KEY" "zz$NONCE" big.bin x.aes 2>&1)"; echo "$out" | grep -q "nonce must be" && ok "bad nonce rejected" || bad "bad nonce: $out"
printf 'AES1' > t.aes; out="$("$UNAES" "$KEY" "$NONCE" t.aes o.bin 2>&1)"; echo "$out" | grep -q "truncated header" && ok "truncated header" || bad "header: $out"
printf 'XXXX01000000' > b.aes; out="$("$UNAES" "$KEY" "$NONCE" b.aes o.bin 2>&1)"; echo "$out" | grep -q "bad magic" && ok "bad magic" || bad "magic: $out"
head -c 12 big.aes > cut.aes; out="$("$UNAES" "$KEY" "$NONCE" cut.aes o.bin 2>&1)"; echo "$out" | grep -q "size mismatch" && ok "truncated body detected" || bad "truncate: $out"

echo "=== empty file ==="
: > empty.bin
"$AES" "$KEY" "$NONCE" empty.bin e.aes >/dev/null && rd e.aes
"$UNAES" "$KEY" "$NONCE" e.aes e.out >/dev/null && rd e.out
cmp -s empty.bin e.out && ok "empty roundtrip" || bad "empty roundtrip"
[ "$(stat -c%s e.aes)" = "8" ] && ok "empty container is header-only" || bad "container size"

echo ""
echo "summary: $PASS passed, $FAIL failed"
[ "$FAIL" -eq 0 ]
