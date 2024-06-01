#include "Rock.h"

Rock::Rock(sf::Texture& image, sf::Vector2f position, Color side)
    :Pieces(image, position, side)
{
}

int Rock::getValue() const
{
    return 5;
}

bool Rock::isValid() const
{
    return false;
}

std::vector<std::pair<int, int>> Rock::possibleMoves(Board*) const
{
    return std::vector<std::pair<int, int>>();
}
