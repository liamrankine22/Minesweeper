#ifndef GRID_H
#define GRID_H

#include <Tile.h>
#include <vector>

// The Grid class represents the entire Minesweeper board containing tiles.
class Grid {
    std::vector<std::vector<Tile>> grid; // 2D vector to store tiles (game board)
    int rows;                            // Number of rows in the grid
    int cols;                            // Number of columns in the grid
    int bombs;                           // Total number of bombs placed in the grid

public:
    // Constructor: Initializes the grid with the given dimensions and number of bombs
    Grid(int rows, int cols, int bombs);

    // Sets neighboring tiles for each tile in the grid (used for bomb count logic)
    void setNeighbours();

    // Returns a reference to the tile at the specified (row, col) position
    Tile& getTile(int row, int col);

    // Randomly places bombs in the grid and updates tile states accordingly
    void placeBombs();

    // Checks if the player has won the game based on revealed tiles and bomb locations
    bool checkWin();

    // Resets the grid to its initial state for restarting the game
    void resetGrid();

    // Frees all tile-related resources (if necessary)
    void exit();  // Although in modern C++, explicit memory freeing isn't usually required unless using raw pointers
};

#endif
