#include "PathfindingBFS.h"
#include <queue>
#include <limits>

std::vector<int> PathfindingBFS::bfs(const GridGraph& graph, int startNode, int targetNode) {
    std::vector<int> prev(graph.getRows() * graph.getCols(), -1);
    std::vector<bool> visited(graph.getRows() * graph.getCols(), false);
    std::queue<int> q;

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == targetNode) {
            break;
        }

        for (int i = 0; i < graph.getRows() * graph.getCols(); ++i) {
            if (graph.getAdjMatrix()[node][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
                prev[i] = node;
            }
        }
    }

    // Reconstruir el camino desde targetNode hasta startNode
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
