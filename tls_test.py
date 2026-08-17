#!/usr/bin/env python3
"""Host-side TLS test driver for the MiniOS kernel TLS client.

Generates a throwaway CA and server certificates with openssl (bounded,
offline), emits tls_test_roots.h (test CA DER + RSA/ECDSA verify
vectors), then runs the compiled tls_test binary against python ssl
servers: positive handshakes (RSA chain, ECDSA P-256 leaf over a P-384
CA) and the negative set (wrong hostname, unknown CA, expired cert).
"""

import os
import re
import shlex
import socket
import ssl
import subprocess
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
WORK = os.path.join(HERE, "build", "tls_test_work")
TMP = os.path.join(HERE, "build")


def run(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)


def check(cmd):
    r = run(cmd)
    if r.returncode != 0:
        raise RuntimeError("openssl failed: %s\n%s\n%s" % (cmd, r.stdout, r.stderr))
    return r


def gen_certs():
    os.makedirs(WORK, exist_ok=True)
    env = dict(os.environ)
    env["RANDFILE"] = os.path.join(WORK, ".rnd")
    p = lambda *n: os.path.join(WORK, *n)
    # The CA, the server certs and the vectors are generated once and
    # reused: regenerating them on every run would desynchronize the
    # tls_test binary (built with tls_test_roots.h) from the servers
    # (started with the on-disk certs). `--regen` forces fresh ones.
    if (os.path.exists(p("srv_rsa.pem")) and
            os.path.exists(p("srv_wild.pem")) and
            os.path.exists(p("srv_rsa_chain.pem")) and
            "--regen" not in sys.argv):
        return p

    # CA: RSA for the RSA chain; P-384 for the ECDSA chain.
    check(["openssl", "req", "-x509", "-newkey", "rsa:2048", "-nodes",
           "-keyout", p("ca_rsa.key"), "-out", p("ca_rsa.pem"), "-days", "30",
           "-subj", "/CN=MiniOS TLS Test RSA CA"])
    check(["openssl", "req", "-x509", "-newkey", "ec",
           "-pkeyopt", "ec_paramgen_curve:secp384r1", "-nodes",
           "-keyout", p("ca_ec.key"), "-out", p("ca_ec.pem"), "-days", "30",
           "-subj", "/CN=MiniOS TLS Test EC CA"])

    def server_cert(name, algo, curve, ca_name, ca_algo, curve_ca, extra=None,
                    subj="/CN=localhost"):
        keyargs = (["-newkey", "rsa:2048"] if algo == "rsa"
                   else ["-newkey", "ec", "-pkeyopt", "ec_paramgen_curve:" + curve])
        check(["openssl", "req", "-new", "-nodes", "-keyout", p(name + ".key"),
               "-out", p(name + ".csr"), "-subj", subj] + keyargs)
        if ca_algo == "rsa":
            capath, cakey = p(ca_name + ".pem"), p(ca_name + ".key")
        else:
            capath, cakey = p(ca_name + ".pem"), p(ca_name + ".key")
        cmd = ["openssl", "x509", "-req", "-in", p(name + ".csr"),
               "-CA", capath, "-CAkey", cakey, "-CAcreateserial",
               "-days", "30", "-sha256",
               "-extfile", p(name + ".ext"), "-out", p(name + ".pem")]
        with open(p(name + ".ext"), "w") as f:
            f.write("subjectAltName=DNS:localhost\n")
            if extra:
                f.write(extra + "\n")
        check(cmd)

    server_cert("srv_rsa", "rsa", "prime256v1", "ca_rsa", "rsa", None)
    server_cert("srv_ec", "ec", "prime256v1", "ca_ec", "ec", "secp384r1")
    server_cert("srv_wrong", "rsa", "prime256v1", "ca_rsa", "rsa", None,
                extra="subjectAltName=DNS:wrong.example")
    server_cert("srv_wild", "rsa", "prime256v1", "ca_rsa", "rsa", None,
                extra="subjectAltName=DNS:*.example.com",
                subj="/CN=wildcard-test")
    # a chain the server presents as leaf + CA: exercises the multi-cert
    # verify path (the chain is stored contiguously)
    with open(p("srv_rsa_chain.pem"), "wb") as f:
        f.write(open(p("srv_rsa.pem"), "rb").read())
        f.write(open(p("ca_rsa.pem"), "rb").read())
    # self-signed server (unknown CA)
    check(["openssl", "req", "-x509", "-newkey", "rsa:2048", "-nodes",
           "-keyout", p("srv_self.key"), "-out", p("srv_self.pem"),
           "-days", "30", "-subj", "/CN=localhost",
           "-addext", "subjectAltName=DNS:localhost"])
    # expired server: notAfter strictly in the past (openssl ca with
    # explicit dates; -days 0 only expires the cert at the exact
    # generation instant, which the day-granularity check accepts)
    check(["openssl", "req", "-new", "-newkey", "rsa:2048", "-nodes",
           "-keyout", p("srv_expired.key"), "-out", p("srv_expired.csr"),
           "-subj", "/CN=localhost"])
    with open(p("expired.ext"), "w") as f:
        f.write("subjectAltName=DNS:localhost\n")
    os.makedirs(p("demoCA"), exist_ok=True)
    for db in ("index.txt", "index.txt.attr"):
        if not os.path.exists(p("demoCA", db)):
            open(p("demoCA", db), "w").close()
    if not os.path.exists(p("demoCA", "serial")):
        with open(p("demoCA", "serial"), "w") as f:
            f.write("1000\n")
    with open(p("ca.cnf"), "w") as f:
        f.write("[ ca ]\ndefault_ca = CA_default\n"
                "[ CA_default ]\ndir = %s\ncertificate = $dir/ca_rsa.pem\n"
                "private_key = $dir/ca_rsa.key\ndatabase = $dir/demoCA/index.txt\n"
                "serial = $dir/demoCA/serial\nnew_certs_dir = $dir/demoCA\n"
                "default_md = sha256\npolicy = policy_any\ndefault_days = 30\n"
                "[ policy_any ]\ncommonName = supplied\n"
                "organizationalUnitName = optional\n"
                "organizationName = optional\n" % WORK)
    import datetime as _dt
    today = _dt.date.today()
    past1 = (today - _dt.timedelta(days=2)).strftime("%Y%m%d000000Z")
    past2 = (today - _dt.timedelta(days=1)).strftime("%Y%m%d000000Z")
    check(["openssl", "ca", "-batch", "-config", p("ca.cnf"),
           "-keyfile", p("ca_rsa.key"), "-cert", p("ca_rsa.pem"),
           "-in", p("srv_expired.csr"), "-out", p("srv_expired.pem"),
           "-md", "sha256", "-startdate", past1, "-enddate", past2,
           "-extfile", p("expired.ext"), "-notext"])
    # RSA/ECDSA verify vectors: sign a fixed payload with each server key
    payload = os.path.join(WORK, "payload.bin")
    with open(payload, "wb") as f:
        f.write(b"sign me please, kernel rsa/ecdsa verify test\n")
    rsa_sig = os.path.join(WORK, "rsa.sig")
    check(["openssl", "dgst", "-sha256", "-sign", p("srv_rsa.key"),
           "-out", rsa_sig, payload])
    rsa384_sig = os.path.join(WORK, "rsa384.sig")
    check(["openssl", "dgst", "-sha384", "-sign", p("srv_rsa.key"),
           "-out", rsa384_sig, payload])
    ec_sig = os.path.join(WORK, "ec.sig")
    check(["openssl", "dgst", "-sha256", "-sign", p("srv_ec.key"),
           "-out", ec_sig, payload])
    # A 4096-bit RSA key: the Montgomery multiplier's temporaries only
    # reach their full width at 128 limbs, so the vectors cover the
    # 2048-bit and the 4096-bit paths separately.
    check(["openssl", "genpkey", "-algorithm", "RSA",
           "-pkeyopt", "rsa_keygen_bits:4096", "-out", p("rsa4096.key")])
    check(["openssl", "dgst", "-sha256", "-sign", p("rsa4096.key"),
           "-out", p("rsa4096.sig"), payload])
    return p


