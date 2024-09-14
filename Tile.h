//
// Created by petrs on 13.09.2024.
//

#ifndef PEXESOK_TILE_H
#define PEXESOK_TILE_H


#include <string>
#include <bitset>
#include <vector>

class Tile {

public:
    Tile();

    std::string name;
    int sides;
    int totalRotations;
    int rotation = 0;

    Tile(std::string name, int sides, int totalRotations);

    [[nodiscard]] int north() const;
    [[nodiscard]] int invertedNorth() const;
    [[nodiscard]] int east() const;
    [[nodiscard]] int south() const;
    [[nodiscard]] int west() const;
    [[nodiscard]] int invertedWest() const;

    void rotate();
    void toString() const;
};


#endif //PEXESOK_TILE_H
