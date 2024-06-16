#include "AIController.h"
#include<iostream> // DEBUG
#include "NBoard.h"
AIController::AIController(Color color)
    :Controller(color)
{
}

bool AIController::turnReady()
{
    return true;
}

Move AIController::playTurn()
{
    depth = 3;
    IGenerate generate;
    Move bestMove = { -1, -1 , -1, -1 ,PawnVal};
    int bestValue = (m_color == WHITE) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    std::vector<std::vector<Move>> allMoves = generate.generateAll(m_color);
    for (auto i : allMoves) {
        for (auto &move : i) {
            NBoard::instance().move(move);
            int boardValue = minimax(depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), m_color == BLACK);
            NBoard::instance().undo();

            if ((m_color == WHITE && boardValue > bestValue) || (m_color == BLACK && boardValue < bestValue)) {
                bestValue = boardValue;
                bestMove = move;
            }
        }
    }
	return bestMove;
}

int AIController::minimax(int depth, int alpha, int beta, bool maximizingPlayer)
{
    if (depth == 0) {
        return evaluateBoard();
    }
    IGenerate generate;
    std::vector<std::vector<Move>> allMoves  = generate.generateAll(maximizingPlayer ? WHITE : BLACK);

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& i : allMoves) {
            for (const auto& move : i) {

                NBoard::instance().move(move);
                int eval = minimax(depth - 1, alpha, beta, false);
                NBoard::instance().undo();

                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();
        for (const auto& i : allMoves) {
            for (const auto& move : i) {

                NBoard::instance().move(move);
                int eval = minimax(depth - 1, alpha, beta, true);
                NBoard::instance().undo();

                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return minEval;
    }
}

int AIController::evaluateBoard()
{
    int score = 0;
    int pieceValue = 0;
    for (int x = 0; x < 64; x++) {
        int piece = NBoard::instance().m_board[x];
        int color = (piece & White) > 0 ? White : Black;
        int pieceType = (piece & 0b111);
        if (piece) {
            switch (pieceType) {
            case PawnVal: {
                pieceValue = color == White ? 10 : -10;
                pieceValue += color == White ? whitePawnTable[x] : -blackPawnTable[x];
                break;
            }
            case RookVal: {
                pieceValue = color == White ? 50 : -50 ;
                pieceValue += color == White ? whiteRookTable[x] : -blackRookTable[x];
                break;
            }
            case KnightVal: {
                pieceValue = color == White ? 30 : -30;
                pieceValue += color == White ? whiteKnightTable[x] : -blackKnightTable[x];
                break;
            }
            case BishopVal: {
                pieceValue = color == White ? 30 : -30;
                pieceValue += color == White ? whiteBishopTable[x] : -blackBishopTable[x];
                break;
            }
            case QueenVal: {
                pieceValue = color == White ? 90 : -90;
                pieceValue += color == White ? whiteQueenTable[x] : -blackQueenTable[x];
                break;
            }
            case KingVal: {
                pieceValue = color == White ? 900 : -900;
                pieceValue += color == White ? whiteKingTableMidgame[x] : -blackKingTableMidgame[x];
                break;
            }
        }
        score += pieceValue;
        }
    }
    return score;
}

