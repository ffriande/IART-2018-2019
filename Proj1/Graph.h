#ifndef GRAPH_H
#define GRAPH_H

#include<iostream> 
#include<list> 
#include <vector>
#include <utility> 

#include "Game.h"
#include "Utils.h"

using namespace std; 

void startAI();
void dfs(Board board);
bool isDFS_visited(Board board);
bool compareMatrix(vector<vector<char>> dfsBoard, vector<vector<char>> matrix);
void bfs(Board board);
bool isBFS_visited(Board board);
void greedy(Board board);
double heuristic(Board board);
int getBestGreedyMove(vector<double> heuristics);
int getRandomMove(vector<double> heuristics);
bool isGreedy_visited(Board board);

#endif