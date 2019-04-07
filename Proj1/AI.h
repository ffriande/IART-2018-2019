#ifndef AI_H
#define AI_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <chrono>

#include "Game.h"

using namespace std::chrono;

struct node{
    //used to save the piece that was selected
    vector<int> from;
    //used to save the coords of the cell that the selected piece changed with
    vector<int> to;
    //level in the tree
    int level;
    //value of the node, used to aStar and greedy
    float value;
    //heuristic value of the node, used only for aStar
    float heuris;
    //game of the father
    Game prevGame;
    //pointer to the father node
    struct node *father;
};



void startAI(Game game);
void bfs(Game game);
void getSolution();
bool checkDuplicated(vector<vector<char>> boardCheck,int level);
bool compareMatrixx(vector<vector<char>> board1, vector<vector<char>> board2);
void dfs(Game game);
int getBestValue(vector<struct node*> &avl);
int calculateGreedyValue(Game game, vector<int> from, vector<int> to);
void greedy(Game game);
void aStar(Game game, int heuristic);
void orderQueue(vector<struct node *> &vectorAux);
float calculateAstarHn(Game game, vector<int> from, vector<int> to, int heuristic);
int getLowestValue(vector<struct node *> &avl);
void startClock();
void stopClock();

#endif