#!/usr/bin/env python3
"""Minimal QEMU guest agent client for MiniOS.

Connects to the guest agent socket (a QEMU chardev mapped to the kernel's
COM2 agent port), sends one QGA JSON request per line, and prints the JSON
reply. Also drives the same protocol QEMU's own QMP guest-agent-command
uses, because the framing is whitespace-delimited.

Usage:
    qga_client.py <command> [arguments_json]
    qga_client.py --sock <path> <command> [arguments_json]

Examples:
    qga_client.py guest-ping
    qga_client.py guest-exec '{"path":"echo hi > /tmp/x"}'
    qga_client.py guest-file-read '{"handle":0,"count":100}'

The socket path defaults to /tmp/minios-ga.sock and can be overridden with
--sock or the MINIOS_GA_SOCK environment variable.
"""

import json
import os
import socket
import sys
import time

DEFAULT_SOCK = os.environ.get("MINIOS_GA_SOCK", "/tmp/minios-ga.sock")
CONNECT_TRIES = 40
CONNECT_DELAY = 0.25


def send_command(sock, cmd, args=None):
    req = {"execute": cmd}
    if args is not None:
        req["arguments"] = args
    line = json.dumps(req, separators=(",", ":"))
    sock.sendall((line + "\n").encode("utf-8"))


def read_reply(sock, timeout=5.0):
    """Read one newline-terminated JSON object from the agent."""
    sock.settimeout(timeout)
    buf = b""
    deadline = time.time() + timeout
    while time.time() < deadline:
        chunk = sock.recv(4096)
        if not chunk:
            break
        buf += chunk
        if b"\n" in buf:
            line, _, _ = buf.partition(b"\n")
            return line.decode("utf-8", "replace")
    raise TimeoutError("no reply from guest agent")


def connect(path):
    last = None
    for _ in range(CONNECT_TRIES):
        try:
            s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
            s.connect(path)
            return s
        except (FileNotFoundError, ConnectionRefusedError, OSError) as e:
            last = e
            try:
                s.close()
            except OSError:
                pass
            time.sleep(CONNECT_DELAY)
    raise RuntimeError(f"cannot connect to guest agent socket {path}: {last}")


def main(argv):
    sock_path = DEFAULT_SOCK
    args = []
    i = 0
    while i < len(argv):
        if argv[i] == "--sock":
            i += 1
            sock_path = argv[i]
        else:
            args.append(argv[i])
        i += 1
    if not args:
        sys.stderr.write(__doc__)
        return 1

    cmd = args[0]
    arguments = None
    if len(args) > 1:
        try:
            arguments = json.loads(args[1])
        except json.JSONDecodeError as e:
            sys.stderr.write(f"qga_client: bad arguments JSON: {e}\n")
            return 1

    s = connect(sock_path)
    try:
        send_command(s, cmd, arguments)
        reply = read_reply(s)
        sys.stdout.write(reply + "\n")
        try:
            obj = json.loads(reply)
            if "error" in obj:
                return 1
        except json.JSONDecodeError:
            pass
        return 0
    finally:
        s.close()


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
