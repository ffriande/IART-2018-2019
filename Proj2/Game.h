#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Game
{
  private:
    //board of the current game.
    vector<vector<int>> board = {
        {0, -1, -1, 0, -1, -1, 0},
        {-2, 0, -1, 0, -1, 0, -2},
        {-2, -2, 0, 0, 0, -2, -2},
        {0, 0, 0, -3, 0, 0, 0},
        {-2, -2, 0, 0, 0, -2, -2},
        {-2, 0, -1, 0, -1, 0, -2},
        {0, -1, -1, 0, -1, -1, 0}};
    //total number of pieces inserted in the board. it does not count the actual number of pieces in the board.
    int numberOfPiecesInserted;
    //number of red pieces in the board.
    int numberOfRedPieces;
    //number of white pieces in the board.
    int numberOfWhitePieces;
  public:
    Game();
    void printBoard();
    void askMove(int player);
    void makeMove(int player, int r, int c, vector<vector<int>> validMoves);
    bool validChoose(int player, int firstChoose, int row, int column);
    bool vectorMember(vector<vector<int>> analyse, vector<int> coord);
    bool validDest(int player, int typeMove, int row, int column, int prevRow, int prevColumn);
    bool checkAdjacent(int row1, int column1, int row2, int column2);
    bool adjacentHorizontal(int row, int col, int colDif);
    bool adjacentVertical(int col, int row, int rowDif);
    void validInput(int &row, int &col);
    vector<vector<int>> getFirstChoice(int player);
    vector<vector<int>> getMoveCoords(int player, int row, int column);
    vector<vector<int>> getPiecesOf(int symbol);
    bool checkNoMovesLeft(int player);
    bool checkLose(int player);
    void gameLoopPvP();
};

#endif