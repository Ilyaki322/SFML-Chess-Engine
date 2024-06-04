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
	int pos = getPosition();

	int x = squares[target] & m_side;
	if (x > 0) return false;

	if (pos + DOWN * 2 + RIGHT == target) return true;
	if (pos + DOWN * 2 + LEFT == target) return true;
	if (pos + RIGHT * 2 + DOWN == target) return true;
	if (pos + RIGHT * 2 + UP == target) return true;
	if (pos + LEFT * 2 + UP == target) return true;
	if (pos + LEFT * 2 + DOWN == target) return true;
	if (pos + UP * 2 + RIGHT == target) return true;
	if (pos + UP * 2 + LEFT == target) return true;

	return false;
}

std::vector<std::pair<int, int>> Knight::possibleMoves(Board*) const
{
	return std::vector<std::pair<int, int>>();
}
