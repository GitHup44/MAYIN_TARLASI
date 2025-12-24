#pragma once

#include "Cell.h"
#include <vector>
#include <memory>
#include <random>

class Board {
private:
    static constexpr int ROWS = 8;
    static constexpr int COLS = 8;
    static constexpr int MINES = 10;

    // Smart pointers - Modern C++ (Dinamik bellek yönetimi)
    std::vector<std::vector<Cell*>> grid;  // Use raw pointers for 2D grid
    int revealedCells;
    bool gameOver;
    bool gameWon;

    // Özel metodlar
    void generateBoard();
    void placeMines();
    void calculateAdjacentMines();
    void revealEmptyCells(int row, int col);

public:
    // Constructor ve Destructor
    Board();
    ~Board();  // Destructor for cleanup

    // Const metodlar (Const mekanizması)
    int getRows() const { return ROWS; }
    int getCols() const { return COLS; }
    int getMines() const { return MINES; }
    
    bool isGameOver() const { return gameOver; }
    bool isGameWon() const { return gameWon; }
    int getRevealedCells() const { return revealedCells; }
    int getRequiredReveals() const { return ROWS * COLS - MINES; }

    // Game methods
    bool revealCell(int row, int col);
    void flagCell(int row, int col);
    bool isCellRevealed(int row, int col) const;
    bool isCellFlagged(int row, int col) const;
    
    // Cell getter
    Cell* getCell(int row, int col);

    // Display
    void display() const;
};
