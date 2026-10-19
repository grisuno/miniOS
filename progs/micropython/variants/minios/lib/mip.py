"""mip.py -- MiniOS package installer (frozen module).

Minimal pip for the MiniOS MicroPython port: fetches one .py module over
HTTP (or HTTPS through the ring-3 TLS engine) and installs it into a
directory on sys.path. Frozen with the port (lib/manifest freeze), so it
is always importable.

Policy, fail closed:

- http and https only. Inside MiniOS, https runs `bin/tlsget` (the
  userspace TLS stack with pinned roots) through SYS_SPAWN and reads the
  captured response; on host CPython https raises OSError (no minios
  module), so host tests cover the http and refusal paths.
- one module per URL and the file name must be a bare identifier plus
  .py ([A-Za-z_][A-Za-z0-9_]*), so a hostile server cannot write outside
  dest (no traversal, subdirectories, percent escapes or dots).
- the download is written to <dest>/<name>.py.part and renamed on
  success: a failed fetch never leaves a half module on sys.path.
- HTTP/1.0 + Connection: close; chunked responses and mismatched
  Content-Length are refused; MAX_BODY caps the download.
- a successful install appends dest to sys.path so the module imports
  in the same session.

Usage inside MiniOS::

    import mip
    mip.install('http://host:8899/pkg.py')          # into ./lib
    mip.install('https://host/pkg.py', 'mylib')     # TLS through tlsget
    micropython -c "import mip; raise SystemExit(mip.main())" install <url>
"""

import os
import sys

DEFAULT_DEST = "lib"
HTTP_PORT_DEFAULT = 80
HTTPS_PORT_DEFAULT = 443
MAX_BODY = 262144
MAX_HEAD_BYTES = 8192
MAX_REDIRECTS = 3
READ_CHUNK = 4096
SOCKET_TIMEOUT_S = 10.0
REDIRECT_STATUS = (301, 302, 303, 307, 308)
TLSGET_PATH = "/bin/tlsget"
TLSGET_OUT = "/tmp/mip_tlsget.out"
EEXIST = 17


def parse_url(url):
    """Split an http/https URL into (scheme, host, port, path).

    Raises ValueError for any other scheme, a missing or malformed
    authority, a port outside 1..65535, or control characters in the
    host or path (request-line injection).
    """
    for scheme, default_port in (("http", HTTP_PORT_DEFAULT),
                                 ("https", HTTPS_PORT_DEFAULT)):
        prefix = scheme + "://"
        if url.startswith(prefix):
            host, port, path = _split_authority_path(
                url, url[len(prefix):], default_port
            )
            return scheme, host, port, path
    raise ValueError("unsupported URL scheme: %r" % url)


def _split_authority_path(url, rest, default_port):
    """Parse host[:port][/path] after the scheme prefix."""
    cut = rest.find("/")
    if cut < 0:
        authority, path = rest, "/"
    else:
        authority, path = rest[:cut], rest[cut:]
    colon = authority.find(":")
    if colon < 0:
        host, port_text = authority, ""
    else:
        host, port_text = authority[:colon], authority[colon + 1:]
    if not host:
        raise ValueError("missing host in URL: %r" % url)
    for ch in host:
        if ch <= " " or ch == "\x7f":
            raise ValueError("bad character in URL host: %r" % url)
    if port_text:
        if not port_text.isdigit():
            raise ValueError("bad port in URL: %r" % url)
        port = int(port_text)
        if port < 1 or port > 65535:
            raise ValueError("bad port in URL: %r" % url)
    else:
        port = default_port
    for ch in path:
        if ch <= " " or ch == "\x7f":
            raise ValueError("bad character in URL path: %r" % url)
    return host, port, path


def split_url(url):
    """Split an http URL into (host, port, path); https is refused here."""
    scheme, host, port, path = parse_url(url)
    if scheme != "http":
        raise ValueError("not an http URL: %r" % url)
    return host, port, path


def split_https_url(url):
    """Split an https URL into (host, port, path); http is refused here."""
    scheme, host, port, path = parse_url(url)
    if scheme != "https":
        raise ValueError("not an https URL: %r" % url)
    return host, port, path


def module_name(url):
    """Return the .py file name a URL installs, validating it is bare.

    The last path segment (query and fragment dropped) must be
    [A-Za-z_][A-Za-z0-9_]*.py and no path segment may be "." or "..";
    anything else raises ValueError so a hostile URL cannot escape the
    destination directory.
    """
    path = parse_url(url)[3]
    path = path.split("?")[0].split("#")[0]
    for segment in path.split("/"):
        if segment in (".", ".."):
            raise ValueError("traversal in URL path: %r" % url)
    name = path.rsplit("/", 1)[-1]
    if not name.endswith(".py"):
        raise ValueError("not a .py module URL: %r" % url)
    stem = name[:-3]
    if not _is_module_stem(stem):
        raise ValueError("invalid module name: %r" % name)
    return name


