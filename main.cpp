#include <iostream>
#include <vector>
#include <unordered_set>
#include "Tile.h"
#include "Board.h"
#include "Solver.h"

int main() {
    std::cout << "DOBRY DEN!!!" << std::endl;

    std::unordered_set<int> usedTiles = {};
    std::vector<Tile> tiles = {
            Tile("sachy", 0b10011001, 1), // sachy
            Tile("tester", 0b10011001, 1), // tester
            Tile("lipovyList", 0b10010101, 3), // lipovy list
            Tile("domek", 0b01100110, 1), // domek
            Tile("diagonalni", 0b10100101, 3), // diagonalni
            Tile("mlyn", 0b01010101, 0), // mlyn

            Tile("vlastovka", 0b01000010, 3), // vlastovka
            Tile("sip", 0b11000101, 3), // sip
            Tile("labut", 0b10111101, 3), // labut

            Tile("serpentyna", 0b00010010, 3), // serpentyna
            Tile("koserpentyna", 0b11101101, 3), // koserpentyna
            Tile("DC", 0b01111000, 3), // DC - jako polsko
            Tile("polsko", 0b00011110, 3), // polsko
            Tile("s", 0b01000100, 1), // s
            Tile("Z", 0b11011101, 1), // Z
            Tile("cesko", 0b00011101, 3), // cesko
            Tile("stromVecer", 0b01110100, 3), // strom vecer

            Tile("vlak", 0b11001100, 1), // vlak
            Tile("sklo", 0b00111100, 3), //sklo - jako lampion
            Tile("tvarian", 0b00000000, 0), // tvarian
            Tile("kotvarian", 0b11111111, 0), // kotvarian
            Tile("stromPoledne", 0b00001100, 3), // strom poledne
            Tile("lampion", 0b11110000, 3), // lampion
            Tile("stromPulnoc", 0b11110011, 3), // strom pulnoc
    };

    Board board(4,4);
    board.fill(0, 0, tiles, usedTiles);

    return 0;
}