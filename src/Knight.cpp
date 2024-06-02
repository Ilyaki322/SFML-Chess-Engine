#include "Knight.h"

Knight::Knight(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side)
{
}

int Knight::getValue() const
{
	return 3;
}

bool Knight::isValid(const int squares[], const int target) const
{
	return false;
}

std::vector<std::pair<int, int>> Knight::possibleMoves(Board*) const
{
	return std::vector<std::pair<int, int>>();
}
