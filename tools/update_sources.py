#!/usr/bin/env python3
"""Update the sibling source checkouts MiniOS builds against.

MiniOS is built from this repository plus one checkout per external source:
the toolchain trio (miniGCC, ld, cvm), the browser (FreeDom), the
interpreters (micropython, cpython, lua), the UI and audio libraries (nuklear,
nuked-opl3) and the reference sources (raycastlib, quake2generic, the
gameboy recompiler). This tool refreshes any subset of them in place.

Safety contract (never violated):

- Local work is never discarded. A dirty worktree is reported and skipped,
  never reset, never stashed, never force-updated.
- History is never rewritten and local commits are never dropped. A checkout
  that carries local commits is merged with the upstream tip; a merge that
  conflicts is aborted and reported, so the checkout stays clean.
- Pinned checkouts stay pinned. A checkout bound to a release tag is
  verified against that tag and restored to it when it drifted.
- Every update records the pre-update revision, so `make update-rollback`
  can put the fleet back exactly where it was.

Usage:
    python3 tools/update_sources.py [options] [NAME ...]

    With no NAME every managed checkout is updated. With one or more NAMEs
    (or --only NAME) only those checkouts are touched.

Options:
    --status         report the state of every checkout, no network access
    --list           list the managed checkouts and exit
    --dry-run        report what would change, touch nothing
    --no-fetch       do not contact the network, only report what is behind
    --strategy MODE  how a diverged branch is reconciled: merge (default),
                     rebase or ff (report only, never touch the branch)
    --rollback       restore the revisions recorded by the last update
    --repo NAME=DIR  override the checkout path of NAME
    --repo NAME=URL  override the origin URL of NAME
    --snapshot PATH  snapshot file (default build/sources-snapshot.json)
    --git PATH       git binary to use (default git)

Output:
    One line per checkout: state, path, revision and a short detail. The
    state is one of updated, current, pinned, repinned, skipped, diverged,
    conflict, absent, not-a-clone, would-update or failed.

Exit codes:
    0  every selected checkout is up to date or was updated
    1  at least one checkout failed to update (the others still ran)
    2  usage error (unknown repository name)
"""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

DEFAULT_SNAPSHOT = "build/sources-snapshot.json"

MODE_TRACK = "track"
MODE_PINNED = "pinned"
MODE_REFERENCE = "reference"

STRATEGY_FF = "ff"
STRATEGY_MERGE = "merge"
STRATEGY_REBASE = "rebase"

STRATEGIES = (STRATEGY_FF, STRATEGY_MERGE, STRATEGY_REBASE)

STATE_UPDATED = "updated"
STATE_CURRENT = "current"
STATE_PINNED = "pinned"
STATE_REPINNED = "repinned"
STATE_SKIPPED = "skipped"
STATE_DIVERGED = "diverged"
STATE_CONFLICT = "conflict"
STATE_ABSENT = "absent"
STATE_NOT_A_CLONE = "not-a-clone"
STATE_WOULD_UPDATE = "would-update"
STATE_FAILED = "failed"

STATE_WIDTH = 13

FETCH_TIMEOUT_SECONDS = 600
DEEPEN_STEP_COMMITS = 50
MAX_DEEPEN_STEPS = 8


@dataclass(frozen=True)
class Repo:
    """A managed external checkout."""

    name: str
    url: str
    default_dir: str
    mode: str
    ref: str | None = None
    submodules: tuple[str, ...] = ()
    summary: str = ""


