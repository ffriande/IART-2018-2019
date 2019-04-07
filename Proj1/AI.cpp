#include "AI.h"
//starting game
Game original;
//current node being analyzed
struct node *currNode;
//queue used to make the bfsTree
queue<struct node *> bfsTree;
//stack used to make the dfsTree
stack<struct node *> dfsTree;
//stack used to make the greedyTree
stack<struct node *> greedyTree;
//queue used to make the aStarTree
queue<struct node *> aStarTree;
//vector used to save all created nodes
vector<struct node> allNodes;

high_resolution_clock::time_point t;

/**
  * To set the default values.
  */
void startAI(Game game)
{
    original = game;
    currNode = NULL;
}
/**
  * Translates the solution to display all the sequence of boards and sequence of moves.
  */
void getSolution()
{
    vector<vector<int>> solution;
    struct node *validNode = currNode;
    while (validNode != NULL)
    {
        solution.push_back(validNode->to);
        solution.push_back(validNode->from);
        validNode = validNode->father;
    }
    reverse(solution.begin(), solution.end());
    int i = 0;
    while (true)
    {
        original.getBoard().printBoard();
        if (!original.applyGravity() && !original.verifyCombos())
        {
            if (i < (int)solution.size() - 1)
            {
                cout << "\t      |\n\t      |\n\t   ONE MOVE\n\t      |\n\t      V\n\n";
                original.swapPiecesAI(solution.at(i)[0], solution.at(i)[1], solution.at(i + 1)[0], solution.at(i + 1)[1]);
                i += 2;
            }
        }
        if (original.checkVictory())
        {
            original.getBoard().printBoard();
            break;
        }
    }
    cout << "Solution: \n";
    for (int index = 0; index < (int)solution.size() - 1; index += 2)
    {
        cout << "Change piece from (" << solution.at(index)[0] << "," << solution.at(index)[1] << ") ";
        cout << "to (" << solution.at(index + 1)[0] << "," << solution.at(index + 1)[1] << ")\n";
    }
}

/**
  * Gets a solution using bfs.
  */
void bfs(Game game)
{
    startClock();
    do
    {
        for (int i = 0; i < (int)game.getBoard().getBoard().size(); i++)
        {
            for (int j = 0; j < (int)game.getBoard().getBoard().at(i).size(); j++)
            {
                vector<vector<int>> possibleMoves = game.possibleMovesList(i, j);
                if (possibleMoves.size() > 0)
                {
                    for (unsigned int w = 0; w < possibleMoves.size(); w++)
                    {
                        vector<int> from = {i, j};
                        vector<int> to = possibleMoves.at(w);
                        struct node *newNode = new node();
                        newNode->from = from;
                        newNode->to = to;
                        newNode->prevGame = game;
                        if (currNode == NULL)
                        {
                            newNode->father = NULL;
                            newNode->level = 1;
                        }
                        else
                        {
                            newNode->father = currNode;
                            newNode->level = currNode->level + 1;
                        }
                        bfsTree.push(newNode);
                    }
                }
            }
        }
        do
        {
            currNode = bfsTree.front();
            bfsTree.pop();
            game = currNode->prevGame;
            game.swapPiecesAI(currNode->from[0], currNode->from[1], currNode->to[0], currNode->to[1]);
            while (game.applyGravity() || game.verifyCombos())
                ;
            if (checkDuplicated(game.getBoard().getBoard(), currNode->level))
                continue;
            else
                allNodes.push_back(*currNode);
            if (game.checkVictory())
            {
                getSolution();
                cout << "\n\n\n\nVitoria do bot em : " << currNode->level << "\n";
                stopClock();
                return;
            }
        } while (game.checkGameOver() || currNode->level >= game.getMaxMoves());

    } while (bfsTree.size() > 0);
    cout << "\n\nError, not a valid board because not a valid sequence found!\n\n";
}

/**
  * Gets a solution using dfs.
  */
