#include "../headers/GameObject.h"
#include "../headers/Button.h"

Button::Button(const sf::Texture& img) : GameObject(img) {}

bool Button::clickCheck(sf::Event event, sf::RenderWindow& window) {
    sf::Mouse mouse;
    sf::Vector2<int> mousePosition = mouse.getPosition(window);
    if (event.type == sf::Event::MouseButtonPressed && sprite.getGlobalBounds().contains(sf::Vector2<float>(mousePosition)))
        return true;
    return false;
}
