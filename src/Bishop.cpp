#include "Bishop.h"
#include "Bishop.h"

#include <iostream> // debug

Bishop::Bishop(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side)
{
}

int Bishop::getValue() const
{
	return 0;
}


bool Bishop::isValid(const int squares[], const int target) const
{
	int pos = getPosition();

	int x = squares[target] & m_side;
	if (x > 0) return false;

	if (target > pos)
	{
		for (int i = pos + BOT_LEFT; i < 64; i += BOT_LEFT)
		{
			if (target == i) return true;
			if (squares[i] != 0) break;
		}
		for (int i = pos + BOT_RIGHT; i < 64; i += BOT_RIGHT)
		{
			if (target == i) return true;
			if (squares[i] != 0) break;
		}
	}
	else
	{
		for (int i = pos + TOP_LEFT; i > 0; i += TOP_LEFT)
		{
			if (target == i) return true;
			if (squares[i] != 0) break;
		}
		for (int i = pos + TOP_RIGHT; i > 0; i += TOP_RIGHT)
		{
			if (target == i) return true;
			if (squares[i] != 0) break;
		}
	}

	return false;
}

std::vector<std::pair<int, int>> Bishop::possibleMoves(Board*) const
{
	return std::vector<std::pair<int, int>>();
}

std::vector<Move> Bishop::generateMoves(const int squares[]) const
{
	std::vector<Move> moves;
	slidingMoves(squares, BOT_LEFT, moves);
	slidingMoves(squares, BOT_RIGHT, moves);
	slidingMoves(squares, TOP_LEFT, moves);
	slidingMoves(squares, TOP_RIGHT, moves);

	return moves;
}
