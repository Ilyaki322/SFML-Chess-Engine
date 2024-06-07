#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(sf::Texture &image, sf::Vector2f position, Color side)
    :Pieces(image,position,side), m_firstMoveFlag(true) {}


int Pawn::getValue() const
{
    return 1;
}


std::vector<Move> Pawn::generateMoves(const int squares[]) const
{
    // TODO: Enpassant
    std::vector<Move> moves;
    int forward;
    int pos = getPosition();
    (m_side == BLACK) ? forward = DOWN : forward = UP;
    
    if (pos - 8 < 0 || pos + 8 > 64) return moves; // THIS SHOULD PROMOTE!
    if (!Board::instance().isOccupied(pos + forward))
    {
        moves.push_back({ pos, pos + forward });
        /*
        if (m_firstMoveFlag && (!Board::instance().isOccupied(pos + forward * 2)))
        {
            moves.push_back({ pos, pos + forward * 2 });
        }
        */
    }

    if (pos % 8 != 7)
    {
        if (Board::instance().isOccupied(pos + forward + RIGHT) &&
            Board::instance().getPieceAt(pos + forward + RIGHT).getColor() != m_side)
        {
            moves.push_back({ pos, pos + forward + RIGHT });
        }
    }

    if (pos % 8 != 0)
    {
        if (Board::instance().isOccupied(pos + forward + LEFT) &&
            Board::instance().getPieceAt(pos + forward + LEFT).getColor() != m_side)
        {
            moves.push_back({ pos, pos + forward + LEFT });
        }
    }

    return moves;
}