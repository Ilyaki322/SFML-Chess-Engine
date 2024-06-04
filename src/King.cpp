#include "King.h"

King::King(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side)  , m_moved(false)
{
}

int King::getValue() const
{
	return 0;
}

bool King::isValid(const int squares[], const int target) const
{
	int pos = getPosition();
	int x = squares[target] & m_side;
	if (x > 0)
		if (!(squares[target] - m_side == 5 && !m_moved)) {
			return false;
		}
	if (pos + DOWN == target) return true;
	if (pos + BOT_LEFT == target) return true;
	if (pos + BOT_RIGHT == target) return true;
	if (pos + RIGHT  == target) return true;
	if (pos + LEFT  == target) return true;
	if (pos + TOP_LEFT == target) return true;
	if (pos + TOP_RIGHT == target) return true;
	if (pos + UP == target) return true;
	return false;
}

std::vector<std::pair<int, int>> King::possibleMoves(Board*) const
{
	return std::vector<std::pair<int, int>>();
}
