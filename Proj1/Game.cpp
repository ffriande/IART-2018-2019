#include "Game.h"

Game ::Game()
{
    this->board = Board();
    this->nMoves = 0;
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
        } while ((this->outsideBounds(r1, c1) || this->board.getBoard().at(r1).at(c1) == ' ') &&
                 cout << "\nNot valid. Choose again:\n");
        cout << "Piece 2 : Row" << endl;
        cin >> r2;
        cout << "Piece 2 : Col" << endl;
        cin >> c2;
    } while (this->outsideBounds(r2, c2) && cout << "\nNot valid. Choose again:\n");

    if(this->board.getPiece(r2,c2)==' '){
        this->movedCols.push_back(c1);
        this->movedCols.push_back(c2);
    } 
    this->board.switchPieces(r1, c1, r2, c2);
    this->nMoves++;     
}

bool Game ::outsideBounds(int r, int c)
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
        if (this->checkVictory()){
            cout << "Victory!" << endl;
            break;
        }
        if( !this->board.updateMatrix(this->movedCols) && !this->verifyCombos()){
            this->swapPieces();
            for (int i = 0; i < this->movedCols.size(); i++){
                cout << this->movedCols.at(i) << " ";
            }
            cout << endl;
        }
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

vector<vector<int>> Game :: possibleMovesList(int row, int col){
    vector<vector<int>> moves;
    char color = this->board.getBoard().at(row).at(col);
    if (color == ' '){
        return moves;
    }
    // Piece top
    if (!this->outsideBounds(row - 1, col)){
        if (this->board.getBoard().at(row - 1).at(col) != ' ' && this->board.getBoard().at(row - 1).at(col) != color){
            vector<int>move ={row - 1, col};
            moves.push_back(move);
        }
    }
    // Piece bottom
    if (!this->outsideBounds(row + 1, col)){
        if (this->board.getBoard().at(row + 1).at(col) != ' ' && this->board.getBoard().at(row + 1).at(col) != color){
            vector<int>move ={row + 1, col};
            moves.push_back(move);
        }
    }
    // Piece left
    if (!this->outsideBounds(row, col - 1)){
        if (this->board.getBoard().at(row).at(col - 1) != ' ' && this->board.getBoard().at(row).at(col - 1) != color){
            vector<int>move ={row, col - 1};
            moves.push_back(move);
        }
    }
    // Piece right
    if (!this->outsideBounds(row, col + 1)){
        if (this->board.getBoard().at(row).at(col + 1) != ' ' && this->board.getBoard().at(row).at(col + 1) != color){
            vector<int>move ={row, col + 1};
            moves.push_back(move);
        }
    }
    // Empty Left
    if (!this->outsideBounds(row, col - 1)){
        if (this->board.getBoard().at(row).at(col - 1) == ' '){
            vector<int>move ={row, col - 1};
            moves.push_back(move);
        }
    }
    // Empty Right
    if (!this->outsideBounds(row, col + 1)){
        if (this->board.getBoard().at(row).at(col + 1) == ' '){
            vector<int>move ={row, col + 1};
            moves.push_back(move);
        }
    }

    return moves;
}

bool Game :: checkVictory(){
    for (int i = 0; i < this->board.getBoard().size(); i++){
        for (int j = 0; j < this->board.getBoard().at(i).size(); j++){
            if (this->board.getBoard().at(i).at(j) != ' ')
                return false;
        }
    }
    return true;
}

void Game :: printStats(){
    cout << "Congratulations!! You won the game with " << this->nMoves << " move(s)!" << endl;
    cout << "Thank you for playing" << endl;
}

void Game :: testMoves(vector<vector<int>> moves){
    for (int i = 0; i < moves.size(); i++){
        for (int j = 0; j < moves.at(i).size(); j++){
            cout << moves.at(i).at(j) << " ";
        }
        cout << endl;
    }
}