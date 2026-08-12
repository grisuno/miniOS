#!/usr/bin/env python3
"""Build a MiniOS ramdisk image from files in a directory."""
import struct, sys, os

MAGIC = 0x4B534452  # "RDSK"
FNAME_LEN = 32
MAX_FILES = 128

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <outfile> <file1> <file2> ...", file=sys.stderr)
        sys.exit(1)

    outfile = sys.argv[1]
    files = sys.argv[2:]

    # Sort files for deterministic output
    file_data = []
    for f in files:
        with open(f, 'rb') as fp:
            data = fp.read()
        name = os.path.basename(f)[:FNAME_LEN - 1]
        file_data.append((name, data))

    # Compute offsets
    offset = 0
    entries = []
    for name, data in file_data:
        entries.append((name, len(data), offset))
        offset += len(data)

    # Write header
    with open(outfile, 'wb') as fp:
        fp.write(struct.pack('<I', MAGIC))       # magic
        fp.write(struct.pack('<I', len(entries))) # count

        for name, size, off in entries:
            name_bytes = name.encode() + b'\x00' * (FNAME_LEN - len(name))
            fp.write(name_bytes[:FNAME_LEN])
            fp.write(struct.pack('<I', size))
            fp.write(struct.pack('<I', off))

        # Pad to align (optional)
        # Write file data
        for _, data in file_data:
            fp.write(data)

    print(f"Wrote {outfile}: {len(entries)} files, {offset} bytes data")

if __name__ == '__main__':
    main()
