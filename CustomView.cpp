#include "CustomView.h"
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>
#include <QDebug>

// Constructor
CustomView::CustomView(QGraphicsScene* scene, GridGraph& graph, int cellWidth, int cellHeight, QWidget* parent)
    : QGraphicsView(scene, parent), graph(graph), cellWidth(cellWidth), cellHeight(cellHeight), selectedTank(nullptr) {
    setRenderHint(QPainter::Antialiasing);
}

// Método para seleccionar un tanque
void CustomView::selectTank(Tank* tank) {
    clearRouteLines();  // Borrar la ruta anterior si existe
    selectedTank = tank;
}

// Reimplementación del método mousePressEvent
void CustomView::mousePressEvent(QMouseEvent* event) {
    if (selectedTank) {
        // Obtener la posición del clic en la escena
        QPointF scenePos = mapToScene(event->pos());
        int targetCol = static_cast<int>(scenePos.x()) / cellWidth;
        int targetRow = static_cast<int>(scenePos.y()) / cellHeight;

        // Calcular la ruta usando Dijkstra o BFS (depende del tipo de tanque)
        std::vector<int> path;
        int startNode = selectedTank->currentRow * graph.getCols() + selectedTank->currentCol;
        int targetNode = targetRow * graph.getCols() + targetCol;

        bool useBFS = selectedTank->usesBFS();
        if (useBFS) {
            qDebug() << "Usando BFS para mover el tanque.";
            path = graph.bfs(startNode, targetNode);
        } else {
            qDebug() << "Usando Dijkstra para mover el tanque.";
            path = graph.dijkstra(startNode, targetNode);
        }

        // Dibujar la ruta en la escena
        drawRoute(path);

        // Mover el tanque seleccionado a la nueva posición
        selectedTank->moveTo(graph, targetRow, targetCol, *scene(), cellWidth, cellHeight, useBFS);

        // Desseleccionar el tanque después de moverlo
        selectedTank = nullptr;
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

// Método para borrar las líneas de la ruta anterior
void CustomView::clearRouteLines() {
    for (auto line : routeLines) {
        scene()->removeItem(line);
        delete line;
    }
    routeLines.clear();
}

// Método para dibujar la ruta en la escena
void CustomView::drawRoute(const std::vector<int>& path) {
    if (path.size() < 2) return;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        int startNode = path[i];
        int endNode = path[i + 1];

        int startRow = startNode / graph.getCols();
        int startCol = startNode % graph.getCols();
        int endRow = endNode / graph.getCols();
        int endCol = endNode % graph.getCols();

        // Calcular las coordenadas de inicio y fin de la línea
        int startX = startCol * cellWidth + cellWidth / 2;
        int startY = startRow * cellHeight + cellHeight / 2;
        int endX = endCol * cellWidth + cellWidth / 2;
        int endY = endRow * cellHeight + cellHeight / 2;

        // Crear la línea que representa el tramo de la ruta
        QGraphicsLineItem* line = scene()->addLine(startX, startY, endX, endY, QPen(Qt::red, 2));
        routeLines.push_back(line);
    }
}
