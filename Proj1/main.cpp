#include <iostream>
#include "Game.h"

using namespace std;

int main(){
    Game game;
    game.welcomeMsg();
    game.startGame();
    game.printStats();
    return 0;
}