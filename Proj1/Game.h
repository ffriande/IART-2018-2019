#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Board.h"
#include <unistd.h>

using namespace std;

class Game{
    private:
        Board board;
        vector<int> movedCols;
        int nMoves;
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
        bool outsideBounds(int r, int c);
        vector<vector<int>> possibleMovesList(int i, int j);
        bool checkVictory();
        void printStats();
        void testMoves(vector<vector<int>> moves);
        vector<vector<int>> checkPiecesMove(int row, int col , char color);
        vector<vector<int>> checkEmptyMove(int row, int col, char color);
};

#endif