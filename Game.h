#pragma once

#include "Board.h"
#include <iostream>
#include <string>

class Game {
private:
    Board board;
    bool running;

    // Private helper methods
    void displayMenu() const;
    void displayGameStatus() const;
    bool parseInput(std::string input, int& row, int& col, char& action);

public:
    // Constructor
    Game();
    
    // Main game loop
    void run();
    void processMove(int row, int col, char action);

    // Const methods
    bool isRunning() const { return running; }
};
