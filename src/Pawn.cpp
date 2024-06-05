#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(sf::Texture &image, sf::Vector2f position, Color side)
    :Pieces(image,position,side), m_firstMoveFlag(true)
{
}

int Pawn::getValue() const
{
    return 1;
}

bool Pawn::isValid(const int squares[], const int target) const
{
    int pos = getPosition();
    int forward = (m_side == BLACK) ?  DOWN :  UP;

    if (Board::instance().isOccupied(target) &&
        Board::instance().getPieceAt(target).getColor() == getColor()) return false;

    if (pos + forward == target) return true;
    if (pos + forward * 2 == target && m_firstMoveFlag) return true;
    if (pos + forward+RIGHT == target && Board::instance().isOccupied(target)) return true;
    if (pos + forward + LEFT == target && Board::instance().isOccupied(target)) return true;

    return false;
}


std::vector<std::pair<int, int>> Pawn::possibleMoves(Board*) const
{
    return std::vector<std::pair<int, int>>();
}


/// WORK IN PROGRESS!!!
std::vector<Move> Pawn::generateMoves(const int squares[]) const
{
    // TODO: Enpassant
    std::vector<Move> moves;
    int forward;
    int pos = getPosition();
    (m_side == BLACK) ? forward = DOWN : forward = UP;
    
    if (!Board::instance().isOccupied(pos + forward))
    {
        moves.push_back({ pos, pos + forward });
        if (pos - 8 < 0 || pos + 8 > 64)
        {
            //TODO: promote
            return moves;
        }

        if (m_firstMoveFlag && (!Board::instance().isOccupied(pos + forward * 2)))
        {
            moves.push_back({ pos, pos + forward * 2 });
        }
    }

    if (pos % 8 != 7)
    {
        if (Board::instance().isOccupied(pos + forward+LEFT) &&
            Board::instance().getPieceAt(pos + forward+LEFT).getColor() != getColor())
        {
            moves.push_back({ pos, pos + forward + LEFT });
        }
    }
    if (pos % 8 != 0)
    {
        if (Board::instance().isOccupied(pos + forward + RIGHT) &&
            Board::instance().getPieceAt(pos + forward + RIGHT).getColor() != getColor())
        {
            moves.push_back({ pos, pos + forward + RIGHT });
        }
    }

    return moves;
}
