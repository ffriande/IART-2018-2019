#include "Game.h"

#define MOVE 2
#define FLY 3

/**
 * Constructor to start a new game.
 */
Game::Game(){
    this->numberOfRedInserted=0;
    this->numberOfWhiteInserted=0;
    this->numberOfRedPieces=0;
    this->numberOfWhitePieces=0;
    this->numberOfPiecesInserted=0;
    gameLoopPvP();
}

/**
 * Prints the board with letters instead of numbers.
 */
void Game::printBoard()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << " O - Represents a free space in the board\n"
    << " W - Represents a white piece on the board\n"
    << " R - Represents a black piece on the board\n\n"
    << " Number of White Pieces: " << this->numberOfWhitePieces << endl
    << " Number of Red Pieces: " << this->numberOfRedPieces << "\n\n";
    cout << "   | 0 |1 |2 |3 |4 |5 |6 |\n"
         << "---|---------------------|---\n";
    for (int r = 0; r < (int)this->board.size(); r++)
    {
        cout << " " << r << " |";
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
        cout << "| " << r << endl;
    }
    cout << "---|---------------------|---\n"
    << "   | 0 |1 |2 |3 |4 |5 |6 |\n\n";
}

void printvector(vector<vector<int>> a){
    for(auto i:a){
        cout << "Col: " << i.at(1) << " Row: " << i.at(0) << endl; 
    }
}

/**
 * Handles all the asking and validation of player turn.
 */
void Game::askMove(int player){
    if(player == 1)
        cout << "WHITE Player turn.\n";
    else
        cout << "RED Player turn.\n";
    int placeOrMove;
    if(this->numberOfPiecesInserted != 18){ 
        cout << "You will choose a place to insert a piece.\n";
        if(player == 1)
            cout << "You have " << (18-this->numberOfPiecesInserted)/2 << " pieces left to insert.\n";
        if(player == 2)
            cout << "You have " << (18-this->numberOfPiecesInserted+1)/2 << " pieces left to insert.\n";
        placeOrMove=1;
    }else
    {
        cout << "Choose one of your pieces.\n";
        placeOrMove=2;
    }
    int column;
    int row;
    vector<vector<int>> validMoves;
    bool pickflag;
    do{
        validInput(row, column);
        pickflag=true;
        if(placeOrMove==2){
            validMoves = getMoveCoords(player,row,column);
            if(validMoves.size()==0)
                pickflag=false;
        }
    }while((!validChoose(player,placeOrMove,row,column) || !pickflag) && cout<< "\nInvalid choose\n");

    if(placeOrMove==2){
        makeMove(player,row,column,validMoves);
    }else
    {
        this->board.at(row).at(column)=player;
        this->numberOfPiecesInserted++;
        if(player==1){
            this->numberOfWhiteInserted++;
            this->numberOfWhitePieces++;
            if(numberOfWhitePieces>=3)
                askElimination(player, row, column);
        }
        else{
            this->numberOfRedInserted++;
            this->numberOfRedPieces++;
            if(numberOfRedPieces>=3)
                askElimination(player, row, column);
        }
    }
}



/**
 * For the player to choose the destination of the piece in (row,column).
 */
void Game::makeMove(int player, int row, int column, vector<vector<int>> validMoves){
    int destRow, destCol;
    do{
        if(player == 1 && this->numberOfWhitePieces == 3)
            cout << "Choose an empty space (O) to fly.\n";
        else if(player == 2 && this->numberOfRedPieces == 3)
            cout << "Choose an empty space (O) to fly.\n";
        else{
            cout << "Choose an empty adjacent (O) to move (horizontal or vertical).\n";
        }
        validInput(destRow,destCol);
    }while(!vectorMember(validMoves,{destRow,destCol}) && cout<< "\nInvalid choose\n");
    this->board.at(row).at(column)=0;
    this->board.at(destRow).at(destCol)=player;
    askElimination(player, destRow, destCol);
}

/**
 * Handles the verification of 3 in a row from player, and gives the output and handles the input.
 */
void Game::askElimination(int player, int row, int column){
    vector<vector<int>> result = check3InRow(player,row,column);
    vector<vector<int>> pieces3InRow;
    if(result.size()==3){
        printBoard();
        if(player==1){
            cout << "WHITE player turn.\n";
        }
        else{
            cout << "RED player turn.\n";
        }
        vector<vector<int>> validElim=validElimination(player);
        if(validElim.size()==0)
            cout << "You have no valid pieces form the other player to remove.\n";
        else{
            cout << "You made 3 in a row.\nYou can now choose a piece from the other player to eliminate (it can not belong to a 3 in a row).\n";
            int eliRow;
            int eliCol;
            do{
                validInput(eliRow,eliCol);
            }while(!vectorMember(validElim,{eliRow,eliCol}) && cout << "Invalid choose\n");
            this->board.at(eliRow).at(eliCol)=0;
            if(player == 1)
                this->numberOfRedPieces--;
            else
                this->numberOfWhitePieces--;
        }
    }
}

