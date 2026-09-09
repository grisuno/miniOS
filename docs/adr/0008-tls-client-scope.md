# ADR-0008: TLS 1.2 client scope

Status: accepted

## Context

`https://` had to work without the browser touching key material, but a
full TLS stack (downgrade, resumption, all suites) does not fit the
kernel's integer-only, bounded-memory contract.

## Decision

Client-only TLS 1.2, two suites
(`TLS_ECDHE_RSA/ECDSA_WITH_AES_128_GCM_SHA256`), no downgrade, no
fallback, no resumption. Constant-time crypto where it counts (no
secret-indexed tables), Montgomery temporaries sized for 4096-bit
moduli, 8 embedded roots (cross-signed anchoring by key equality below
a still-verified chain), hostname SAN/CN match, RTC validity window,
per-handshake heap state freed on close, deadline-bounded reads.
Syscalls 201-203 (`tls_handshake/send/recv`); `tls_recv` returns 0 only
on clean EOF.

## Consequences

Host-tested (`make test-tls`: fixed vectors, OpenSSL-driven full
handshakes RSA/ECDSA, negative set, close_notify EOF); BDD covers
in-OS wiring fail-closed. ClientRandom mixes TSC/RX counters: documented,
not hidden; there is no CSPRNG.
