//
// Created by petrs on 13.09.2024.
//

#ifndef PEXESOK_SOLVER_H
#define PEXESOK_SOLVER_H


#include <unordered_set>
#include "Board.h"

class Solver {

public:
    explicit Solver(Board board, std::vector<Tile> tiles, std::unordered_set<int> usedTiles);
    void solveAll();

    Board board;

    std::vector<Tile> tiles;
    std::unordered_set<int> usedTiles;

    bool solve(int rStart, int cStart);
private:

    static int nextRow(int r, int c);
    static int nextCol(int c);
    static int getCell(int r, int c);
    std::pair<int, int> nextEmptyPos(int r, int c);

    void updatePos(int r, int c, int digit);
    void undoPos(int r, int c, int digit);

};


#endif //PEXESOK_SOLVER_H
