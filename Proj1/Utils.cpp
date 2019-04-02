#include "Utils.h"

// Dado um board retorna um vetor com as posicoes de todas as suas pecas
vector<vector<int>> getPiecesList(Board board){
    vector<vector<int>> piecesList;
    for (int i = 0; i < board.getBoard().size(); i++){
        for (int j = 0; j < board.getBoard()[i].size(); j++){
            if (board.getBoard()[i][j] != ' '){
                vector<int> piece;
                piece.push_back(i);
                piece.push_back(j);
                piecesList.push_back(piece);
            }
        }
    }
    return piecesList;
}

// Dada um peca retorna todas a posicoes para as quais se pode movimentar
vector<vector<int>> possibleMovesList(int row, int col, Board actualBoard)
{
    vector<vector<int>> moves;
    char color = actualBoard.getBoard().at(row).at(col);
    if (color == ' ')
    {
        return moves;
    }
    // Piece top
    if (!outsideBounds(row - 1, col, actualBoard)){
        if (actualBoard.getBoard().at(row - 1).at(col) != ' ' && actualBoard.getBoard().at(row - 1).at(col) != color){
            vector<int>move ={row - 1, col};
            moves.push_back(move);
        }
    }
    // Piece bottom
    if (!outsideBounds(row + 1, col, actualBoard)){
        if (actualBoard.getBoard().at(row + 1).at(col) != ' ' && actualBoard.getBoard().at(row + 1).at(col) != color){
            vector<int>move ={row + 1, col};
            moves.push_back(move);
        }
    }
    // Piece left
    if (!outsideBounds(row, col - 1, actualBoard)){
        if (actualBoard.getBoard().at(row).at(col - 1) != ' ' && actualBoard.getBoard().at(row).at(col - 1) != color){
            vector<int>move ={row, col - 1};
            moves.push_back(move);
        }
    }
    // Piece right
    if (!outsideBounds(row, col + 1, actualBoard)){
        if (actualBoard.getBoard().at(row).at(col + 1) != ' ' && actualBoard.getBoard().at(row).at(col + 1) != color){
            vector<int>move ={row, col + 1};
            moves.push_back(move);
        }
    }
    // Empty Left
    if (!outsideBounds(row, col - 1, actualBoard)){
        if (actualBoard.getBoard().at(row).at(col - 1) == ' '){
            vector<int>move ={row, col - 1};
            moves.push_back(move);
        }
    }
    // Empty Right
    if (!outsideBounds(row, col + 1, actualBoard)){
        if (actualBoard.getBoard().at(row).at(col + 1) == ' '){
            vector<int>move ={row, col + 1};
            moves.push_back(move);
        }
    }
    return moves;
}

bool outsideBounds(int r, int c, Board board){
    if (r < 0 || r >= (int)board.getBoard().size() ||
    c < 0 || c >= (int)board.getBoard().at(r).size())
    return true;
return false;
}

Board verifyGravity(Board board, vector<int> movedCols){
    board.updateMatrix(movedCols);
    return board;
}

// Dada uma peca e o Board atual retorna todos os novos boards que ela pode gerar
vector<Board> getNextMoveBoards(vector<int> piecePos, Board actualBoard){
    vector<Board> nextMoveBoards;
    vector<vector<int>> pieceMoves = possibleMovesList(piecePos[0], piecePos[1], actualBoard);
    for (int i = 0; i < pieceMoves.size(); i++){
        Board newBoard = Board(actualBoard.getBoard());
        newBoard.switchPieces(piecePos[0], piecePos[1], pieceMoves[i][0], pieceMoves[i][1]);
        vector<int> v;
        v.push_back(piecePos[1]);
        v.push_back(pieceMoves[i][1]);
        newBoard = verifyGravity(newBoard,v);
        newBoard = verifyCombos(newBoard);
        nextMoveBoards.push_back(newBoard);
    }
    return nextMoveBoards;
}

bool checkCombosHorizontal(int i, int j, vector<vector<int>> &clear, Board board)
{
    if (j + 2 < (int)board.getBoard().at(i).size())
    {
        if (board.getBoard().at(i).at(j) != ' ' && board.getBoard().at(i).at(j) == board.getBoard().at(i).at(j + 1) && board.getBoard().at(i).at(j) == board.getBoard().at(i).at(j + 2))
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

bool checkCombosVertical(int i, int j, vector<vector<int>> &clear, Board board)
{
    if (i + 2 < (int)board.getBoard().size())
    {
        if (board.getBoard().at(i).at(j) != ' ' && board.getBoard().at(i).at(j) == board.getBoard().at(i + 1).at(j) && board.getBoard().at(i).at(j) == board.getBoard().at(i + 2).at(j))
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

Board clearCombos(vector<vector<int>> clear, Board board)
{
    for (int i = 0; i < (int)clear.size(); i++)
    {
        board.setPiece(clear.at(i).at(0), clear.at(i).at(1), ' ');
    }
    return board;
}

Board verifyCombos(Board board)
{
    bool checkFlag = false;
    vector<vector<int>> clear;
    for (int i = 0; i < (int)board.getBoard().size(); i++)
    {
        for (int j = 0; j < (int)board.getBoard().at(i).size(); j++)
        {
            if (checkCombosVertical(i, j, clear, board) || checkCombosHorizontal(i, j, clear, board))
            {
                checkFlag = true;
            }
        }
    }
    return clearCombos(clear, board);
}

bool checkVictory(Board board){
    for (int i = 0; i < board.getBoard().size(); i++){
        for (int j = 0; j < board.getBoard()[i].size(); j++){
            if (board.getBoard()[i][j] != ' '){
                return false;
            }
        }
    }
    return true;
}