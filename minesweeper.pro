QT       += core widgets gui
TARGET = minesweeper
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 
SOURCES += main.cpp Grid.cpp Tile.cpp MainWindow.cpp CRightClickEnabler.cpp
HEADERS += Grid.h Tile.h MainWindow.h CRightClickEnabler.h
