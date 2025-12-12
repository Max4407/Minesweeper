#ifndef MINESWEEPER_TILEGRID_H
#define MINESWEEPER_TILEGRID_H
#include "SFML/Graphics.hpp"
#include "../headers/Tile.h"

class TileGrid {
private:
    Tile** Tiles;
    int rows, cols;
    bool debugMode = false;
public:
    TileGrid(int r, int c, int mines);

    void display(sf::RenderWindow& window);

    void flip(int row, int col);

    void clickCheck(sf::Event event, sf::RenderWindow& window);
    bool winCheck();
    bool loseCheck();

    void debugModeDraw(sf::RenderWindow& window,int rows, int cols);
    void pausedDraw(sf::RenderWindow& window,int rows, int cols);
};

#endif //MINESWEEPER_TILEGRID_H