#!/usr/bin/env python3
"""Debug driver: boot MiniOS through the MCP bridge and run freedom."""
import json
import os
import select
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
TMO = 120.0


class Client:
    def __init__(self):
        env = dict(os.environ)
        env["MINIOS_IMAGE"] = os.path.join(os.path.dirname(HERE), "os.img")
        env["MINIOS_PIDFILE"] = "/tmp/opencode/dbg/qemu.pid"
        env["MINIOS_ADDON_STATE"] = "/tmp/opencode/dbg/state.json"
        self.proc = subprocess.Popen(
            [sys.executable, os.path.join(HERE, "minios_mcp.py")],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, env=env, text=True, bufsize=1)
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
                resp = json.loads(line)
                if resp.get("id") == msg["id"]:
                    return resp
            if time.monotonic() > deadline:
                raise TimeoutError("no response for %r" % msg)

    def tool(self, name, params=None):
        r = self.request("tools/call", {"name": name, "arguments": params or {}})
        res = r["result"]
        text = res.get("content", [{}])[0].get("text", "")
        if res.get("isError"):
            raise AssertionError("tool error: %s" % text)
        return json.loads(text)

    def close(self):
        if self.proc.poll() is None:
            self.proc.stdin.close()
            self.proc.terminate()
            try:
                self.proc.wait(timeout=10)
            except subprocess.TimeoutExpired:
                self.proc.kill()


def main():
    c = Client()
    try:
        r = c.request("initialize", {"protocolVersion": "2024-11-05"})
        print("init ok")
        r = c.tool("minios_boot", {})
        print("booted:", r.get("booted"))
        r = c.tool("minios_send", {"line": "run bin/freedom --dump-css http://10.0.2.2:8911/styled"})
        print("---- dump-css ----")
        print(r.get("text", ""))
        r = c.tool("minios_send", {"line": "run bin/freedom --dump-dom http://10.0.2.2:8911/styled"})
        print("---- dump-dom ----")
        print(r.get("text", ""))
        r = c.tool("minios_send", {"line": "run bin/freedom --nosuchflag http://10.0.2.2:8911/styled"})
        print("---- unknown flag ----")
        print(r.get("text", ""))
        c.tool("minios_poweroff", {})
        print("powered off")
    finally:
        c.close()


if __name__ == "__main__":
    main()