REPOS: tuple[Repo, ...] = (
    Repo(
        "minigcc",
        "https://github.com/grisuno/miniGCC",
        "../miniGCC",
        MODE_TRACK,
        summary="C compiler (C to x86-64 assembly)",
    ),
    Repo(
        "ld",
        "https://github.com/grisuno/ld",
        "../ld",
        MODE_TRACK,
        summary="assembler and linker (assembly to ELF or CVM)",
    ),
    Repo(
        "cvm",
        "https://github.com/grisuno/cvm",
        "../cvm",
        MODE_TRACK,
        summary="CVM v2 bytecode interpreter",
    ),
    Repo(
        "freedom",
        "https://github.com/grisuno/FreeDom",
        "../FreeDom",
        MODE_TRACK,
        summary="browser engine and GUI (freedom, freedom-ui)",
    ),
    Repo(
        "micropython",
        "https://github.com/micropython/micropython",
        "../micropython",
        MODE_PINNED,
        ref="v1.28.0",
        submodules=("lib/micropython-lib",),
        summary="MicroPython interpreter (pinned release)",
    ),
    Repo(
        "cpython",
        "https://github.com/python/cpython",
        "../cpython",
        MODE_PINNED,
        ref="v3.12.11",
        summary="CPython 3.12 interpreter (pinned release)",
    ),
    Repo(
        "lua",
        "https://github.com/lua/lua",
        "../lua",
        MODE_PINNED,
        ref="v5.4.7",
        summary="Lua 5.4 interpreter (pinned release)",
    ),
    Repo(
        "nuklear",
        "https://github.com/Immediate-Mode-UI/Nuklear",
        "../nuklear",
        MODE_TRACK,
        summary="immediate-mode GUI header (doomedit, freedom-ui)",
    ),
    Repo(
        "nuked-opl3",
        "https://github.com/nukeykt/Nuked-OPL3",
        "../nuked-opl3",
        MODE_TRACK,
        summary="OPL3 FM emulator (piano, doomedit)",
    ),
    Repo(
        "raycastlib",
        "https://gitlab.com/drummyfish/raycastlib.git",
        "../raycastlib",
        MODE_REFERENCE,
        summary="raycaster reference (doomedit DDA preview)",
    ),
    Repo(
        "quake2",
        "https://github.com/ozkl/quake2generic",
        "progs/quake2generic/quake2generic",
        MODE_REFERENCE,
        summary="Quake 2 upstream (port sources)",
    ),
    Repo(
        "pokemon",
        "https://github.com/arcanite24/gb-recompiled.git",
        "progs/pokemon/upstream",
        MODE_REFERENCE,
        summary="gameboy recompiler upstream (optional)",
    ),
)

REPOS_BY_NAME = {repo.name: repo for repo in REPOS}


@dataclass
class GitResult:
    """Outcome of one git invocation."""

    returncode: int
    stdout: str
    stderr: str

    @property
    def ok(self) -> bool:
        return self.returncode == 0


@dataclass
class Outcome:
    """Result of handling one checkout."""

    name: str
    state: str
    path: str
    before: str = ""
    after: str = ""
    branch: str = ""
    detail: str = ""

    @property
    def changed(self) -> bool:
        return self.state in (STATE_UPDATED, STATE_REPINNED)


class GitError(RuntimeError):
    """Raised when git fails in a way the caller cannot recover from."""


def run_git(git: str, cwd: Path, *args: str) -> GitResult:
    """Run git in a directory and capture its output."""
    try:
        proc = subprocess.run(
            [git, "-C", str(cwd), *args],
            capture_output=True,
            text=True,
            check=False,
            timeout=FETCH_TIMEOUT_SECONDS,
        )
    except subprocess.TimeoutExpired:
        return GitResult(124, "", f"git timed out after {FETCH_TIMEOUT_SECONDS}s")
    except OSError as exc:
        return GitResult(127, "", str(exc))
    return GitResult(proc.returncode, proc.stdout.strip(), proc.stderr.strip())


def git_out(git: str, cwd: Path, *args: str) -> str:
    """Run git and return stdout, or the empty string on failure."""
    result = run_git(git, cwd, *args)
    if not result.ok:
        return ""
    return result.stdout


def head_sha(git: str, path: Path) -> str:
    """Return the checked-out revision, or the empty string."""
    return git_out(git, path, "rev-parse", "HEAD")


def short_sha(sha: str) -> str:
    """Shorten a revision for display."""
    return sha[:7] if sha else "-"


def current_branch(git: str, path: Path) -> str:
    """Return the checked-out branch name, empty when detached."""
    return git_out(git, path, "symbolic-ref", "--short", "-q", "HEAD")


def is_dirty(git: str, path: Path) -> bool:
    """Report whether the worktree carries uncommitted changes."""
    return bool(git_out(git, path, "status", "--porcelain"))


def is_shallow(git: str, path: Path) -> bool:
    """Report whether the checkout is a shallow clone."""
    return git_out(git, path, "rev-parse", "--is-shallow-repository") == "true"


