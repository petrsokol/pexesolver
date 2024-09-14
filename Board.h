//
// Created by petrs on 13.09.2024.
//

#ifndef PEXESOK_BOARD_H
#define PEXESOK_BOARD_H


#include <vector>
#include <iostream>
#include <bitset>
#include <unordered_set>
#include "Tile.h"

class Board {

private:
    std::vector<std::vector<Tile>> grid; // 2D vector to store the tiles
    int rows, cols;
    int reps;

public:
    // Constructor to initialize the board with blank tiles
    Board(int r, int c) : rows(r), cols(c), reps(0) {
        grid = std::vector<std::vector<Tile>>(rows, std::vector<Tile>(cols, Tile()));
    }

    bool fill(int rStart, int cStart, std::vector<Tile> tiles, std::unordered_set<int> usedTiles) {
        auto [r, c] = nextEmptyPos(rStart, cStart);
        reps++;

        if (r == rows + 1) {
            std::cout << "solution exists" << std::endl;
            showGrid();
            return true;
        }

        if (reps % 1000000 == 0) {
            std::cout << reps << "\n";
            showGrid();
        }

//        if (grid[rows - 1][cols - 3].name != "default") {
//            showGrid();
//        }

        for (int digit = 0; digit < tiles.size(); ++digit) {
//            std::cout << "currently trying: " << tiles.at(digit).name << ": ";
            if (usedTiles.contains(digit)) {
//                std::cout << "tile " << tiles.at(digit).name << " is already placed somewhere" << std::endl;
                continue;
            }

            Tile candidate = tiles.at(digit);
            for (int rotations = 0; rotations < candidate.max_orientation; ++rotations) {
                if (canBePlaced(r, c, candidate)) {
                    grid[r][c] = candidate;
//                    std::cout << "PLACED " << candidate.name << " with orientation " << candidate.orientation << " at [" << r << ", " << c << "]" << std::endl << std::endl;
                    usedTiles.insert(digit);
                    if (fill(r, c, tiles, usedTiles)) {
                        return true;
                    }
                    usedTiles.erase(digit);
                }
                candidate.rotate();
            }
        }
        grid[r][c] = Tile();
        return false;

    }

    std::pair<int, int> nextEmptyPos(int r, int c) {
        while (r < rows) {
            if (isEmpty(r, c)) {
                return {r, c};
            }
            r = nextRow(r, c);
            c = nextCol(c);
        }
        return {rows + 1, 0}; // out of bounds
    }

    bool canBePlaced(int row, int col, const Tile& tile) {

        if (row == 0 & col == 0) {
            return true;
        } else if (row == 0 && col != 0) {
            return grid[row][col - 1].east() == tile.invertedWest();
        } else if (row != 0 && col == 0) {
            return grid[row - 1][col].south() == tile.invertedNorth();
        } else {
            return grid[row][col - 1].east() == tile.invertedWest() && grid[row - 1][col].south() == tile.invertedNorth();
        }
    }

    bool isEmpty(int r, int c) {
        return grid[r][c].name == "default";
    }

    [[nodiscard]] int nextCol(int c) const {
        return (c + 1) % cols;
    }

    [[nodiscard]] int nextRow(int r, int c) const {
        return r + (c + 1) / cols;
    }

    void showGrid() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << grid[i][j].name << " (" << grid[i][j].orientation << ")  :  ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n";
    }
};



#endif //PEXESOK_BOARD_H
