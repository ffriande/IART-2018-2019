#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Board.h"

using namespace std;

class Game{
    private:
        Board board;
    public:
        Game();
        void welcomeMsg();
        void startGame();
        void swapPieces();
        void gameLoop();
};

#endif