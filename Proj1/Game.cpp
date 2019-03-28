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
    do
    {
        do
        {
            cout << "Piece 1 : Row" << endl;
            cin >> r1;
            cout << "Piece 1 : Col" << endl;
            cin >> c1;
        } while ((this->checkInput(r1, c1) || this->board.getBoard().at(r1).at(c1) == ' ') &&
                 cout << "\nNot valid. Choose again:\n");
        cout << "Piece 2 : Row" << endl;
        cin >> r2;
        cout << "Piece 2 : Col" << endl;
        cin >> c2;
    } while (this->checkInput(r2, c2) && cout << "\nNot valid. Choose again:\n");

    this->board.switchPieces(r1, c1, r2, c2);
    if(this->board.getPiece(r2,c2)==' '){
        this->movedCols.push_back(c1);
        this->movedCols.push_back(c2);
    }      
}

bool Game ::checkInput(int r, int c)
{
    if (r < 0 || r >= (int)this->board.getBoard().size() ||
        c < 0 || c >= (int)this->board.getBoard().at(r).size())
        return true;
    return false;
}

void Game ::startGame()
{
    this->gameLoop();
    //this->board.updateMatrix();
}

void Game ::gameLoop()
{
    while (true)
    {
        sleep(1);
        cout<<endl<<endl;
        this->board.printBoard();
        if( !this->board.updateMatrix(this->movedCols) && !this->verifyCombos())
        this->swapPieces();
    }
}

bool Game ::checkCombosHorizontal(int i, int j, vector<vector<int>> &clear)
{
    if (j + 2 < (int)this->board.getBoard().at(i).size())
    {
        if (this->board.getBoard().at(i).at(j) != ' ' && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i).at(j + 1) && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i).at(j + 2))
        {
            vector<int> a = {i, j};
            vector<int> b = {i, j + 1};
            vector<int> c = {i, j + 2};
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
    if (i + 2 < (int)this->board.getBoard().size())
    {
        if (this->board.getBoard().at(i).at(j) != ' ' && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i + 1).at(j) && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i + 2).at(j))
        {
            vector<int> a = {i, j};
            vector<int> b = {i + 1, j};
            vector<int> c = {i + 2, j};
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
    bool checkFlag = false;
    vector<vector<int>> clear;
    for (int i = 0; i < (int)this->board.getBoard().size(); i++)
    {
        for (int j = 0; j < (int)this->board.getBoard().at(i).size(); j++)
        {
            if (checkCombosVertical(i, j, clear) || checkCombosHorizontal(i, j, clear))
            {
                checkFlag = true;
            }
        }
    }
    this->clearCombos(clear);
    return checkFlag;
}

void Game ::clearCombos(vector<vector<int>> clear)
{
    for (int i = 0; i < (int)clear.size(); i++)
    {
        this->board.setPiece(clear.at(i).at(0), clear.at(i).at(1), ' ');
        this->movedCols.push_back(clear.at(i).at(1));
    }
}