#include "Game.h"

Game :: Game(){
    this->board = Board();
}

void Game :: welcomeMsg(){
    cout << "----- Welcome to BREAK THE ICE - SNOW WORLD -----" << endl;
}

void Game :: swapPieces(){
    cout << "Swap Pieces" << endl;
    int r1, c1, r2, c2;
    cout << "Piece 1 : Row" << endl;
    cin >> r1;
    cout << "Piece 1 : Col" << endl;
    cin >> c1;
    cout << "Piece 2 : Row" << endl;
    cin >> r2;
    cout << "Piece 2 : Col" << endl;
    cin >> c2;
    this->board.switchPieces(r1,c1,r2,c2);
}

void Game :: startGame(){
    this->board.printBoard();
    this->swapPieces();
    cout << this->verifyHorizontalCombos() << endl;
    cout << this->verifyVerticalCombos() << endl;
    this->board.printBoard();
    this->gameLoop();
}

void Game :: gameLoop(){
    while(true){
        this->swapPieces();
        cout << this->verifyHorizontalCombos() << endl;
        cout << this->verifyVerticalCombos() << endl;
        this->board.printBoard();
    }
}

bool Game :: verifyCombos(){
    if (this->verifyHorizontalCombos() && this->verifyVerticalCombos())
        return true;
    return false;
}

bool Game :: verifyHorizontalCombos(){
    for(int i = 0; i < this->board.getBoard().size(); i++){
        for (int j = 0; j < this->board.getBoard().at(i).size() - 2; j++){
            if (this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i).at(j+1) && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i).at(j+2) && this->board.getBoard().at(i).at(j) != ' '){
                this->board.setPiece(i,j,' ');
                this->board.setPiece(i,j+1,' ');
                this->board.setPiece(i,j+2,' ');
            }
        }    
    }
    return false;
}

bool Game :: verifyVerticalCombos(){
    for(int i = 0; i < this->board.getBoard().size() - 2; i++){
        for (int j = 0; j < this->board.getBoard().at(i).size(); j++){
            if (this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i+1).at(j) && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i+2).at(j) && this->board.getBoard().at(i).at(j) != ' '){
                this->board.setPiece(i,j,' ');
                this->board.setPiece(i+1,j,' ');
                this->board.setPiece(i+2,j,' ');
            }
        }    
    }
    return false;
}