#ifndef MINESWEEPER_BUTTON_H
#define MINESWEEPER_BUTTON_H
#include "SFML/Graphics.hpp"
#include "../headers/GameObject.h"

class Button : public GameObject {
public:
    Button() = default;
    explicit Button(const sf::Texture& img);

    virtual bool clickCheck(sf::Event event, sf::RenderWindow& window);
};
#endif //MINESWEEPER_BUTTON_H