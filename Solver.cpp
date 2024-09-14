////
//// Created by petrs on 13.09.2024.
////
//
//#include "Solver.h"
//
//#include <utility>
//#include <iostream>
//
//Solver::Solver(Board board, std::vector<Tile> tiles, std::unordered_set<int> usedTiles) {
//    Solver::board = std::move(board);
//}
//
//int Solver::nextRow(int r, int c) {
//    return r + (c + 1) / Board::cols;
//}
//
//int Solver::nextCol(int c) {
//    return (c + 1) % Board::cols;
//}
//
//std::pair<int, int> Solver::nextEmptyPos(int r, int c) {
//    while(r != 9) {
//        if (board.isEmpty(r, c)) {
//            return {r, c};
//        }
//        r = nextRow(r, c); //move to next empty position
//        c = nextCol(c);
//    }
//    return {Board::rows + 1,0};
//}
//
//bool Solver::solve(int rStart, int cStart) {
//
//    auto [r, c] = nextEmptyPos(rStart, cStart);
//    if (r == Board::rows + 1) {
//        return true;
//    }
//
//    //main recursion loop
//    for (int i = 0; i < tiles.size(); ++i) {
//        if (usedTiles.contains(i)) {
//            continue;
//        }
//        Tile candidate = tiles.at(i);
//        int northernSide = board.getS(r - 1, c).south(); //co ty na kraji?
//        int westernSide = board.getS(r, c - 1).east();
//        for (int j = 0; j < 4; ++j) {
//            if (candidate.north() == northernSide && candidate.west() == westernSide) {
//                board.set(r, c, candidate);
//                usedTiles.insert(i);
//                if (solve(r, c)) {
//                    return true;
//                }
//            }
//            candidate.rotate();
//        }
//        board.set(r, c, Tile());
//        usedTiles.erase(i);
//    }
//
//    /*
//    for (int digit = 0; digit < 9; ++digit) {
//        if (!contains[vec[digit]]) {
//            board.set(r, c, vec[digit] + 1);
//            updatePos(r, c, vec[digit]);
//            if (solve(r, c, tiles, usedTiles)) { //goes a level deeper
//                return true; //if the previous level is true, so is this one
//            }
//            undoPos(r, c, vec[digit]);
//            // if the lower recursion level is false (not a legal sudoku configuration), this undoes the wrong step
//        }
//    }
//    board.set(r, c, Tile());
//    return false; // all options on this level of recursion were exhausted, there is a mistake somewhere earlier
//     */
//}
//
///**
// * updates the bitsets which allow the algorithm to check for neighbouring numbers
// * in the current row, column and 3x3 cell
// *
// * @param r row you want to update
// * @param c column you want to update
// * @param digit the number you want to insert at the chosen position
// */
//
////void Solver::updatePos(int r, int c, int digit) {
////    int s = getCell(r, c);
////    rows[r].set(digit);
////    cols[c].set(digit);
////    sqrs[s].set(digit);
////}
////
/////**
//// * takes the digit from the chosen row, column and 3x3 cell - updates the bitsets
//// * @param r row you want to update
//// * @param c column you want to update
//// * @param digit number you want to take away from the bitsets
//// */
////void Solver::undoPos(int r, int c, int digit) {
////    int s = getCell(r, c);
////    rows[r].reset(digit);
////    cols[c].reset(digit);
////    sqrs[s].reset(digit);
////}
////
/////**
//// * returns the index of a 3x3 cell based on the input row and column
//// * @param r row inside the 3x3 cell
//// * @param c column inside the 3x3 cell
//// * @return an index from 0-8 starting at row=0 and column=0
//// */
////int Solver::getCell(int r, int c) {
////    return (r / 3) * 3 + c / 3;
////}
////
/////**
//// * solves a given sudoku board, either randomly (used for boards that start off completely empty),
//// * or not, which is faster
//// *
//// * It then informs about the number of found solutions
//// *
//// * @param isRandom determines if the solution should look more random
//// */
//// /*
////void Solver::solveAll() {
////    solve(0, 0);
////    if (solutions == 0) {
////        std::cout << "this sudoku does not have a solution." << std::endl;
////    } else if (solutions == 1) {
////        std::cout << "this sudoku has a unique solution." << std::endl;
////    } else if (solutions <= 10) {
////        std::cout << "this sudoku has " << solutions << " solutions." << std::endl;
////    } else {
////        std::cout << "this sudoku has more than 10 solutions." << std::endl;
////    }
////}
////  */