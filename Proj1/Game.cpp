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

    if (this->board.getPiece(r2, c2) == ' ')
    {
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
        cout << endl
             << endl;
        this->board.printBoard();
        if (this->checkVictory())
        {
            cout << "Victory!" << endl;
            break;
        }
        if (!this->board.updateMatrix(this->movedCols) && !this->verifyCombos())
        {
            this->swapPieces();
            for (int i = 0; i < (int)this->movedCols.size(); i++)
            {
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

vector<vector<int>> Game ::possibleMovesList(int row, int col)
{
    vector<vector<int>> moves;
    char color = this->board.getBoard().at(row).at(col);
    if (color == ' ')
    {
        return moves;
    }
    // Piece top
    moves.insert(moves.end(), checkPiecesMove(row - 1, col, color).begin(), checkPiecesMove(row - 1, col, color).end());

    // Piece bottom
    moves.insert(moves.end(), checkPiecesMove(row + 1, col, color).begin(), checkPiecesMove(row + 1, col, color).end());

    // Piece left
    moves.insert(moves.end(), checkPiecesMove(row, col - 1, color).begin(), checkPiecesMove(row, col - 1, color).end());

    // Piece right
    moves.insert(moves.end(), checkPiecesMove(row, col + 1, color).begin(), checkPiecesMove(row, col + 1, color).end());

    // Empty Left
    moves.insert(moves.end(), checkEmptyMove(row, col - 1, color).begin(), checkEmptyMove(row, col - 1, color).end());

    // Empty Right
    moves.insert(moves.end(), checkEmptyMove(row, col + 1, color).begin(), checkEmptyMove(row, col + 1, color).end());

    return moves;
}

vector<vector<int>> Game::checkPiecesMove(int row, int col, char color)
{
    vector<vector<int>> moves;
    if (!this->outsideBounds(row, col))
    {
        if (this->board.getBoard().at(row).at(col) != ' ' && this->board.getBoard().at(row).at(col) != color)
        {
            vector<int> move = {row, col};
            moves.push_back(move);
        }
    }
    return moves;
}

vector<vector<int>> Game::checkEmptyMove(int row, int col, char color)
{
    vector<vector<int>> moves;
    if (!this->outsideBounds(row, col))
    {
        if (this->board.getBoard().at(row).at(col) == ' ')
        {
            vector<int> move = {row, col};
            moves.push_back(move);
        }
    }
    return moves;
}

bool Game ::checkVictory()
{
    for (int i = 0; i < (int)this->board.getBoard().size(); i++)
    {
        for (int j = 0; j < (int)this->board.getBoard().at(i).size(); j++)
        {
            if (this->board.getBoard().at(i).at(j) != ' ')
                return false;
        }
    }
    return true;
}

void Game ::printStats()
{
    cout << "Congratulations!! You won the game with " << this->nMoves << " move(s)!" << endl;
    cout << "Thank you for playing" << endl;
}

void Game ::testMoves(vector<vector<int>> moves)
{
    for (int i = 0; i < (int)moves.size(); i++)
    {
        for (int j = 0; j < (int)moves.at(i).size(); j++)
        {
            cout << moves.at(i).at(j) << " ";
        }
        cout << endl;
    }
}