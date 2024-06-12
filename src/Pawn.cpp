#include "Pawn.h"
#include "Board.h"
#include "SpecialMove.h"

#include <iostream>

Pawn::Pawn(sf::Texture &image, sf::Vector2f position, Color side, char symbol)
    :Pieces(image,position,side,symbol), m_firstMoveFlag(2) {}


int Pawn::getValue() const
{
    return 1;
}


std::vector<Move> Pawn::generateMoves() const
{
    std::vector<Move> moves;
    int forward;
    int pos = getPosition();
    (m_side == BLACK) ? forward = DOWN : forward = UP;
    
    if (pos - 8 < 0 || pos + 8 > 64) return moves; // THIS SHOULD PROMOTE!

    if (!Board::instance().isOccupied(pos + forward))
    {
        moves.push_back({ pos, pos + forward });
        
        if (SpecialMove::instance().canDouble(pos) && (!Board::instance().isOccupied(pos + forward * 2)))
        {
            moves.push_back({ pos, pos + forward * 2 });
        }
    }

    if (pos % 8 != 7)
    {
        if (Board::instance().isOccupied(pos + forward + RIGHT) &&
            Board::instance().getPieceAt(pos + forward + RIGHT).getColor() != m_side)
        {
            moves.push_back({ pos, pos + forward + RIGHT });
        }

        if (Board::instance().isOccupied(pos + RIGHT) &&
            Board::instance().getPieceAt(pos + RIGHT).getColor() != m_side)
        {
            if (SpecialMove::instance().enPassant(pos + RIGHT))
            {
                moves.push_back({ pos, pos + forward + RIGHT });
            }
        }
    }

    if (pos % 8 != 0)
    {
        if (Board::instance().isOccupied(pos + forward + LEFT) &&
            Board::instance().getPieceAt(pos + forward + LEFT).getColor() != m_side)
        {
            moves.push_back({ pos, pos + forward + LEFT });
        }

        if (Board::instance().isOccupied(pos + LEFT) &&
            Board::instance().getPieceAt(pos + LEFT).getColor() != m_side)
        {
            if (SpecialMove::instance().enPassant(pos + LEFT))
            {
                moves.push_back({ pos, pos + forward + LEFT });
            }
        }
    }

    return moves;
}