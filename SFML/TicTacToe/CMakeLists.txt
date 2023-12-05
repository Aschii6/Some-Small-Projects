cmake_minimum_required(VERSION 3.27)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

add_executable(TicTacToe main.cpp
        Game.cpp
        Game.h
)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_ROOT "C:/SFML")

set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics REQUIRED)

include_directories(C:SFML)

target_link_libraries(TicTacToe sfml-graphics)