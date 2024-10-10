#include "Tank.h"
#include "Pathfinding.h"
#include <QtWidgets/QGraphicsScene>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Tank::Tank(int health, const QString &imagePath) : health(health), pixmap(imagePath) {
    if (pixmap.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde" << imagePath;
    }
    setPixmap(pixmap);
}

void Tank::display(QGraphicsScene &scene, int row, int col, int cellWidth, int cellHeight) {
    QPixmap scaledPixmap = pixmap.scaled(cellWidth, cellHeight, Qt::KeepAspectRatio);
    setPixmap(scaledPixmap);
    int x = col * cellWidth;
    int y = row * cellHeight;
    setPos(x, y);
    currentRow = row;
    currentCol = col;
    scene.addItem(this);
}

void Tank::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit tankSelected(this);
    qDebug() << "Tanque seleccionado en posición (" << currentRow << "," << currentCol << ")";  // Mensaje de depuración

    // Además, mostrar las coordenadas del clic en la escena
    QPointF clickPos = event->scenePos();
    qDebug() << "Coordenadas del clic: (" << clickPos.x() << "," << clickPos.y() << ")";

    // Llamar a la implementación base para asegurarse de que se manejen otros eventos
    QGraphicsPixmapItem::mousePressEvent(event);
}

void Tank::moveTo(GridGraph &graph, int targetRow, int targetCol, QGraphicsScene &scene, int cellWidth, int cellHeight) {
    int startNode = currentRow * graph.getCols() + currentCol;
    int targetNode = targetRow * graph.getCols() + targetCol;

    if (graph.isObstacle(targetRow, targetCol)) {
        qDebug() << "El destino es un obstáculo";
        return;
    }

    // Probabilidad para usar Dijkstra (80%) o movimiento aleatorio (20%)
    if (QRandomGenerator::global()->bounded(100) < 80) {
        qDebug() << "Usando Dijkstra para mover el tanque.";
        std::vector<int> path = Pathfinding::dijkstra(graph, startNode, targetNode);

        if (path.empty()) {
            qDebug() << "No se encontró una ruta válida con Dijkstra";
            return;
        }

        for (int i = 1; i < path.size(); ++i) {
            int nextNode = path[i];
            int nextRow = nextNode / graph.getCols();
            int nextCol = nextNode % graph.getCols();
            qDebug() << "Moviendo a (" << nextRow << "," << nextCol << ")";
            this->display(scene, nextRow, nextCol, cellWidth, cellHeight);
        }
    } else {
        qDebug() << "Usando movimiento aleatorio.";
        int randomRow, randomCol;
        bool moved = false;

        int attempts = 10;
        int maxDistance = 3;

        for (int i = 0; i < attempts; ++i) {
            randomRow = currentRow + QRandomGenerator::global()->bounded(-maxDistance, maxDistance + 1);
            randomCol = currentCol + QRandomGenerator::global()->bounded(-maxDistance, maxDistance + 1);

            if (randomRow >= 0 && randomRow < graph.getRows() &&
                randomCol >= 0 && randomCol < graph.getCols() &&
                !graph.isObstacle(randomRow, randomCol)) {

                qDebug() << "Moviendo a posición aleatoria (" << randomRow << "," << randomCol << ")";
                this->display(scene, randomRow, randomCol, cellWidth, cellHeight);
                moved = true;
                break;
            }
        }

        if (!moved) {
            qDebug() << "No se encontró una posición válida para moverse aleatoriamente.";
        }
    }

    currentRow = targetRow;
    currentCol = targetCol;
}
