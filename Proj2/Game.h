#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

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
    int numberOfPiecesInserted;
    int numberOfRedPieces;
    int numberOfWhitePieces;
  public:
    Game();
    void printBoard();
};

#endif