def _is_module_stem(stem):
    """True when stem is an ASCII MicroPython module identifier."""
    if not stem:
        return False
    first = stem[0]
    if not ("a" <= first <= "z" or "A" <= first <= "Z" or first == "_"):
        return False
    for ch in stem:
        if not ("a" <= ch <= "z" or "A" <= ch <= "Z" or
                "0" <= ch <= "9" or ch == "_"):
            return False
    return True


def parse_response(data):
    """Split one HTTP/1.x response into (status, headers, body).

    Headers are lowercased keys with stripped values. Fails closed:
    a missing terminator, malformed status line or header, a chunked
    transfer-encoding, or a Content-Length that disagrees with the body
    all raise ValueError.
    """
    cut = data.find(b"\r\n\r\n")
    if cut >= 0:
        head, body = data[:cut], data[cut + 4:]
    else:
        cut = data.find(b"\n\n")
        if cut < 0:
            raise ValueError("malformed HTTP response: no header terminator")
        head, body = data[:cut], data[cut + 2:]
    lines = head.replace(b"\r\n", b"\n").split(b"\n")
    status = _status_code(lines[0])
    headers = {}
    for line in lines[1:]:
        if not line:
            continue
        colon = line.find(b":")
        if colon <= 0:
            raise ValueError("malformed HTTP header: %r" % line)
        name = line[:colon].strip().lower().decode()
        value = line[colon + 1:].strip().decode()
        headers[name] = value
    if "chunked" in headers.get("transfer-encoding", "").lower():
        raise ValueError("chunked responses are not supported")
    length = headers.get("content-length")
    if length is not None:
        if not length.isdigit():
            raise ValueError("bad Content-Length: %r" % length)
        if int(length) != len(body):
            raise ValueError(
                "Content-Length %s but body is %d bytes" % (length, len(body))
            )
    return status, headers, body


def _status_code(line):
    """Extract the numeric status from an HTTP status line."""
    parts = line.split(b" ")
    if len(parts) < 2 or not parts[0].startswith(b"HTTP/"):
        raise ValueError("malformed HTTP status line: %r" % line)
    code = parts[1].decode()
    if not code.isdigit() or len(code) != 3:
        raise ValueError("malformed HTTP status line: %r" % line)
    return int(code)


def absolute_url(base, location):
    """Resolve a redirect Location against base; http and https survive.

    Absolute locations pass through unchanged (re-validated by the
    caller's next parse_url), path-absolute locations keep base's scheme
    and authority; truly relative locations raise ValueError.
    """
    scheme, host, port, _ = parse_url(base)
    if location.startswith("http://") or location.startswith("https://"):
        return location
    if not location.startswith("/"):
        raise ValueError("cannot resolve relative redirect: %r" % location)
    default_port = HTTP_PORT_DEFAULT if scheme == "http" else HTTPS_PORT_DEFAULT
    if port == default_port:
        authority = host
    else:
        authority = "%s:%d" % (host, port)
    return "%s://%s%s" % (scheme, authority, location)


def http_get(host, port, path):
    """Fetch http://host:port/path, returning the raw response bytes.

    One HTTP/1.0 request with Connection: close, read to EOF over a
    timed socket; the response is capped at MAX_BODY + MAX_HEAD_BYTES.
    """
    import socket

    if port == HTTP_PORT_DEFAULT:
        authority = host
    else:
        authority = "%s:%d" % (host, port)
    request = (
        "GET %s HTTP/1.0\r\nHost: %s\r\nUser-Agent: mip/1\r\n"
        "Connection: close\r\n\r\n" % (path, authority)
    ).encode()
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.settimeout(SOCKET_TIMEOUT_S)
        addr = socket.getaddrinfo(
            host, port, socket.AF_INET, socket.SOCK_STREAM
        )[0][-1]
        sock.connect(addr)
        sent = 0
        while sent < len(request):
            n = sock.send(request[sent:])
            if n <= 0:
                raise OSError("socket send made no progress")
            sent += n
        chunks = []
        total = 0
        while True:
            chunk = sock.recv(READ_CHUNK)
            if not chunk:
                break
            total += len(chunk)
            if total > MAX_BODY + MAX_HEAD_BYTES:
                raise ValueError(
                    "response exceeds %d bytes" % (MAX_BODY + MAX_HEAD_BYTES)
                )
            chunks.append(chunk)
    finally:
        sock.close()
    return b"".join(chunks)


