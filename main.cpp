#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Tile.h"
#include "Board.h"

int main() {
    std::cout << "DOBRY DEN!!!" << std::endl;

    std::bitset<64> usedTiles = {};
    std::vector<Tile> tiles = {
            Tile("Z", 0b11011101, 2), // Z
            Tile("sachy", 0b10011001, 2), // sachy
            Tile("cesko", 0b00011101, 4), // cesko

            Tile("vlak", 0b11001100, 2), // vlak
            Tile("sklo", 0b00111100, 4), //sklo - jako lampion
            Tile("tvarian", 0b00000000, 1), // tvarian
            Tile("kotvarian", 0b11111111, 1), // kotvarian
            Tile("stromPoledne", 0b00001100, 4), // strom poledne
            Tile("lampion", 0b11110000, 4), // lampion
            Tile("stromPulnoc", 0b11110011, 4), // strom pulnoc

            Tile("serpentyna", 0b00010010, 4), // serpentyna
            Tile("koserpentyna", 0b11101101, 4), // koserpentyna
            Tile("DC", 0b01111000, 4), // DC - jako polsko
            Tile("polsko", 0b00011110, 4), // polsko
            Tile("s", 0b01000100, 2), // s
            Tile("stromVecer", 0b01110100, 4), // strom vecer

            Tile("vlastovka", 0b01000010, 4), // vlastovka
            Tile("sip", 0b11000101, 4), // sip
            Tile("labut", 0b10111101, 4), // labut

            Tile("tester", 0b10011001, 2), // tester
            Tile("lipovyList", 0b10010101, 4), // lipovy list
            Tile("domek", 0b01100110, 2), // domek
            Tile("diagonalni", 0b10100101, 4), // diagonalni
//            Tile("diagonalni", 0b10100101, 4), // diagonalni
//            Tile("diagonalni", 0b10100101, 4), // diagonalni
//            Tile("diagonalni", 0b10100101, 4), // diagonalni

//            Tile("mlynKladny", 0b01010101, 1), // mlyn
            Tile("mlynZaporny", 0b10101010, 1), // zaporny patri do rozsirujici sady
    };

    std::vector<Tile> altTiles = {
            Tile("tulipanRano", 0b10001110, 4),
            Tile("tulipanVecer", 0b01110001, 4),
            Tile("RuzeRano", 0b10110010, 4),
            Tile("RuzeVecer", 0b01001101, 4),
            Tile("obalkaBila", 0b01111110, 4),
            Tile("obalkaCerna", 0b10000001, 4),
            Tile("sipkaBila", 0b11100111, 4),
            Tile("sipkaCerna", 0b00011000, 4),
            Tile("J", 0b00011110, 4),
            Tile("L", 0b00011110, 4),
            Tile("cernochVlevo", 0b10000111, 4),
            Tile("cernochVpravo", 0b01111000, 4),
            Tile("rytirVlevo", 0b10010101, 4),
            Tile("rytirVpravo", 0b01101010, 4),
            Tile("S", 0b11101110, 2),
            Tile("z", 0b10001000, 2),
            Tile("domekRano", 0b10011001, 4),
            Tile("ceskoChiralni", 0b11100010, 4),
            Tile("lipovyListChiralni", 0b10100110, 4), // jako rytir mozna
            Tile("stromRano", 0b10001011, 4),
//            Tile("sipChiralni", 0b11101000, 4),
//            Tile("sipChiralni", 0b11101000, 4),
//            Tile("sipChiralni", 0b11101000, 4),
            Tile("sipChiralni", 0b11101000, 4),
            Tile("vojevudce", 0b10100101, 4),
            Tile("presypaciHodiny", 0b10110100, 4),
            Tile("mlynKladny", 0b01010101, 1),
//            Tile("mlynZaporny", 0b10101010, 1),
    };

    std::vector<Tile> omega;
    omega.insert(omega.end(), tiles.begin(), tiles.end());
    omega.insert(omega.end(), altTiles.begin(), altTiles.end());

    auto start = std::chrono::high_resolution_clock::now();
    Board board(6,8);

    bool doRandomShallowAttempts = true;
    int attempts = doRandomShallowAttempts ? 100 : 1;
    board.setDepthLimit(doRandomShallowAttempts ? 3e7 : 2e9);

    for (int i = 0; i < attempts; ++i) {
        if (doRandomShallowAttempts) {
            // Use a doRandomShallowAttempts number generator engine to shuffle the vector
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(omega.begin(), omega.end(), g);
        }
        std::cout << "starting cycle number " << i << std::endl;
        board.resetReps();
        board.fill(0, 0, omega, usedTiles);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Execution Time: " << duration.count() << " seconds" << std::endl;

    return 0;
}