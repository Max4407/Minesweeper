#include "headers/WindowLoaders.h"
#include <fstream>

int main() {

    std::ifstream config("../config.cfg");
    int cols, rows, mines;
    config >> cols >> rows >> mines;
    config.close();
    sf::RenderWindow window(sf::VideoMode(cols*32,rows*32 + 100), "Minesweeper");

    while(window.isOpen())
    {
        bool playing = true;
        std::string name = loadWelcomeWindow(window,cols*32,rows*32+100);
        while (playing) {
              playing = loadGameWindow(window, rows, cols, mines, name);
        }
    }
    return 0;
}