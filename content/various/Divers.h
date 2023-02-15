struct pairhash {
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &p) const {
    // return std::hash<T>()(x.first) ^ std::hash<U>()(x.second); // simpler alternative
    const auto h1 = hash<T>{}(p.first);
    const auto h2 = hash<U>{}(p.second);
    if (h1 == h2) return h1;
    return h1 ^ h2;
  }
};

// fast CIN
ios_base::sync_with_stdio(false);
cin.tie(NULL);

// This is pseudocode of A star
fn A_Star(start: node, goal: node, h: (Fn(node) -> score)) -> Option<[node]>
    openSet := {start}
    cameFrom := empty map<node, node>
    gScore := map<node, score> with default value of Infinity
    gScore[start] := 0
    fScore := map<node, score> with default value of Infinity
    fScore[start] := h(start)

    while openSet is not empty
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        current := the node in openSet having the lowest fScore[] value
        if current = goal
            return reconstruct_path(cameFrom, current)

        openSet.Remove(current)
        for each neighbor of current
            tentative_gScore := gScore[current] + d(current, neighbor)
            if tentative_gScore < gScore[neighbor]
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                fScore[neighbor] := tentative_gScore + h(neighbor)
                if neighbor not in openSet
                    openSet.add(neighbor)
    return failure