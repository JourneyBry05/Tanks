#include "Pathfinding.h"
#include <queue>
#include <limits>

std::vector<int> Pathfinding::dijkstra(const GridGraph& graph, int startNode, int targetNode) {
    int rows = graph.getRows();
    int cols = graph.getCols();
    int totalNodes = rows * cols;

    std::vector<int> dist(totalNodes, std::numeric_limits<int>::max());
    std::vector<int> prev(totalNodes, -1);
    dist[startNode] = 0;

    auto compare = [&dist](int lhs, int rhs) { return dist[lhs] > dist[rhs]; };
    std::priority_queue<int, std::vector<int>, decltype(compare)> pq(compare);
    pq.push(startNode);

    int** adjMatrix = graph.getAdjMatrix();

    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();

        if (node == targetNode) {
            break;
        }

        for (int i = 0; i < totalNodes; ++i) {
            if (adjMatrix[node][i] == 1 && dist[i] > dist[node] + 1) {
                dist[i] = dist[node] + 1;
                prev[i] = node;
                pq.push(i);
            }
        }
    }

    std::vector<int> path;
    for (int at = targetNode; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    if (path.front() != startNode) {
        path.clear();
    }

    return path;
}
