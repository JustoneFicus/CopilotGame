#pragma once

#include <vector>
#include <array>
#include "Tetromino.h"

class Board {
public:
    static const int WIDTH = 10;
    static const int HEIGHT = 20;
    static const int CELL_SIZE = 30;

    Board();
    ~Board();

    bool canPlace(const Tetromino& tetromino, int x, int y) const;
    void placeTetromino(const Tetromino& tetromino, int x, int y);
    std::vector<int> getFullRows() const;
    void clearRows(const std::vector<int>& rows);
    void reset();
    
    int getCell(int x, int y) const;
    const std::array<std::array<int, WIDTH>, HEIGHT>& getGrid() const { return grid; }

private:
    std::array<std::array<int, WIDTH>, HEIGHT> grid;
    
    bool isValidPosition(int x, int y) const;
};