def _unlink_quiet(path):
    """Best-effort remove; the following call reports the real error."""
    try:
        os.remove(path)
    except OSError:
        pass


def ensure_dir(path):
    """Create path and its parents; existing directories are fine.

    The final write reports real errors, so a mkdir refusal here is not
    fatal (the directory may already exist).
    """
    if not path or path in (".", "/"):
        return
    cur = "/" if path.startswith("/") else ""
    for part in path.split("/"):
        if not part:
            continue
        if cur and cur != "/":
            cur = cur + "/" + part
        else:
            cur = cur + part
        try:
            os.mkdir(cur)
        except OSError:
            pass


def https_get(host, port, path):
    """Fetch https://host:port/path through the ring-3 TLS engine.

    Spawns bin/tlsget (the userspace TLS stack with pinned roots, the
    same engine freedom uses) through the minios module's SYS_SPAWN and
    reads the response from the capture file. -q keeps tlsget's success
    diagnostic out of the capture, so the file holds exactly the raw
    HTTP response. This is MiniOS-only: on host CPython there is no
    minios module and OSError says so.
    """
    try:
        import minios
    except ImportError:
        raise OSError("https needs MiniOS (no TLS engine on this host)")
    _unlink_quiet(TLSGET_OUT)
    args = ["-q", host, path]
    if port != HTTPS_PORT_DEFAULT:
        args.append("%d" % port)
    try:
        rc = minios.run(TLSGET_PATH, args, TLSGET_OUT)
    except OSError as exc:
        raise OSError("tlsget spawn failed (%s)" % exc)
    if rc != 0:
        raise OSError("tlsget exit %d for %s" % (rc, host))
    try:
        with open(TLSGET_OUT, "rb") as fh:
            data = fh.read(MAX_BODY + MAX_HEAD_BYTES + 1)
    except OSError:
        raise OSError("tlsget wrote no response for %s" % host)
    if not data:
        raise OSError("tlsget produced no output for %s" % host)
    if len(data) > MAX_BODY + MAX_HEAD_BYTES:
        raise ValueError(
            "response exceeds %d bytes" % (MAX_BODY + MAX_HEAD_BYTES)
        )
    return data


def install(url, dest=DEFAULT_DEST):
    """Fetch url and write it as <dest>/<module>.py; returns the path.

    Follows up to MAX_REDIRECTS redirects across http and https;
    refuses non-200 answers, unsafe module names and chunked responses.
    The file appears atomically (write to .part, then rename) and dest
    joins sys.path so the module imports in the same session.
    """
    redirects = 0
    while True:
        scheme, host, port, path = parse_url(url)
        name = module_name(url)
        if scheme == "https":
            data = https_get(host, port, path)
        else:
            data = http_get(host, port, path)
        status, headers, body = parse_response(data)
        if status in REDIRECT_STATUS:
            location = headers.get("location")
            if not location:
                raise ValueError("redirect without Location header")
            redirects += 1
            if redirects > MAX_REDIRECTS:
                raise ValueError("too many redirects (last url %r)" % url)
            url = absolute_url(url, location)
            continue
        if status != 200:
            raise OSError("HTTP %d for %s" % (status, url))
        break
    if dest and dest != ".":
        ensure_dir(dest)
        dest_dir = dest.rstrip("/")
    else:
        dest_dir = ""
    final = (dest_dir + "/" + name) if dest_dir else name
    tmp = final + ".part"
    with open(tmp, "wb") as fh:
        fh.write(body)
    try:
        os.rename(tmp, final)
    except OSError as exc:
        # MiniFS rename refuses an existing target (EEXIST) where Linux
        # overwrites; drop the old module and retry once so reinstalling
        # works. The .part file keeps the common path atomic.
        if not (exc.args and exc.args[0] == EEXIST):
            _unlink_quiet(tmp)
            raise
        _unlink_quiet(final)
        try:
            os.rename(tmp, final)
        except OSError:
            _unlink_quiet(tmp)
            raise
    if dest_dir and dest_dir != "." and dest_dir not in sys.path:
        sys.path.append(dest_dir)
    return final


def main(argv=None):
    """CLI entry point: install <url> [dest]; returns the exit code.

    MicroPython's -c puts the code first in sys.argv and every argument
    after it next, so the shell form is::

        micropython -c "import mip; raise SystemExit(mip.main())" install <url> [dest]
    """
    if argv is None:
        argv = getattr(sys, "argv", ["mip"])
    if len(argv) >= 3 and argv[1] == "install":
        dest = argv[3] if len(argv) > 3 else DEFAULT_DEST
        print("installed", install(argv[2], dest))
        return 0
    print('usage: micropython -c "import mip; raise SystemExit(mip.main())" '
          "install <url> [dest]")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