/**
 * Gets all the positions where a piece can be eliminated.
 */
vector<vector<int>> Game::validElimination(int player){
    vector<vector<int>> valid;
    vector<vector<int>> pieces;
    vector<vector<int>> pieces3Row;
    int symbol;
    if(player==1)
        symbol=2;
    else
        symbol=1;

    pieces=getPiecesOf(symbol);
    for(auto it:pieces){
        if(!vectorMember(pieces3Row,it)){
            vector<vector<int>> aux=check3InRow(symbol,it.at(0),it.at(1));
            if(aux.size()==3){
                for(auto itaux:aux){
                    if(!vectorMember(pieces3Row,itaux))
                        pieces3Row.push_back(itaux);
                }
            }else
                valid.push_back(it);
        }
    }
    return valid;
}

/**cout << "horizontal\n";
 * Checks if player is doing 3 in a row, on the position row column, if yes returns the vector with the coords of the pieces in that 3 in row.
 * Returns a empty vector if not
 */
vector<vector<int>> Game::check3InRow(int player, int row, int column){
    vector<vector<int>> horizontal={{row,column}};
    vector<vector<int>> vertical={{row,column}};
    for(int i=1; i<7; i++){
        if((row+i) < (int)this->board.size() && this->board.at(row+i).at(column) == player && checkConnected(vertical,(row+i),column)){
            vector<int> coord = {row+i,column};
            if(!vectorMember(vertical, coord))
                vertical.push_back(coord);
        }
        if((row-i) >= 0 && this->board.at(row-i).at(column) == player && checkConnected(vertical,(row-i),column)){
            vector<int> coord = {row-i,column};
            if(!vectorMember(vertical, coord))
                vertical.push_back(coord);
        }
        if((column+i) < (int)this->board.at(0).size() && this->board.at(row).at(column+i) == player && checkConnected(horizontal,row,(column+i))){
            vector<int> coord = {row,column+i};
            if(!vectorMember(horizontal, coord))
                horizontal.push_back(coord);
        }
        if((column-i) >= 0 && this->board.at(row).at(column-i) == player && checkConnected(horizontal,row,(column-i))){
            vector<int> coord = {row,column-i};
            if(!vectorMember(horizontal, coord))
                horizontal.push_back(coord);
        }
        if(horizontal.size()==3)
            return horizontal;
        if(vertical.size()==3)
            return vertical;
    }
    return {{}};
}

/**
 * Checks if cell (row,column) is adjacent to any of the coords in the vector coords.
 * Returns true if yes, false if not.
 */
bool Game::checkConnected(vector<vector<int>> coords, int row, int column){
    for(auto it:coords){
        if(checkAdjacent(it.at(0), it.at(1), row, column))
            return true;
    }
    return false;
}



/**
 * Auxiliary function that sees if coord is member of analyse vector.
 * We couldn't use find because coord is a vector too.
 */
bool Game::vectorMember(vector<vector<int>> analyse, vector<int> coord){
    for(auto i:analyse){
        if(coord[0]==i[0] && coord[1]==i[1])
            return true;
    }
    return false;
}

/**
 * Function used to get all the coords that a player can choose in the first pick of coords.
 */
vector<vector<int>> Game::getFirstChoice(int player){
    vector<vector<int>> coords;
    int symbol;
    if(this->numberOfPiecesInserted!=18)
        symbol=0;
    else
        symbol=player;
    return getPiecesOf(symbol);
}

/**
 * Returns a vector with al the coords in the board that have as number symbol.
 */
vector<vector<int>> Game::getPiecesOf(int symbol){
    vector<vector<int>> coords;
    for(int r = 0; r < (int)this->board.size(); r++){
        for(int c = 0; c < (int)this->board.at(0).size(); c++){
            if(this->board.at(r).at(c)==symbol){
                vector<int> coord={r,c};
                coords.push_back(coord);
            }
        }
    }
    return coords;
}

/**
 * Function that returns a vector with all the possible moves of a piece.
 */
