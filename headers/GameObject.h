#ifndef MINESWEEPER_GAMEOBJECT_H
#define MINESWEEPER_GAMEOBJECT_H
#include "SFML/Graphics.hpp"

class GameObject {
protected:
    sf::Sprite sprite;
public:
    virtual ~GameObject() = default;
    GameObject() = default;
    explicit GameObject(const sf::Texture& img);

    void setPosition(sf::Vector2<float> pos);
    void setTexture(const sf::Texture& img);

    sf::Sprite getSprite();

    virtual bool clickCheck(sf::Event event);
};

#endif //MINESWEEPER_GAMEOBJECT_H