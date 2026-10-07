#!/usr/bin/env python3
"""Build progs/topogpt3/vocab.bin from the GPT-2 encoder.json.

Output format (little-endian, read by load_vocab in topogpt3.c):
    magic "VOCB", u32 token count, then per token: u16 byte length
    followed by the raw token bytes.

GPT-2 encoder keys are unicode strings using the bytes_to_unicode
mapping, so each token is decoded back to raw bytes through the
inverse map. Token 0-255 become the single bytes 0x00-0xFF.
"""

import json
import struct
import sys


def bytes_to_unicode():
    """Reversible byte to unicode map used by the GPT-2 encoder."""
    byte_values = (
        list(range(ord("!"), ord("~") + 1))
        + list(range(ord("¡"), ord("¬") + 1))
        + list(range(ord("®"), ord("ÿ") + 1))
    )
    unicode_values = byte_values[:]
    offset = 0
    for byte in range(256):
        if byte not in byte_values:
            byte_values.append(byte)
            unicode_values.append(256 + offset)
            offset += 1
    return {byte: chr(code) for byte, code in zip(byte_values, unicode_values)}


def main(encoder_path, vocab_path):
    """Convert encoder.json to the VOCB binary vocabulary.

    Args:
        encoder_path: Path to the GPT-2 encoder.json file.
        vocab_path: Destination path for the vocab.bin file.
    """
    with open(encoder_path, encoding="utf-8") as handle:
        encoder = json.load(handle)
    decode_map = {char: byte for byte, char in bytes_to_unicode().items()}
    ordered = sorted(encoder.items(), key=lambda item: item[1])
    tokens = []
    for token, _ in ordered:
        try:
            tokens.append(bytes(decode_map[char] for char in token))
        except KeyError as error:
            raise ValueError(f"Unmapped char in token {token!r}") from error
    with open(vocab_path, "wb") as handle:
        handle.write(b"VOCB")
        handle.write(struct.pack("<I", len(tokens)))
        for token in tokens:
            handle.write(struct.pack("<H", len(token)))
            handle.write(token)
    print(f"Wrote {len(tokens)} tokens to {vocab_path}")


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
