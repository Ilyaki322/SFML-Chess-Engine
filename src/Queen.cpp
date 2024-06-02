#include "Queen.h"

Queen::Queen(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side)
{
}

int Queen::getValue() const
{
	return 0;
}

bool Queen::isValid() const
{
	return false;
}

std::vector<std::pair<int, int>> Queen::possibleMoves(Board*) const
{
	return std::vector<std::pair<int, int>>();
}
