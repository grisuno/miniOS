"""Host suite for the MiniFS image tools (docs/spec/shell-fs.md).

tools/mkfs.minifs.py builds the MiniFS image the kernel mounts and
tools/minifs_fsck.py gates it in the build. These cases pin the two
contracts the kernel cannot see at boot:

  - the superblock free counters equal the bitmaps, and fsck rejects an
    image whose counters drift;
  - same-named directories from several roots merge into one, and any
    other duplicate name is a build error.

Usage:
    python3 tests/test_minifs_tools.py -v
"""
import os
import struct
import subprocess
import sys
import tempfile
import unittest


class Config:
    """Every tunable of the suite in one place."""
    REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    MKFS = os.path.join(REPO, "tools", "mkfs.minifs.py")
    FSCK = os.path.join(REPO, "tools", "minifs_fsck.py")
    DUMP = os.path.join(REPO, "tools", "minifs_dump.py")
    BLOCKS = 256
    FREE_BLOCKS_OFF = 16
    FREE_INODES_OFF = 24
    PAYLOAD = b"nameserver 10.0.2.3\n"


def run(args):
    """Run a tool under the current interpreter; returns the process."""
    return subprocess.run([sys.executable] + args, capture_output=True, text=True)


class MiniFSToolsTest(unittest.TestCase):
    """mkfs.minifs.py and minifs_fsck.py agree on a consistent image."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.work = self.tmp.name

    def tearDown(self):
        self.tmp.cleanup()

    def tree(self, root, rel, data=Config.PAYLOAD):
        """Create file root/rel holding data and return the root path."""
        path = os.path.join(self.work, root, rel)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "wb") as handle:
            handle.write(data)
        return os.path.join(self.work, root)

    def mkfs(self, *paths):
        """Build an image from paths; returns (process, image path)."""
        image = os.path.join(self.work, "fs.bin")
        proc = run([Config.MKFS, image, str(Config.BLOCKS)] + list(paths))
        return proc, image

    def superblock_word(self, image, off):
        with open(image, "rb") as handle:
            handle.seek(off)
            return struct.unpack("<I", handle.read(4))[0]

    def test_counters_match_bitmaps(self):
        etc = os.path.join(self.tree("a", "etc/resolv.conf"), "etc")
        proc, image = self.mkfs(etc)
        self.assertEqual(proc.returncode, 0, proc.stderr)
        fsck = run([Config.FSCK, image])
        self.assertEqual(fsck.returncode, 0, fsck.stdout)
        self.assertIn("errors: 0", fsck.stdout)
        self.assertLess(self.superblock_word(image, Config.FREE_BLOCKS_OFF),
                        Config.BLOCKS)

    def test_fsck_rejects_drifted_counters(self):
        for off in (Config.FREE_BLOCKS_OFF, Config.FREE_INODES_OFF):
            with self.subTest(offset=off):
                etc = os.path.join(self.tree("b", "etc/hosts"), "etc")
                proc, image = self.mkfs(etc)
                self.assertEqual(proc.returncode, 0, proc.stderr)
                value = self.superblock_word(image, off)
                with open(image, "r+b") as handle:
                    handle.seek(off)
                    handle.write(struct.pack("<I", value + 1))
                fsck = run([Config.FSCK, image])
                self.assertNotEqual(fsck.returncode, 0, fsck.stdout)
                self.assertIn("!= bitmap", fsck.stdout)

    def test_same_named_directories_merge(self):
        one = os.path.join(self.tree("c", "etc/hosts"), "etc")
        two = os.path.join(self.tree("d", "etc/resolv.conf"), "etc")
        proc, image = self.mkfs(one, two)
        self.assertEqual(proc.returncode, 0, proc.stderr)
        self.assertEqual(proc.stdout.count("+ etc/\n"), 2)
        fsck = run([Config.FSCK, image])
        self.assertEqual(fsck.returncode, 0, fsck.stdout)
        listing = run([Config.DUMP, image])
        self.assertEqual(listing.returncode, 0, listing.stderr)
        self.assertEqual(listing.stdout.count("  etc/\n"), 1, listing.stdout)
        self.assertIn("  hosts\n", listing.stdout)
        self.assertIn("  resolv.conf\n", listing.stdout)

    def test_duplicate_file_is_an_error(self):
        one = os.path.join(self.tree("e", "etc/hosts"), "etc")
        two = os.path.join(self.tree("f", "etc/hosts"), "etc")
        proc, _ = self.mkfs(one, two)
        self.assertNotEqual(proc.returncode, 0)
        self.assertIn("duplicate name 'hosts'", proc.stderr + proc.stdout)


if __name__ == "__main__":
    unittest.main()
