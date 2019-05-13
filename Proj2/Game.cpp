#include "Game.h"


Game::Game(){
    printBoard();
}


void Game::printBoard()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "|0|1|2|3|4|5|6|\n"
         << "-----------------------------\n";
    for (int r = 0; r < (int)this->board.size(); r++)
    {
        for (int c = 0; c < (int)this->board.at(r).size(); c++)
        {
            if(this->board.at(r).at(c)==-1)
                cout << "---";
            if(this->board.at(r).at(c)==-2)
                cout << " | ";
            if(this->board.at(r).at(c)==-3)
                cout << "   ";
            if(this->board.at(r).at(c)==0)
                cout << " O ";
            if(this->board.at(r).at(c)==1)
                cout << " W ";
            if(this->board.at(r).at(c)==2)
                cout << " R ";
        }
        cout << endl;
    }
}