def resolve_path(directory: str) -> Path:
    """Resolve a checkout directory against the repository root."""
    candidate = Path(directory)
    if candidate.is_absolute():
        return candidate
    return (REPO_ROOT / candidate).resolve()


def fetch_upstream(git: str, path: Path, branch: str, shallow_depth: int | None) -> GitResult:
    """Fetch the upstream branch, optionally with a bounded depth."""
    args = ["fetch", "--prune", "--tags"]
    if shallow_depth is not None:
        args += ["--depth", str(shallow_depth)]
    if branch:
        args += ["origin", branch]
    else:
        args += ["origin"]
    return run_git(git, path, *args)


def deepen_upstream(git: str, path: Path, branch: str, commits: int) -> GitResult:
    """Deepen a shallow checkout so a fast-forward becomes provable."""
    args = ["fetch", "--deepen", str(commits)]
    if branch:
        args += ["origin", branch]
    else:
        args += ["origin"]
    return run_git(git, path, *args)


def upstream_target(git: str, path: Path, branch: str) -> str:
    """Return the revision the upstream branch points at."""
    if branch:
        candidate = git_out(git, path, "rev-parse", "--verify", "--quiet", f"refs/remotes/origin/{branch}^{{commit}}")
        if candidate:
            return candidate
    return git_out(git, path, "rev-parse", "--verify", "--quiet", "FETCH_HEAD^{commit}")


def ahead_behind(git: str, path: Path, branch: str) -> tuple[int, int]:
    """Return the (ahead, behind) commit counts against the upstream branch."""
    if not branch:
        return (0, 0)
    counts = git_out(git, path, "rev-list", "--left-right", "--count", f"HEAD...origin/{branch}")
    parts = counts.split()
    if len(parts) != 2:
        return (0, 0)
    try:
        return (int(parts[0]), int(parts[1]))
    except ValueError:
        return (0, 0)


def fast_forward(git: str, path: Path, target: str) -> GitResult:
    """Merge an upstream revision, refusing anything but a fast-forward."""
    return run_git(git, path, "merge", "--ff-only", target)


def reconcile(git: str, path: Path, target: str, strategy: str) -> GitResult:
    """Integrate an upstream revision into a branch that carries local commits."""
    if strategy == STRATEGY_REBASE:
        return run_git(git, path, "rebase", target)
    return run_git(git, path, "merge", "--no-edit", target)


def abort_reconcile(git: str, path: Path, strategy: str) -> None:
    """Undo a failed reconciliation so the checkout stays clean."""
    if strategy == STRATEGY_REBASE:
        run_git(git, path, "rebase", "--abort")
        return
    run_git(git, path, "merge", "--abort")


def conflicted_files(git: str, path: Path) -> list[str]:
    """List the files a failed reconciliation left unmerged."""
    listing = git_out(git, path, "diff", "--name-only", "--diff-filter=U")
    return [name for name in listing.splitlines() if name]


def update_submodules(git: str, path: Path, submodules: tuple[str, ...]) -> str:
    """Initialize and refresh the submodules of a checkout."""
    if not submodules:
        return ""
    result = run_git(git, path, "submodule", "update", "--init", *submodules)
    if not result.ok:
        return result.stderr or "submodule update failed"
    return ""