void dfs(Game game)
{
    startClock();
    do
    {
        for (int i = 0; i < (int)game.getBoard().getBoard().size(); i++)
        {
            for (int j = 0; j < (int)game.getBoard().getBoard().at(i).size(); j++)
            {
                vector<vector<int>> possibleMoves = game.possibleMovesList(i, j);
                if (possibleMoves.size() > 0)
                {
                    for (unsigned int w = 0; w < possibleMoves.size(); w++)
                    {
                        vector<int> from = {i, j};
                        vector<int> to = possibleMoves.at(w);
                        struct node *newNode = new node();
                        newNode->from = from;
                        newNode->to = to;
                        newNode->prevGame = game;
                        if (currNode == NULL)
                        {
                            newNode->father = NULL;
                            newNode->level = 1;
                        }
                        else
                        {
                            newNode->father = currNode;
                            newNode->level = currNode->level + 1;
                        }
                        dfsTree.push(newNode);
                    }
                }
            }
        }
        do
        {
            currNode = dfsTree.top();
            dfsTree.pop();
            game = currNode->prevGame;
            game.swapPiecesAI(currNode->from[0], currNode->from[1], currNode->to[0], currNode->to[1]);
            while (game.applyGravity() || game.verifyCombos())
                ;
            if (checkDuplicated(game.getBoard().getBoard(), currNode->level))
                continue;
            else
                allNodes.push_back(*currNode);
            if (game.checkVictory())
            {
                getSolution();
                cout << "\n\n\n\nVitoria do bot em : " << currNode->level << "\n";
                stopClock();
                return;
            }
        } while (game.checkGameOver() || currNode->level >= game.getMaxMoves());
    } while (dfsTree.size() > 0);
    cout << "\n\nError, not a valid board because not a valid sequence found!\n\n";
}


/**
  * Gets a solution using greedy.
  */
void greedy(Game game)
{
    startClock();
    vector<struct node *> children;
    do
    {
        for (int i = 0; i < (int)game.getBoard().getBoard().size(); i++)
        {
            for (int j = 0; j < (int)game.getBoard().getBoard().at(i).size(); j++)
            {
                vector<vector<int>> possibleMoves = game.possibleMovesList(i, j);
                if (possibleMoves.size() > 0)
                {
                    for (unsigned int w = 0; w < possibleMoves.size(); w++)
                    {
                        vector<int> from = {i, j};
                        vector<int> to = possibleMoves.at(w);
                        struct node *newNode = new node();
                        newNode->from = from;
                        newNode->to = to;
                        newNode->prevGame = game;
                        newNode->value = calculateGreedyValue(game, from, to);
                        if (newNode->value != -1)
                        {
                            if (currNode == NULL)
                            {
                                newNode->father = NULL;
                                newNode->level = 1;
                            }
                            else
                            {
                                newNode->father = currNode;
                                newNode->level = currNode->level + 1;
                            }
                            allNodes.push_back(*newNode);
                            children.push_back(newNode);
                        }
                    }
                }
            }
        }
        while (children.size() > 0)
        {
            int index = getBestValue(children);
            greedyTree.push(children.at(index));
            children.erase(children.begin() + index);
        }
        do
        {
            currNode = greedyTree.top();
            greedyTree.pop();
            game = currNode->prevGame;
            game.swapPiecesAI(currNode->from[0], currNode->from[1], currNode->to[0], currNode->to[1]);
            while (game.applyGravity() || game.verifyCombos())
                ;
            if (game.checkVictory())
            {
                getSolution();
                cout << "\n\n\n\nVitoria do bot em : " << currNode->level << "\n";
                stopClock();
                return;
            }
        } while (game.checkGameOver() || currNode->level >= game.getMaxMoves());
    } while (greedyTree.size() > 0);
    cout << "\n\nError, not a valid board because not a valid sequence found!\n\n";
}

/**
  * Gets a solution using a*.
  */
