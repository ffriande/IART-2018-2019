#include <iostream>
#include <chrono>
#include "Game.h"
#include "AI.h"

using namespace std;

void selectAstarHeuristic(Game game){
    cout << "Select A* Algorithm heuristics function" << endl;
    cout << "1." << endl;
    cout << "2." << endl;
    cout << "3." << endl;
    int input;
    cin >> input;
    aStar(game, input);
}
void selectAI(Game game){
    cout << "Select Game Mode" << endl;
    cout << "1. BFS" << endl;
    cout << "2. DFS" << endl;
    cout << "3. Greedy" << endl;
    cout << "4. A*" << endl;
    int input;
    cin >> input;
    if (input == 1){
        bfs(game);
    }
    else if (input == 2){
        dfs(game);
    }
    else if (input == 3){
        greedy(game);
    }
    else if (input == 4){
        selectAstarHeuristic(game);
    }
}


void selectMode(Game game){
    cout << "Select Game Mode" << endl;
    cout << "1. Player" << endl;
    cout << "2. AI" << endl;
    int input;
    cin >> input;
    if (input == 1){
        game.welcomeMsg();
        game.startGame();
    }
    else if (input == 2){
        game.chooseLevel();
        game.countPiecesNr();
        startAI(game);
        selectAI(game);
    }

}

int main(){
    Game game;
    selectMode(game);
    return 0;
}