#include "AI.h"

map<vector<int>, vector<vector<int>>> getBotMoves(Game game, int player)
{
    map<vector<int>, vector<vector<int>>> moves;
    vector<vector<int>> firstChoice = game.getPiecesOf(player);
    for (auto it : firstChoice)
    {
        vector<vector<int>> toWhere;
        toWhere = game.getMoveCoords(player, it.at(0), it.at(1));
        moves[it] = toWhere;
    }
    return moves;
}

int evaluate(Game game, int player, int agent)
{
    int value;
    switch (agent)
    {
    case 1:
        value = evaluation1(game, player);
        break;
    case 2:
        value = evaluation2(game, player);
        break;
    case 3:
        value = evaluation3(game, player);
        break;
    }
    return value;
}

int evaluation1(Game game, int player)
{
    return (game.checkLose(switchPlayer(player)) - game.checkLose(player));
}

int evaluation2(Game game, int player)
{
    int value = 100 * evaluation1(game, player) + game.getnrPlayerPieces(player) - game.getnrPlayerPieces(switchPlayer(player));
    return value;
}

int evaluation3(Game game, int player)
{
    int value = 2 * evaluation2(game, player) + game.count2inRow(player) - game.count2inRow(switchPlayer(player));
    return value;
}

bool max(int n1, int n2)
{
    if (n2 > n1)
        return true;
    return false;
}

bool min(int n1, int n2)
{
    if (n2 < n1)
        return true;
    return false;
}

int switchPlayer(int currPlayer)
{
    if (currPlayer == 1)
        return 2;
    else
        return 1;
}

