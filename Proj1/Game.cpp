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
    this->board.switchPieces(1,0,0,1);
}

void Game :: startGame(){
    this->board.printBoard();
    this->swapPieces();
    this->board.printBoard();
    this->gameLoop();
}

void Game :: gameLoop(){
    while(true){
        this->swapPieces();
        this->board.printBoard();
    }
}