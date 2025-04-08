cmake_minimum_required(VERSION 3.28)
project(2SR LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Source files
set(SRC
    src/2SRGame.cpp
    src/card.cpp
    src/deck.cpp
    src/player.cpp
    src/randomNumbers.cpp
    src/trialLogger.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE "include/")
