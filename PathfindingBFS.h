#ifndef PATHFINDINGBFS_H
#define PATHFINDINGBFS_H

#include <vector>
#include "GridGraph.h"

class PathfindingBFS {
public:
    static std::vector<int> bfs(const GridGraph& graph, int startNode, int targetNode);
};

#endif // PATHFINDINGBFS_H
