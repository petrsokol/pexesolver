cmake_minimum_required(VERSION 3.26)
project(pexesok)

set(CMAKE_CXX_STANDARD 23)

add_executable(pexesok main.cpp
        Tile.cpp
        Tile.h
        Board.cpp
        Board.h
)
