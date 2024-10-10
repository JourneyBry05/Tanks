#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QScreen>
#include <QtGui/QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>
#include "GridGraph.h"
#include "Tank.h"
#include "Pathfinding.h"
#include "PathfindingBFS.h"
#include "CustomView.h"

// Función para manejar la selección del tanque
void handleTankSelection(Tank* tank, CustomView& view) {
    view.selectTank(tank);  // Usar el método selectTank de CustomView
    qDebug() << "Tanque seleccionado";  // Mensaje para verificar que el tanque ha sido seleccionado
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Obtener dimensiones de pantalla
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // Definir el tamaño de la cuadrícula
    int rows = 15;
    int cols = 30;

    // Crear la escena gráfica
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, screenWidth, screenHeight);

    // Crear el grafo que representa la cuadrícula
    GridGraph graph(rows, cols);

    // Generar obstáculos con una densidad del 10% del mapa
    float obstacleDensity = 0.1;
    graph.generateObstacles(obstacleDensity);

    // Definir el factor de escala y tamaño de las celdas
    float scaleFactor = 0.8;
    int cellWidth = (screenWidth / cols) * scaleFactor;
    int cellHeight = (screenHeight / rows) * scaleFactor;

    // Dibujar la cuadrícula en la escena
    graph.drawGrid(scene, screenWidth, screenHeight, scaleFactor);

    // Tanques jugador 1 (rojos y azules)
    Tank player1TankRed1(100, "D:/Personal/Tanks/RedTank.png");
    Tank player1TankRed2(100, "D:/Personal/Tanks/RedTank.png");
    Tank player1TankBlue1(100, "D:/Personal/Tanks/BlueTank.png");
    Tank player1TankBlue2(100, "D:/Personal/Tanks/BlueTank.png");

    // Tanques jugador 2 (amarillos y celestes)
    Tank player2TankYellow1(100, "D:/Personal/Tanks/YellowTank.png");
    Tank player2TankYellow2(100, "D:/Personal/Tanks/YellowTank.png");
    Tank player2TankLight1(100, "D:/Personal/Tanks/LightBlueTank.png");
    Tank player2TankLight2(100, "D:/Personal/Tanks/LightBlueTank.png");

    // Colocar los tanques en la cuadrícula
    graph.addTank(player1TankRed1, 2, 0, scene, cellWidth, cellHeight);
    graph.addTank(player1TankRed2, 5, 1, scene, cellWidth, cellHeight);
    graph.addTank(player1TankBlue1, 9, 0, scene, cellWidth, cellHeight);
    graph.addTank(player1TankBlue2, 12, 1, scene, cellWidth, cellHeight);

    graph.addTank(player2TankYellow1, 2, 29, scene, cellWidth, cellHeight);
    graph.addTank(player2TankYellow2, 5, 28, scene, cellWidth, cellHeight);
    graph.addTank(player2TankLight1, 9, 29, scene, cellWidth, cellHeight);
    graph.addTank(player2TankLight2, 12, 28, scene, cellWidth, cellHeight);

    // Crear una vista personalizada para manejar los clics del ratón
    CustomView view(&scene, graph, cellWidth, cellHeight);
    view.setWindowTitle("Tank Attack!");
    view.showFullScreen();

    // Conectar la señal de selección del tanque (para los tanques rojos)
    QObject::connect(&player1TankRed1, &Tank::tankSelected, [&view](Tank* tank) {
        handleTankSelection(tank, view);
    });
    QObject::connect(&player1TankRed2, &Tank::tankSelected, [&view](Tank* tank) {
        handleTankSelection(tank, view);
    });

    // Conectar la señal de selección del tanque (para los tanques amarillos)
    QObject::connect(&player2TankYellow1, &Tank::tankSelected, [&view](Tank* tank) {
        handleTankSelection(tank, view);
    });
    QObject::connect(&player2TankYellow2, &Tank::tankSelected, [&view](Tank* tank) {
        handleTankSelection(tank, view);
    });

    // Conectar la señal de selección del tanque (para los tanques azules y celestes)
    QObject::connect(&player1TankBlue1, &Tank::tankSelected, [&view](Tank* tank) {
        handleTankSelection(tank, view);
    });
    QObject::connect(&player1TankBlue2, &Tank::tankSelected, [&view](Tank* tank) {
        handleTankSelection(tank, view);
    });
    QObject::connect(&player2TankLight1, &Tank::tankSelected, [&view](Tank* tank) {
        handleTankSelection(tank, view);
    });
    QObject::connect(&player2TankLight2, &Tank::tankSelected, [&view](Tank* tank) {
        handleTankSelection(tank, view);
    });

    return app.exec();
}
