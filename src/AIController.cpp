#include "AIController.h"
#include<iostream> // DEBUG
#include "SpecialMove.h"
AIController::AIController(Color color)
    :Controller(color)
{
    depth = 1;
}

bool AIController::playTurn(Move& bestMove)
{
    int bestValue = (m_color == WHITE) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    std::vector<std::vector<Move>> allMoves = Board::instance().allMovesOf(m_color);
    for (auto i : allMoves) {
        for (auto move : i) {
            EndMove e = SpecialMove::instance().MoveType(move);
            if (e != Regular){
                Board::instance().makeMove(move);
            }
            else {
                Board::instance().fakeMove(move);
                if (SpecialMove::instance().fakeMove(move, Board::instance().AllMoves()))
                {
                    Board::instance().undoMove(move);
                    Board::instance().makeMove(move);
                    
                }
            }

            int boardValue = minimax(depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), m_color == BLACK);
            if(e == Regular)
                SpecialMove::instance().undo();
            Board::instance().undoMove(move);

            if ((m_color == WHITE && boardValue > bestValue) || (m_color == BLACK && boardValue < bestValue)) {
                bestValue = boardValue;
                bestMove = move;
            }
        }
    }
	return true;
}

int AIController::minimax(int depth, int alpha, int beta, bool maximizingPlayer)
{
    if (depth == 0) {
        return evaluateBoard();
    }

    std::vector<std::vector<Move>> allMoves  = Board::instance().allMovesOf(maximizingPlayer ? WHITE : BLACK);

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& i : allMoves) {
            for (const auto& move : i) {
                Board::instance().fakeMove(move);

                int eval = minimax(depth - 1, alpha, beta, false);

                Board::instance().undoMove(move);

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

                Board::instance().fakeMove(move);

                int eval = minimax(depth - 1, alpha, beta, true);

                Board::instance().undoMove(move);


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
    for (int x = 0; x < 64; x++) {
        std::shared_ptr<Pieces> piece = Board::instance().getPiece(x);
        if (piece) {
            int pieceValue = 0;
            switch (piece->getSymbol()) {
            case 'P': pieceValue = 10; break;
            case 'R': pieceValue = 50; break;
            case 'N': pieceValue = 30; break;
            case 'B': pieceValue = 30; break;
            case 'Q': pieceValue = 90; break;
            case 'K': pieceValue = 900; break;
            case 'p': pieceValue = -10; break;
            case 'r': pieceValue = -50; break;
            case 'n': pieceValue = -30; break;
            case 'b': pieceValue = -30; break;
            case 'q': pieceValue = -90; break;
            case 'k': pieceValue = -900; break;
        }
        score += pieceValue;
        }
    }
    return score;
}

