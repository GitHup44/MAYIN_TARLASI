#include "Board.h"
#include <iostream>
#include <algorithm>

Board::Board() 
    : revealedCells(0), gameOver(false), gameWon(false) 
{
    generateBoard();
}

Board::~Board() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            delete grid[i][j];
        }
    }
}

void Board::generateBoard() {
    // Create empty cells - Smart pointers kullanarak
    for (int i = 0; i < ROWS; ++i) {
        std::vector<Cell*> row;
        for (int j = 0; j < COLS; ++j) {
            row.push_back(new EmptyCell());
        }
        grid.push_back(row);
    }
    
    placeMines();
    calculateAdjacentMines();
}

void Board::placeMines() {
    // Random generator - Modern C++
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_row(0, ROWS - 1);
    std::uniform_int_distribution<> dis_col(0, COLS - 1);
    
    int placed = 0;
    while (placed < MINES) {
        int row = dis_row(gen);
        int col = dis_col(gen);
        
        if (!grid[row][col]->isMine()) {
            // Replace with mine cell
            delete grid[row][col];
            grid[row][col] = new MineCell();
            placed++;
        }
    }
}

void Board::calculateAdjacentMines() {
    // Lambda function - Modern C++
    auto countAdjacentMines = [this](int row, int col) -> int {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                
                int newRow = row + i;
                int newCol = col + j;
                
                if (newRow >= 0 && newRow < ROWS && 
                    newCol >= 0 && newCol < COLS) {
                    if (grid[newRow][newCol]->isMine()) {
                        count++;
                    }
                }
            }
        }
        return count;
    };
    
    // Set adjacent mine count for each cell
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (!grid[i][j]->isMine()) {
                grid[i][j]->setAdjacentMines(countAdjacentMines(i, j));
            }
        }
    }
}

void Board::revealEmptyCells(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return;
    }
    
    Cell* cell = grid[row][col];  // Raw pointer
    
    if (cell->isRevealed() || cell->isFlagged()) {
        return;
    }
    
    if (cell->isMine()) {
        return;
    }
    
    cell->reveal();
    revealedCells++;
    
    // Flood fill algorithm - Eğer boş ise çevresini de aç
    if (cell->getAdjacentMines() == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i != 0 || j != 0) {
                    revealEmptyCells(row + i, col + j);
                }
            }
        }
    }
}

bool Board::revealCell(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return false;
    }
    
    Cell* cell = grid[row][col];
    
    if (cell->isRevealed() || cell->isFlagged()) {
        return false;
    }
    
    if (cell->isMine()) {
        gameOver = true;
        // Reveal all mines when game over
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (grid[i][j]->isMine()) {
                    grid[i][j]->reveal();
                }
            }
        }
        return false;
    }
    
    revealEmptyCells(row, col);
    
    // Check win condition
    if (revealedCells == getRequiredReveals()) {
        gameWon = true;
        gameOver = true;
    }
    
    return true;
}

void Board::flagCell(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return;
    }
    
    grid[row][col]->toggleFlag();
}

bool Board::isCellRevealed(int row, int col) const {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return false;
    }
    return grid[row][col]->isRevealed();
}

bool Board::isCellFlagged(int row, int col) const {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return false;
    }
    return grid[row][col]->isFlagged();
}

Cell* Board::getCell(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return nullptr;
    }
    return grid[row][col];
}

void Board::display() const {
    std::cout << "\n  ";
    for (int j = 0; j < COLS; ++j) {
        std::cout << j << " ";
    }
    std::cout << "\n";
    
    for (int i = 0; i < ROWS; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < COLS; ++j) {
            const Cell* cell = grid[i][j];
            std::cout << cell->getDisplay() << " ";
        }
        std::cout << "\n";
    }
}
