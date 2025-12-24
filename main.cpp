#include "Game.h"
#include <iostream>

int main() {
    // Oyun nesnesi oluştur ve çalıştır
    // Object instantiation - Sınıftan nesne oluşturma
    Game game;
    
    try {
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
