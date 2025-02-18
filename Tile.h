#ifndef TILE_H
#define TILE_H

#include <vector>  // Required for using std::vector

// The Tile class represents a single cell in the Minesweeper grid.
class Tile {
    int number;                      // Stores the number of adjacent bombs (0-8)
    bool bomb;                       // True if the tile contains a bomb
    bool marked;                     // True if the tile is flagged by the player
    bool revealed;                   // True if the tile has been revealed
    std::vector<Tile*> neighbours;   // Pointers to neighboring tiles (up to 8 neighbors)

public:
    Tile(); // Constructor declaration: Initializes default values for a tile

    // Getter for the number of adjacent bombs
    int getNumber() const;

    // Checks if the tile contains a bomb
    bool isBomb() const;

    // Marks the tile as containing a bomb
    void setBomb();

    // Checks if the tile is flagged by the player
    bool isMarked() const;

    // Checks if the tile has been revealed
    bool isRevealed() const;

    // Adds a neighboring tile to the current tile's neighbor list
    void setNeighbour(Tile* neighbour);

    // Sets the marked (flagged) status of the tile
    void setMarked(bool new_marked);

    // Sets the revealed status of the tile
    void setRevealed(bool new_revealed);

    // Counts the number of bombs in neighboring tiles and updates the 'number' field
    void checkNeighbours();

    // Handles the behavior when the tile is clicked (reveal logic)
    bool onClick();

    // Reveals all neighboring tiles recursively (used for revealing empty spaces)
    void revealNeighbours();
};

#endif
