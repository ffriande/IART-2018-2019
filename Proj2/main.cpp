#include "Game.h"

using namespace std;

int chooseAgent(){
    int option=0;
    while(1){
        cout << "1- agent1 = loose(2) - loose(1).\n";
        cout << "2- agent2 = 100 * agent1 + nrpieces(1) - nrpieces(2).\n";
        cout << "3- agent3 = 10 * agent2 + nr1todo3inrow(1) - nr1todo3inrow(2).\n";
        cout << "Option:\n";
        cin >> option;
        if(option >= 1 && option <= 3)
            break;
        cout << "Not a valid option. Please pick again.\n";
    }
    return option;
}

int chooseDepth(){
    int option=0;
    while(1){
        cout << "Choose a depth from 1 to 4.\n";
        cout << "Option:\n";
        cin >> option;
        if(option >= 1 && option <= 4)
            break;
        cout << "Not a valid option. Please pick again.\n";
    }
    return option;
}


int main(){
    int option=-1;
    int agent1=0;
    int agent2=0;
    int depth1=0;
    int depth2=0;
    cout << "Welcome to 9 Men's Morris\n";
    while(1){
        cout << "Choose an option to play.\n";
        cout << "1- Player vs Player.\n";
        cout << "2- Computer vs Player.\n";
        cout << "3- Player vs Computer.\n";
        cout << "4- Computer vs Computer.\n";
        cout << "0 - Leave.\n";
        cout << "Option:\n";
        cin >> option;
        if(option==0){
            cout << "\n\nThank you, come again!.\n";
            break;
        }
        if(option < 0 || option > 4){
            cout << "Not a valid option. Choose Again.";
            continue;
        }
        if(option==2 || option ==3){
            cout << "Choose which agent you want to play against.\n";
            agent1 = chooseAgent();
            cout << "Depth for the computer you will play against.\n";
            depth1 = chooseDepth();
        }
        if(option==4){
            cout << "Choose agent to computer1.\n";
            agent1 = chooseAgent();
            cout << "Depth for the computer1.\n";
            depth1 = chooseDepth();
            cout << "\n\nChoose agent to computer2.\n";
            agent2 = chooseAgent();
            cout << "Depth for the computer2.\n";
            depth2 = chooseDepth();
        }
        Game game = Game(option, agent1, depth1, agent2, depth2);
    }
}