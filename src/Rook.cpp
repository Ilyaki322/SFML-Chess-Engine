#include "Rook.h"

Rook::Rook(sf::Texture& image, sf::Vector2f position, Color side)
    :Pieces(image, position, side), m_moved(false)
{
}

int Rook::getValue() const
{
    return 5;
}

bool Rook::isValid(const int squares[], const int target) const
{
    int pos = getPosition();

    int x = squares[target] & m_side;
    if (x > 0 )
        if(!(squares[target]-m_side == 1 && !m_moved)){
            return false;
        }
	int up = pos+UP ,down = pos+DOWN,left=pos+LEFT, right = pos+RIGHT;
	while (target >= down || target >= right || target <= up || target <= left){
		if (down < 64) {
			if (target == down) return true;
			if (squares[down] != 0) down = target + 1;
		}
		if (right < 64) {
			if (target == right) return true;
			if (squares[right] != 0) right = target + 1;
		}
		if (up > -1) {
			if (target == up) return true;
			if (squares[up] != 0) up = target - 1;
		}
		if (left > -1) {
			if (target == left) return true;
			if (squares[left] != 0) left = target - 1;
		}

		up += UP;
		left += LEFT;
		down += DOWN;
		right += RIGHT;
	}
	return false;
}

std::vector<std::pair<int, int>> Rook::possibleMoves(Board*) const
{
    return std::vector<std::pair<int, int>>();
}
