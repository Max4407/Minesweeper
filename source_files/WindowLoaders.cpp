#include "../headers/TileGrid.h"
#include "../headers/Utils.h"
#include <fstream>

bool loadGameWindow(sf::RenderWindow& window, int& rows, int& cols, int& mines, std::string name) {
    TileGrid Tiles(rows,cols,mines);

    sf::Texture dbug;
    dbug.loadFromFile("../images/debug.png");
    Button debugButton(dbug);
    debugButton.setPosition(sf::Vector2<float>((cols*32)-304 - 32,(rows+0.5)*32));

    sf::Texture minesFirstDigit;
    sf::Texture minesSecondDigit;
    sf::Texture minesThirdDigit;

    sf::Sprite firstDig;
    sf::Sprite secondDig;
    sf::Sprite thirdDig;

    firstDig.setPosition(sf::Vector2<float>(75,(rows+0.5)*32 + 16));
    secondDig.setPosition(sf::Vector2<float>(54,(rows+0.5)*32 + 16));
    thirdDig.setPosition(sf::Vector2<float>(33,(rows+0.5)*32 + 16));


    sf::Clock clock;
    float time = 0;

    bool paused = false;
    sf::Texture play;
    sf::Texture pause;

    play.loadFromFile("../images/play.png");
    pause.loadFromFile("../images/pause.png");

    Button playPause(pause);
    playPause.setPosition(sf::Vector2<float>((cols)*32-240 - 32,(rows+0.5)*32));

    bool debugMode = false;

    sf::Texture happyFace;
    sf::Texture winFace;
    sf::Texture loseFace;

    bool win = false, lose = false, leaderboardToggle = false;

    happyFace.loadFromFile("../images/face_happy.png");
    winFace.loadFromFile("../images/face_win.png");
    loseFace.loadFromFile("../images/face_lose.png");
    Button reset(happyFace);
    reset.setPosition(sf::Vector2<float>((cols*32)/2-32,(rows+0.5)*32));

    sf::Texture leaderboardButtonTexture;
    leaderboardButtonTexture.loadFromFile("../images/leaderboard.png");
    Button leaderboardButton(leaderboardButtonTexture);
    leaderboardButton.setPosition(sf::Vector2<float>((cols)*32-176 - 32,(rows+0.5)*32));

    bool open = true;
    while (open) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if (leaderboardToggle)
                break;

            if (event.type == sf::Event::Closed) {
                open = false;
                window.close();
            }

            if (reset.clickCheck(event,window)) {
                return true;
            }

            if (debugButton.clickCheck(event,window)) {
                debugMode = !debugMode;
            }

            if (leaderboardButton.clickCheck(event,window)) {
                leaderboardToggle = true;
                paused = true;
            }

            if (playPause.clickCheck(event,window)) {
                if (!paused) {
                    paused = true;
                    playPause.setTexture(play);
                } else {
                    paused = false;
                    playPause.setTexture(pause);
                }
            }
            if (!win && !lose)
                Tiles.clickCheck(event,window);
         }

        float temp = clock.restart().asSeconds();
        if (!paused && !win && !lose)
            time += temp;

        int minutes = static_cast<int>(time) / 60;
        int seconds = static_cast<int>(time) % 60;

        sf::Texture secondsFirstDigit;
        sf::Texture secondsSecondDigit;
        sf::Texture minsFirstDigit;
        sf::Texture minsSecondDigit;

        loadDigit(secondsFirstDigit,std::abs(seconds)%10);
        loadDigit(secondsSecondDigit,(std::abs(seconds) - std::abs(seconds%10))/10);
        loadDigit(minsFirstDigit,std::abs(minutes)%10);
        loadDigit(minsSecondDigit,(std::abs(minutes) - std::abs(minutes%10))/10);

        sf::Sprite secondsFirstDig(secondsFirstDigit);
        sf::Sprite secondsSecondDig(secondsSecondDigit);
        sf::Sprite minsFirstDig(minsFirstDigit);
        sf::Sprite minsSecondDig(minsSecondDigit);

        secondsFirstDig.setPosition(sf::Vector2<float>((cols)*32 - 54,(rows+0.5)*32 + 16));
        secondsSecondDig.setPosition(sf::Vector2<float>((cols)*32 - 54 - 21,(rows+0.5)*32 + 16));
        minsFirstDig.setPosition(sf::Vector2<float>((cols)*32 - 97,(rows+0.5)*32 + 16));
        minsSecondDig.setPosition(sf::Vector2<float>((cols)*32 - 97 - 21,(rows+0.5)*32 + 16));

        int fullNum = mines - Tile::numFlags;

        sf::Texture minesNegative;
        if (fullNum<0)
            loadDigit(minesNegative,10);
        sf::Sprite negativeDig(minesNegative);
        negativeDig.setPosition(sf::Vector2<float>(12,(rows+0.5)*32 + 16));

        loadDigit(minesFirstDigit,std::abs(fullNum)%10);
        loadDigit(minesSecondDigit,(std::abs(fullNum) - std::abs(fullNum%10))/10);
        loadDigit(minesThirdDigit,(std::abs(fullNum) - std::abs(fullNum%100))/100);

        firstDig.setTexture(minesFirstDigit);
        secondDig.setTexture(minesSecondDigit);
        thirdDig.setTexture(minesThirdDigit);
        negativeDig.setTexture(minesNegative);

        if (!win && Tiles.winCheck()) {
            win = true;
            reset.setTexture(winFace);
            leaderboardChange(minutes,seconds,name);
        }

        if (Tiles.loseCheck()) {
            lose = true;
            reset.setTexture(loseFace);
        }

        window.clear(sf::Color::White);
        Tiles.display(window);
        if (paused)
            Tiles.pausedDraw(window,rows,cols);
        else if (debugMode)
            Tiles.debugModeDraw(window, rows, cols);
        window.draw(debugButton.getSprite());
        window.draw(firstDig);
        window.draw(secondDig);
        window.draw(thirdDig);
        window.draw(negativeDig);
        window.draw(secondsFirstDig);
        window.draw(secondsSecondDig);
        window.draw(minsFirstDig);
        window.draw(minsSecondDig);
        window.draw(playPause.getSprite());
        window.draw(reset.getSprite());
        window.draw(leaderboardButton.getSprite());
        window.display();

        while (leaderboardToggle) {
            int width = cols*16;
            int height = rows*16+50;
            sf::RenderWindow leaderboard(sf::VideoMode(width,height), "Leaderboard");

            sf::Font english;
            english.loadFromFile("../fonts/font.ttf");

            std::ifstream readLeaderboard;
            readLeaderboard.open("../leaderboard.txt");
            std::string list = "";
            std::string name, time;
            int i = 1;
            while (readLeaderboard >> time >> name) {
                list += std::to_string(i) + ".    " + time.substr(0,time.length()-1) + "    " + name + "\n\n";
                i++;
            }

            sf::Text leaderboardText(list,english, 18);
            leaderboardText.setStyle(sf::Text::Bold);
            leaderboardText.setFillColor(sf::Color::White);
            setText(leaderboardText,width/2 , height/2 + 20);

            sf::Text leaderboardHeader("LEADERBOARD",english,20);
            leaderboardHeader.setStyle(sf::Text::Underlined | sf::Text::Bold);
            leaderboardHeader.setFillColor(sf::Color::White);
            setText(leaderboardHeader,width/2 , height/2 -120);

            leaderboard.clear(sf::Color::Blue);
            leaderboard.draw(leaderboardText);
            leaderboard.draw(leaderboardHeader);
            leaderboard.display();

            while(leaderboard.isOpen()) {
                while(leaderboard.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        leaderboardToggle = false;
                        paused = false;
                        leaderboard.close();
                    }
                }
            }
        }
    }
    return false;
}

