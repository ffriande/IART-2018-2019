#include "Board.h"

Board :: Board(){
    this->matrix = {{' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ','x',' '},
                    {' ',' ','x','x',' ','x',' '}};
}

Board :: Board(vector<vector<char>> matrix){
    this->matrix = matrix;
}

vector<vector<char>> Board :: getBoard(){
    return this->matrix;
}

void Board :: setBoard(vector<vector<char>> newBoard){
    this->matrix = newBoard;
}

char Board :: getPiece(int row, int col){
    return this->matrix.at(row).at(col);
}

void Board :: setPiece(int row, int col, char piece){
    this->matrix.at(row).at(col) = piece;
}

void Board :: printBoard(){
    cout << "  | ";
    for (int colIndex = 1; colIndex < this->matrix.at(0).size() + 1; colIndex++){
        cout << colIndex - 1 << " | ";
    }
    cout << endl;
    for (int row = 0; row < this->matrix.size(); row ++) {
        cout << row;
        for (int col = 0; col < this->matrix.at(row).size(); col++) {
            cout << " | " << this->matrix[row][col];
        }
        cout << " | " << endl;
    }
}

void Board :: switchPieces(int r1, int c1, int r2, int c2){
    char p1 = this->getPiece(r1, c1);
    char p2 = this->getPiece(r2, c2);
    cout << "Peca 1:" << p1 << ";";
    cout << "Peca 2:" << p2 << ";";
    this->setPiece(r1, c1, p2);
    this->setPiece(r2,c2, p1);
}

char Board :: getPieceBelow(int row, int col){
    return this->matrix.at(row+1).at(col);
}