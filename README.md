# Tetris Game in C++

A feature-rich Tetris game implementation in C++ using SDL2 library.

## Features

- **7 Different Tetromino Pieces**: Each with distinct colors
  - I-piece (Cyan)
  - O-piece (Yellow)
  - T-piece (Purple)
  - S-piece (Green)
  - Z-piece (Red)
  - J-piece (Blue)
  - L-piece (Orange)

- **Game Mechanics**:
  - Piece rotation
  - Line clearing with scoring
  - Progressive difficulty (increasing drop speed)
  - Level system based on lines cleared
  - Next piece preview
  - Score tracking

- **Controls**:
  - **LEFT/RIGHT Arrow Keys** - Move piece horizontally
  - **DOWN Arrow Key** - Drop piece faster
  - **UP Arrow Key** - Rotate piece
  - **SPACE** - Pause/Resume game
  - **R** - Restart game (when game over)

## Requirements

- C++17 or later
- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer
- CMake 3.10+

## Installation

### Ubuntu/Debian

```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev cmake
```

### macOS (with Homebrew)

```bash
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer cmake
```

### Windows

Download and install SDL2 development libraries from [libsdl.org](https://libsdl.org/)

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
./tetris
```

## Project Structure

```
CopilotGame/
├── CMakeLists.txt
├── include/
│   ├── Game.h
│   ├── Board.h
│   ├── Tetromino.h
│   ├── Renderer.h
│   └── AudioManager.h
├── src/
│   ├── main.cpp
│   ├── Game.cpp
│   ├── Board.cpp
│   ├── Tetromino.cpp
│   ├── Renderer.cpp
│   └── AudioManager.cpp
└── assets/
    └── sounds/
        ├── drop.wav
        ├── lineclear.wav
        └── bgm.ogg
```

## Game Mechanics

### Scoring

- 100 points per line cleared
- Score increases with level

### Difficulty

- Starts at Level 1 with 1 second drop interval
- Level increases every 10 lines cleared
- Drop interval decreases as level increases (minimum 100ms)

### Game Over

- Game ends when pieces reach the top of the board
- Press R to restart

## Future Enhancements

- Sound effects and background music
- High score persistence
- Multiplayer modes
- Advanced AI
- Different game modes (Marathon, Time Attack, etc.)

## License

MIT License - feel free to use and modify this code!
