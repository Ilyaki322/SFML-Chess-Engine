#include "Rook.h"

Rook::Rook(sf::Texture& image, sf::Vector2f position, Color side)
    :Pieces(image, position, side)
{
}

int Rook::getValue() const
{
    return 5;
}

bool Rook::isValid(const int squares[], const int target) const
{
    return false;
}

std::vector<std::pair<int, int>> Rook::possibleMoves(Board*) const
{
    return std::vector<std::pair<int, int>>();
}
