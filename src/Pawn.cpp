#include "Pawn.h"


Pawn::Pawn(sf::Texture &image, sf::Vector2f position, Color side)
    :Pieces(image,position,side)
{
}

int Pawn::getValue() const
{
    return 1;
}

bool Pawn::isValid(const int squares[], const int target) const
{
    return false;
}


std::vector<std::pair<int, int>> Pawn::possibleMoves(Board*) const
{
    return std::vector<std::pair<int, int>>();
}