def der_bytes(pem_path):
    r = subprocess.run(["openssl", "x509", "-in", pem_path, "-outform", "DER"],
                       capture_output=True)
    if r.returncode != 0:
        raise RuntimeError("openssl der failed: %s" % r.stderr)
    return r.stdout


def rsa_params(key_path):
    r = check(["openssl", "rsa", "-in", key_path, "-modulus", "-noout"])
    m = re.search(r"Modulus=([0-9A-Fa-f]+)", r.stdout)
    n = bytes.fromhex(m.group(1))
    r = check(["openssl", "rsa", "-in", key_path, "-text", "-noout"])
    exp = int(re.search(r"publicExponent: (\d+)", r.stdout).group(1))
    e = exp.to_bytes((exp.bit_length() + 7) // 8, "big")
    return n, e


def ec_pub(key_path):
    r = check(["openssl", "ec", "-in", key_path, "-text", "-noout"])
    m = re.search(r"pub:\s*\n((?:\s{4}[0-9a-f:]{8,60}\n)+)", r.stdout)
    hexstr = re.sub(r"[^0-9a-f]", "", m.group(1))
    if hexstr.startswith("04"):
        hexstr = hexstr[2:]
    raw = bytes.fromhex(hexstr)
    half = len(raw) // 2
    return raw[:half], raw[half:]


def c_bytes(data, name):
    lines = ["static const unsigned char %s[%d] = {" % (name, len(data))]
    for i in range(0, len(data), 16):
        lines.append("    " + ", ".join("0x%02x" % b for b in data[i:i + 16]) + ",")
    lines.append("};")
    return "\n".join(lines)


def gen_header(p):
    ca_rsa = der_bytes(p("ca_rsa.pem"))
    ca_ec = der_bytes(p("ca_ec.pem"))
    n, e = rsa_params(p("srv_rsa.key"))
    rsa_sig = open(p("rsa.sig"), "rb").read()
    rsa384_sig = open(p("rsa384.sig"), "rb").read()
    n4096, e4096 = rsa_params(p("rsa4096.key"))
    rsa4096_sig = open(p("rsa4096.sig"), "rb").read()
    ecx, ecy = ec_pub(p("srv_ec.key"))
    ec_sig = open(p("ec.sig"), "rb").read()
    payload = open(p("payload.bin"), "rb").read()

    out = [
        "/* tls_test_roots.h - generated by tls_test.py; never built into",
        " * the kernel. The test root replaces the production table. */",
        "",
    ]
    out.append(c_bytes(ca_rsa, "test_ca_rsa_der"))
    out.append(c_bytes(ca_ec, "test_ca_ec_der"))
    out.append("const struct tls_root tls_roots[TLS_ROOT_COUNT] = {")
    out.append("    { test_ca_rsa_der, %d }," % len(ca_rsa))
    out.append("    { test_ca_ec_der, %d }," % len(ca_ec))
    out.append("    { test_ca_rsa_der, %d }," % len(ca_rsa))
    # Pad to the production TLS_ROOT_COUNT (tls.h): the verify loop skips
    # entries whose DER does not parse, so empty slots cost nothing.
    try:
        tls_h = open(os.path.join(HERE, "tls.h")).read()
        m = re.search(r"#define\s+TLS_ROOT_COUNT\s+(\d+)", tls_h)
        root_count = int(m.group(1)) if m else 3
    except OSError:
        root_count = 3
    out.extend("    { 0, 0 }," for _ in range(max(0, root_count - 3)))
    out.append("};")
    out.append("")
    out.append(c_bytes(n, "test_rsa_n"))
    out.append(c_bytes(e, "test_rsa_e"))
    out.append(c_bytes(rsa_sig, "test_rsa_sig"))
    out.append(c_bytes(rsa384_sig, "test_rsa384_sig"))
    out.append(c_bytes(n4096, "test_rsa4096_n"))
    out.append(c_bytes(e4096, "test_rsa4096_e"))
    out.append(c_bytes(rsa4096_sig, "test_rsa4096_sig"))
    out.append(c_bytes(ecx, "test_ec_x"))
    out.append(c_bytes(ecy, "test_ec_y"))
    out.append(c_bytes(ec_sig, "test_ec_sig"))
    out.append(c_bytes(payload, "test_payload"))
    out.append("")
    with open(os.path.join(HERE, "tls_test_roots.h"), "w") as f:
        f.write("\n".join(out))


class Server(threading.Thread):
    def __init__(self, cert, key, tls13_ok=False):
        super().__init__(daemon=True)
        self.cert, self.key = cert, key
        self.port = None
        self.done = threading.Event()

    def run(self):
        ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
        ctx.minimum_version = ssl.TLSVersion.TLSv1_2
        ctx.maximum_version = ssl.TLSVersion.TLSv1_2
        ctx.set_ciphers("ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES128-GCM-SHA256")
        ctx.load_cert_chain(self.cert, self.key)
        ls = socket.socket()
        ls.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        ls.bind(("127.0.0.1", 0))
        ls.listen(1)
        self.port = ls.getsockname()[1]
        try:
            conn, _ = ls.accept()
            try:
                tls = ctx.wrap_socket(conn, server_side=True)
                try:
                    buf = b""
                    while b"\r\n\r\n" not in buf and len(buf) < 4096:
                        chunk = tls.recv(4096)
                        if not chunk:
                            break
                        buf += chunk
                    tls.sendall(b"HTTP/1.0 200 OK\r\nContent-Length: 9\r\n\r\nhello-tls")
                finally:
                    tls.close()
            finally:
                conn.close()
        finally:
            ls.close()
        self.done.set()


def serve(cert, key):
    s = Server(cert, key)
    s.start()
    while s.port is None:
        pass
    return s


def serve_openssl(cert, key, chain=None):
    # openssl s_server sends a real close_notify on shutdown, which the
    # Python ssl server does not: the clean-EOF contract needs one
    # scenario driven by openssl.
    probe = socket.socket()
    probe.bind(("127.0.0.1", 0))
    port = probe.getsockname()[1]
    probe.close()
    cmd = ["openssl", "s_server", "-quiet", "-accept", str(port),
           "-cert", cert, "-key", key, "-tls1_2", "-www"]
    if chain:
        cmd += ["-cert_chain", chain]
    proc = subprocess.Popen(cmd, stdout=subprocess.DEVNULL,
                            stderr=subprocess.DEVNULL)
    time.sleep(0.5)
    return proc, port


def expect(bin_path, args, want_zero, marker):
    r = run([bin_path] + args, timeout=120)
    body = (r.stdout or "") + (r.stderr or "")
    ok = (r.returncode == 0) == want_zero
    if marker and marker not in body:
        ok = False
    print("  %-38s rc=%d %s" % (" ".join(args), r.returncode,
                                 "PASS" if ok else "FAIL"))
    if not ok:
        print(body[:4000])
    return ok


def main():
    bin_path = os.path.join(TMP, "tls_test")
    if "--gen-only" in sys.argv:
        p = gen_certs()
        gen_header(p)
        print("tls_test_roots.h generated")
        return 0
    if not os.path.exists(bin_path):
        print("tls_test binary missing; run through 'make test-tls'")
        return 1
    p = gen_certs()
    gen_header(p)

    print("=== tls unit vectors ===")
    ok = True
    ok &= expect(bin_path, [], True, "all vectors pass")
    print("=== tls handshakes ===")
    s_rsa = serve(p("srv_rsa.pem"), p("srv_rsa.key"))
    s_ec = serve(p("srv_ec.pem"), p("srv_ec.key"))
    s_wrong = serve(p("srv_wrong.pem"), p("srv_wrong.key"))
    s_self = serve(p("srv_self.pem"), p("srv_self.key"))
    s_exp = serve(p("srv_expired.pem"), p("srv_expired.key"))
    # one Server per connection: each scenario gets its own listener
    s_wild1 = serve(p("srv_wild.pem"), p("srv_wild.key"))
    s_wild2 = serve(p("srv_wild.pem"), p("srv_wild.key"))
    s_wild3 = serve(p("srv_wild.pem"), p("srv_wild.key"))
    s_chain = serve(p("srv_rsa_chain.pem"), p("srv_rsa.key"))
    s_close, s_close_port = serve_openssl(p("srv_rsa.pem"), p("srv_rsa.key"),
                                          p("ca_rsa.pem"))
    ok &= expect(bin_path, ["good-rsa", str(s_rsa.port)], True, "hello-tls")
    ok &= expect(bin_path, ["good-ec", str(s_ec.port)], True, "hello-tls")
    ok &= expect(bin_path, ["bad-host", str(s_wrong.port)], True, "failed")
    ok &= expect(bin_path, ["bad-ca", str(s_self.port)], True, "failed")
    ok &= expect(bin_path, ["expired", str(s_exp.port)], True, "failed")
    ok &= expect(bin_path, ["wild-good", str(s_wild1.port)], True, "hello-tls")
    ok &= expect(bin_path, ["wild-root", str(s_wild2.port)], True, "failed")
    ok &= expect(bin_path, ["wild-deep", str(s_wild3.port)], True, "failed")
    ok &= expect(bin_path, ["chain-good", str(s_chain.port)], True, "hello-tls")
    # openssl sends close_notify: clean EOF must end the dialogue with 0
    ok &= expect(bin_path, ["good-rsa", str(s_close_port)], True, None)
    s_close.terminate()
    s_close.wait()
    for s in (s_rsa, s_ec, s_wrong, s_self, s_exp, s_wild1, s_wild2, s_wild3,
              s_chain):
        s.done.wait(10)
    print("=== tls suite: %s ===" % ("PASS" if ok else "FAIL"))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
