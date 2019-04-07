#include "Game.h"

/**
 *Constructor of the class Game. 
 */
Game ::Game()
{
    this->board = Board();
    this->nMoves = 0;
    //this->maxMoves = 5;
}

/**
 *Prints a welcome message to the screen. 
 */
void Game ::welcomeMsg()
{
    cout << "----- Welcome to BREAK THE ICE - SNOW WORLD -----" << endl;
    chooseLevel();
}

/**
 * Asks the user to select the level he wants to play
 */
void Game ::chooseLevel()
{
    string level;
    string filename;
    cout << "Choose level (number + enter)" << endl;
    cin >> level;
    filename = "level" + level + ".txt";
    ifstream myReadFile;
    myReadFile.open(filename);
    vector<vector<char>> matrix;
    string line, plays;
    vector<char> row;
    if (myReadFile.is_open())
    {
        getline(myReadFile, plays);
        this->maxMoves = stoi(plays) + 2;
        while (getline(myReadFile, line))
        {
            row.clear();
            for (char &c : line)
                if (c != '\n' && c != '|')
                    row.push_back(c);
            matrix.push_back(row);
        }
        this->board = Board(matrix);
    }
    else
        return;
    myReadFile.close();
}

/**
 * Asks the user which piece he wants to move and to where.
 * As all the restrictions of the movement.
 */
void Game ::swapPieces()
{
    this->movedCols.clear();
    cout << "Swap Pieces" << endl;
    int r1, c1, r2, c2;
    vector<int> newPos;
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
        newPos.clear();
        newPos.push_back(r2);
        newPos.push_back(c2);
    } while ((this->outsideBounds(r2, c2) || !this->isPossible(newPos, this->possibleMovesList(r1, c1))) && cout << "\nNot valid. Choose again:\n");

    if (this->board.getPiece(r2, c2) == ' ')
    {
        this->movedCols.push_back(c1);
        this->movedCols.push_back(c2);
    }
    this->board.switchPieces(r1, c1, r2, c2);
    this->nMoves++;
}

/**
 * Used to move a piece for the AI.
 */
void Game ::swapPiecesAI(int oldRow, int oldCol, int newRow, int newCol){
    this->movedCols.clear();
    if (this->board.getPiece(newRow, newCol) == ' ')
    {
        this->movedCols.push_back(oldCol);
        this->movedCols.push_back(newCol);
    }
    this->board.switchPieces(oldRow, oldCol, newRow, newCol);
    this->nMoves++;
}

/**
 * Checks if coords (r,c) are on limits of the board.
 */
bool Game ::outsideBounds(int r, int c)
{
    if (r < 0 || r >= (int)this->board.getBoard().size() ||
        c < 0 || c >= (int)this->board.getBoard().at(r).size())
        return true;
    return false;
}

/**
 * Starts the game for the player.
 */
void Game ::startGame()
{
    this->countPiecesNr();
    this->gameLoop();
}

bool Game ::applyGravity(){
    return this->board.updateMatrix(this->movedCols);
}


/**
 * GameLoop for the player applying all the verificiations, win, lose, destruction and gravity.
 */
void Game ::gameLoop()
{
    while (true)
    {
        sleep(1);
        this->board.printBoard();
        if (this->checkGameOver())
        {
            cout << "You Lost ..." << endl;
            break;
        }
        if (this->checkVictory())
        {
            cout << "Victory!" << endl;
            this->printStats();
            break;
        }
        if (!this->board.updateMatrix(this->movedCols) && !this->verifyCombos())
        {
            this->swapPieces();
        }
    }
}

/**
 * Counts the number for each type of piece.
 */
void Game ::countPiecesNr()
{
    char piece;
    map<char, int>::iterator it;
    for (int i = 0; i < (int)this->board.getBoard().size(); i++)
    {
        for (int j = 0; j < (int)this->board.getBoard().at(i).size(); j++)
        {
            piece = this->board.getBoard().at(i).at(j);
            if (piece != ' ')
            {
                it = piecesNr.find(piece);
                if (it != piecesNr.end())
                    piecesNr[piece] += 1;
                else
                    piecesNr[piece] = 1;
            }
        }
    }
}

/**
 * Checks if there is any 3 pieces of the same type in a row on the horizontal.
 */
bool Game ::checkCombosHorizontal(int i, int j, vector<vector<int>> &clear)
{
    if (j + 2 < (int)this->board.getBoard().at(i).size())
    {
        if (this->board.getBoard().at(i).at(j) != ' ' && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i).at(j + 1) && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i).at(j + 2))
        {
            vector<int> a = {i, j};
            if (!this->checkDuplicated(clear, a))
                clear.push_back(a);
            vector<int> b = {i, j + 1};
            if (!this->checkDuplicated(clear, b))
                clear.push_back(b);
            vector<int> c = {i, j + 2};
            if (!this->checkDuplicated(clear, c))
                clear.push_back(c);
            return true;
        }
    }
    return false;
}

