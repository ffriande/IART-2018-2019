#include "Graph.h"

int idCount = 0;
vector<pair<pair<Board, int>, pair<int, bool>>> dfsList;
int bfsIdCount = 0;
vector<pair<pair<Board, int>, pair<int, bool>>> bfsList;
int greedyCount = 0;
vector<pair<pair<Board, int>, pair<int, bool>>> greedyList;

void startAI(){

}

void dfs(Board currBoard){

    pair<Board, int> p1;
    p1.first = currBoard;
    p1.second = idCount++;
    pair<int, bool> p2;
    p2.first = -1;
    p2.second = false;
    pair<pair<Board, int>, pair<int, bool>> firstPair;
    firstPair.first = p1;
    firstPair.second = p2;
    dfsList.push_back(firstPair);

    for (int a = 0; a < currBoard.getBoard().size(); a++){
        for (int b = 0; b < currBoard.getBoard()[a].size(); b++){
            cout << currBoard.getBoard()[a][b] << " | ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;

    if (checkVictory(currBoard)){
        cout << "Victory!!!" << endl;
        exit(0);
    }

    vector<Board> nextBoardsPiece;
    vector<Board> nextBoards;
    for (int i = 0; i < getPiecesList(currBoard).size(); i++){
        nextBoardsPiece = getNextMoveBoards(getPiecesList(currBoard)[i], currBoard);
        for (int j = 0; j < nextBoardsPiece.size(); j++){
            nextBoards.push_back(nextBoardsPiece[j]);
        }
    }

    for (int i = 0; i < nextBoards.size(); i++){
        if(!isDFS_visited(nextBoards[i])){
            dfs(nextBoards[i]);
        }

    }
}

bool isDFS_visited(Board board){
    int count = 0;
    for (int i = 0; i < dfsList.size(); i++){
        vector<vector<char>> dfsBoard = dfsList[i].first.first.getBoard();
        vector<vector<char>> matrix = board.getBoard();
        if (compareMatrix(dfsBoard, matrix))
            count++;
    }
    if (count != 0){
        return true;
    }
    return false;
}

bool compareMatrix(vector<vector<char>> dfsBoard, vector<vector<char>> matrix){
    for (int z = 0; z < matrix.size(); z++){
        for (int x = 0; x < matrix[x].size(); x++){
            if (matrix[z][x] != dfsBoard[z][x]){
                return false;
            }
        }
    }
    return true;
}

void bfs(Board board){
    pair<Board, int> p1;
    p1.first = board;
    p1.second = bfsIdCount++;
    pair<int, bool> p2;
    p2.first = -1;
    p2.second = false;
    pair<pair<Board, int>, pair<int, bool>> firstPair;
    firstPair.first = p1;
    firstPair.second = p2;
    bfsList.push_back(firstPair);
    list<Board> bfsQueue; 
    bfsQueue.push_back(board);

    if (checkVictory(board)){
        cout << "Victory!!!" << endl;
        exit(0);
    }  
  
    while(!bfsQueue.empty()) 
    { 
        board = bfsQueue.front(); 

        for (int a = 0; a < board.getBoard().size(); a++){
            for (int b = 0; b < board.getBoard()[a].size(); b++){
                cout << board.getBoard()[a][b] << " | ";
            }
            cout << endl;
        }
        cout << "------------------------" << endl;
        bfsQueue.pop_front(); 


        vector<Board> nextBoardsPiece;
        vector<Board> nextBoards;
        for (int i = 0; i < getPiecesList(board).size(); i++){
            nextBoardsPiece = getNextMoveBoards(getPiecesList(board)[i], board);
            for (int j = 0; j < nextBoardsPiece.size(); j++){
                nextBoards.push_back(nextBoardsPiece[j]);
            }
        }

        for (int i = 0; i < nextBoards.size(); i++){
            if(!isBFS_visited(nextBoards[i])){
                bfs(nextBoards[i]);
            }

        }
    } 
}

bool isBFS_visited(Board board){
    int count = 0;
    for (int i = 0; i < bfsList.size(); i++){
        vector<vector<char>> bfsBoard = bfsList[i].first.first.getBoard();
        vector<vector<char>> matrix = board.getBoard();
        if (compareMatrix(bfsBoard, matrix))
            count++;
    }
    if (count != 0){
        return true;
    }
    return false;
}

void greedy(Board board){
    pair<Board, int> p1;
    p1.first = board;
    p1.second = greedyCount++;
    pair<int, bool> p2;
    p2.first = -1;
    p2.second = false;
    pair<pair<Board, int>, pair<int, bool>> firstPair;
    firstPair.first = p1;
    firstPair.second = p2;
    greedyList.push_back(firstPair);

    for (int a = 0; a < board.getBoard().size(); a++){
        for (int b = 0; b < board.getBoard()[a].size(); b++){
            cout << board.getBoard()[a][b] << " | ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;

    if (checkVictory(board)){
        cout << "Victory!!!" << endl;
        exit(0);
    }

    vector<Board> nextBoardsPiece;
    vector<Board> nextBoards;
    for (int i = 0; i < getPiecesList(board).size(); i++){
        nextBoardsPiece = getNextMoveBoards(getPiecesList(board)[i], board);
        for (int j = 0; j < nextBoardsPiece.size(); j++){
            nextBoards.push_back(nextBoardsPiece[j]);
        }
    }

    vector<double> heuristics;
    for (int i = 0; i < nextBoards.size(); i++){
        heuristics.push_back(heuristic(nextBoards[i]));
    }
    int index = getBestGreedyMove(heuristics);

    for (int i = 0; i < nextBoards.size(); i++){
        if(!isGreedy_visited(nextBoards[index])){
            greedy(nextBoards[index]);
        }
        else{
            greedy(nextBoards[getRandomMove(heuristics)]);
        }

    }

}

// The less the value the better
double heuristic(Board board){
    vector<vector<int>> v = getPiecesList(board);
    return v.size()/5;
}

int getBestGreedyMove(vector<double> heuristics){
    int index;
    int min = 9999;
    for (int i = 0; i < heuristics.size(); i++){
        if (heuristics[i] < min){
            min = heuristics[i];
            index = i;
        }
    }
    return index;
}

int getRandomMove(vector<double> heuristics){
    return rand() % heuristics.size();
}

bool isGreedy_visited(Board board){
    int count = 0;
    for (int i = 0; i < greedyList.size(); i++){
        vector<vector<char>> bfsBoard = greedyList[i].first.first.getBoard();
        vector<vector<char>> matrix = board.getBoard();
        if (compareMatrix(bfsBoard, matrix))
            count++;
    }
    if (count != 0){
        return true;
    }
    return false;
}