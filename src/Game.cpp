#include "Game.h"
#include <iostream>

Game::Game() : window(nullptr), renderer(nullptr), posX(3), posY(0), gameState(GameState::MENU),
               running(true), gameRenderer(nullptr), audioManager(nullptr), score(0), lines(0), 
               level(1), lastDropTime(0), dropInterval(1000) {
}

Game::~Game() {
    if (gameRenderer) {
        delete gameRenderer;
    }
    if (audioManager) {
        delete audioManager;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL initialization failed!" << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "Tetris Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600, 650,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window creation failed!" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer creation failed!" << std::endl;
        return false;
    }

    gameRenderer = new Renderer(renderer);
    audioManager = new AudioManager();
    
    if (!audioManager->initialize()) {
        std::cerr << "Audio initialization failed!" << std::endl;
    }

    currentTetromino = Tetromino::createRandom();
    nextTetromino = Tetromino::createRandom();
    
    gameState = GameState::PLAYING;
    lastDropTime = SDL_GetTicks();

    return true;
}

void Game::run() {
    SDL_Event event;
    
    while (running) {
        handleInput();
        update();
        render();
        
        SDL_Delay(16); // ~60 FPS
    }
}

void Game::handleInput() {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        moveTetromino(-1);
                        break;
                    case SDLK_RIGHT:
                        moveTetromino(1);
                        break;
                    case SDLK_DOWN:
                        dropTetromino();
                        break;
                    case SDLK_UP:
                        rotateTetromino();
                        break;
                    case SDLK_SPACE:
                        if (gameState == GameState::PLAYING) {
                            gameState = GameState::PAUSED;
                        } else if (gameState == GameState::PAUSED) {
                            gameState = GameState::PLAYING;
                        }
                        break;
                    case SDLK_r:
                        if (gameState == GameState::GAME_OVER) {
                            resetGame();
                        }
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}

void Game::update() {
    if (gameState != GameState::PLAYING) return;

    Uint32 currentTime = SDL_GetTicks();
    
    if (currentTime - lastDropTime > dropInterval) {
        dropTetromino();
        lastDropTime = currentTime;
    }
}

void Game::render() {
    gameRenderer->clear();

    gameRenderer->renderBoard(board);
    gameRenderer->renderTetromino(currentTetromino, posX, posY);
    gameRenderer->renderNextTetromino(nextTetromino);
    gameRenderer->renderScore(score, lines, level);

    if (gameState == GameState::GAME_OVER) {
        gameRenderer->renderGameOver(score);
    }

    gameRenderer->present();
}

void Game::spawnNewTetromino() {
    currentTetromino = nextTetromino;
    nextTetromino = Tetromino::createRandom();
    posX = 3;
    posY = 0;

    if (!board.canPlace(currentTetromino, posX, posY)) {
        gameState = GameState::GAME_OVER;
    }
}

void Game::dropTetromino() {
    if (board.canPlace(currentTetromino, posX, posY + 1)) {
        posY++;
    } else {
        board.placeTetromino(currentTetromino, posX, posY);
        checkLineClears();
        spawnNewTetromino();
    }
}

void Game::moveTetromino(int dx) {
    if (board.canPlace(currentTetromino, posX + dx, posY)) {
        posX += dx;
    }
}

void Game::rotateTetromino() {
    Tetromino rotated = currentTetromino;
    rotated.rotate();
    
    if (board.canPlace(rotated, posX, posY)) {
        currentTetromino = rotated;
    }
}

void Game::checkLineClears() {
    auto fullRows = board.getFullRows();
    
    if (!fullRows.empty()) {
        board.clearRows(fullRows);
        audioManager->playSound("lineClear");
        
        int rowCount = fullRows.size();
        score += 100 * rowCount;
        lines += rowCount;
        updateDifficulty();
    }
}

void Game::updateDifficulty() {
    level = lines / 10 + 1;
    dropInterval = std::max(100, 1000 - (level - 1) * 50);
}

void Game::resetGame() {
    board.reset();
    score = 0;
    lines = 0;
    level = 1;
    dropInterval = 1000;
    gameState = GameState::PLAYING;
    spawnNewTetromino();
}

void Game::showGameOver() {
    std::cout << "Game Over! Final Score: " << score << std::endl;
}
