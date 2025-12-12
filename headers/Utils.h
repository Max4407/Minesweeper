#ifndef MINESWEEPER_UTILS_H
#define MINESWEEPER_UTILS_H
#include "SFML/Graphics.hpp"
#include <array>

void setText(sf::Text &text, float x, float y);

extern std::array<std::pair<int, int>, 8> NEIGHBOR_OFFSETS;

void loadDigit(sf::Texture &tex, int digit);

void leaderboardChange (int min, int sec, std::string name);
#endif //MINESWEEPER_UTILS_H