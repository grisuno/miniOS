"""MiniOS addon marketplace (lazyaddons-style).

Addons are YAML files that say where a program's source lives on GitHub and
how it is built *inside* the OS. This module parses that YAML with a strict
stdlib-only subset parser (no PyYAML) and installs addons into a running
MiniOS session: clone the repo, upload each source through the editor in
bounded chunks, reassemble with `cat`, build and verify inside the OS.

The host shell is never invoked; the only commands run are the addon's own
build/verify lines, driven line by line through the MiniOS shell.
"""

import json
import os
import re
import shutil
import subprocess
import tempfile
import time

ADDON_MAX_NAME = 32
ADDON_MAX_DESC = 512
ADDON_MAX_ITEMS = 32
ADDON_LINE_MAX = 200

ADDON_PATH_CHARS = frozenset(
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._/-"
)

ADDON_KEYS = frozenset(["name", "description", "author", "version", "install"])
ADDON_INSTALL_KEYS = frozenset(["repo_url", "files", "build", "verify"])

ADDON_REGISTRY_PATH = "var/lib/addons.txt"

ADDON_TMO_CLONE_S = 120
ADDON_TMO_SHELL_MS = 60000

ADDON_CHUNK_LINES = 511
ADDON_CHUNK_LINE_MAX = 127


class AddonError(Exception):
    """Expected marketplace failure, reported to the client as isError."""

    pass


def _clean(s):
    return s.replace("\t", "    ")


def _unquote(v):
    v = v.strip()
    if len(v) >= 2 and v[0] == v[-1] and v[0] in "\"'":
        return v[1:-1]
    return v


def parse_addon_yaml(text):
    """Parse the strict YAML subset. Returns the addon dict.

    Grammar: flat `key: value` lines; `install:` opens an indented block
    with `repo_url:`, a `files:` list of `- src:`/`dst:` pairs, and
    `build:` / `verify:` lists of `- ...` command lines (`verify` items
    may carry a nested `exit_code:`). Everything else is a parse error
    with its line number.
    """

    def fail(lineno, why):
        raise AddonError("addon yaml line %d: %s" % (lineno, why))

    addon = {}
    install = {}
    section = None
    key = None
    pending_file = None
    pending_verify = None

    for lineno, raw in enumerate(text.split("\n"), 1):
        line = _clean(raw.rstrip("\r"))
        if not line.strip() or line.strip().startswith("#"):
            continue
        if not line.startswith(" ") and section is not None:
            section = None
            key = None
            pending_file = None
            pending_verify = None
        if section is None:
            if not line or line[0] == " ":
                fail(lineno, "unexpected indentation")
            if ":" not in line:
                fail(lineno, "expected 'key: value'")
            k, _, v = line.partition(":")
            k = k.strip()
            v = _unquote(v)
            if k not in ADDON_KEYS:
                fail(lineno, "unknown key %r" % k)
            if k == "install":
                if v:
                    fail(lineno, "install takes a block, not a value")
                addon["install"] = {}
                install = addon["install"]
                section = "install"
            else:
                addon[k] = v
            continue
        if line.startswith("  ") and not line.startswith("   "):
            body = line[2:]
            if ":" in body and body.split(":", 1)[0].strip() in ADDON_INSTALL_KEYS:
                k, _, v = body.partition(":")
                k = k.strip()
                v = _unquote(v)
                if k in ("files", "build", "verify"):
                    if v == "[]":
                        v = ""
                    if v:
                        fail(lineno, "%s takes a list, not a value" % k)
                    install.setdefault(k, [])
                    key = k
                    pending_file = None
                    pending_verify = None
                else:
                    install[k] = v
                    key = None
                    pending_file = None
                    pending_verify = None
                continue
            fail(lineno, "unknown install key in %r" % body)
        if line.startswith("    ") and not line.startswith("     "):
            body = line[4:]
            if key == "files":
                if body.startswith("- "):
                    pending_file = {}
                    install["files"].append(pending_file)
                    body = body[2:]
                if pending_file is None:
                    fail(lineno, "expected '- src:'")
                if body.startswith("src:") or body.startswith("dst:"):
                    k, _, v = body.partition(":")
                    pending_file[k] = v.strip()
                else:
                    fail(lineno, "file entries take 'src:' and 'dst:'")
                continue
            if key == "build":
                if not body.startswith("- "):
                    fail(lineno, "build entries start with '-'")
                install["build"].append(body[2:].strip())
                continue
            if key == "verify":
                if body.startswith("- "):
                    pending_verify = {}
                    install["verify"].append(pending_verify)
                    body = body[2:]
                if pending_verify is None:
                    fail(lineno, "expected '- line:'")
                if body.startswith("line:") or body.startswith("exit_code:"):
                    k, _, v = body.partition(":")
                    pending_verify[k] = v.strip()
                else:
                    fail(lineno, "verify entries take 'line:' and 'exit_code:'")
                continue
            fail(lineno, "list items must follow files:, build: or verify:")
        if line.startswith("      ") and not line.startswith("       "):
            body = line[6:]
            if key == "files":
                if pending_file is None:
                    fail(lineno, "continuation without '- src:'")
                if body.startswith("src:") or body.startswith("dst:"):
                    k, _, v = body.partition(":")
                    pending_file[k] = v.strip()
                else:
                    fail(lineno, "file entries take 'src:' and 'dst:'")
                continue
            if key == "verify":
                if pending_verify is None:
                    fail(lineno, "continuation without '- line:'")
                if body.startswith("line:") or body.startswith("exit_code:"):
                    k, _, v = body.partition(":")
                    pending_verify[k] = v.strip()
                else:
                    fail(lineno, "verify entries take 'line:' and 'exit_code:'")
                continue
            fail(lineno, "continuation not allowed here")
        fail(lineno, "install entries are indented two or four spaces")

    return addon


