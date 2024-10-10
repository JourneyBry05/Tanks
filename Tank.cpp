#include "Tank.h"
#include "GridGraph.h"
#include <QtWidgets/QGraphicsScene>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QLabel>
#include <QThread>


extern std::vector<QGraphicsLineItem*> routeLines;  // Declaración externa para usar la variable global

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
    qDebug() << "Tanque seleccionado en posición (" << currentRow << "," << currentCol << ")";

    // Mostrar las coordenadas del clic en la escena
    QPointF clickPos = event->scenePos();
    qDebug() << "Coordenadas del clic: (" << clickPos.x() << "," << clickPos.y() << ")";

    // Llamar a la implementación base para asegurarse de que se manejen otros eventos
    QGraphicsPixmapItem::mousePressEvent(event);
}

void Tank::moveTo(GridGraph &graph, int targetRow, int targetCol, QGraphicsScene &scene, int cellWidth, int cellHeight, bool useBFS) {
    int startNode = currentRow * graph.getCols() + currentCol;
    int targetNode = targetRow * graph.getCols() + targetCol;

    if (graph.isObstacle(targetRow, targetCol)) {
        qDebug() << "El destino es un obstáculo";
        return;
    }

    std::vector<int> path;

    // Selección del algoritmo (50% BFS o 50% Aleatorio)
    if (useBFS) {
        qDebug() << "Usando BFS para mover el tanque.";
        path = PathfindingBFS::bfs(graph, startNode, targetNode);
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
                targetRow = randomRow;
                targetCol = randomCol;
                moved = true;
                break;
            }
        }

        if (!moved) {
            qDebug() << "No se encontró una posición válida para moverse aleatoriamente.";
            return;
        }
    }

    // Mover el tanque paso a paso siguiendo la ruta calculada
    if (!path.empty()) {
        for (size_t i = 1; i < path.size(); ++i) {
            int nextNode = path[i];
            int nextRow = nextNode / graph.getCols();
            int nextCol = nextNode % graph.getCols();

            qDebug() << "Moviendo a (" << nextRow << "," << nextCol << ")";

            // Actualizar la posición del tanque en la escena
            this->display(scene, nextRow, nextCol, cellWidth, cellHeight);

            // Esperar un corto período para que el movimiento sea visible (simulando animación)
            QThread::msleep(200);
            QApplication::processEvents();
        }

        // Actualizar la posición actual del tanque
        currentRow = targetRow;
        currentCol = targetCol;
    }
}
