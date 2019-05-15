#include "Game.h"


Game::Game(){
    this->numberOfRedPieces=0;
    this->numberOfWhitePieces=0;
    this->numberOfPiecesInserted=0;
    printBoard();
    gameLoopPvP();
}


void Game::printBoard()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << " O - Represents a free space in the board\n"
    << " W - Represents a white piece on the board\n"
    << " R - Represents a black piece on the board\n\n\n";
    cout << "   | 0 |1 |2 |3 |4 |5 |6 |\n"
         << "---|---------------------|---\n";
    for (int r = 0; r < (int)this->board.size(); r++)
    {
        cout << " " << r << " |";
        for (int c = 0; c < (int)this->board.at(r).size(); c++)
        {
            if(this->board.at(r).at(c)==-1)
                cout << "---";
            if(this->board.at(r).at(c)==-2)
                cout << " | ";
            if(this->board.at(r).at(c)==-3)
                cout << "   ";
            if(this->board.at(r).at(c)==0)
                cout << " O ";
            if(this->board.at(r).at(c)==1)
                cout << " W ";
            if(this->board.at(r).at(c)==2)
                cout << " R ";
        }
        cout << "| " << r << endl;
    }
    cout << "---|---------------------|---\n"
    << "   | 0 |1 |2 |3 |4 |5 |6 |\n\n";
}


void Game::askMove(int player){
    if(player == 1)
        cout << "WHITE Player turn.\n";
    else
        cout << "RED Player turn.\n";
    int firstChoose;
    if(this->numberOfPiecesInserted != 18){
        cout << "You will choose a place to insert a piece.\n";
        if(player == 1)
            cout << "You have " << (9-this->numberOfWhitePieces) << " pieces left to insert.\n";
        if(player == 2)
            cout << "You have " << (9-this->numberOfRedPieces) << " pieces left to insert.\n";
        firstChoose=1;
    }else
    {
        cout << "Choose a piece.";
        firstChoose=2;
    }
    int column;
    int row;
    do{
        do{
            cout << "Select a Column (From 0 to 6):\n";
            cin >> column;
        }while(column < 0 && column > 6);

        do{
            cout << "Select a Row (From 0 to 6):\n";
            cin >> row;
        }while(row < 0 && row > 6);
    }while(!validChoose(player,firstChoose,row,column));

    if(this->numberOfPiecesInserted == 18){
        int typeMove=2;
        if(player == 1 && this->numberOfWhitePieces == 3)
            cout << "Choose an empty space (O) to fly.\n";
        else if(player == 2 && this->numberOfRedPieces == 3)
            cout << "Choose an empty space (O) to fly.\n";
        else{
            cout << "Choose an empty adjacent (O) to move.\n";
            typeMove=1;
        }
        makeMove(player,typeMove,row,column);
    }else
    {
        this->board.at(row).at(column)=player;
    }
}

void Game::makeMove(int player, int typeMove, int r, int c){
    this->board.at(r).at(c)=player;
}

bool Game::validChoose(int player, int firstChoose, int row, int column){
    if(firstChoose==1){
        if(this->board.at(row).at(column)!=0)
            return false;
    }else
    {
        if(this->board.at(row).at(column)!=player)
            return false;
    }
    return true;
}

void Game::gameLoopPvP()
{
    askMove(1);
    printBoard();
    askMove(2);
    printBoard();
}