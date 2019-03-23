#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

using namespace std;

class Board{
    private:
        vector<vector<char> > matrix;
    public:
        Board();
        Board(vector<vector<char>> matrix);
        vector<vector<char>> getBoard();
        void setBoard(vector<vector<char>> newBoard);
        char getPiece(int row, int col);
        void setPiece(int row, int col, char piece);
        void printBoard();
        void switchPieces(int r1, int c1, int r2, int c2);
};

#endif