#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <map>
#include "Board.h"
#include <unistd.h>

using namespace std;

class Game{
    private:
        Board board;
        vector<int> movedCols;
        map<char, int> piecesNr;
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
        bool isPossible(vector<int> newPos, vector<vector<int>> list);
        bool checkVictory();
        bool checkGameOver();
        bool checkDuplicated(vector<vector<int>> clear, vector<int> coords);
        void countPiecesNr();
        void printStats();
        void testMoves(vector<vector<int>> moves);
        vector<vector<int>> checkPiecesMove(int row, int col , char color);
        vector<vector<int>> checkEmptyMove(int row, int col, char color);
};

#endif