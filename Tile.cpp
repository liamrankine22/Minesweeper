#include "Tile.h"
#include <iostream>
#include <vector>
#include <random>
#include <Tile.h>
#include <random>
#include <algorithm>

// Constructor
Tile::Tile() : bomb(false), number(0), marked(false), revealed(false) {}

int Tile::getNumber() const {
    return number;
}

bool Tile::isBomb() const {
    return bomb;
}

void Tile::setBomb() {
    bomb = true;
}

bool Tile::isMarked() const {
    return marked;
}

bool Tile::isRevealed() const {
    return revealed;
}

void Tile::setMarked(bool new_marked) {
    marked = new_marked;
}

void Tile::setRevealed(bool new_revealed) {
    revealed = new_revealed;
}

void Tile::setNeighbour(Tile* neighbour) {
    neighbours.push_back(neighbour);
}

void Tile::checkNeighbours() {
    if (!bomb) {
        for (Tile* neighbour : neighbours) {
            if (neighbour && neighbour->isBomb()) {
                number++;
            }
        }
    }
}

bool Tile::onClick() {
    if (revealed || marked) return false;  // Prevent redundant clicks and respect markings
    
    setRevealed(true);

    if (bomb) {
        return true;  // Game over condition
    }

    if (number == 0) {
        revealNeighbours();
    }

    return false;
}

void Tile::revealNeighbours() {
    for (Tile* neighbour : neighbours) {
        if (neighbour && !neighbour->isRevealed() && !neighbour->isBomb()) {
            neighbour->onClick();  // Recursively reveal safe neighbors
        }
    }
}
