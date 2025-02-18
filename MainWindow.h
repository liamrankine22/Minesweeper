#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVector>
#include "Grid.h"
#include "CRightClickEnabler.h" 

class QPushButton;  // Forward declaration for QPushButton

// Window class is derived from QWidget and represents the game window
class Window : public QWidget {
public:
    // Constructor: Initializes the game window and sets up the grid of buttons
    explicit Window(QWidget *parent = 0);

    // Handles the left-click on a tile (reveal tile functionality)
    void handleButtonClick(int x, int y);

    // Handles the right-click on a tile (flag or unflag functionality)
    void handleRightClick(int x, int y);

    // Updates button icons based on the revealed state of the grid
    void updateImages();

private:
    // 2D QVector to store all buttons on the game grid (30x16 grid)
    QVector<QVector<QPushButton*>> m_buttons;

    // QVector to store the right-click enabler objects for each button
    QVector<CRightClickEnabler*> m_clickEnablers;

    // The game grid that handles the state of all tiles (bombs, numbers, etc.)
    Grid m_grid;

    // Displays the "Game Over" menu
    void endMenu();

    // Displays the "You Won!" menu
    void wonMenu();

    // Restarts the game by resetting the grid and buttons
    void restartGame();
};

#endif