def handle_tracked(
    git: str,
    repo: Repo,
    path: Path,
    dry_run: bool,
    fetch_enabled: bool,
    strategy: str,
) -> Outcome:
    """Bring a tracked checkout to the upstream tip, keeping local commits."""
    before = head_sha(git, path)
    branch = current_branch(git, path)
    if is_dirty(git, path):
        return Outcome(repo.name, STATE_SKIPPED, str(path), before, before, branch, "local changes")

    if fetch_enabled:
        fetched = fetch_upstream(git, path, branch, None)
        if not fetched.ok:
            return Outcome(repo.name, STATE_FAILED, str(path), before, before, branch, fetched.stderr or "fetch failed")

    target = upstream_target(git, path, branch)
    if not target:
        return Outcome(repo.name, STATE_FAILED, str(path), before, before, branch, "no upstream revision")

    if before == target:
        return Outcome(repo.name, STATE_CURRENT, str(path), before, before, branch, "up to date")

    ahead, behind = ahead_behind(git, path, branch)

    if dry_run:
        if ahead and behind:
            detail = f"would merge: {behind} upstream commit(s), {ahead} local commit(s) kept"
        elif ahead:
            detail = f"{ahead} local commit(s) not published upstream"
        else:
            detail = f"would fast-forward {behind} commit(s)"
        return Outcome(repo.name, STATE_WOULD_UPDATE, str(path), before, target, branch, detail)

    merged = fast_forward(git, path, target)
    if not merged.ok and is_shallow(git, path):
        for _ in range(MAX_DEEPEN_STEPS):
            deepened = deepen_upstream(git, path, branch, DEEPEN_STEP_COMMITS)
            if not deepened.ok:
                break
            merged = fast_forward(git, path, target)
            if merged.ok:
                break

    if not merged.ok:
        ahead, behind = ahead_behind(git, path, branch)
        if not (ahead and behind):
            detail = merged.stderr or "fast-forward refused"
            return Outcome(repo.name, STATE_FAILED, str(path), before, before, branch, detail)
        if strategy == STRATEGY_FF:
            detail = f"diverged: {ahead} local commit(s), {behind} upstream commit(s)"
            return Outcome(repo.name, STATE_DIVERGED, str(path), before, before, branch, detail)
        reconciled = reconcile(git, path, target, strategy)
        if not reconciled.ok:
            files = conflicted_files(git, path)
            abort_reconcile(git, path, strategy)
            where = ", ".join(files) if files else "unknown files"
            detail = f"conflict in {where}; aborted, checkout left clean"
            return Outcome(repo.name, STATE_CONFLICT, str(path), before, before, branch, detail)

    after = head_sha(git, path)
    if after == before:
        ahead, behind = ahead_behind(git, path, branch)
        detail = f"{ahead} local commit(s) ahead of upstream" if ahead else "up to date"
        return Outcome(repo.name, STATE_CURRENT, str(path), before, after, branch, detail)
    return Outcome(repo.name, STATE_UPDATED, str(path), before, after, branch, f"{short_sha(before)} -> {short_sha(after)}")


def handle_pinned(
    git: str,
    repo: Repo,
    path: Path,
    dry_run: bool,
    fetch_enabled: bool,
) -> Outcome:
    """Hold a checkout at the release tag it is pinned to."""
    before = head_sha(git, path)
    branch = current_branch(git, path)
    if not repo.ref:
        return Outcome(repo.name, STATE_FAILED, str(path), before, before, branch, "no pinned ref configured")
    if is_dirty(git, path):
        return Outcome(repo.name, STATE_SKIPPED, str(path), before, before, branch, "local changes")

    if fetch_enabled:
        fetched = run_git(git, path, "fetch", "--depth", "1", "origin", repo.ref)
        if not fetched.ok:
            return Outcome(repo.name, STATE_FAILED, str(path), before, before, branch, fetched.stderr or "fetch failed")

    pinned = git_out(git, path, "rev-parse", "--verify", "--quiet", "FETCH_HEAD^{commit}")
    if not pinned:
        return Outcome(repo.name, STATE_FAILED, str(path), before, before, branch, f"ref {repo.ref} not found")

    if before == pinned:
        detail = update_submodules(git, path, repo.submodules)
        state = STATE_PINNED
        if detail:
            state = STATE_FAILED
        return Outcome(repo.name, state, str(path), before, before, branch, detail or f"at {repo.ref}")

    if dry_run:
        return Outcome(repo.name, STATE_WOULD_UPDATE, str(path), before, pinned, branch, f"would pin {repo.ref}")

    checked_out = run_git(git, path, "checkout", "--detach", pinned)
    if not checked_out.ok:
        detail = checked_out.stderr or "checkout failed"
        return Outcome(repo.name, STATE_FAILED, str(path), before, before, branch, detail)

    after = head_sha(git, path)
    detail = update_submodules(git, path, repo.submodules)
    state = STATE_REPINNED
    if detail:
        state = STATE_FAILED
    return Outcome(repo.name, state, str(path), before, after, branch, detail or f"pinned {repo.ref}")


