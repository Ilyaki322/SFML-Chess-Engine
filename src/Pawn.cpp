#include "Pawn.h"

int Pawn::getValue() const
{
    return 0;
}

bool Pawn::isValid() const
{
    return false;
}


std::vector<std::pair<int, int>> Pawn::possibleMoves(Board*) const
{
    return std::vector<std::pair<int, int>>();
}
