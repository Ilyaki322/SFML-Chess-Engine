#include "King.h"

King::King(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side)
{
}

int King::getValue() const
{
	return 0;
}

bool King::isValid() const
{
	return false;
}

std::vector<std::pair<int, int>> King::possibleMoves(Board*) const
{
	return std::vector<std::pair<int, int>>();
}
