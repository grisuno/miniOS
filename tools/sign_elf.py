"""Sign MiniOS user binaries with Ed25519 (development key).
.
Usage:
    python3 tools/sign_elf.py [--check] [--key-id N] FILE [FILE ...]
    python3 tools/sign_elf.py [--check] [--key-id N] --walk DIR [DIR ...]
.
Inputs: ET_EXEC/ET_DYN ELF files. Other files are skipped, never
modified. Outputs: the same files with a signature note carrying one
key id byte plus the 64-byte signature, either patched into an
existing PT_NOTE/SHT_NOTE slot or appended as a new non-allocated
.note.minios.sign section. With --check nothing is written; unsigned
or badly signed images are reported and the exit status is 1.
.
Failure modes: non-ELF input skips silently; truncated headers,
missing section tables on images without a note slot, and unknown
key ids fail loudly with a non-zero exit. Signing is idempotent: an
image whose current bytes already verify under the requested key is
left untouched, so rebuilds stay mtime-stable.
.
The development seed below is a published test key for dogfood
builds only (docs/spec/kernel.md). Production images use key id 1
with a key file passed through MINIOS_SIGN_KEY.
"""

import hashlib
import os
import struct
import sys


class Config:
    """Central configuration, no magic numbers outside this class."""

    note_name = b"MiniOS"
    note_section = b".note.minios.sign"
    note_sign_type = 2
    note_align = 4
    key_dev = 0
    key_prod = 1
    sig_bytes = 64
    desc_bytes = 65
    desc_padded = 68
    note_total = 88
    pub_bytes = 32
    dev_pub_hex = "df968c9d646953eded22bab208669cb7ec1a94e32be5ebeb95b3aeacb8d7561e"
    dev_seed_label = b"minios-dev-key-v1"
    field_p = 2 ** 255 - 19
    group_l = 2 ** 252 + 27742317777372353535851937790883648493
    curve_d = (-121665 * pow(121666, 2 ** 255 - 21, 2 ** 255 - 19)) % (2 ** 255 - 19)
    e_machine_x86_64 = 62
    et_exec = 2
    et_dyn = 3
    pt_load = 1
    pt_note = 4
    sht_note = 7
    ehdr_size = 64
    phdr_size = 56
    shdr_size = 64


def sha512(data):
    """One-shot SHA-512."""
    return hashlib.sha512(data).digest()


def encodepoint_raw(x, y):
    """Encode affine (x, y) to 32 bytes."""
    return (((x & 1) << 255) | y).to_bytes(32, "little")


def edwards_add(p, q):
    """Add two extended points, all math mod field_p."""
    P = Config.field_p
    D = Config.curve_d
    x1, y1, z1, t1 = p
    x2, y2, z2, t2 = q
    a = ((y1 - x1) * (y2 - x2)) % P
    b = ((y1 + x1) * (y2 + x2)) % P
    c = (t1 * 2 * D * t2) % P
    dd = (z1 * 2 * z2) % P
    e = (b - a) % P
    f = (dd - c) % P
    g = (dd + c) % P
    h = (b + a) % P
    return ((e * f) % P, (g * h) % P, (f * g) % P, (e * h) % P)


def scalarmult(p, e):
    """Multiply extended point p by scalar e."""
    q = (0, 1, 1, 0)
    while e > 0:
        if e & 1:
            q = edwards_add(q, p)
        p = edwards_add(p, p)
        e >>= 1
    return q


