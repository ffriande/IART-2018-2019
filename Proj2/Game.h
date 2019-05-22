#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <ctime>

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
    Game(int option, int agent1, int depth1, int agent2, int depth2);
    void startNewGame(int option, int agent1, int depth1, int agent2, int depth2);
    bool isInsert();
    int getnrPlayerPieces(int player);
    void printBoard();
    void askMove(int player);
    void makeMove(int player, int r, int c, vector<vector<int>> validMoves);
    void askElimination(int player, int row, int column);
    void getBotNextMove(int player, int agent, int depth);
    int count2inRow(int player);
    bool check2inRowHorizontal(int player, int r, int c);
    bool check2inRowVertical(int player, int r, int c);
    vector<vector<int>> check3InRow(int player, int row, int column);
    bool checkConnected(vector<vector<int>> coords, int row, int column);
    vector<vector<int>> validElimination(int player);
    bool validChoose(int player, int firstChoose, int row, int column);
    bool vectorMember(vector<vector<int>> analyse, vector<int> coord);
    bool validDest(int player, int typeMove, int row, int column, int prevRow, int prevColumn);
    bool checkAdjacent(int row1, int column1, int row2, int column2);
    void movePiece(int player, int row1, int col1, int row2, int col2);
    void insertPiece(int player, int row, int column);
    void removePiece(int player, int row, int column);
    bool adjacentHorizontal(int row, int col, int colDif);
    bool adjacentVertical(int col, int row, int rowDif);
    void validInput(int &row, int &col);
    vector<vector<int>> getFirstChoice(int player);
    vector<vector<int>> getMoveCoords(int player, int row, int column);
    vector<vector<int>> getPiecesOf(int symbol);
    bool checkNoMovesLeft(int player);
    bool checkLose(int player);
    void gameLoopPvP();
    void gameLoopCvP(int agent, int depth);
    void gameLoopPvC(int agent, int depth);
    void gameLoopCvC(int agent1, int depth1, int agent2, int depth2);
};

#endif