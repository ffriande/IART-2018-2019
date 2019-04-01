#include "Board.h"

Board :: Board(){
    // this->matrix = {{' ',' ',' ',' ',' ',' ',' '},
    //                 {' ',' ',' ',' ',' ',' ',' '},
    //                 {' ',' ',' ',' ',' ',' ',' '},
    //                 {' ',' ',' ',' ',' ',' ',' '},
    //                 {' ',' ',' ',' ',' ',' ',' '},
    //                 {' ','b',' ',' ',' ',' ',' '},
    //                 {' ','a',' ',' ',' ',' ',' '},
    //                 {' ','R',' ',' ',' ',' ',' '},
    //                 {' ','R','a','a',' ',' ',' '},
    //                 {'R','z','R','R',' ',' ',' '}};
    this->matrix = {{' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ','a','a',' ',' ',' '},
                    {'R','a','R','R',' ','a',' '}};
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
    for (int colIndex = 1; colIndex < (int) this->matrix.at(0).size() + 1; colIndex++){
        cout << colIndex - 1 << " | ";
    }
    cout << endl;
    for (int row = 0; row < (int) this->matrix.size(); row ++) {
        cout << row;
        for (int col = 0; col < (int) this->matrix.at(row).size(); col++) {
            cout << " | " << this->matrix[row][col];
        }
        cout << " | " << endl;
    }
}

void Board :: switchPieces(int r1, int c1, int r2, int c2){
    char p1 = this->getPiece(r1, c1);
    char p2 = this->getPiece(r2, c2);
    this->setPiece(r1, c1, p2);
    this->setPiece(r2,c2, p1);
}

char Board :: getPieceBelow(int row, int col){
    return this->matrix.at(row+1).at(col);
}

bool Board :: updateMatrix(vector<int> cols){
   bool ret=false;
   for (auto col: cols)
        if(checkAbove(col))
            ret=true;
    return ret;
}
    
bool Board :: checkAbove(int column){
    bool flag=false, ret=false;
    for(int row=this->matrix.size()-1; row >= 0; row--){
        if(this->matrix.at(row).at(column)==' '){
            flag=true;
            continue;
        }
        else if (this->matrix.at(row).at(column)!=' ' && flag){
            row+=checkBelow(row, column);
            flag=false;
            ret=true;
        }
    }
    return ret;
}

int Board :: checkBelow(int r, int c){
    int counter=0;
    for(int row=r+1; row <  (int) this->matrix.size(); row++){
        if(this->matrix.at(row).at(c)==' ')
            counter++;
    }
    switchPieces(r,c,r+counter,c);
    return counter;
}