vector<vector<int>> minimax(Game game, int depth, int alpha, int beta, int maximizingPlayer, int currPlayer, int agent)
{
    if (depth == 0 || game.checkLose(1) || game.checkLose(2))
    {
        return {{evaluate(game, maximizingPlayer, agent)}};
    }

    if (maximizingPlayer == currPlayer)     //case it is the maximizing player
    {
        int maxEval = INT_MIN;
        vector<vector<int>> result;
        //case it is an insertion
        if (game.isInsert())
        {
            vector<vector<int>> inserts = game.getPiecesOf(0);
            for (auto it : inserts)
            {
                Game newgame = game;
                newgame.insertPiece(currPlayer, it.at(0), it.at(1));
                //case the player needs to remove a piece from enemy
                if (newgame.check3InRow(currPlayer, it.at(0), it.at(1)).size() == 3)
                {
                    vector<vector<int>> elim = newgame.validElimination(currPlayer);
                    for (auto el : elim)
                    {
                        Game newGameElim=newgame;
                        newGameElim.removePiece(currPlayer, el.at(0), el.at(1));
                        vector<vector<int>> next = minimax(newGameElim, depth - 1, alpha, beta, maximizingPlayer, switchPlayer(currPlayer), agent);
                        int eval = next.at(0).at(0);
                        if (max(maxEval, eval))
                        {
                            maxEval = eval;
                            result = {{eval}, it, el};
                        }
                        alpha = max(alpha, eval);
                        if (beta <= alpha)
                            return result;
                    }
                }
                else
                { //case the player only inserts a piece
                    vector<vector<int>> next = minimax(newgame, depth - 1, alpha, beta, maximizingPlayer, switchPlayer(currPlayer), agent);
                    int eval = next.at(0).at(0);
                    if (max(maxEval, eval))
                    {
                        maxEval = eval;
                        result = {{eval}, it};
                    }
                    alpha = max(alpha, eval);
                    if (beta <= alpha)
                        break;
                }
            }
            return result;
        }
        else
        { //case it is a move
            map<vector<int>, vector<vector<int>>> moves = getBotMoves(game, currPlayer);
            for (auto it : moves)
            { //loop that goes by all the pieces of a player
                for (auto move : it.second)
                { //loop that goes by all the moves of a certain piece
                    Game newgame = game;
                    newgame.movePiece(currPlayer, it.first.at(0), it.first.at(1), move.at(0), move.at(1));
                    //if after the move it needs to choose a piece to remove.
                    if (newgame.check3InRow(currPlayer, move.at(0), move.at(1)).size() == 3)
                    {
                        vector<vector<int>> elim = newgame.validElimination(currPlayer);
                        for (auto el : elim)
                        {
                            Game newGameElim=newgame;
                            newGameElim.removePiece(currPlayer, el.at(0), el.at(1));
                            vector<vector<int>> next = minimax(newGameElim, depth - 1, alpha, beta, maximizingPlayer, switchPlayer(currPlayer), agent);
                            int eval = next.at(0).at(0);
                            if (max(maxEval, eval))
                            {
                                maxEval = eval;
                                result = {{eval}, it.first, move, el};
                            }
                            alpha = max(alpha, eval);
                            if (beta <= alpha)
                                return result;
                        }
                    }
                    else
                    { //if it only needs to move a piece.
                        vector<vector<int>> next = minimax(newgame, depth - 1, alpha, beta, maximizingPlayer, switchPlayer(currPlayer), agent);
                        int eval = next.at(0).at(0);
                        if (max(maxEval, eval))
                        {
                            maxEval = eval;
                            result = {{eval}, it.first, move};
                        }
                        alpha = max(alpha, eval);
                        if (beta <= alpha)
                            return result;
                    }
                }
            }
            return result;
        }
    }
    else
    {// case is not the maximizing player
        int minEval = INT_MAX;
        vector<vector<int>> result;
        //case it is an insertion
        if (game.isInsert())
        {
            vector<vector<int>> inserts = game.getPiecesOf(0);
            for (auto it : inserts)
            {
                Game newgame = game;
                newgame.insertPiece(currPlayer, it.at(0), it.at(1));
                //case the player needs to remove a piece from enemy
                if (newgame.check3InRow(currPlayer, it.at(0), it.at(1)).size() == 3)
                {
                    vector<vector<int>> elim = newgame.validElimination(currPlayer);
                    for (auto el : elim)
                    {
                        Game newGameElim=newgame;
                        newGameElim.removePiece(currPlayer, el.at(0), el.at(1));
                        vector<vector<int>> next = minimax(newGameElim, depth - 1, alpha, beta, maximizingPlayer, switchPlayer(currPlayer), agent);
                        int eval = next.at(0).at(0);
                        if (min(minEval, eval))
                        {
                            minEval = eval;
                            result = {{eval}, it, el};
                        }
                        beta = min(beta, eval);
                        if (beta <= alpha)
                            return result;
                    }
                }
                else
                { //case the player only inserts a piece
                    vector<vector<int>> next = minimax(newgame, depth - 1, alpha, beta, maximizingPlayer, switchPlayer(currPlayer), agent);
                    int eval = next.at(0).at(0);
                    if (min(minEval, eval))
                    {
                        minEval = eval;
                        result = {{eval}, it};
                    }
                    beta = min(beta, eval);
                    if (beta <= alpha)
                        break;
                }
            }
            return result;
        }
        else
        { //case it is a move
            map<vector<int>, vector<vector<int>>> moves = getBotMoves(game, currPlayer);
            for (auto it : moves)
            { //loop that goes by all the pieces of a player
                for (auto move : it.second)
                { //loop that goes by all the moves of a certain piece
                    Game newgame = game;
                    newgame.movePiece(currPlayer, it.first.at(0), it.first.at(1), move.at(0), move.at(1));
                    //if after the move it needs to choose a piece to remove.
                    if (newgame.check3InRow(currPlayer, move.at(0), move.at(1)).size() == 3)
                    {
                        vector<vector<int>> elim = newgame.validElimination(currPlayer);
                        for (auto el : elim)
                        {
                            Game newGameElim=newgame;
                            newGameElim.removePiece(currPlayer, el.at(0), el.at(1));
                            vector<vector<int>> next = minimax(newGameElim, depth - 1, alpha, beta, maximizingPlayer, switchPlayer(currPlayer), agent);
                            int eval = next.at(0).at(0);
                            if (min(minEval, eval))
                            {
                                minEval = eval;
                                result = {{eval}, it.first, move, el};
                            }
                            beta = min(beta, eval);
                            if (beta <= alpha)
                                return result;
                        }
                    }
                    else
                    { //if it only needs to move a piece.
                        vector<vector<int>> next = minimax(newgame, depth - 1, alpha, beta, maximizingPlayer, switchPlayer(currPlayer), agent);
                        int eval = next.at(0).at(0);
                        if (min(minEval, eval))
                        {
                            minEval = eval;
                            result = {{eval}, it.first, move};
                        }
                        beta = min(beta, eval);
                        if (beta <= alpha)
                            return result;
                    }
                }
            }
            return result;
        }
    }
}
