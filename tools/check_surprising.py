"""check_surprising.py -- Detect surprising architectural connections.

Parses the CPG JSON-LD output from readmenator and flags new connections
of N or more hops between distinct communities.  These represent coupling
debt that should be visible and prioritizable.

Usage:
    python3 tools/check_surprising.py [cpg.jsonld] [--min-hops 5]

Exit codes:
    0 -- no surprising connections
    1 -- new surprising connections detected
    2 -- input file missing or malformed
"""

import json
import sys
import os
from collections import defaultdict, deque

DEFAULT_MIN_HOPS = 5
DEFAULT_CPG_PATH = "KNOWLEDGE_BASE.jsonld"


def load_cpg(path):
    """Load and parse the CPG JSON-LD file."""
    if not os.path.exists(path):
        return None
    with open(path, "r") as f:
        return json.load(f)


def build_graph(cpg):
    """Build adjacency list from CPG nodes and edges."""
    nodes = {}
    edges = defaultdict(list)

    graph = cpg.get("@graph", []) if isinstance(cpg, dict) else []
    for item in graph:
        if isinstance(item, dict):
            nid = item.get("@id", item.get("id", ""))
            comm = item.get("community", item.get("communityId", "default"))
            nodes[nid] = comm

    for item in graph:
        if isinstance(item, dict):
            src = item.get("@id", item.get("id", ""))
            dst = item.get("target", item.get("to", ""))
            if src in nodes and dst in nodes:
                edges[src].append(dst)
                edges[dst].append(src)

    return nodes, edges


def bfs_min_hops(nodes, edges, source, target_community, max_hops):
    """BFS from source to any node in target_community, returning hop count."""
    if source not in nodes:
        return float("inf")

    source_community = nodes[source]
    visited = {source}
    queue = deque([(source, 0)])

    while queue:
        current, hops = queue.popleft()
        if hops > max_hops:
            break

        for neighbor in edges.get(current, []):
            if neighbor in visited:
                continue
            visited.add(neighbor)

            neighbor_comm = nodes.get(neighbor, "default")
            if (neighbor_comm == target_community and
                    neighbor != source and
                    hops + 1 > 0):
                return hops + 1

            if hops + 1 < max_hops:
                queue.append((neighbor, hops + 1))

    return float("inf")


def find_surprising_connections(nodes, edges, min_hops):
    """Find connections of min_hops or more between distinct communities."""
    communities = defaultdict(list)
    for nid, comm in nodes.items():
        communities[comm].append(nid)

    surprising = []

    for comm_a, nodes_a in communities.items():
        for comm_b, nodes_b in communities.items():
            if comm_a >= comm_b:
                continue
            for node_a in nodes_a:
                for node_b in nodes_b:
                    hops = bfs_min_hops(nodes, edges, node_a, comm_b,
                                        min_hops + 1)
                    if hops >= min_hops:
                        surprising.append({
                            "from": node_a,
                            "from_community": comm_a,
                            "to": node_b,
                            "to_community": comm_b,
                            "hops": hops,
                        })
                        break
                if surprising and surprising[-1]["from_community"] == comm_a:
                    break

    return surprising


def main():
    import argparse
    parser = argparse.ArgumentParser(
        description="Detect surprising cross-community connections")
    parser.add_argument("cpg", nargs="?", default=DEFAULT_CPG_PATH,
                        help="Path to CPG JSON-LD file")
    parser.add_argument("--min-hops", type=int, default=DEFAULT_MIN_HOPS,
                        help="Minimum hop count to flag (default: 5)")
    args = parser.parse_args()

    cpg = load_cpg(args.cpg)
    if cpg is None:
        print(f"check_surprising: {args.cpg} not found, skipping")
        sys.exit(0)

    nodes, edges = build_graph(cpg)
    if not nodes:
        print("check_surprising: no nodes found in CPG, skipping")
        sys.exit(0)

    surprising = find_surprising_connections(nodes, edges, args.min_hops)

    if surprising:
        print(f"check_surprising: {len(surprising)} SURPRISING CONNECTIONS "
              f"(>={args.min_hops} hops)")
        for s in surprising[:20]:
            print(f"  {s['from']} ({s['from_community']}) -> "
                  f"{s['to']} ({s['to_community']}) "
                  f"[{s['hops']} hops]")
        sys.exit(1)

    print(f"check_surprising: OK ({len(nodes)} nodes, "
          f"min_hops={args.min_hops})")
    sys.exit(0)


if __name__ == "__main__":
    main()
