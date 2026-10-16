# `tools/mkroots.sh`

> Source: [tools/mkroots.sh:1](../../tools/mkroots.sh#L1) | language `sh` | coverage 100.0% | [API index](../index.md)

mkroots.sh - regenerate tls_roots.h from the DER files in tls_roots_src/.

Provenance of each root (2026 web PKI reality; everything a real site chains to is one of these):  isrg_root_x1.der          Let's Encrypt ISRG Root X1 (RSA, older chains) https://letsencrypt.org/certs/isrg-root-x1.pem isrg_root_x2.der          Let's Encrypt ISRG Root X2 (ECDSA P-384, current) https://letsencrypt.org/certs/isrg-root-x2.pem digicert_global_root_g2.der  DigiCert Global Root G2 (RSA) https://cacerts.digicert.com/DigiCertGlobalRootG2.crt globalsign_root_r3.der    GlobalSign Root CA R3 (RSA) https://secure.globalsign.com/cacert/root-r3.crt gts_root_r4.der           Google Trust Services Root R4 (ECDSA P-384) https://pki.goog/repo/certs/gtsr4.pem sslcom_ecc_2022.der       SSL.com TLS ECC Root CA 2022 (Cloudflare ECC chains) sslcom_rsa_2022.der       SSL.com TLS RSA Root CA 2022 (Cloudflare RSA chains)  The two SSL.com roots have no stable public URL; they are extracted from the certificate chain example.com serves (openssl s_client -showcerts, ECDHE-ECDSA and ECDHE-RSA respectively). The build never runs this script: tls_roots.h is a committed input, regenerated only when the root set changes.