def base_point():
    """Recompute the base point from y = 4/5."""
    P = Config.field_p
    y = (4 * pow(5, P - 2, P)) % P
    x2 = ((y * y - 1) * pow(Config.curve_d * y * y + 1, P - 2, P)) % P
    x = pow(x2, (P + 3) // 8, P)
    if (x * x - x2) % P != 0:
        x = (x * pow(2, (P - 1) // 4, P)) % P
    if x & 1:
        x = P - x
    return (x, y, 1, (x * y) % P)


def publickey(seed):
    """Derive the 32-byte public key from a 32-byte seed."""
    h = sha512(seed)
    a = 2 ** 254 + sum(2 ** i * ((h[i // 8] >> (i % 8)) & 1) for i in range(3, 254))
    x, y, z, _t = scalarmult(base_point(), a)
    return encodepoint_raw((x * pow(z, Config.field_p - 2, Config.field_p)) % Config.field_p,
                           (y * pow(z, Config.field_p - 2, Config.field_p)) % Config.field_p)


def sign_digest(digest, seed):
    """Sign a 64-byte canonical digest, returning 64 signature bytes."""
    h = sha512(seed)
    a = 2 ** 254 + sum(2 ** i * ((h[i // 8] >> (i % 8)) & 1) for i in range(3, 254))
    r = int.from_bytes(sha512(h[32:] + digest), "little") % Config.group_l
    rx, ry, rz, _t = scalarmult(base_point(), r)
    inv = pow(rz, Config.field_p - 2, Config.field_p)
    enc_r = encodepoint_raw((rx * inv) % Config.field_p, (ry * inv) % Config.field_p)
    pk = publickey(seed)
    hram = int.from_bytes(sha512(enc_r + pk + digest), "little") % Config.group_l
    s = (r + hram * a) % Config.group_l
    return enc_r + s.to_bytes(32, "little")


def pad_to(blob, alignment):
    """Pad blob with zero bytes up to alignment."""
    over = len(blob) % alignment
    if over:
        blob += b"\x00" * (alignment - over)
    return blob


def parse_ehdr(data):
    """Unpack the ELF header, raising ValueError when truncated."""
    if len(data) < Config.ehdr_size or data[:4] != b"\x7fELF":
        raise ValueError("not an ELF image")
    (e_type, e_machine, _ver, e_entry, e_phoff, e_shoff, _flags,
     e_ehsize, e_phentsize, e_phnum, e_shentsize, e_shnum,
     e_shstrndx) = struct.unpack("<HHIQQQIHHHHHH", data[16:64])
    return {
        "type": e_type, "machine": e_machine, "entry": e_entry,
        "phoff": e_phoff, "shoff": e_shoff, "phentsize": e_phentsize,
        "phnum": e_phnum, "shentsize": e_shentsize, "shnum": e_shnum,
        "shstrndx": e_shstrndx,
    }


def parse_phdrs(data, ehdr):
    """Unpack the program headers, raising ValueError when out of range."""
    out = []
    for i in range(ehdr["phnum"]):
        off = ehdr["phoff"] + i * ehdr["phentsize"]
        if ehdr["phentsize"] < Config.phdr_size or off + Config.phdr_size > len(data):
            raise ValueError("program header out of range")
        p_type, p_flags, p_offset, p_vaddr, _paddr, p_filesz, p_memsz, _align = \
            struct.unpack("<IIQQQQQQ", data[off:off + Config.phdr_size])
        out.append({"type": p_type, "flags": p_flags, "offset": p_offset,
                    "vaddr": p_vaddr, "filesz": p_filesz, "memsz": p_memsz})
    return out


def canonical_digest(data, ehdr, phdrs):
    """Build the kernel-agreed digest: entry plus PT_LOAD segments.

    File bytes below 64 (the ELF header) are excluded from the
    segment feeds while the entry stays bound as a value: appending
    the signature section rewrites the section index there, and a
    digest covering it would invalidate its own signature.
    """
    h = hashlib.sha512()
    h.update(struct.pack("<Q", ehdr["entry"]))
    for p in phdrs:
        if p["type"] != Config.pt_load:
            continue
        if p["offset"] + p["filesz"] > len(data):
            raise ValueError("segment beyond file")
        h.update(struct.pack("<Q", p["vaddr"]))
        h.update(struct.pack("<I", p["flags"] & 0xFFFFFFFF))
        h.update(struct.pack("<Q", p["filesz"]))
        start = p["offset"]
        if start < Config.ehdr_size:
            start = Config.ehdr_size
        end = p["offset"] + p["filesz"]
        if start < end:
            h.update(data[start:end])
    return h.digest()


def find_note_slots(data, ehdr, phdrs):
    """Locate patchable signature slots, returning file offsets of descs."""
    slots = []
    for p in phdrs:
        if p["type"] != Config.pt_note:
            continue
        pos = p["offset"]
        end = pos + p["filesz"]
        if end > len(data):
            continue
        while pos + 12 <= end:
            namesz, descsz, ntype = struct.unpack("<III", data[pos:pos + 12])
            body = ((namesz + 3) // 4) * 4 + ((descsz + 3) // 4) * 4
            if body > end - pos - 12:
                break
            name = data[pos + 12:pos + 12 + namesz]
            if (namesz == len(Config.note_name) + 1 and ntype == Config.note_sign_type and
                    descsz == Config.desc_bytes and name == Config.note_name + b"\x00"):
                slots.append(pos + 12 + ((namesz + 3) // 4) * 4)
            pos += 12 + body
    return slots


def find_section_slot(data, ehdr):
    """Locate the .note.minios.sign section descriptor, else -1."""
    if ehdr["shnum"] == 0 or ehdr["shentsize"] < Config.shdr_size:
        return -1
    end = ehdr["shoff"] + ehdr["shnum"] * ehdr["shentsize"]
    if end > len(data) or ehdr["shstrndx"] >= ehdr["shnum"]:
        return -1
    shdrs = []
    for i in range(ehdr["shnum"]):
        off = ehdr["shoff"] + i * ehdr["shentsize"]
        shdrs.append(struct.unpack("<IIQQQQIIQQ", data[off:off + Config.shdr_size]))
    sname, _stype, _flags, saddr, soffset, ssize = shdrs[ehdr["shstrndx"]][:6]
    del sname, _stype, _flags, saddr
    if soffset + ssize > len(data):
        return -1
    stab = data[soffset:soffset + ssize]
    for sh in shdrs:
        _name, stype, _flags, _addr, offset, size = sh[:6]
        if stype != Config.sht_note or offset + size > len(data):
            continue
        if size != Config.note_total:
            continue
        if _name >= len(stab):
            continue
        tail = stab[_name:].split(b"\x00", 1)[0]
        if tail != Config.note_section:
            continue
        namesz, descsz, ntype = struct.unpack("<III", data[offset:offset + 12])
        name = data[offset + 12:offset + 12 + namesz]
        if (namesz == len(Config.note_name) + 1 and ntype == Config.note_sign_type and
                descsz == Config.desc_bytes and name == Config.note_name + b"\x00"):
            return offset + 12 + ((namesz + 3) // 4) * 4
    return -1


def append_section(data, ehdr, desc):
    """Append a .note.minios.sign section, returning the new image."""
    if ehdr["shnum"] == 0 or ehdr["shentsize"] < Config.shdr_size:
        raise ValueError("no section table to extend")
    if ehdr["shstrndx"] >= ehdr["shnum"]:
        raise ValueError("no string table index")
    old_end = ehdr["shoff"] + ehdr["shnum"] * ehdr["shentsize"]
    if old_end > len(data):
        raise ValueError("section table out of range")
    shdrs = []
    for i in range(ehdr["shnum"]):
        off = ehdr["shoff"] + i * ehdr["shentsize"]
        shdrs.append(bytearray(data[off:off + Config.shdr_size]))
    sfields = struct.unpack("<IIQQQQIIQQ", bytes(shdrs[ehdr["shstrndx"]]))
    if sfields[4] + sfields[5] > len(data):
        raise ValueError("string table out of range")
    oldstr = data[sfields[4]:sfields[4] + sfields[5]]
    name_off = len(oldstr)
    newstr = pad_to(oldstr + Config.note_section + b"\x00", 8)
    note = struct.pack("<III", len(Config.note_name) + 1, Config.desc_bytes,
                       Config.note_sign_type)
    note += Config.note_name + b"\x00"
    note = pad_to(note, Config.note_align) + pad_to(desc, Config.note_align)
    assert len(note) == Config.note_total
    out = bytearray(data)
    while len(out) % 8:
        out += b"\x00"
    note_off = len(out)
    out += note
    str_off = len(out)
    out += newstr
    while len(out) % 8:
        out += b"\x00"
    strtab = bytearray(shdrs[ehdr["shstrndx"]])
    struct.pack_into("<Q", strtab, 24, str_off)
    struct.pack_into("<Q", strtab, 32, len(newstr))
    shdrs[ehdr["shstrndx"]] = strtab
    note_shdr = struct.pack("<IIQQQQIIQQ", name_off, Config.sht_note, 0, 0,
                            note_off, len(note), 0, 0, 4, 0)
    new_shoff = len(out)
    for s in shdrs:
        out += s
    out += note_shdr
    struct.pack_into("<Q", out, 40, new_shoff)
    struct.pack_into("<H", out, 60, ehdr["shnum"] + 1)
    return bytes(out)


def pub_for_key(key_id):
    """Resolve the trusted public key for checking without secrets."""
    if key_id == Config.key_dev:
        return bytes.fromhex(Config.dev_pub_hex)
    if key_id == Config.key_prod:
        raw = os.environ.get("MINIOS_SIGN_PUB", "")
        try:
            pub = bytes.fromhex(raw)
        except ValueError:
            pub = b""
        if len(pub) != Config.pub_bytes or not any(pub):
            raise ValueError("MINIOS_SIGN_PUB must hold a provisioned key")
        return pub
    raise ValueError("unknown key id %d" % key_id)


def key_material(key_id):
    """Resolve the signing seed and public key for a key id."""
    if key_id == Config.key_dev:
        seed = hashlib.sha256(Config.dev_seed_label).digest()
        pub = publickey(seed)
        if pub.hex() != Config.dev_pub_hex:
            raise ValueError("development key drifted from headers/sign.h")
        return seed, pub
    if key_id == Config.key_prod:
        raw = os.environ.get("MINIOS_SIGN_KEY", "")
        try:
            seed = bytes.fromhex(raw)
        except ValueError:
            seed = b""
        if len(seed) != 32:
            raise ValueError("MINIOS_SIGN_KEY must hold 64 hex chars")
        return seed, publickey(seed)
    raise ValueError("unknown key id %d" % key_id)


def process(path, key_id, check_only):
    """Sign or verify one file, returning (action, detail)."""
    if os.path.isdir(path):
        return ("skip", "directory")
    with open(path, "rb") as f:
        data = f.read()
    try:
        ehdr = parse_ehdr(data)
    except ValueError:
        return ("skip", "not ELF")
    if ehdr["machine"] != Config.e_machine_x86_64:
        return ("skip", "not x86-64")
    if ehdr["type"] not in (Config.et_exec, Config.et_dyn):
        return ("skip", "not executable")
    phdrs = parse_phdrs(data, ehdr)
    digest = canonical_digest(data, ehdr, phdrs)
    slots = find_note_slots(data, ehdr, phdrs)
    sec = find_section_slot(data, ehdr)
    if sec >= 0 and sec not in slots:
        slots.append(sec)
    if check_only:
        pubs = []
        try:
            pubs.append(pub_for_key(key_id))
        except ValueError as exc:
            return ("bad", str(exc))
        for s in slots:
            for pub in pubs:
                if verify_external(data[s + 1:s + 65], digest, pub):
                    return ("ok", "signature valid")
        if not slots:
            return ("unsigned", "no signature note")
        return ("bad", "no slot verifies")
    seed, pub = key_material(key_id)
    own = [s for s in slots if data[s] == key_id]
    for s in own:
        if verify_external(data[s + 1:s + 65], digest, pub):
            return ("ok", "already signed")
    desc = bytes([key_id]) + sign_digest(digest, seed)
    if own:
        out = bytearray(data)
        for s in own:
            out[s:s + Config.desc_bytes] = desc
        changed = bytes(out) != data
    else:
        out = append_section(data, ehdr, desc)
        changed = True
    if changed:
        with open(path, "wb") as f:
            f.write(bytes(out))
        return ("signed", "key %d" % key_id)
    return ("ok", "already signed")


def verify_external(sig, digest, pub):
    """Verify with PyNaCl when present, else the local fallback."""
    try:
        from nacl.bindings import crypto_sign_verify_detached
        crypto_sign_verify_detached(sig, digest, pub)
        return True
    except ImportError:
        pass
    except Exception:
        return False
    return fallback_verify(sig, digest, pub)


def fallback_verify(sig, digest, pub):
    """Pure-python Ed25519 verify for hosts without PyNaCl."""
    P = Config.field_p
    L = Config.group_l
    if len(sig) != Config.sig_bytes or len(pub) != Config.pub_bytes:
        return False
    r_raw = sig[:32]
    s = int.from_bytes(sig[32:], "little")
    if s >= L:
        return False
    try:
        r_pt = decode_point(r_raw)
        a_pt = decode_point(pub)
    except ValueError:
        return False
    h = int.from_bytes(sha512(r_raw + pub + digest), "little") % L
    left = scalarmult(base_point(), s)
    right = edwards_add(scalarmult(a_pt, h), r_pt)
    return points_equal(left, right)


def decode_point(raw):
    """Decode a point encoding to extended coordinates."""
    P = Config.field_p
    y = int.from_bytes(raw, "little") & ((1 << 255) - 1)
    sign = (raw[31] >> 7) & 1
    if y >= P:
        raise ValueError("non-canonical")
    x2 = ((y * y - 1) * pow(Config.curve_d * y * y + 1, P - 2, P)) % P
    x = pow(x2, (P + 3) // 8, P)
    if (x * x - x2) % P != 0:
        x = (x * pow(2, (P - 1) // 4, P)) % P
    if (x * x - x2) % P != 0:
        raise ValueError("no root")
    if (x & 1) != sign:
        x = P - x
    return (x, y, 1, (x * y) % P)


def points_equal(p, q):
    """Compare extended points by cross-multiplied coordinates."""
    P = Config.field_p
    return ((p[0] * q[2] - q[0] * p[2]) % P == 0 and
            (p[1] * q[2] - q[1] * p[2]) % P == 0)


def main(argv):
    """Drive signing or checking over files and directory walks."""
    key_id = Config.key_dev
    check_only = False
    walk = []
    files = []
    i = 1
    while i < len(argv):
        if argv[i] == "--check":
            check_only = True
        elif argv[i] == "--key-id" and i + 1 < len(argv):
            i += 1
            key_id = int(argv[i])
        elif argv[i] == "--walk" and i + 1 < len(argv):
            i += 1
            walk.append(argv[i])
        else:
            files.append(argv[i])
        i += 1
    for root in walk:
        for base, _dirs, names in os.walk(root):
            for n in sorted(names):
                files.append(os.path.join(base, n))
    failed = 0
    changed = 0
    for path in sorted(files):
        try:
            action, detail = process(path, key_id, check_only)
        except (OSError, ValueError) as exc:
            print("%s: FAIL %s" % (path, exc))
            failed += 1
            continue
        if action in ("bad", "unsigned", "FAIL"):
            print("%s: %s (%s)" % (path, action.upper(), detail))
            failed += 1
        elif action == "signed":
            print("%s: SIGNED (%s)" % (path, detail))
            changed += 1
    print("sign_elf: %d signed, %d failed" % (changed, failed))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
