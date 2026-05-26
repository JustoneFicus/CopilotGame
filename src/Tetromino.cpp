#include "Tetromino.h"
#include <cstdlib>
#include <ctime>

Tetromino::Tetromino() : type(TetrominoType::NONE), rotationState(0) {
    setColor();
}

Tetromino::Tetromino(TetrominoType type) : type(type), rotationState(0) {
    initializeBlocks();
    setColor();
}

void Tetromino::initializeBlocks() {
    blocks.clear();
    
    switch (type) {
        case TetrominoType::I:
            blocks = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
            break;
        case TetrominoType::O:
            blocks = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
            break;
        case TetrominoType::T:
            blocks = {{1, 0}, {0, 1}, {1, 1}, {2, 1}};
            break;
        case TetrominoType::S:
            blocks = {{1, 0}, {2, 0}, {0, 1}, {1, 1}};
            break;
        case TetrominoType::Z:
            blocks = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
            break;
        case TetrominoType::J:
            blocks = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
            break;
        case TetrominoType::L:
            blocks = {{2, 0}, {0, 1}, {1, 1}, {2, 1}};
            break;
        default:
            break;
    }
}

void Tetromino::setColor() {
    switch (type) {
        case TetrominoType::I:
            color = {0, 255, 255, 255}; // Cyan
            break;
        case TetrominoType::O:
            color = {255, 255, 0, 255}; // Yellow
            break;
        case TetrominoType::T:
            color = {128, 0, 128, 255}; // Purple
            break;
        case TetrominoType::S:
            color = {0, 255, 0, 255}; // Green
            break;
        case TetrominoType::Z:
            color = {255, 0, 0, 255}; // Red
            break;
        case TetrominoType::J:
            color = {0, 0, 255, 255}; // Blue
            break;
        case TetrominoType::L:
            color = {255, 165, 0, 255}; // Orange
            break;
        default:
            color = {128, 128, 128, 255}; // Gray
            break;
    }
}

void Tetromino::rotate() {
    // Simple 90-degree clockwise rotation
    std::vector<std::pair<int, int>> rotated;
    
    for (const auto& block : blocks) {
        int newX = -block.second;
        int newY = block.first;
        rotated.push_back({newX, newY});
    }
    
    // Normalize to origin
    int minX = rotated[0].first, minY = rotated[0].second;
    for (const auto& block : rotated) {
        minX = std::min(minX, block.first);
        minY = std::min(minY, block.second);
    }
    
    for (auto& block : rotated) {
        block.first -= minX;
        block.second -= minY;
    }
    
    blocks = rotated;
    rotationState = (rotationState + 1) % 4;
}

void Tetromino::rotateCounterClockwise() {
    for (int i = 0; i < 3; ++i) {
        rotate();
    }
}

Tetromino Tetromino::createRandom() {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }
    
    TetrominoType types[] = {
        TetrominoType::I, TetrominoType::O, TetrominoType::T,
        TetrominoType::S, TetrominoType::Z, TetrominoType::J,
        TetrominoType::L
    };
    
    return Tetromino(types[rand() % 7]);
}
