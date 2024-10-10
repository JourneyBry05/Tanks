#include "CustomView.h"
#include <QMouseEvent>
#include <QDebug>

extern Tank* selectedTank;  // Declaración externa para usar la variable global

CustomView::CustomView(QGraphicsScene* scene, GridGraph& graph, int cellWidth, int cellHeight)
    : QGraphicsView(scene), graph(graph), cellWidth(cellWidth), cellHeight(cellHeight) {}

void CustomView::mousePressEvent(QMouseEvent* event) {
    if (selectedTank) {
        // Obtener las coordenadas del clic en la vista y convertirlas a coordenadas de la escena
        QPointF scenePos = mapToScene(event->pos());

        // Convertir las coordenadas en filas y columnas del grid
        int targetRow = static_cast<int>(scenePos.y()) / cellHeight;
        int targetCol = static_cast<int>(scenePos.x()) / cellWidth;

        // Mover el tanque seleccionado a la nueva posición
        selectedTank->moveTo(graph, targetRow, targetCol, *scene(), cellWidth, cellHeight);
        selectedTank = nullptr;  // Desseleccionar el tanque después de moverlo
    }
}
