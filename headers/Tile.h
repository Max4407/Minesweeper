#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H
#include "SFML/Graphics.hpp"
#include "../headers/Button.h"

class Tile : public Button {
private:
    bool bomb;
    bool flagged;
    int bordering;
    bool flipped_;
    sf::Texture hidden;
    sf::Texture flipped;
    sf::Texture number;
    sf::Texture bombImage;
    sf::Texture flagImage;
public:

    static int numFlags;

    Tile();

    void setNumber(int num);
    void plantMine();

    int getNumber() const;
    bool isMine() const;
    bool isFlipped() const;
    bool isFlagged() const;

    int tileClickCheck(sf::Event event, sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);
    void drawMine(sf::RenderWindow& window);
    void drawFlipped(sf::RenderWindow& window);

    void flag(sf::RenderWindow& window);

    void flip();
};


#endif //MINESWEEPER_TILE_H