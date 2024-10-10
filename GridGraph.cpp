#include "GridGraph.h"
#include <limits>
#include <algorithm>

// Constructor
GridGraph::GridGraph(int rows, int cols) : rows(rows), cols(cols) {
    adjMatrix = new int*[rows * cols];
    for (int i = 0; i < rows * cols; ++i) {
        adjMatrix[i] = new int[rows * cols];
        std::memset(adjMatrix[i], 0, rows * cols * sizeof(int));
    }
    generateConnections();
}

// Destructor
GridGraph::~GridGraph() {
    for (int i = 0; i < rows * cols; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

// Generar conexiones entre nodos
void GridGraph::generateConnections() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int node = i * cols + j;
            if (i > 0) addEdge(node, (i - 1) * cols + j);
            if (i < rows - 1) addEdge(node, (i + 1) * cols + j);
            if (j > 0) addEdge(node, i * cols + (j - 1));
            if (j < cols - 1) addEdge(node, i * cols + (j + 1));
        }
    }
}

// Agregar aristas al grafo
void GridGraph::addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}

// Implementación de BFS
std::vector<int> GridGraph::bfs(int startNode, int targetNode) {
    std::vector<int> prev(rows * cols, -1);
    std::vector<bool> visited(rows * cols, false);
    std::queue<int> q;

    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == targetNode) {
            break;
        }

        for (int i = 0; i < rows * cols; ++i) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                visited[i] = true;
                prev[i] = node;
                q.push(i);
            }
        }
    }

    // Reconstruir el camino desde targetNode hasta startNode
    std::vector<int> path;
    for (int at = targetNode; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    // Si el primer nodo no es el nodo inicial, no hay camino
    if (path.front() != startNode) {
        path.clear();
    }

    return path;
}

// Implementación de Dijkstra
std::vector<int> GridGraph::dijkstra(int startNode, int targetNode) {
    std::vector<int> dist(rows * cols, std::numeric_limits<int>::max());
    std::vector<int> prev(rows * cols, -1);
    dist[startNode] = 0;

    auto compare = [&dist](int lhs, int rhs) { return dist[lhs] > dist[rhs]; };
    std::priority_queue<int, std::vector<int>, decltype(compare)> pq(compare);
    pq.push(startNode);

    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();

        if (node == targetNode) {
            break;
        }

        for (int i = 0; i < rows * cols; ++i) {
            if (adjMatrix[node][i] == 1) { // Nodo vecino
                int alt = dist[node] + 1;  // Asumimos que la distancia entre nodos es 1
                if (alt < dist[i]) {
                    dist[i] = alt;
                    prev[i] = node;
                    pq.push(i);
                }
            }
        }
    }

    // Reconstruir el camino desde targetNode hasta startNode
    std::vector<int> path;
    for (int at = targetNode; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    // Si el primer nodo no es el nodo inicial, no hay camino
    if (path.front() != startNode) {
        path.clear();
    }

    return path;
}
