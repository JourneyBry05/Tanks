#ifndef TANK_H
#define TANK_H

#include <QLabel>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include "GridGraph.h"

class Tank : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    // Constructor para inicializar el tanque con vida y una imagen
    Tank(int health, const QString &imagePath);

    // Metodo para mostrar el tanque en la ventana
    void display(QGraphicsScene &scene, int row, int col, int cellWidth, int cellHeight);

    // Metodo para mover el tanque, ahora con la opción de usar BFS
    void moveTo(GridGraph &graph, int targetRow, int targetCol, QGraphicsScene &scene, int cellWidth, int cellHeight, bool useBFS);

    // Eventos de clic
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // Almacenar las coordenadas actuales
    int currentRow;
    int currentCol;

    signals:
        void tankSelected(Tank* tank);  // Señal para notificar que un tanque ha sido seleccionado

private:
    int health;
    QPixmap pixmap;
};

#endif // TANK_H
