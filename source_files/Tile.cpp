#include "../headers/GameObject.h"
#include "../headers/Button.h"
#include "../headers/Tile.h"


Tile::Tile() : bomb(false), flipped_(false), flagged(false), Button() {
    hidden.loadFromFile("../images/tile_hidden.png");
    flipped.loadFromFile("../images/tile_revealed.png");
    bombImage.loadFromFile("../images/mine.png");
    flagImage.loadFromFile("../images/flag.png");
    setTexture(hidden);
}

void Tile::setNumber(int num) {
    bordering = num;
}

int Tile::getNumber() const{
    return bordering;
}

bool Tile::isMine() const{
    return bomb;
}

bool Tile::isFlagged() const{
    return flagged;
}

void Tile::plantMine() {
    bomb = true;
}

bool Tile::isFlipped() const {
    return flipped_;
}

int Tile::tileClickCheck(sf::Event event, sf::RenderWindow& window) {
    sf::Mouse mouse;
    sf::Vector2<int> mousePosition = mouse.getPosition(window);
    if (event.type == sf::Event::MouseButtonPressed && sprite.getGlobalBounds().contains(sf::Vector2<float>(mousePosition))) {
        if (event.mouseButton.button == sf::Mouse::Left)
            return 1;
        if (event.mouseButton.button == sf::Mouse::Right)
            return 2;
    }
    return 0;
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    if (flagged && !flipped_) {
        sf::Sprite flag(flagImage);
        flag.setPosition(sprite.getPosition());
        window.draw(flag);
    } else if (bomb && flipped_) {
        sf::Sprite mine(bombImage);
        mine.setPosition(sprite.getPosition());
        window.draw(mine);
    } else if (bordering != 0 && flipped_) {
        sf::Sprite num(number);
        num.setPosition(sprite.getPosition());
        window.draw(num);
    }
}

void Tile::drawMine(sf::RenderWindow& window) {
    window.draw(sprite);
    sf::Sprite mine(bombImage);
    mine.setPosition(sprite.getPosition());
    window.draw(mine);
}

void Tile::drawFlipped(sf::RenderWindow& window) {
    sf::Sprite flippedTile(flipped);
    flippedTile.setPosition(sprite.getPosition());
    window.draw(flippedTile);
}

void Tile::flag(sf::RenderWindow& window) {
    if (flagged) {
        flagged = false;
        numFlags--;
    } else {
        flagged = true;
        numFlags++;
    }
}

void Tile::flip() {
    if (flipped_ == false) {
        flipped_ = true;
        setTexture(flipped);
        switch (bordering) {
            case 1:
                number.loadFromFile("../images/number_1.png");
                break;
            case 2:
                number.loadFromFile("../images/number_2.png");
                break;
            case 3:
                number.loadFromFile("../images/number_3.png");
                break;
            case 4:
                number.loadFromFile("../images/number_4.png");
                break;
            case 5:
                number.loadFromFile("../images/number_5.png");
                break;
            case 6:
                number.loadFromFile("../images/number_6.png");
                break;
            case 7:
                number.loadFromFile("../images/number_7.png");
                break;
            case 8:
                number.loadFromFile("../images/number_8.png");
                break;
            default:
                break;
        };
    };
};


int Tile::numFlags = 0;