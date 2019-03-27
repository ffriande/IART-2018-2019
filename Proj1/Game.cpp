#include "Game.h"

Game ::Game()
{
    this->board = Board();
}

void Game ::welcomeMsg()
{
    cout << "----- Welcome to BREAK THE ICE - SNOW WORLD -----" << endl;
}

void Game ::swapPieces()
{
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
    this->board.switchPieces(r1, c1, r2, c2);
}

void Game ::startGame()
{
    this->board.printBoard();
    // this->swapPieces();
    this->verifyCombos();
    // this->gameLoop();
    //this->board.updateMatrix();
    this->board.printBoard();
}

void Game ::gameLoop()
{
    while (true)
    {
        this->swapPieces();
        
        this->board.printBoard();
    }
}

bool Game ::checkCombosHorizontal(int i, int j, vector<vector<int>> &clear)
{
    if(j+2<(int)this->board.getBoard().at(i).size()){
        if (this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i).at(j + 1) && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i).at(j + 2) && this->board.getBoard().at(i).at(j) != ' ')
        {
            vector<int> a={i,j};
            vector<int> b={i,j+1};
            vector<int> c={i,j+2};
            clear.push_back(a);
            clear.push_back(b);
            clear.push_back(c);
            return true;
        }
    }
    return false;
}


bool Game ::checkCombosVertical(int i, int j, vector<vector<int>> &clear)
{
    if(i+2<(int)this->board.getBoard().size()){
        if (this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i + 1).at(j) && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i + 2).at(j) && this->board.getBoard().at(i).at(j) != ' ')
        {
            vector<int> a={i,j};
            vector<int> b={i+1,j};
            vector<int> c={i+2,j};
            clear.push_back(a);
            clear.push_back(b);
            clear.push_back(c);
            return true;
        }
    }
    return false;
}

bool Game ::verifyCombos()
{
    bool checkFlag=false;
    vector<vector<int>> clear;
    for (int i = 0; i < (int)this->board.getBoard().size(); i++)
    {
        for (int j = 0; j < (int)this->board.getBoard().at(i).size(); j++)
        {
            if(checkCombosVertical(i, j, clear) || checkCombosHorizontal(i, j, clear)){
                checkFlag=true;
            }
        }
    }
    this->clearCombos(clear);
    return checkFlag;
}

void clearCombos(vector<vector<int>> clear){
    for(int i = 0; i < (int) clear.size(); i++){
        cout << "clear : " clear.at(i).at(0) << " / " << clear.at(i).at(1) << endl;
    }
}