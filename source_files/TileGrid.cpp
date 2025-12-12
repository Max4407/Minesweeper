#include "../headers/TileGrid.h"
#include "../headers/Tile.h"
#include "../headers/Utils.h"

TileGrid::TileGrid(int r, int c, int mines) : rows(r), cols(c) {
    Tiles = new Tile*[rows];
    for (int i = 0; i < rows; i++)
        Tiles[i] = new Tile[cols];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tiles[i][j].setPosition(sf::Vector2<float>(32*j,32*i));
        }
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < mines; i++) {
        int new_mine = std::rand() % (rows * cols);
        int row = new_mine/cols;
        int col = new_mine % cols;
        if (Tiles[row][col].isMine())
            i--;
        else
            Tiles[row][col].plantMine();
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int bombCount = 0;
            for (int k = 0; k < 8; k++) {
                int test_row = i + NEIGHBOR_OFFSETS[k].first;
                int test_col = j + NEIGHBOR_OFFSETS[k].second;
                if (test_row >= 0 && test_col >= 0 && test_row < rows && test_col < cols && Tiles[test_row][test_col].isMine())
                    bombCount++;
                Tiles[i][j].setNumber(bombCount);
            }

        }
    }
}

void TileGrid::display(sf::RenderWindow& window) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tiles[i][j].draw(window);
        }
    }
}

void TileGrid::flip(int row, int col) {
    Tiles[row][col].Tile::flip();
    if (Tiles[row][col].getNumber() == 0 && !Tiles[row][col].isMine()) {
        for (int k = 0; k < 8; k++) {
            int test_row = row + NEIGHBOR_OFFSETS[k].first;
            int test_col = col + NEIGHBOR_OFFSETS[k].second;
            if (test_row >= 0 && test_col >= 0 && test_row < rows && test_col < cols && !Tiles[test_row][test_col].isFlipped())
                flip(test_row,test_col);
        }
    }
}

void TileGrid::clickCheck(sf::Event event, sf::RenderWindow& window) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (Tiles[i][j].tileClickCheck(event,window) == 1 && !Tiles[i][j].isFlagged())
                flip(i,j);
            if (Tiles[i][j].tileClickCheck(event,window) == 2)
                Tiles[i][j].flag(window);
        }
    }
}

bool TileGrid::winCheck() {
    bool win = true;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!Tiles[i][j].isMine() && !Tiles[i][j].isFlipped())
                win = false;
        }
    }
    return win;
}

bool TileGrid::loseCheck() {
    bool lose = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (Tiles[i][j].isMine() && Tiles[i][j].isFlipped())
                lose = true;
        }
    }
    return lose;
}

void TileGrid::debugModeDraw(sf::RenderWindow& window,int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (Tiles[i][j].isMine())
                Tiles[i][j].drawMine(window);
        }
    }
}

void TileGrid::pausedDraw(sf::RenderWindow& window,int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tiles[i][j].drawFlipped(window);
        }
    }
}