def handle_repo(
    git: str,
    repo: Repo,
    directory: str,
    dry_run: bool,
    fetch_enabled: bool,
    strategy: str,
) -> Outcome:
    """Dispatch one checkout to the handler its mode asks for."""
    path = resolve_path(directory)
    if not path.exists():
        return Outcome(repo.name, STATE_ABSENT, str(path), detail="run 'make sources'")
    if not (path / ".git").exists():
        return Outcome(repo.name, STATE_NOT_A_CLONE, str(path), detail="local directory, not a git clone")

    if repo.mode == MODE_PINNED:
        return handle_pinned(git, repo, path, dry_run, fetch_enabled)
    return handle_tracked(git, repo, path, dry_run, fetch_enabled, strategy)


def write_snapshot(path: Path, outcomes: list[Outcome]) -> None:
    """Record the pre-update revision of every checkout that moved."""
    moved = [item for item in outcomes if item.changed]
    if not moved:
        return
    payload = {
        "created": datetime.now(timezone.utc).isoformat(timespec="seconds"),
        "repos": {
            item.name: {
                "path": item.path,
                "before": item.before,
                "after": item.after,
                "branch": item.branch,
                "state": item.state,
            }
            for item in moved
        },
    }
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(payload, indent=2) + "\n", encoding="utf-8")


