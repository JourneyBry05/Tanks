cmake_minimum_required(VERSION 3.29)
project(Personal)

set(CMAKE_CXX_STANDARD 14)

# Ruta a las bibliotecas de Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64/lib/cmake")

# Activa las herramientas automáticas de Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Busca los módulos necesarios de Qt (Widgets para la ventana)
find_package(Qt6 COMPONENTS Widgets Charts REQUIRED)

# Incluye el directorio actual para que los archivos de cabecera sean encontrados
include_directories(${CMAKE_SOURCE_DIR})

# Añade el ejecutable principal del proyecto y todos los archivos fuente que componen el proyecto
add_executable(Personal main.cpp
        GridGraph.cpp
        Tank.cpp
        Pathfinding.cpp
        CustomView.cpp
        CustomView.cpp
        PathfindingBFS.cpp)

# Enlaza las bibliotecas de Qt necesarias
target_link_libraries(Personal Qt6::Widgets)
