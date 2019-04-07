#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "Board.h"
#include <unistd.h>

using namespace std;

class Game{
    private:
        /*Board of the game*/
        Board board;
        /*Columns that have suffered an alteration*/
        vector<int> movedCols;
        /*Map with all the numbers of each type of piece*/
        map<char, int> piecesNr;
        /*Number of moves already executed*/
        int nMoves;
        /*Maximum number of moves*/
        int maxMoves;
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
        Board getBoard(){return this->board;}
        void setBoard(Board newBoard){this->board = newBoard;}
        void chooseLevel();
        void swapPiecesAI(int oldRow, int oldCol, int newRow, int newCol);
        vector<int> getMovedCols(){return this->movedCols;};
        int getMaxMoves(){return this->maxMoves;};
        bool applyGravity();
        int getNrPieces();
};

#endif