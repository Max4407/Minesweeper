cmake_minimum_required(VERSION 3.2...3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Minesweeper)

set(SFML_DIR "C:/Users/maxaf/Documents/SFML/SFML-3.0.2/lib/cmake/SFML" )

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

add_executable(sfml_test main.cpp
        source_files/GameObject.cpp
        source_files/GameObject.cpp
        source_files/Button.cpp
        source_files/Tile.cpp
        source_files/TileGrid.cpp
        source_files/Utils.cpp
        source_files/WindowLoaders.cpp
        headers/Button.h
        headers/GameObject.h
        headers/Tile.h
        headers/TileGrid.h
        headers/Utils.h
        headers/WindowLoaders.h)

target_link_libraries(sfml_test sfml-system sfml-window sfml-graphics sfml-audio)