void aStar(Game game, int heuristic)
{
    startClock();
    vector<struct node *> children;
    do
    {
        for (int i = 0; i < (int)game.getBoard().getBoard().size(); i++)
        {
            for (int j = 0; j < (int)game.getBoard().getBoard().at(i).size(); j++)
            {
                vector<vector<int>> possibleMoves = game.possibleMovesList(i, j);
                if (possibleMoves.size() > 0)
                {
                    for (unsigned int w = 0; w < possibleMoves.size(); w++)
                    {
                        vector<int> from = {i, j};
                        vector<int> to = possibleMoves.at(w);
                        struct node *newNode = new node();
                        newNode->from = from;
                        newNode->to = to;
                        newNode->prevGame = game;
                        newNode->heuris = calculateAstarHn(game, from, to, heuristic);
                        if (newNode->heuris != -1)
                        {
                            if (currNode == NULL)
                            {
                                newNode->father = NULL;
                                newNode->level = 1;
                            }
                            else
                            {
                                newNode->father = currNode;
                                newNode->level = currNode->level + 1;
                            }
                            newNode->value = newNode->heuris + newNode->level;
                            allNodes.push_back(*newNode);
                            children.push_back(newNode);
                        }
                    }
                }
            }
        }
        orderQueue(children);
        do
        {
            currNode = aStarTree.front();
            aStarTree.pop();
            game = currNode->prevGame;
            game.swapPiecesAI(currNode->from[0], currNode->from[1], currNode->to[0], currNode->to[1]);
            while (game.applyGravity() || game.verifyCombos())
                ;
            if (game.checkVictory())
            {
                getSolution();
                cout << "\n\n\n\nVitoria do bot em : " << currNode->level << "\n";
                stopClock();
                return;
            }
        } while (game.checkGameOver() || currNode->level >= game.getMaxMoves());
    } while (aStarTree.size() > 0);
    cout << "\n\nError, not a valid board because not a valid sequence found!\n\n";
}

/**
  * Gets the nodes from vectorAux to the aStarTree by order of value
  */
void orderQueue(vector<struct node *> &vectorAux)
{
    while (!aStarTree.empty())
    {
        vectorAux.push_back(aStarTree.front());
        aStarTree.pop();
    }
    while (vectorAux.size() > 0)
    {
        int index = getLowestValue(vectorAux);
        aStarTree.push(vectorAux.at(index));
        vectorAux.erase(vectorAux.begin() + index);
    }
}

/**
  * Calculates the heuristic value of a move.
  */
float calculateAstarHn(Game game, vector<int> from, vector<int> to, int heuristic)
{
    float ret;
    int g = calculateGreedyValue(game, from, to);
    if(g==0){
        return 0;
    }
    if (g == -1)
        return -1;
    switch (heuristic)
    {
    case 1:
        ret = (float)g / (float)game.getNrPieces();
        break;
    case 2:
        ret = (float)game.getNrPieces() / (float)g;
        break;
    case 3:
        ret=(float)g;
        break;
    default:
        break;
    }
    return ret;
}


/**
  * Calculates the greedy value of a move.
  */
int calculateGreedyValue(Game game, vector<int> from, vector<int> to)
{
    game.swapPiecesAI(from[0], from[1], to[0], to[1]);
    while (game.applyGravity() || game.verifyCombos())
        ;
    if (game.checkGameOver() || (currNode != NULL && checkDuplicated(game.getBoard().getBoard(), currNode->level)))
        return -1;
    else
        return game.getNrPieces();
}

/**
  * Returns the index of the best value in vector of nodes avl.
  */
int getBestValue(vector<struct node *> &avl)
{
    int maxValue = INT_MIN;
    int i;
    for (int k = 0; k < (int)avl.size(); k++)
    {
        int curValue = avl.at(k)->value;
        if (maxValue < curValue)
        {
            maxValue = curValue;
            i = k;
        }
    }
    return i;
}

/**
 * Returns the index of the lowest value in vector of nodes avl.
 */
int getLowestValue(vector<struct node *> &avl)
{
    int lowestValue = INT_MAX;
    int i;
    for (int k = 0; k < (int)avl.size(); k++)
    {
        int curValue = avl.at(k)->value;
        if (lowestValue > curValue)
        {
            lowestValue = curValue;
            i = k;
        }
    }
    return i;
}

/**
  * Checks if boardCheck is already in a board of allNodes
  */
bool checkDuplicated(vector<vector<char>> boardCheck, int level)
{
    for (int i = 0; i < (int)allNodes.size(); i++)
    {
        if (allNodes.at(i).level <= level)
            if (compareMatrixx(allNodes.at(i).prevGame.getBoard().getBoard(), boardCheck))
                return true;
    }
    return false;
}

/**
 * Compares board1 and board2, returns true if they are equal, false if not.
 */
bool compareMatrixx(vector<vector<char>> board1, vector<vector<char>> board2)
{
    for (int z = 0; z < (int)board2.size(); z++)
    {
        for (int x = 0; x < (int)board2[z].size(); x++)
        {
            if (board2[z][x] != board1[z][x])
            {
                return false;
            }
        }
    }
    return true;
}


void startClock(){
    t = high_resolution_clock::now();
}

void stopClock(){
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t ).count();
    duration /= 100;
    std::cout << "Elapsed time: " << duration << " us\n";
}