std::string loadWelcomeWindow(sf::RenderWindow& window,int width,int height) {
    sf::Font english;
    english.loadFromFile("../fonts/font.ttf");

    sf::Text welcome("WELCOME TO MINESWEEPER!",english,24);
    setText(welcome,width/2,height/2-150);
    welcome.setStyle(sf::Text::Underlined | sf::Text::Bold);
    welcome.setFillColor(sf::Color::White);

    sf::Text enterName("Enter your name:", english, 20);
    setText(enterName,width/2,height/2-75);
    enterName.setStyle(sf::Text::Bold);
    enterName.setFillColor(sf::Color::White);

    sf::Text input("|", english, 18);
    input.setStyle(sf::Text::Bold);
    input.setFillColor(sf::Color::White);

    bool open = true;
    while (open) {
        setText(input,width/2,height/2-45);

        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 13 && input.getString().getSize() > 1) {
                    open = false;//enter name
                    std::string result = input.getString();
                    return result.substr(0,result.length() - 1);
                }
                if (event.text.unicode == 8) {   //backspace logic
                    if (input.getString().getSize() > 1)
                        input.setString(input.getString().substring(0,input.getString().getSize()-2) + "|");
                }
                else if (input.getString().getSize() == 1)
                    (input.setString(std::string(1,static_cast<char>(std::toupper(static_cast<char>(event.text.unicode)))) + "|"));
                else if (input.getString().getSize() <= 10)    // enter name up to 10 char
                    (input.setString(input.getString().substring(0,input.getString().getSize()-1) + static_cast<char>(std::tolower(static_cast<char>(event.text.unicode))) + "|"));
            }

            if (event.type == sf::Event::Closed) {
                open = false;
                window.close();
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(welcome);
        window.draw(enterName);
        window.draw(input);
        window.display();
    }
    return "";
}