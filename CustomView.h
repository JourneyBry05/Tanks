#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "GridGraph.h"
#include "Tank.h"

// Declaración de la clase CustomView
class CustomView : public QGraphicsView {
    Q_OBJECT
public:
    CustomView(QGraphicsScene* scene, GridGraph& graph, int cellWidth, int cellHeight, QWidget* parent = nullptr);

    // Método para seleccionar un tanque
    void selectTank(Tank* tank);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    GridGraph& graph;             // Referencia al grafo
    int cellWidth;                // Ancho de la celda
    int cellHeight;               // Alto de la celda
    Tank* selectedTank;           // Puntero al tanque seleccionado
    std::vector<QGraphicsLineItem*> routeLines; // Líneas para mostrar la ruta

    void clearRouteLines();       // Método para borrar las líneas de la ruta
    void drawRoute(const std::vector<int>& path); // Método para dibujar la ruta
};

#endif // CUSTOMVIEW_H
