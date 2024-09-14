//
// Created by petrs on 13.09.2024.
//

#ifndef PEXESOK_BOARD_H
#define PEXESOK_BOARD_H


#include <vector>
#include <iostream>
#include <bitset>
#include <unordered_set>
#include <fstream>
#include <ctime>
#include <chrono>
#include "Tile.h"

class Board {

private:
    std::vector<std::vector<Tile>> grid; // 2D vector to store the tiles
    int rows, cols;
    int reps;
    int depthLimit;
    const Tile defaultTile = Tile();
    const std::string path = R"(C:\Users\petrs\Documents\art\PEXESOK\tiling_solutions)";

    int partialSolutionThreshold = 22;

public:
    // Constructor to initialize the board with blank tiles
    Board(int r, int c) : rows(r), cols(c), reps(0), depthLimit(2e9) {
        grid = std::vector<std::vector<Tile>>(rows, std::vector<Tile>(cols, Tile()));
    }

    bool fill(int rStart, int cStart, std::vector<Tile>& tiles, std::bitset<64>& usedTiles) {
        auto [r, c] = nextEmptyPos(rStart, cStart);
        reps++;

        if (r == rows + 1) {
            std::cout << "solution exists" << std::endl;
            exportSolution(path, "final_solution_" + std::to_string(rows) + "_" + std::to_string(cols) + "_" + getTime());
            showGrid();
            return true;
        }

//        if (reps % 10000000 == 0) {
//            std::cout << reps << "\n";
//            showGrid();
//        }

        if (reps > depthLimit) {
//            std::cout << "reached depth limit of search without a complete solution" << std::endl;
            return false;
        }

        if (usedTiles.count() >= partialSolutionThreshold) {
            exportSolution(path, "solution_" + std::to_string(partialSolutionThreshold) + "_" + std::to_string(reps) + "_" + getTime());
            showGrid();
            partialSolutionThreshold++;
        }

        for (int digit = 0; digit < tiles.size(); ++digit) {
//            std::cout << "currently trying: " << tiles.at(digit).name << ": ";
            if (usedTiles.test(digit)) {
//                std::cout << "tile " << tiles.at(digit).name << " is already placed somewhere" << std::endl;
                continue;
            }

            Tile candidate = tiles.at(digit);
            for (int rotations = 0; rotations < candidate.totalRotations; ++rotations) {
                if (canBePlaced(r, c, candidate)) {
                    grid[r][c] = candidate;
//                    std::cout << "PLACED " << candidate.name << " with rotation " << candidate.rotation << " at [" << r << ", " << c << "]" << std::endl << std::endl;
                    usedTiles.set(digit);
                    if (fill(r, c, tiles, usedTiles)) {
                        return true;
                    }
                    usedTiles.reset(digit);
                }
                candidate.rotate();
            }
        }
        grid[r][c] = defaultTile;
        return false;

    }

    std::pair<int, int> nextEmptyPos(int r, int c) {
        while (r < rows) {
            if (isEmpty(r, c)) {
//                std::cout << "nextEmptyPos: [" << r << ":" << c << "] \n";
                return {r, c};
            }
            r = nextRow(r, c);
            c = nextCol(c);
        }
        return {rows + 1, 0}; // out of bounds
    }

    bool canBePlaced(int row, int col, const Tile& tile) {

        if (row == 0 & col == 0) { // TODO change order for efficiency?
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
                std::cout << grid[i][j].name << " (" << grid[i][j].rotation << ")  :  ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n";
    }

    void exportSolution(std::string adress, std::string name) {
        std::ofstream stream(adress + "\\" + name + ".dat");
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                stream << grid[i][j].name << "(" << grid[i][j].rotation << ") : ";
            }
            stream << std::endl;
        }
        stream.close();
    }

    std::string getTime() {
        // Get current time
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        // Convert current time to tm struct for easy manipulation
        std::tm *timeInfo = std::localtime(&currentTime);

        // Extract hours and minutes
        int hours = timeInfo->tm_hour;
        int minutes = timeInfo->tm_min;

        // Create a string stream to build the formatted time string
        std::ostringstream formattedTime;
        formattedTime << std::setfill('0') << std::setw(2) << hours << "h" << std::setw(2) << minutes << "m";

        // Return the formatted time string
        return formattedTime.str();
    }

    void setDepthLimit(int depthLimit) {
        Board::depthLimit = depthLimit;
    }

    void resetReps() {
        reps = 0;
        partialSolutionThreshold = 22;
    }
};



#endif //PEXESOK_BOARD_H