def rollback(git: str, snapshot_path: Path, directories: dict[str, str]) -> int:
    """Restore the revisions recorded by the last update."""
    if not snapshot_path.exists():
        print(f"update-rollback: no snapshot at {snapshot_path}", file=sys.stderr)
        return 1
    try:
        payload = json.loads(snapshot_path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        print(f"update-rollback: unreadable snapshot: {exc}", file=sys.stderr)
        return 1

    repos = payload.get("repos", {})
    failures = 0
    for name, entry in repos.items():
        target = entry.get("before", "")
        directory = directories.get(name, entry.get("path", ""))
        path = resolve_path(directory)
        if not target or not (path / ".git").exists():
            print(f"{name:<14} {STATE_FAILED:<13} {path} no revision to restore")
            failures += 1
            continue
        if is_dirty(git, path):
            print(f"{name:<14} {STATE_SKIPPED:<13} {path} local changes, left untouched")
            continue
        current = head_sha(git, path)
        if current == target:
            print(f"{name:<14} {STATE_CURRENT:<13} {path} already at {short_sha(target)}")
            continue
        restored = run_git(git, path, "reset", "--keep", target)
        if not restored.ok:
            print(f"{name:<14} {STATE_FAILED:<13} {path} {restored.stderr or 'reset failed'}")
            failures += 1
            continue
        print(f"{name:<14} {STATE_UPDATED:<13} {path} {short_sha(current)} -> {short_sha(target)}")
    return 1 if failures else 0


def print_status(git: str, selected: list[Repo], directories: dict[str, str]) -> None:
    """Print the revision of every managed checkout."""
    print("drift is measured against the last fetched remote ref, not the live remote")
    for repo in selected:
        path = resolve_path(directories.get(repo.name, repo.default_dir))
        if not path.exists():
            print(f"{repo.name:<14} {STATE_ABSENT:<13} {path}")
            continue
        if not (path / ".git").exists():
            print(f"{repo.name:<14} {STATE_NOT_A_CLONE:<13} {path}")
            continue
        branch = current_branch(git, path) or "detached"
        sha = head_sha(git, path)
        subject = git_out(git, path, "log", "-1", "--format=%s")
        ahead, behind = ahead_behind(git, path, current_branch(git, path))
        drift = f"ahead {ahead}, behind {behind}" if (ahead or behind) else "in sync"
        detail = f"{short_sha(sha)} {branch} {drift}"
        if subject:
            detail = f"{detail} {subject}"
        print(f"{repo.name:<14} {STATE_CURRENT:<13} {path} {detail}")


def print_outcome(outcome: Outcome) -> None:
    """Print one checkout result."""
    print(f"{outcome.name:<14} {outcome.state:<{STATE_WIDTH}} {outcome.path} {outcome.detail}".rstrip())


def select_repos(names: list[str]) -> list[Repo]:
    """Resolve the requested repository names, failing on unknown ones."""
    if not names:
        return list(REPOS)
    selected = []
    for name in names:
        repo = REPOS_BY_NAME.get(name)
        if repo is None:
            known = ", ".join(sorted(REPOS_BY_NAME))
            print(f"update: unknown repository '{name}' (known: {known})", file=sys.stderr)
            raise SystemExit(2)
        selected.append(repo)
    return selected


def parse_overrides(pairs: list[str]) -> tuple[dict[str, str], dict[str, str]]:
    """Split the --repo overrides into directory and URL maps."""
    directories: dict[str, str] = {}
    urls: dict[str, str] = {}
    for pair in pairs:
        if "=" not in pair:
            print(f"update: malformed override '{pair}' (expected NAME=VALUE)", file=sys.stderr)
            raise SystemExit(2)
        name, value = pair.split("=", 1)
        if name not in REPOS_BY_NAME:
            known = ", ".join(sorted(REPOS_BY_NAME))
            print(f"update: unknown repository '{name}' (known: {known})", file=sys.stderr)
            raise SystemExit(2)
        if value.startswith("http://") or value.startswith("https://") or value.endswith(".git"):
            urls[name] = value
        else:
            directories[name] = value
    return directories, urls


def main(argv: list[str]) -> int:
    """Run the updater and report what happened."""
    parser = argparse.ArgumentParser(
        prog="update_sources.py",
        description="Update the sibling source checkouts MiniOS builds against.",
    )
    parser.add_argument("names", nargs="*", help="repositories to update (default: all)")
    parser.add_argument("--only", action="append", default=[], metavar="NAME",
                        help="update only this repository (repeatable)")
    parser.add_argument("--status", action="store_true", help="report the state, no network")
    parser.add_argument("--list", action="store_true", help="list the managed repositories")
    parser.add_argument("--dry-run", action="store_true", help="report what would change")
    parser.add_argument("--no-fetch", action="store_true", help="do not contact the network")
    parser.add_argument("--rollback", action="store_true", help="restore the last snapshot")
    parser.add_argument("--strategy", choices=STRATEGIES, default=STRATEGY_MERGE,
                        help="how a diverged branch is reconciled (default: merge)")
    parser.add_argument("--repo", action="append", default=[], metavar="NAME=VALUE",
                        help="override the directory or the origin URL of a repository")
    parser.add_argument("--snapshot", default=DEFAULT_SNAPSHOT, help="snapshot file path")
    parser.add_argument("--git", default="git", help="git binary to use")
    args = parser.parse_args(argv)

    directories, urls = parse_overrides(args.repo)

    if args.list:
        for repo in REPOS:
            location = directories.get(repo.name, repo.default_dir)
            ref = f" @{repo.ref}" if repo.ref else ""
            print(f"{repo.name:<14} {repo.mode:<10} {location}{ref}  {repo.summary}")
        return 0

    selected = select_repos(args.names + args.only)

    for repo in selected:
        if repo.name in urls:
            repo = Repo(repo.name, urls[repo.name], repo.default_dir, repo.mode, repo.ref, repo.submodules, repo.summary)
        directories.setdefault(repo.name, repo.default_dir)

    if args.rollback:
        return rollback(args.git, resolve_path(args.snapshot), directories)

    if args.status:
        print_status(args.git, selected, directories)
        return 0

    fetch_enabled = not args.no_fetch
    outcomes: list[Outcome] = []
    for repo in selected:
        outcome = handle_repo(args.git, repo, directories[repo.name], args.dry_run, fetch_enabled, args.strategy)
        outcomes.append(outcome)
        print_outcome(outcome)

    if not args.dry_run:
        write_snapshot(resolve_path(args.snapshot), outcomes)

    failures = sum(1 for item in outcomes if item.state in (STATE_FAILED, STATE_DIVERGED, STATE_CONFLICT))
    skipped = sum(1 for item in outcomes if item.state == STATE_SKIPPED)
    changed = sum(1 for item in outcomes if item.changed)
    print(
        f"update: {changed} updated, {sum(1 for item in outcomes if item.state == STATE_CURRENT)} current, "
        f"{sum(1 for item in outcomes if item.state == STATE_PINNED)} pinned, {skipped} skipped, {failures} failed"
    )
    if changed and not args.dry_run:
        print("update: run 'make' to rebuild the image with the new sources")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
