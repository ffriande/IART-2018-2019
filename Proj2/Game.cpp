#include "Game.h"

#define PLACE 1
#define MOVE 2
#define FLY 3


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
    int placeOrMove;
    if(this->numberOfPiecesInserted != 18){ 
        cout << "You will choose a place to insert a piece.\n";
        if(player == 1)
            cout << "You have " << (9-this->numberOfWhitePieces) << " pieces left to insert.\n";
        if(player == 2)
            cout << "You have " << (9-this->numberOfRedPieces) << " pieces left to insert.\n";
        placeOrMove=1;
    }else
    {
        cout << "Choose one of your pieces.";
        placeOrMove=2;
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
    }while(!validChoose(player,placeOrMove,row,column) && cout<< "\nInvalid input\n");

    if(placeOrMove==2){
        int typeMove=FLY;
        if(player == 1 && this->numberOfWhitePieces == 3)
            cout << "Choose an empty space (O) to fly.\n";
        else if(player == 2 && this->numberOfRedPieces == 3)
            cout << "Choose an empty space (O) to fly.\n";
        else{
            cout << "Choose an empty adjacent (O) to move.\n";
            typeMove=MOVE;
        }
        makeMove(player,typeMove,row,column);
    }else
    {
        makeMove(player,PLACE,row,column);
    }
}


void Game::makeMove(int player, int typeMove, int r, int c){
    int destRow, destCol;
    if(typeMove==PLACE){
        do{
            do{
                cout << "Column (From 0 to 6):\n";
                cin >> destCol;
            }while(destCol < 0 && destCol > 6);
            do{
                cout << "Row (From 0 to 6):\n";
                cin >> destRow;
            }while(destRow < 0 && destRow > 6);
        }while(!validChoose(player, PLACE, destRow, destCol) && cout<< "\nInvalid input\n"); 
    }

    else if(typeMove==MOVE){
        do{
            do{
                cout << "Column (From 0 to 6):\n";
                cin >> destCol;
            }while(destCol < 0 && destCol > 6);
            do{
                cout << "Row (From 0 to 6):\n";
                cin >> destRow;
            }while(destRow < 0 && destRow > 6);
        }while(!validChooseMove(r,c,destRow,destCol) && cout<< "\nInvalid input\n"); 

        this->board.at(r).at(c)=0;
        this->board.at(destRow).at(destCol)=player;
    }
    else if(typeMove==FLY){
        do{
            do{
                cout << "Column (From 0 to 6):\n";
                cin >> destCol;
            }while(destCol < 0 && destCol > 6);
            do{
                cout << "Row (From 0 to 6):\n";
                cin >> destRow;
            }while(destRow < 0 && destRow > 6);
        }while(!validChoose(player,1,destRow,destCol) && cout<< "\nInvalid input\n"); 

        this->board.at(r).at(c)=0;
        this->board.at(destRow).at(destCol)=player;
    }
}

bool Game::validChoose(int player, int placeOrMove, int row, int column){
    if(placeOrMove==1){
        if(this->board.at(row).at(column)!=0)
            return false;
    }else
    {
        if(this->board.at(row).at(column)!=player)
            return false;
    }
    return true;
}

//for moving, not flying
bool Game::validChooseMove(int row, int column, int destRow, int destColumn){
    if((destColumn==column && (destRow==row+1 || destRow==row-1)) || (destRow==row && (destColumn==column+1 || destColumn==column-1)) && this->board.at(destRow).at(destColumn)==0)
        return true;
    return false;
}


void validInput(int &row, int &col){
            do{
                cout << "Column (From 0 to 6):\n";
                cin >> col;
            }while((col < 0 && col > 6) && cout<< "\nInvalid column\n");
            do{
                cout << "Row (From 0 to 6):\n";
                cin >> row;
            }while((row < 0 && row > 6) && cout<< "\nInvalid row\n");
}

void Game::gameLoopPvP()
{
    askMove(1);
    printBoard();
    askMove(2);
    printBoard();
}