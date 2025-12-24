#pragma once

#include <iostream>
#include <string>

// Abstract base class - Soyut taban sınıf (Polymorphism)
class Cell {
protected:
    bool mineFlag;
    bool revealed;
    bool flagged;
    int adjacentMines;

public:
    // Constructor ve Destructor
    Cell();
    virtual ~Cell() = default;

    // Pure Virtual Functions - Saf sanal fonksiyonlar
    virtual void reveal() = 0;
    virtual char getDisplay() const = 0;
    virtual std::string getInfo() const = 0;

    // Virtual Functions - Sanal fonksiyonlar
    virtual bool isMine() const;
    virtual void toggleFlag();
    
    // Setter/Getter fonksiyonları (Encapsulation)
    void setMine();
    void setAdjacentMines(int count);
    
    bool isRevealed() const { return revealed; }
    bool isFlagged() const { return flagged; }
    int getAdjacentMines() const { return adjacentMines; }
};

// Derived class - Türetilmiş sınıf
class EmptyCell : public Cell {
public:
    EmptyCell() : Cell() {}
    
    void reveal() override;
    char getDisplay() const override;
    std::string getInfo() const override;
};

// Derived class - Türetilmiş sınıf
class MineCell : public Cell {
public:
    MineCell() : Cell() { setMine(); }
    
    void reveal() override;
    char getDisplay() const override;
    std::string getInfo() const override;
    bool isMine() const override;
};