def validate_addon(addon, source):
    """Check bounds and character sets. Raises AddonError."""

    name = addon.get("name")
    if not isinstance(name, str) or not name:
        raise AddonError("%s: name is required" % source)
    if len(name) > ADDON_MAX_NAME:
        raise AddonError("%s: name longer than %d" % (source, ADDON_MAX_NAME))
    for ch in name:
        if not (ch.isalnum() or ch in "._-"):
            raise AddonError("%s: name character not allowed: %r" % (source, ch))
    for k in ("description", "author", "version"):
        v = addon.get(k, "")
        if not isinstance(v, str) or len(v) > ADDON_MAX_DESC:
            raise AddonError("%s: %s missing or too long" % (source, k))

    install = addon.get("install")
    if not isinstance(install, dict):
        raise AddonError("%s: install block is required" % source)
    repo_url = install.get("repo_url")
    if not isinstance(repo_url, str) or len(repo_url) > ADDON_MAX_DESC or not repo_url:
        raise AddonError("%s: repo_url is required and bounded" % source)
    if "\n" in repo_url or "\r" in repo_url:
        raise AddonError("%s: repo_url must be one line" % source)

    files = install.get("files", [])
    if not isinstance(files, list) or not files or len(files) > ADDON_MAX_ITEMS:
        raise AddonError("%s: files must be a list of 1..%d entries" % (source, ADDON_MAX_ITEMS))
    for entry in files:
        src = entry.get("src")
        dst = entry.get("dst")
        if not isinstance(src, str) or not src or os.path.isabs(src) or ".." in src.split("/"):
            raise AddonError("%s: bad src %r" % (source, src))
        problem = validate_addon_path(dst)
        if problem:
            raise AddonError("%s: bad dst %r: %s" % (source, dst, problem))

    build = install.get("build", [])
    if not isinstance(build, list) or len(build) > ADDON_MAX_ITEMS:
        raise AddonError("%s: build must be a list of at most %d lines" % (source, ADDON_MAX_ITEMS))
    verify = install.get("verify", [])
    if not isinstance(verify, list) or len(verify) > ADDON_MAX_ITEMS:
        raise AddonError("%s: verify must be a list of at most %d lines" % (source, ADDON_MAX_ITEMS))
    for line in build:
        problem = validate_shell_line(line)
        if problem:
            raise AddonError("%s: build line: %s" % (source, problem))
    for entry in verify:
        line = entry.get("line")
        problem = validate_shell_line(line)
        if problem:
            raise AddonError("%s: verify line: %s" % (source, problem))
        code = entry.get("exit_code")
        if code is not None:
            try:
                entry["exit_code"] = int(code)
            except (TypeError, ValueError):
                raise AddonError("%s: exit_code must be an integer" % source)
    return addon


