cmake_minimum_required(VERSION 3.10)
project(TetrisGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

# Source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Tetromino.cpp
    src/Renderer.cpp
    src/AudioManager.cpp
)

# Create executable
add_executable(tetris ${SOURCES})

# Link libraries
target_link_libraries(tetris
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# Copy assets to build directory
if(NOT EXISTS ${CMAKE_BINARY_DIR}/assets)
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
endif()
