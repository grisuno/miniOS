#!/usr/bin/env python3
"""test_net_fixture.py -- host-side UDP and TCP echo fixture for lxnet.

The lxnet probe (progs/src/lxnet.c, docs/spec/network.md "Linux socket ABI")
proves the guest's datagram and stream sockets against something the guest
can reach through QEMU slirp (10.0.2.2 is the host). python -m http.server
cannot echo datagrams or hold a raw stream, so this fixture serves both:

  UDP <port>   echoes every datagram back to its sender, byte for byte
  TCP <port>   echoes every byte back on each accepted connection until the
               peer closes

Usage:
  python3 tools/test_net_fixture.py <port>

Inputs: one port number, used for both the UDP and the TCP listener.
Outputs: none on success; runs until killed (the BDD harness stops it).
Failure modes: exits 2 on a bad argument and 1 when either port cannot be
bound (already in use).
"""
import socket
import sys
import threading


class Config:
    """Every tunable of the fixture in one place."""
    HOST = "0.0.0.0"
    DATAGRAM_MAX = 65535
    STREAM_CHUNK = 4096
    BACKLOG = 8


def serve_udp(port):
    """Echo each datagram back to its sender."""
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind((Config.HOST, port))
    while True:
        data, addr = s.recvfrom(Config.DATAGRAM_MAX)
        s.sendto(data, addr)


def echo_stream(conn):
    """Echo one accepted stream until the peer closes it."""
    with conn:
        while True:
            data = conn.recv(Config.STREAM_CHUNK)
            if not data:
                return
            conn.sendall(data)


def serve_tcp(port):
    """Accept streams forever, one echo thread each."""
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((Config.HOST, port))
    s.listen(Config.BACKLOG)
    while True:
        conn, _ = s.accept()
        threading.Thread(target=echo_stream, args=(conn,), daemon=True).start()


def main():
    if len(sys.argv) != 2 or not sys.argv[1].isdigit():
        print(__doc__)
        return 2
    port = int(sys.argv[1])
    try:
        threading.Thread(target=serve_udp, args=(port,), daemon=True).start()
        serve_tcp(port)
    except OSError as exc:
        print("test_net_fixture: %s" % exc, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
