#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include "GridGraph.h"

class Pathfinding {
public:
    static std::vector<int> dijkstra(const GridGraph& graph, int startNode, int targetNode);
};

#endif // PATHFINDING_H
