#!/usr/bin/env python3
"""Host-side HTTP fixture for the freedom BDD scenarios.

Serves behaviours that python -m http.server cannot produce:

  /chunked      Transfer-Encoding: chunked body split into three chunks
  /redirect302  302 with Location: /final (absolute-path redirect)
  /final        200 with Content-Length; the connection is then held open
                far beyond the BDD timeout, so a client that waits for EOF
                instead of honouring Content-Length stalls the scenario.

Usage: python3 test_http_server.py <port>
"""
import sys
import time
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

HOLD_SECONDS = 240


class Handler(BaseHTTPRequestHandler):
    protocol_version = "HTTP/1.1"

    def do_GET(self):
        if self.path == "/chunked":
            parts = (b"chunked ", b"body ", b"works")
            self.send_response(200)
            self.send_header("Content-Type", "text/plain")
            self.send_header("Transfer-Encoding", "chunked")
            self.end_headers()
            for part in parts:
                self.wfile.write(b"%x\r\n" % len(part))
                self.wfile.write(part)
                self.wfile.write(b"\r\n")
            self.wfile.write(b"0\r\n\r\n")
            self.wfile.flush()
            return
        if self.path == "/redirect302":
            self.send_response(302)
            self.send_header("Location", "/final")
            self.send_header("Content-Length", "0")
            self.end_headers()
            return
        if self.path == "/redirecthttps":
            self.send_response(302)
            self.send_header("Location", "https://10.0.2.2:8899/README.txt")
            self.send_header("Content-Length", "0")
            self.end_headers()
            return
        if self.path == "/styled":
            body = (b"<html><head><title>styled</title>"
                    b"<style>p { color: red; }</style>"
                    b"<link rel=\"stylesheet\" href=\"/style.css\">"
                    b"</head><body>"
                    b"<p id=\"x\" class=\"y\" style=\"font-size: 12px\">hello</p>"
                    b"</body></html>")
            self.send_response(200)
            self.send_header("Content-Type", "text/html")
            self.send_header("Content-Length", str(len(body)))
            self.end_headers()
            self.wfile.write(body)
            return
        if self.path == "/style.css":
            body = b"body { margin: 0; }\n"
            self.send_response(200)
            self.send_header("Content-Type", "text/css")
            self.send_header("Content-Length", str(len(body)))
            self.end_headers()
            self.wfile.write(body)
            return
        if self.path == "/acktest":
            # Two-part response gated on the peer's TCP acknowledgement:
            # the second half is sent only once the guest has ACKed the
            # first (an ACK that never advances stalls real servers, and
            # the mutant suite must see the difference).
            self.send_response(200)
            self.send_header("Content-Type", "text/plain")
            self.send_header("Content-Length", "6000")
            self.end_headers()
            self.wfile.write(b"A" * 3000)
            self.wfile.flush()
            deadline = time.time() + 5
            unacked = 3000
            while unacked > 0 and time.time() < deadline:
                import fcntl
                import struct as _struct
                try:
                    unacked = _struct.unpack(
                        "I", fcntl.ioctl(self.connection.fileno(), 0x5411,
                                         _struct.pack("I", 0)))[0]
                except OSError:
                    break
                time.sleep(0.1)
            if unacked > 0:
                return  # the peer never ACKed: leave the body short
            self.wfile.write(b"B" * 2999)
            self.wfile.write(b"Z")
            self.wfile.flush()
            return
        if self.path == "/final":
            body = b"FINAL PAGE MARKER\n"
            self.send_response(200)
            self.send_header("Content-Type", "text/plain")
            self.send_header("Content-Length", str(len(body)))
            self.end_headers()
            self.wfile.write(body)
            self.wfile.flush()
            time.sleep(HOLD_SECONDS)
            return
        self.send_response(404)
        self.send_header("Content-Length", "0")
        self.end_headers()

    def log_message(self, fmt, *args):
        return


if __name__ == "__main__":
    port = int(sys.argv[1])
    ThreadingHTTPServer(("0.0.0.0", port), Handler).serve_forever()
