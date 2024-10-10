#ifndef TANK_H
#define TANK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "GridGraph.h"

class Tank : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tank(int health, const QString &imagePath);

    void display(QGraphicsScene &scene, int row, int col, int cellWidth, int cellHeight);
    void moveTo(GridGraph &graph, int targetRow, int targetCol, QGraphicsScene &scene, int cellWidth, int cellHeight);

    int currentRow;
    int currentCol;

    signals:
        void tankSelected(Tank* tank);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int health;
    QPixmap pixmap;
};

#endif // TANK_H
