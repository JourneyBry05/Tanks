#ifndef GRIDGRAPH_H
#define GRIDGRAPH_H

#include <QtWidgets/QGraphicsScene>
#include <vector>

class Tank;  // Declaración adelantada para evitar dependencia circular

class GridGraph {
private:
    int rows;
    int cols;
    int** adjMatrix;

public:
    // Constructor y destructor
    GridGraph(int rows, int cols);
    ~GridGraph();

    // Métodos del grafo
    void addEdge(int u, int v);
    void generateConnections();
    void drawGrid(QGraphicsScene& scene, int screenWidth, int screenHeight, float scaleFactor);
    void generateObstacles(float obstacleDensity);
    void addTank(Tank &tank, int row, int col, QGraphicsScene &scene, int cellWidth, int cellHeight);

    // Obtener filas y columnas
    int getCols() const;
    int getRows() const;

    // Verificar si una celda es un obstáculo
    bool isObstacle(int row, int col) const;

    // Acceso a la matriz de adyacencia
    int** getAdjMatrix() const;

private:
    void dfs(int node, bool* visited) const;
};

#endif // GRIDGRAPH_H