/**
 * Checks if there is any 3 pieces of the same type in a row on the vertical.
 */
bool Game ::checkCombosVertical(int i, int j, vector<vector<int>> &clear)
{
    if (i + 2 < (int)this->board.getBoard().size())
    {
        if (this->board.getBoard().at(i).at(j) != ' ' && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i + 1).at(j) && this->board.getBoard().at(i).at(j) == this->board.getBoard().at(i + 2).at(j))
        {
            vector<int> a = {i, j};
            if (!this->checkDuplicated(clear, a))
                clear.push_back(a);
            vector<int> b = {i + 1, j};
            if (!this->checkDuplicated(clear, b))
                clear.push_back(b);
            vector<int> c = {i + 2, j};
            if (!this->checkDuplicated(clear, c))
                clear.push_back(c);
            return true;
        }
    }
    return false;
}

/**
 * Checks if parameter coords is already inside of parameter clear
 * if it is returns true if not false
 */
bool Game ::checkDuplicated(vector<vector<int>> clear, vector<int> coords)
{
    for (int i = 0; i < (int)clear.size(); i++)
    {
        if (clear.at(i) == coords)
            return true;
    }
    return false;
}

/**
 * Checks if the state of the game is impossible, so the game is lost.
 */
bool Game ::checkGameOver()
{
    map<char, int>::iterator it;
    for (it = piecesNr.begin(); it != piecesNr.end(); it++)
    {
        if (it->second < 3 && it->second > 0)
            return true;
    }
    return false;
}

/**
 * Handles the verification of the destruction of pieces.
 */
bool Game ::verifyCombos()
{
    bool checkFlag = false;
    vector<vector<int>> clear;
    for (int i = 0; i < (int)this->board.getBoard().size(); i++)
    {
        for (int j = 0; j < (int)this->board.getBoard().at(i).size(); j++)
        {
            if (this->checkCombosVertical(i, j, clear) || this->checkCombosHorizontal(i, j, clear))
            {
                checkFlag = true;
            }
        }
    }
    this->clearCombos(clear);
    return checkFlag;
}

/**
 * Clears all the pieces in the vector clear.
 */
void Game ::clearCombos(vector<vector<int>> clear)
{
    char piece;
    for (int i = 0; i < (int)clear.size(); i++)
    {
        piece = this->board.getBoard().at(clear.at(i).at(0)).at(clear.at(i).at(1));
        if (this->piecesNr.find(piece)->second == 1)
            this->piecesNr.erase(piece);
        else
            this->piecesNr[piece] -= 1;
        this->board.setPiece(clear.at(i).at(0), clear.at(i).at(1), ' ');
        this->movedCols.push_back(clear.at(i).at(1));
    }
}

/**
 * Gets all the possible and with some restrictions for a given coords (row,col).
 */
vector<vector<int>> Game ::possibleMovesList(int row, int col)
{
    vector<vector<int>> moves;
    char color = this->board.getBoard().at(row).at(col);
    if (color == ' ')
    {
        return moves;
    }
    // Piece top
    if (!this->outsideBounds(row - 1, col))
    {
        if (this->board.getBoard().at(row - 1).at(col) != ' ' && this->board.getBoard().at(row - 1).at(col) != color)
        {
            vector<int> move = {row - 1, col};
            moves.push_back(move);
        }
    }
    // Piece bottom
    if (!this->outsideBounds(row + 1, col))
    {
        if (this->board.getBoard().at(row + 1).at(col) != color)
        {
            vector<int> move = {row + 1, col};
            moves.push_back(move);
        }
    }
    // Piece left
    if (!this->outsideBounds(row, col - 1))
    {
        if (this->board.getBoard().at(row).at(col - 1) != color)
        {
            vector<int> move = {row, col - 1};
            moves.push_back(move);
        }
    }
    // Piece right
    if (!this->outsideBounds(row, col + 1))
    {
        if (this->board.getBoard().at(row).at(col + 1) != color)
        {
            vector<int> move = {row, col + 1};
            moves.push_back(move);
        }
    }
    return moves;
}

/**
 * Calculates the number of pieces in the board.
 */
int Game ::getNrPieces(){
    int count=0;
    for (map<char,int>::iterator it=piecesNr.begin(); it!=piecesNr.end(); ++it)
        count+=it->second;
    return count;
}

/**
 * Checks if the state of the game is win.
 */
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

/**
 * Prints all the moves used and a message of win.
 */
void Game ::printStats()
{
    cout << "Congratulations!! You won the game with " << this->nMoves << " move(s)!" << endl;
    cout << "Thank you for playing" << endl;
}



/**
 *
 */
bool Game ::isPossible(vector<int> newPos, vector<vector<int>> list)
{
    char newR = newPos[0];
    char newC = newPos[1];
    for (int i = 0; i < (int)list.size(); i++)
    {
        if (list[i][0] == newR && list[i][1] == newC)
        {
            return true;
        }
    }
    return false;
}
