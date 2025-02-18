#include <Grid.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <Tile.h>

// Constructor: Initializes the grid with the specified number of rows, columns, and bombs
Grid::Grid(int rows, int cols, int bombs) : rows(rows), cols(cols), bombs(bombs) {
    // Resize the grid to the specified number of rows and columns, initializing each tile
    grid.resize(rows, std::vector<Tile>(cols));

    // Place bombs randomly on the grid
    placeBombs();

    // Set up neighbouring tiles for each tile in the grid
    setNeighbours();

    // Check each tile's neighbours to determine how many bombs are nearby
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j].checkNeighbours(); // Calculate the number of bombs around each tile
        }
    }
}

// Set the 8 neighbouring tiles for each tile in the grid
void Grid::setNeighbours() {
    // Loop through every tile in the grid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Tile& tile = grid[i][j];

            // Loop through the 8 surrounding positions (x, y) around the current tile
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    if (x == 0 && y == 0) continue; // Skip the current tile itself
                    if (i + x < 0 || i + x >= rows || j + y < 0 || j + y >= cols) continue; // Skip out-of-bounds tiles

                    // Set the neighbour tile for the current tile
                    tile.setNeighbour(&grid[i + x][j + y]);
                }
            }
        }
    }
}

// Return a reference to a specific tile at the given row and column
Tile& Grid::getTile(int row, int col) {
    return grid[row][col];  // Return the tile at the specified location
}

// Randomly place bombs on the grid
void Grid::placeBombs() {
    // Create a list of all positions on the grid
    std::vector<int> positions;
    for (int i = 0; i < rows * cols; ++i) {
        positions.push_back(i); // Add all positions as possible bomb locations
    }

    // Shuffle the positions to randomize where the bombs will be placed
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::shuffle(positions.begin(), positions.end(), gen);  // Randomly shuffle the positions list

    // Set the first 'bombs' number of tiles as bombs in the shuffled positions
    for (int i = 0; i < bombs; ++i) {
        int flat_index = positions[i];  // Get the flattened index from the shuffled positions
        int row = flat_index / cols;  // Calculate the row from the index
        int col = flat_index % cols;  // Calculate the column from the index

        grid[row][col].setBomb();  // Set the tile at the computed position as a bomb
    }
}

// Check if the player has won the game
bool Grid::checkWin() {
    // Loop through all the tiles to check if all non-bomb tiles are revealed
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            Tile& tile = grid[row][col];

            // If the tile is not revealed
            if (!tile.isRevealed()) {
                if (!tile.isBomb()) {
                    // If a non-bomb tile is not revealed, the game is not won yet
                    return false;
                }
            } else {
                // If the tile is revealed, it should not be a bomb
                if (tile.isBomb()) {
                    // If a revealed tile is a bomb, the player hasn't won
                    return false;
                }
            }
        }
    }

    return true; // If all conditions are satisfied, the player has won
}
