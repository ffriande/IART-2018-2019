#ifndef AI_H
#define AI_H

#include "Game.h"
#include <vector>
#include <map>
#include <climits>

using namespace std;


map<vector<int>,vector<vector<int>>> getBotMoves(Game game, int player);
int evaluation1(Game game, int player);
int evaluation2(Game game, int player);
int evaluation3(Game game, int player);
int switchPlayer(int currPlayer);
bool min(int n1, int n2);
bool max(int n1, int n2);
int evaluate(Game game, int player, int agent);
vector<vector<int>> minimax(Game game, int depth, int alpha, int beta, int maximizingPlayer, int currPlayer, int agent);




/**
 * evaluation1= loose(2) - loose(1);
 * evaluation2= 100*evaluation1 + nrpieces(1) - nrpieces(2);
 * evaluation3= evaluation2 + nr1todo3inrow(1) - nr1todo3inrow(2);
 * funcao minimax vai retornar um vetor de vetores, se for para inserir envia um vetor de tamanho 1
 * se for para mover de tamanho 2
 * se tiver de remover alguma peça envia mais 1.
 * caso tenha de eliminar testa todas as eliminações e escolhe a jogada conforme a eliminação.
 */

#endif