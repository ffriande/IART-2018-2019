#include <iostream>
#include "Game.h"
#include "Graph.h"

using namespace std;

void selectAI(Game game){
    cout << "Select Game Mode" << endl;
    cout << "1. BFS" << endl;
    cout << "2. DFS" << endl;
    cout << "3. Greedy" << endl;
    cout << "4. A*" << endl;
    int input;
    cin >> input;
    if (input == 1){
        bfs(game.getBoard());
    }
    else if (input == 2){
        dfs(game.getBoard());
    }
    else if (input == 3){
        greedy(game.getBoard());
    }
    else if (input == 4){
        exit(0);
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
        selectAI(game);
    }

}

int main(){
    Game game;
    selectMode(game);
    return 0;
}