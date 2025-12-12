#ifndef MINESWEEPER_WINDOWLOADERS_H
#define MINESWEEPER_WINDOWLOADERS_H
#include "SFML/Graphics.hpp"

std::string loadWelcomeWindow(sf::RenderWindow& window,int width,int height);
bool loadGameWindow(sf::RenderWindow& window, int& rows, int& cols, int& mines, std::string name);

#endif //MINESWEEPER_WINDOWLOADERS_H