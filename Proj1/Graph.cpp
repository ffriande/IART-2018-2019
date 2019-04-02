#include "Graph.h"

int idCount = 0;
vector<pair<pair<Board, int>, pair<int, bool>>> dfsList;
int bfsIdCount = 0;
vector<pair<pair<Board, int>, pair<int, bool>>> bfsList;
int greedyCount = 0;
vector<pair<pair<Board, int>, pair<int, bool>>> greedyList;
int aStarCount = 0;
vector<pair<pair<Board, int>, pair<int, bool>>> aStarList;
high_resolution_clock::time_point t1 = high_resolution_clock::now();

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
        cout << "You won the game in " << idCount << "moves" << endl;
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        std::cout << "Elapsed time: " << duration << " s\n";
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
        cout << "You won the game in " << bfsIdCount << "moves" << endl;
                high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        std::cout << "Elapsed time: " << duration << " s\n";
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

        Board b = bfsQueue.back();
        bfsQueue.pop_front();

        vector<Board> nextBoardsPiece;
        vector<Board> nextBoards;
        for (int i = 0; i < getPiecesList(board).size(); i++){
            nextBoardsPiece = getNextMoveBoards(getPiecesList(board)[i], board);
            for (int j = 0; j < nextBoardsPiece.size(); j++){
                nextBoards.push_back(nextBoardsPiece[j]);
                bfsQueue.push_back(nextBoardsPiece[j]);
            }
        }

        if(!isBFS_visited(b)){
            bfs(b);
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
        cout << "You won the game in " << greedyCount << "moves" << endl;
                high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        std::cout << "Elapsed time: " << duration << " s\n";
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
    int repeatedN = 0;
    for (int i = 0; i < heuristics.size(); i++){
        if (heuristics[i] == min){
            repeatedN++;
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

Board calculateF(Board board){
    vector<Board> nextBoardsPiece;
    vector<Board> nextBoards;
    for (int i = 0; i < getPiecesList(board).size(); i++){
        nextBoardsPiece = getNextMoveBoards(getPiecesList(board)[i], board);
        for (int j = 0; j < nextBoardsPiece.size(); j++){
            nextBoards.push_back(nextBoardsPiece[j]);
        }
    }
    Board newBoard = nextBoards[0];
    double val = 9999;
    for (int i = 0; i < nextBoards.size(); i++){
        int value = heuristic(nextBoards[i]) + aStarCount;
        if (value < val){
            val = value;
            newBoard = nextBoards[i];
        }
    }
    return newBoard;
}


bool isAStar_visited(Board board){
    int count = 0;
    for (int i = 0; i < aStarList.size(); i++){
        vector<vector<char>> bfsBoard = aStarList[i].first.first.getBoard();
        vector<vector<char>> matrix = board.getBoard();
        if (compareMatrix(bfsBoard, matrix))
            count++;
    }
    if (count != 0){
        return true;
    }
    return false;
}

int getBestAStarMove(vector<double> heuristics){
    int index;
    int min = 9999;
    for (int i = 0; i < heuristics.size(); i++){
        if (heuristics[i] < min){
            min = heuristics[i];
            index = i;
        }
    }
    int repeatedN = 0;
    for (int i = 0; i < heuristics.size(); i++){
        if (heuristics[i] == min){
            repeatedN++;
        }
    }
    if (repeatedN > 1)
        return -1;
    return index;
}

void aStar(Board board){
    pair<Board, int> p1;
    p1.first = board;
    p1.second = aStarCount++;
    pair<int, bool> p2;
    p2.first = -1;
    p2.second = false;
    pair<pair<Board, int>, pair<int, bool>> firstPair;
    firstPair.first = p1;
    firstPair.second = p2;
    aStarList.push_back(firstPair);

    for (int a = 0; a < board.getBoard().size(); a++){
        for (int b = 0; b < board.getBoard()[a].size(); b++){
            cout << board.getBoard()[a][b] << " | ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;

    if (checkVictory(board)){
        cout << "Victory!!!" << endl;
        cout << "You won the game in " << aStarCount << "moves" << endl;
                high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        std::cout << "Elapsed time: " << duration << " s\n";
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

    Board b = calculateF(board);

    vector<double> heuristics;
    for (int i = 0; i < nextBoards.size(); i++){
        heuristics.push_back(heuristic(nextBoards[i]));
    }
    int index = getBestAStarMove(heuristics);
    for (int i = 0; i < nextBoards.size(); i++){
        if (index != -1){
            if(!isAStar_visited(b)){
                aStar(b);
            }
            else{
                aStar(nextBoards[getRandomMove(heuristics)]);
            }
        }
        else{
            aStar(nextBoards[getRandomMove(heuristics)]);
        }
    }
}