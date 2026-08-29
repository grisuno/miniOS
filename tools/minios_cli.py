#!/usr/bin/env python3
"""minios_cli.py — drive MiniOS through the MCP bridge, not by hand.

Starts mcp/minios_mcp.py (which owns the QEMU child and the serial console)
over stdio JSON-RPC and executes a sequence of actions in one session, then
powers the machine off. This is the hammer the minios skill wants: never
boot QEMU by hand; every shell interaction goes through the bridge.

Usage: python3 tools/minios_cli.py ACTION [ARG] [ACTION [ARG] ...]

Actions:
  boot             boot the image, wait for the shell prompt
  status           {booted, pid, log_bytes}
  send LINE        send one shell line, wait for the next prompt, print output
  cat PATH         print a ramdisk file
  snapshot         print the unconsumed console tail
  expect MARKER    wait for a marker; print matched: true/false
  write PATH       send lines from stdin through minios_write
  poweroff         power off and assert QEMU exit

Example: python3 tools/minios_cli.py boot send "help" send "ls etc/" poweroff
"""
import json
import os
import select
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
MCP = os.path.join(HERE, "..", "mcp", "minios_mcp.py")
IMAGE = os.path.join(HERE, "..", "os.img")
PIDFILE = os.path.join("/tmp/opencode", "minios_cli.pid")
TMO = 120.0


class Client:
    def __init__(self):
        env = dict(os.environ)
        env["MINIOS_IMAGE"] = IMAGE
        env["MINIOS_PIDFILE"] = PIDFILE
        env["MINIOS_TMO_PROMPT"] = "120000"
        env["MINIOS_TMO_BOOT"] = "120000"
        self.proc = subprocess.Popen(
            [sys.executable, MCP],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            env=env,
            text=True,
            bufsize=1,
        )
        self.next_id = 0

    def request(self, method, params=None):
        msg = {"jsonrpc": "2.0", "id": self.next_id, "method": method}
        if params is not None:
            msg["params"] = params
        self.next_id += 1
        self.proc.stdin.write(json.dumps(msg) + "\n")
        self.proc.stdin.flush()
        deadline = time.monotonic() + TMO
        while True:
            r, _, _ = select.select([self.proc.stdout], [], [], 1.0)
            if r:
                line = self.proc.stdout.readline()
                if not line:
                    raise RuntimeError("mcp server exited")
                resp = json.loads(line)
                if resp.get("id") != msg["id"]:
                    continue
                return resp
            if time.monotonic() > deadline:
                raise TimeoutError("no response for %r" % msg)

    def tool(self, name, params=None):
        r = self.request("tools/call", {"name": name, "arguments": params or {}})
        if "error" in r:
            raise AssertionError("rpc error: %r" % r)
        res = r["result"]
        text = res.get("content", [{}])[0].get("text", "")
        if res.get("isError"):
            raise AssertionError("tool error: %s" % text)
        return json.loads(text)

    def close(self):
        if self.proc.poll() is None:
            try:
                self.proc.stdin.close()
            except Exception:
                pass
            self.proc.terminate()
            try:
                self.proc.wait(timeout=5)
            except Exception:
                self.proc.kill()


def main():
    args = sys.argv[1:]
    if not args:
        print(__doc__)
        return 1
    c = Client()
    try:
        i = 0
        while i < len(args):
            a = args[i]
            if a == "boot":
                print(json.dumps(c.tool("minios_boot")))
            elif a == "status":
                print(json.dumps(c.tool("minios_status")))
            elif a == "send":
                i += 1
                line = args[i]
                print(c.tool("minios_send", {"line": line}))
            elif a == "cat":
                i += 1
                print(c.tool("minios_cat", {"path": args[i]}))
            elif a == "snapshot":
                print(c.tool("minios_snapshot"))
            elif a == "expect":
                i += 1
                print(json.dumps(c.tool("minios_expect", {"marker": args[i]})))
            elif a == "write":
                i += 1
                path = args[i]
                content = sys.stdin.read()
                print(c.tool("minios_write", {"path": path, "content": content}))
            elif a == "poweroff":
                print(json.dumps(c.tool("minios_poweroff")))
            else:
                print("unknown action: %s" % a, file=sys.stderr)
                return 1
            i += 1
    finally:
        c.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())