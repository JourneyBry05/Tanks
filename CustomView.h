#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QtWidgets/QGraphicsView>
#include "GridGraph.h"
#include "Tank.h"

class CustomView : public QGraphicsView {
    Q_OBJECT
public:
    CustomView(QGraphicsScene* scene, GridGraph& graph, int cellWidth, int cellHeight);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    GridGraph& graph;
    int cellWidth;
    int cellHeight;
};

#endif // CUSTOMVIEW_H
