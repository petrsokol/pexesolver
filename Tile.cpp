//
// Created by petrs on 13.09.2024.
//

#include <iostream>
#include <utility>
#include "Tile.h"

Tile::Tile(std::string name, int sides, int max_orientation) {
    Tile::name = std::move(name);
    Tile::sides = sides;
    Tile::orientation = 0;
    Tile::max_orientation = max_orientation;
}

Tile::Tile() : Tile("default", 0b00110011, 3) {}

void Tile::rotate() {
    orientation++;
    sides = (sides >> 2) | (sides << (8-2));
}

void Tile::toString() const {
    std::cout << "name: " << name << ", orientation: " << orientation << ", sides: " << std::bitset<8>(sides) << std::endl;
}

int Tile::north() const {
    return (sides >> 6) & 0b11;
}

int Tile::east() const {
    return (sides >> 4) & 0b11;
}

int Tile::south() const {
    return (sides >> 2) & 0b11;
}

int Tile::west() const {
    return (sides >> 0) & 0b11;
}

int Tile::invertedWest() const {
    return ((sides & 0b01) << 1) | ((sides & 0b10) >> 1);
}

int Tile::invertedNorth() const {
    return ((sides & 0b01000000) >> 5) | ((sides & 0b10000000) >> 7);
}
