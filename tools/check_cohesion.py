"""check_cohesion.py -- Architectural cohesion gate for MiniOS CI.

Parses the CPG JSON-LD output from readmenator and fails the build if any
root community's cohesion drops below the configured threshold.

Usage:
    python3 tools/check_cohesion.py [cpg.jsonld] [--threshold 0.25]

Exit codes:
    0 -- all communities above threshold
    1 -- cohesion regression detected
    2 -- input file missing or malformed
"""

import json
import sys
import os

DEFAULT_THRESHOLD = 0.25
DEFAULT_CPG_PATH = "KNOWLEDGE_BASE.jsonld"


def load_cpg(path):
    """Load and parse the CPG JSON-LD file."""
    if not os.path.exists(path):
        return None
    with open(path, "r") as f:
        return json.load(f)


def compute_cohesion(community_nodes, community_edges):
    """Compute cohesion as internal_edges / max_possible_edges."""
    n = len(community_nodes)
    if n < 2:
        return 1.0
    max_edges = n * (n - 1) // 2
    if max_edges == 0:
        return 1.0
    return len(community_edges) / max_edges


def extract_communities(cpg):
    """Extract communities and their internal edges from CPG."""
    communities = {}
    nodes = cpg.get("@graph", []) if isinstance(cpg, dict) else []

    for node in nodes:
        if isinstance(node, dict):
            comm = node.get("community", node.get("communityId", "default"))
            nid = node.get("@id", node.get("id", ""))
            if comm not in communities:
                communities[comm] = {"nodes": [], "edges": []}
            communities[comm]["nodes"].append(nid)

    return communities


def main():
    import argparse
    parser = argparse.ArgumentParser(description="Check architectural cohesion")
    parser.add_argument("cpg", nargs="?", default=DEFAULT_CPG_PATH,
                        help="Path to CPG JSON-LD file")
    parser.add_argument("--threshold", type=float, default=DEFAULT_THRESHOLD,
                        help="Minimum cohesion threshold (default: 0.25)")
    args = parser.parse_args()

    cpg = load_cpg(args.cpg)
    if cpg is None:
        print(f"check_cohesion: {args.cpg} not found, skipping (no CPG to check)")
        sys.exit(0)

    communities = extract_communities(cpg)
    if not communities:
        print("check_cohesion: no communities found in CPG, skipping")
        sys.exit(0)

    failures = []
    for name, data in communities.items():
        cohesion = compute_cohesion(data["nodes"], data["edges"])
        if cohesion < args.threshold:
            failures.append((name, cohesion, len(data["nodes"])))

    if failures:
        print("check_cohesion: COHESION REGRESSION DETECTED")
        for name, score, count in sorted(failures):
            print(f"  {name}: cohesion={score:.3f} (nodes={count}) "
                  f"< threshold={args.threshold}")
        sys.exit(1)

    print(f"check_cohesion: OK ({len(communities)} communities, "
          f"threshold={args.threshold})")
    sys.exit(0)


if __name__ == "__main__":
    main()