def validate_addon_path(path):
    """dst paths live on the ramdisk: relative, no '..', bounded charset."""
    if not isinstance(path, str):
        return "path must be a string"
    if not path or len(path) > 32:
        return "path length must be 1..32"
    if path.startswith("/") or ".." in path:
        return "path must be relative and must not contain '..'"
    for ch in path:
        if ch not in ADDON_PATH_CHARS:
            return "path character not allowed: %r" % ch
    return None


def validate_shell_line(line):
    """Build/verify lines are single printable-ASCII shell commands."""
    if not isinstance(line, str) or not line.strip():
        return "line must be a non-empty string"
    if "\n" in line or "\r" in line:
        return "line must not contain newlines"
    if len(line) > ADDON_LINE_MAX:
        return "line longer than %d characters" % ADDON_LINE_MAX
    for ch in line:
        if ord(ch) < 32 or ord(ch) > 126:
            return "line character not allowed: U+%04X" % ord(ch)
    return None


def load_addons_dir(addons_dir):
    """Load every addon yaml; each entry is a dict or an error string."""
    entries = []
    try:
        names = sorted(os.listdir(addons_dir))
    except OSError:
        return entries
    for name in names:
        if not name.endswith(".yaml"):
            continue
        path = os.path.join(addons_dir, name)
        try:
            with open(path, "r") as f:
                text = f.read()
            addon = validate_addon(parse_addon_yaml(text), name)
            addon["file"] = name
            entries.append(addon)
        except AddonError as exc:
            entries.append({"name": name, "error": str(exc)})
        except OSError:
            continue
    return entries


def split_for_editor(text):
    """Split a source into editor-sized chunks. Raises AddonError."""
    if not isinstance(text, str):
        raise AddonError("source is not text")
    for ch in text:
        code = ord(ch)
        if ch == "\n":
            continue
        if code < 32 or code > 126:
            raise AddonError("source character not allowed: U+%04X" % code)
    lines = text.split("\n")
    if lines and lines[-1] == "":
        lines.pop()
    for line in lines:
        if len(line) > ADDON_CHUNK_LINE_MAX:
            raise AddonError(
                "source line of %d chars cannot cross the kernel readline (%d)"
                % (len(line), ADDON_CHUNK_LINE_MAX)
            )
    chunks = []
    for start in range(0, len(lines), ADDON_CHUNK_LINES):
        chunks.append("\n".join(lines[start:start + ADDON_CHUNK_LINES]) + "\n")
    return chunks


def exit_code_of(text):
    match = re.search(r"exit code: (-?\d+)", text or "")
    return int(match.group(1)) if match else None


class AddonState:
    """Host-side record of installed addons (system temp dir)."""

    def __init__(self, path):
        self.path = path

    def load(self):
        try:
            with open(self.path, "r") as f:
                data = json.load(f)
            if not isinstance(data, dict) or not isinstance(data.get("addons"), dict):
                return {}
            return data["addons"]
        except (OSError, ValueError):
            return {}

    def save(self, addons):
        data = {"addons": addons}
        tmp = self.path + ".tmp"
        with open(tmp, "w") as f:
            json.dump(data, f)
        os.replace(tmp, self.path)


