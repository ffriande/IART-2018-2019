#ifndef UTILS_H
#define UTILS_H


#include<iostream> 
#include "Graph.h"
#include <map>
#include "Game.h"
using namespace std; 

vector<vector<int>> getPiecesList(Board board);
vector<vector<int>> possibleMovesList(int row, int col, Board actualBoard);
bool outsideBounds(int r, int c, Board board);
vector<Board> getNextMoveBoards(vector<int> piecePos, Board actualBoard);
bool checkVictory(Board board);
bool checkCombosHorizontal(int i, int j, vector<vector<int>> &clear, Board board);
bool checkCombosVertical(int i, int j, vector<vector<int>> &clear, Board board);
Board clearCombos(vector<vector<int>> clear, Board board);
Board verifyCombos(Board board);
Board verifyGravity(Board board,vector<int> v);

#endif