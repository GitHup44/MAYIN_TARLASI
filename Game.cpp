#include "Game.h"
#include <sstream>
#include <cctype>

Game::Game() : board(), running(true) {}
void Game::displayMenu() const {
    std::cout << "\n========================================\n";
    std::cout << "       MAYIN TARLASI OYUNU\n";
    std::cout << "========================================\n";
    std::cout << "\nKomutlar:\n";
    std::cout << "  r <satir> <sutun> - Hucre ac (ornek: r 3 4)\n";
    std::cout << "  f <satir> <sutun> - Bayrak koy (ornek: f 3 4)\n";
    std::cout << "  q - Cik\n";
    std::cout << "========================================\n";
}
void Game::displayGameStatus() const {
    int flaggedCount = 0;
    for (int i = 0; i < board.getRows(); ++i) {
        for (int j = 0; j < board.getCols(); ++j) {
            if (board.isCellFlagged(i, j)) {
                flaggedCount++;
            }
        }
    }
    std::cout << "\nKalan mayin: " << (board.getMines() - flaggedCount);
    std::cout << " | Acilan: " << board.getRevealedCells() 
              << "/" << board.getRequiredReveals() << "\n";
}
bool Game::parseInput(std::string input, int& row, int& col, char& action) {
    // Boş input kontrol
    if (input.empty()) {
        return false;
    }
    std::istringstream iss(input);
    if (!(iss >> action)) {
        return false;
    }
    action = std::tolower(static_cast<unsigned char>(action));
    if (action == 'q') {
        return true;
    }
    if (action != 'r' && action != 'f') {
        return false;
    }
    if (!(iss >> row >> col)) {
        return false;
    }
    if (row < 0 || row >= board.getRows() || 
        col < 0 || col >= board.getCols()) {
        return false;
    }
    return true;
}
void Game::processMove(int row, int col, char action) {
    if (action == 'r') {
        if (!board.revealCell(row, col)) {
            std::cout << "\n[!] Mayina bastiniz! Oyun bitti!\n";
        }
    } else if (action == 'f') {
        board.flagCell(row, col);
        std::cout << "\n[+] Bayrak koyuldu/kaldirildi.\n";
    }
}
void Game::run() {
    displayMenu();
    while (running) {
        board.display();
        displayGameStatus();
        if (board.isGameOver()) {
            if (board.isGameWon()) {
                std::cout << "\n[*] TEBRIKLER! Oyunu kazandiniz!\n";
            } else {
                std::cout << "\n[*] Oyun bitti. Kaybettiniz!\n";
            }
            running = false;
            break;
        }
        std::cout << "\nKomut girin (r/f satir sutun veya q): ";
        std::string input;
        std::getline(std::cin, input);
        // Trim whitespace
        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);
        int row = -1, col = -1;
        char action = ' ';
        if (!parseInput(input, row, col, action)) {
            if (input.empty()) continue;
            if (input[0] == 'q' || input[0] == 'Q') {
                running = false;
                std::cout << "\nOyundan ciktiniz.\n";
            } else {
                std::cout << "\n[!] HATA! Format: r/f <satir 0-" << (board.getRows()-1) << "> <sutun 0-" << (board.getCols()-1) << "> veya q\n";
                std::cout << "   Ornek: r 3 4  veya  f 2 1\n";
            }
            continue;
        }
        if (action == 'q') {
            running = false;
            std::cout << "\nOyundan ciktiniz.\n";
        } else {
            processMove(row, col, action);
        }
    }
}