def install_addon(session, addon, cfg):
    """Install one validated addon into the booted MiniOS session.

    Failure at any step raises AddonError; upload parts are removed and
    nothing is recorded, so a half-installed package is never reported.
    """
    git = cfg.get("git", "git")
    timeout_ms = cfg.get("timeout_ms")
    state_file = cfg.get("state_file")
    name = addon["name"]
    version = addon.get("version", "")
    install = addon["install"]

    if not session.booted():
        session.boot(timeout_ms)

    workdir = tempfile.mkdtemp(prefix="minios_addon_")
    parts = []
    try:
        repo_dir = os.path.join(workdir, "repo")
        proc = subprocess.run(
            [git, "clone", "--depth", "1", install["repo_url"], repo_dir],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=ADDON_TMO_CLONE_S,
        )
        if proc.returncode != 0:
            raise AddonError("git clone failed: %s" % proc.stdout.decode("latin-1", "replace")[:400])

        for entry in install["files"]:
            src_path = os.path.join(repo_dir, entry["src"].replace("/", os.sep))
            try:
                with open(src_path, "r") as f:
                    source = f.read()
            except OSError as exc:
                raise AddonError("cannot read source %s: %s" % (entry["src"], exc))
            chunks = split_for_editor(source)
            entry_parts = []
            for idx, chunk in enumerate(chunks):
                part = "%s.part%d" % (entry["dst"], idx)
                session.write(part, chunk)
                parts.append(part)
                entry_parts.append(part)
            # The editor never stores a trailing newline, so a part holds its
            # chunk minus the terminator; `cat` re-adds exactly one newline
            # per invocation, which restores each part and joins the chunks.
            session.send(
                "cat %s > %s" % (entry_parts[0], entry["dst"]),
                timeout_ms or ADDON_TMO_SHELL_MS,
            )
            for part in entry_parts[1:]:
                session.send(
                    "cat %s >> %s" % (part, entry["dst"]),
                    timeout_ms or ADDON_TMO_SHELL_MS,
                )
            body = session.cat_body(entry["dst"])
            expected = source.rstrip("\n")
            if body.rstrip("\n") != expected:
                raise AddonError("round-trip mismatch for %s" % entry["dst"])

        for line in install["build"]:
            out = session.send(line, timeout_ms or ADDON_TMO_SHELL_MS)["text"]
            code = exit_code_of(out)
            if code is not None and code != 0:
                raise AddonError("build line %r failed with exit code %d" % (line, code))

        for entry in install["verify"]:
            out = session.send(entry["line"], timeout_ms or ADDON_TMO_SHELL_MS)["text"]
            code = exit_code_of(out)
            if code is None:
                raise AddonError("verify line %r produced no exit code" % entry["line"])
            if "exit_code" in entry and code != entry["exit_code"]:
                raise AddonError(
                    "verify line %r: expected exit code %d, got %d"
                    % (entry["line"], entry["exit_code"], code)
                )

        registry = session.cat_body(ADDON_REGISTRY_PATH, missing_ok=True)
        lines = [ln for ln in registry.split("\n") if ln.strip()]
        found = False
        rebuilt = []
        for ln in lines:
            fields = ln.split()
            if fields and fields[0] == name:
                found = True
                rebuilt.append("%s %s" % (name, version))
            else:
                rebuilt.append(ln)
        if not found:
            rebuilt.append("%s %s" % (name, version))
        session.write(ADDON_REGISTRY_PATH, "\n".join(rebuilt) + "\n")

        state = AddonState(state_file)
        addons = state.load()
        addons[name] = {"version": version, "installed_at": int(time.time())}
        state.save(addons)

        session._cleanup_parts(parts)
        parts = []
        return {
            "name": name,
            "version": version,
            "registry": ADDON_REGISTRY_PATH,
            "files": [entry["dst"] for entry in install["files"]],
            "build": install["build"],
            "verify": install["verify"],
        }
    except AddonError:
        raise
    finally:
        if parts:
            session._cleanup_parts(parts)
        shutil.rmtree(workdir, ignore_errors=True)
