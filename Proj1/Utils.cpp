#include "Utils.h"

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
