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
