#include "Bishop.h"

Bishop::Bishop(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side)
{
}

int Bishop::getValue() const
{
	return 0;
}

bool Bishop::isValid() const
{
	return false;
}

std::vector<std::pair<int, int>> Bishop::possibleMoves(Board*) const
{
	return std::vector<std::pair<int, int>>();
}
