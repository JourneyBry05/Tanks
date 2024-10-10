#ifndef GRIDGRAPH_H
#define GRIDGRAPH_H

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtCore/QRandomGenerator>
#include "Tank.h"

class GridGraph {
private:
    int rows;
    int cols;
    int** adjMatrix;

public:
    GridGraph(int rows, int cols);
    ~GridGraph();

    // Métodos getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int** getAdjMatrix() const { return adjMatrix; }

    void addEdge(int u, int v);
    void generateConnections();
    void drawGrid(QGraphicsScene& scene, int screenWidth, int screenHeight, float scaleFactor);
    void generateObstacles(float obstacleDensity);
    void addTank(Tank &tank, int row, int col, QGraphicsScene &scene, int cellWidth, int cellHeight);
    bool isNavigable() const;

    // Métodos de búsqueda
    std::vector<int> bfs(int startNode, int targetNode);
    std::vector<int> dijkstra(int startNode, int targetNode);

    bool isObstacle(int row, int col) const;


private:
    void dfs(int node, bool* visited) const;
};

#endif // GRIDGRAPH_H
