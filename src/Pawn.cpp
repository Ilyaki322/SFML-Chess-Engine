#include "Pawn.h"
#include "Pawn.h"

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
    return true;
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
    
    if (squares[pos + forward] == 0)
    {
        moves.push_back({ pos, pos + forward });
        if (pos - 8 < 0 || pos + 8 > 64)
        {
            //TODO: promote
            return moves;
        }

        if (m_firstMoveFlag && (squares[pos + forward * 2] == 0))
        {
            //m_firstMoveFlag = false; // fuck consts okay?
            moves.push_back({ pos, pos + forward * 2 });
        }
    }

    if (pos % 8 != 7)
    {
        if (((squares[pos + TOP_LEFT] & m_side) == 0) && (squares[pos + TOP_LEFT] != 0))
        {
            moves.push_back({ pos, pos + TOP_LEFT });
        }
    }
    if (pos % 8 != 0)
    {
        if (((squares[pos + TOP_RIGHT] & m_side) == 0) && (squares[pos + TOP_RIGHT] != 0))
        {
            moves.push_back({ pos, pos + TOP_RIGHT });
        }
    }

    return moves;
}
