#include "../headers/GameObject.h"

GameObject::GameObject(const sf::Texture& img) {sprite = sf::Sprite(img);};

void GameObject::setPosition(sf::Vector2<float> pos) {
    sprite.setPosition(pos);
}

void GameObject::setTexture(const sf::Texture& img) {
    sprite.setTexture(img);
}

sf::Sprite GameObject::getSprite() {
    return sprite;
}

bool GameObject::clickCheck(sf::Event event) {
     sf::Vector2<float> mousePosition(event.mouseButton.x, event.mouseButton.y);
     if (event.type == sf::Event::MouseButtonPressed || sprite.getGlobalBounds().contains(mousePosition))
        return true;
     return false;
}