vector<vector<int>> Game::getMoveCoords(int player, int row, int column){
    vector<vector<int>> coords;
    if((player == 1 && this->numberOfWhitePieces == 3) || 
    (player == 2 && this->numberOfRedPieces == 3))  //condition to see if the player can fly.
        return getPiecesOf(0);
    else
    {
        for(int i=1; i<=3; i++){
            if((row+i)<(int)this->board.size() && validDest(player,MOVE,row+i,column,row,column)){     //check down
                vector<int> coord={row+i,column};
                coords.push_back(coord);
            }
            if((row-i)>=0 && validDest(player,MOVE,row-i,column,row,column)){     //check up
                vector<int> coord={row-i,column};
                coords.push_back(coord);
            }
            if((column+i)<(int)this->board.at(row).size() && validDest(player,MOVE,row,column+i,row,column)){   //check right
                vector<int> coord={row,column+i};
                coords.push_back(coord);
            }
            if((column-i)>=0 && validDest(player,MOVE,row,column-i,row,column)){    //check left
                vector<int> coord={row,column-i};
                coords.push_back(coord);
            }
        }
    }
    return coords;
}


/**
 * Checks if row and col are valid coords in the first ask of coords.
 * If it is an insert needs to be 0 at those coords in board.
 * If not, it needs to be equals the number of the player.
 */
bool Game::validChoose(int player, int placeOrMove, int row, int column){
    if(placeOrMove==1){
        if(this->board.at(row).at(column)!=0)
        {
            return false;
        }
    }else
    {
        if(this->board.at(row).at(column)!=player)
            return false;
    }
    return true;
}


/**
 * Checks if (newRow,newColumn) is a valid place to move the piece from (prevRow,prevColumn).
 * Returns false if not.
 */
bool Game::validDest(int player, int typeMove, int newRow, int newColumn, int prevRow, int prevColumn){
    if(this->board.at(newRow).at(newColumn)!=0)
        return false;
    if(typeMove == MOVE)
        return checkAdjacent(prevRow,prevColumn,newRow,newColumn);
    return true;
    
}

/**
 * Checks if (row1,column1) is adjacent to (row2,column2).
 */
bool Game::checkAdjacent(int row1, int column1, int row2, int column2){
    int rowDif=row1-row2;
    int colDif=column1-column2;
    if(rowDif!=0 && colDif!=0)
        return false;
    if(abs(rowDif) > 3 || abs(colDif) > 3)
        return false;
    if(rowDif==0){
        if(colDif>0)
            return adjacentHorizontal(row1,column2,abs(colDif));
        else
            return adjacentHorizontal(row1,column1,abs(colDif));
    }else{
        if(rowDif>0)
            return adjacentVertical(column1,row2,abs(rowDif));
        else
            return adjacentVertical(column1,row1,abs(rowDif));

    }
    
}

/**
 * To help checkAdjacent, handles the verification of the horizontal adjancent cells.
 */
bool Game::adjacentHorizontal(int row, int col, int colDif){
    for(int i=1; i <colDif; i++){
        if(this->board.at(row).at(col+i)!=-1&&this->board.at(row).at(col+i)!=-2)
            return false;
    }
    return true;
}

/**
 * To help checkAdjacent, handles the verification of the vertical adjancent cells.
 */
bool Game::adjacentVertical(int col, int row, int rowDif){
    for(int i=1; i <rowDif; i++){
        if(this->board.at(row+i).at(col)!=-1&&this->board.at(row+i).at(col)!=-2)
            return false;
    }
    return true;
}

/**
 * Function with a loop that only accepts inputs within the limits of the board.
 */
void Game::validInput(int &row, int &col){
    do{
        do{
            cout << "Column (From 0 to 6):\n";
            cin >> col;
        }while((col < 0 || col > 6) && cout<< "\nInvalid column\n");
        cout << "Row (From 0 to 6):\n";
        cin >> row;
    }while((row < 0 || row > 6) && cout<< "\nInvalid row\n");
}

/**
 * Checks if the player has no more moves left.
 */
bool Game::checkNoMovesLeft(int player){
    vector<vector<int>> pieces=getPiecesOf(player);
    for(auto it:pieces){
        if(getMoveCoords(player,it.at(0),it.at(1)).size()>0)
            return false;
    }
    return true;
}

/**
 * Checks if the player loses the game.
 */
bool Game::checkLose(int player){
    if(this->numberOfPiecesInserted!=18)
        return false;
    if(player==1 && this->numberOfWhitePieces<3)
        return true;
    if(player==2 && this->numberOfRedPieces<3)
        return true;
    if(checkNoMovesLeft(player))
        return true;
    return false;
}

/**
 * GameLoop to handle all the player vs player.
 */
void Game::gameLoopPvP()
{
    while(true){
    printBoard();
    if(checkLose(1)){
        cout << "White Player lost, better luck next time.\n"
        << "Well done Red player.\n";
        return;
    }
    askMove(1);
    printBoard();
    if(checkLose(2)){
        cout << "Red Player lost, better luck next time.\n"
        << "Well done White player.\n";
        return;
    }
    askMove(2);
    }
}