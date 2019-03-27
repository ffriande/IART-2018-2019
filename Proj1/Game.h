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
        bool verifyCombos();
        bool checkCombosHorizontal(int i, int j, vector<vector<int>> &clear);
        bool checkCombosVertical(int i, int j, vector<vector<int>> &clear);
        void gameLoop();
        void clearCombos(vector<vector<int>> clear);
};

#endif