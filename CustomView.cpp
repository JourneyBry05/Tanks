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
    selectedTank = tank;
}

// Reimplementación del método mousePressEvent
void CustomView::mousePressEvent(QMouseEvent* event) {
    if (selectedTank) {
        // Obtener la posición del clic en la escena
        QPointF scenePos = mapToScene(event->pos());
        int targetCol = static_cast<int>(scenePos.x()) / cellWidth;
        int targetRow = static_cast<int>(scenePos.y()) / cellHeight;

        // Determinar si el tanque seleccionado debe usar BFS (50% de probabilidad)
        bool useBFS = (QRandomGenerator::global()->bounded(100) < 50);

        // Mover el tanque seleccionado a la nueva posición
        selectedTank->moveTo(graph, targetRow, targetCol, *scene(), cellWidth, cellHeight, useBFS);

        // Desseleccionar el tanque después de moverlo
        selectedTank = nullptr;
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}
