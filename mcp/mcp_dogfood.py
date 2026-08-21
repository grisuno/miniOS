#!/usr/bin/env python3
"""Dogfood: drive minios_mcp.py over stdio JSON-RPC and install the
freedom addon from a git repo, then browse with the installed binary.

Stdlib only. Usage: python3 mcp_dogfood.py <addons-dir>
"""
import json
import os
import select
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
TMO = 240.0


class Client:
    def __init__(self, addons_dir):
        env = dict(os.environ)
        env["MINIOS_ADDONS_DIR"] = addons_dir
        env["MINIOS_IMAGE"] = os.path.join(os.path.dirname(HERE), "os.img")
        env["MINIOS_PIDFILE"] = os.path.join("/tmp/opencode/dogfood", "qemu.pid")
        env["MINIOS_ADDON_STATE"] = os.path.join("/tmp/opencode/dogfood", "state.json")
        env["MINIOS_TMO_PROMPT"] = "60000"
        env["MINIOS_TMO_BOOT"] = "60000"
        self.proc = subprocess.Popen(
            [sys.executable, os.path.join(HERE, "minios_mcp.py")],
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
                resp = json.loads(line)
                assert resp.get("id") == msg["id"], (msg, resp)
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
            self.proc.stdin.close()
            self.proc.terminate()
            try:
                self.proc.wait(timeout=10)
            except subprocess.TimeoutExpired:
                self.proc.kill()


def main():
    c = Client(sys.argv[1])
    try:
        r = c.request("initialize", {"protocolVersion": "2024-11-05"})
        print("initialize:", r["result"]["serverInfo"])

        tools = c.request("tools/list")["result"]["tools"]
        print("tools:", ", ".join(t["name"] for t in tools))

        r = c.tool("minios_boot")
        assert r["booted"], r
        print("boot: MiniOS Kernel seen")

        r = c.tool("minios_addons")
        print("addons:", [(a["name"], a.get("installed")) for a in r["addons"]])

        r = c.tool("minios_install", {"name": "freedom", "timeout_ms": 300000})
        print("install:", r["name"], "files:", r["files"])

        r = c.tool("minios_send", {"line": "freedom"})
        assert "usage: freedom" in r["text"], r
        print("freedom (no args): usage diagnostic OK")

        r = c.tool("minios_send", {"line": "freedom https://example.com"})
        assert "TLS" in r["text"], r
        print("freedom (https): TLS refusal OK")

        r = c.tool("minios_send", {"line": "freedom http://10.0.2.2:8899/docs/hostile.html"})
        assert "first block" in r["text"], r
        assert "bold & safe" in r["text"], r
        assert "evil" not in r["text"], r
        assert "freedom: 10.0.2.2 (" in r["text"], r
        print("freedom (http fetch): filtered page OK")

        r = c.tool("minios_poweroff")
        print("poweroff OK:", "powering off" in r["text"])
    finally:
        c.close()


if __name__ == "__main__":
    main()
