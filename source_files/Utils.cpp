#include "../headers/Utils.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdio>

void setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
    textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

std::array<std::pair<int, int>, 8> NEIGHBOR_OFFSETS = {
    {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    }
};

void loadDigit(sf::Texture &tex, int digit) {
    tex.loadFromFile("../images/digits.png", sf::IntRect(21*(digit),0,21,36));
}

void leaderboardChange (int min, int sec, std::string name) {
    std::ifstream readLeaderboard;
    readLeaderboard.open("../leaderboard.txt");
    std::string currName, time;
    std::string newList = "";
    int pos = 6;
    while (readLeaderboard >> time >> currName) {
        int oldTime = std::stoi(time.substr(0,2)) * 60 + std::stoi(time.substr(3,4));
        int newTime = min*60 + sec;
        if (oldTime>newTime)
            pos--;
    }
    readLeaderboard.clear();
    readLeaderboard.seekg(0, std::ios::beg);
    int i = 1;
    std::string newTimeStr = "";
    if (std::to_string(min).length() < 2)
        newTimeStr += "0";
    newTimeStr += std::to_string(min) + ":";
    if (std::to_string(sec).length() < 2)
        newTimeStr += "0";
    newTimeStr += std::to_string(sec);

    while (readLeaderboard >> time >> currName) {
        if (i == pos)
            newList += newTimeStr + ", " + name + "*\n";
        newList += time + " " + currName + "\n";
        i++;
        if (i >= 5)
            break;
    }
    std::remove("../leaderboard.txt");
    std::ofstream out("../leaderboard.txt");
    out << newList;
}