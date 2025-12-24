#include "Cell.h"

// Base class implementation
Cell::Cell() 
    : mineFlag(false), revealed(false), flagged(false), adjacentMines(0) 
{
}

bool Cell::isMine() const {
    return mineFlag;
}

void Cell::toggleFlag() {
    if (!revealed) {
        flagged = !flagged;
    }
}

void Cell::setMine() {
    mineFlag = true;
}

void Cell::setAdjacentMines(int count) {
    adjacentMines = count;
}

// EmptyCell implementation - Türetilmiş sınıf
void EmptyCell::reveal() {
    if (!revealed && !flagged) {
        revealed = true;
    }
}

char EmptyCell::getDisplay() const {
    if (flagged) {
        return 'F';  // Flagged
    }
    if (!revealed) {
        return '?';  // Hidden
    }
    if (adjacentMines == 0) {
        return '.';  // Empty
    }
    return static_cast<char>('0' + adjacentMines);  // 1-8
}

std::string EmptyCell::getInfo() const {
    if (flagged) return "Bayraklı";
    if (!revealed) return "Kapalı";
    if (adjacentMines == 0) return "Boş";
    return "Komşu mayın: " + std::to_string(adjacentMines);
}

// MineCell implementation - Türetilmiş sınıf
void MineCell::reveal() {
    revealed = true;
}

char MineCell::getDisplay() const {
    if (flagged && !revealed) {
        return 'F';  // Flagged mine
    }
    if (!revealed) {
        return '?';  // Hidden
    }
    return 'X';  // Mine
}

std::string MineCell::getInfo() const {
    if (!revealed && flagged) return "Bayrakli mayin";
    if (!revealed) return "Kapali hucre";
    return "MAYINLAR!";
}

bool MineCell::isMine() const {
    return true;
}
