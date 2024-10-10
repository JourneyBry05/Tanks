#include "GridGraph.h"
#include "Tank.h"
#include <cstring>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

GridGraph::GridGraph(int rows, int cols) : rows(rows), cols(cols) {
    adjMatrix = new int*[rows * cols];
    for (int i = 0; i < rows * cols; ++i) {
        adjMatrix[i] = new int[rows * cols];
        std::memset(adjMatrix[i], 0, rows * cols * sizeof(int));
    }
    generateConnections();
}

GridGraph::~GridGraph() {
    for (int i = 0; i < rows * cols; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

void GridGraph::addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}

void GridGraph::generateConnections() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int node = i * cols + j;
            if (i > 0) addEdge(node, (i - 1) * cols + j);  // Nodo de arriba
            if (i < rows - 1) addEdge(node, (i + 1) * cols + j);  // Nodo de abajo
            if (j > 0) addEdge(node, i * cols + (j - 1));  // Nodo de la izquierda
            if (j < cols - 1) addEdge(node, i * cols + (j + 1));  // Nodo de la derecha
        }
    }
}

void GridGraph::generateObstacles(float obstacleDensity) {
    QRandomGenerator* generator = QRandomGenerator::global();
    for (int i = 0; i < rows; ++i) {
        for (int j = 2; j < cols - 2; ++j) {  // Ignorar las primeras 2 y últimas 2 columnas
            int node = i * cols + j;
            if (generator->bounded(1.0) < obstacleDensity) {
                for (int k = 0; k < rows * cols; ++k) {
                    adjMatrix[node][k] = -1;
                    adjMatrix[k][node] = -1;
                }
            }
        }
    }
}

void GridGraph::drawGrid(QGraphicsScene& scene, int screenWidth, int screenHeight, float scaleFactor) {
    int cellWidth = (screenWidth / cols) * scaleFactor;
    int cellHeight = (screenHeight / rows) * scaleFactor;

    QBrush brush(QColor(210, 190, 150));
    QBrush obstacleBrush(QColor(150, 150, 150));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x = j * cellWidth;
            int y = i * cellHeight;
            int node = i * cols + j;

            if (adjMatrix[node][node] == -1) {
                scene.addRect(x, y, cellWidth, cellHeight, QPen(Qt::black), obstacleBrush);
            } else {
                scene.addRect(x, y, cellWidth, cellHeight, QPen(Qt::black), brush);
            }
        }
    }
}

void GridGraph::addTank(Tank &tank, int row, int col, QGraphicsScene &scene, int cellWidth, int cellHeight) {
    int node = row * cols + col;
    if (adjMatrix[node][node] == -1) {
        qDebug() << "Error: No se puede colocar un tanque en una celda bloqueada.";
        return;
    }
    tank.display(scene, row, col, cellWidth, cellHeight);
}

bool GridGraph::isObstacle(int row, int col) const {
    int node = row * cols + col;
    return adjMatrix[node][node] == -1;
}

int GridGraph::getCols() const {
    return cols;
}

int GridGraph::getRows() const {
    return rows;
}

int** GridGraph::getAdjMatrix() const {
    return adjMatrix;
}
