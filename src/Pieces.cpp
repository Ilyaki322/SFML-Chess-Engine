#include "Pieces.h"
#include "Board.h"
#include <iostream>

Pieces::Pieces(sf::Texture& image, sf::Vector2f position, Color side)
	: m_side(side), m_value(0)
{
	m_piece.setPosition(position);
	m_piece.setTexture(image);
	m_piece.setScale(96.f / image.getSize().x, 96.f / image.getSize().y);

}

int Pieces::getValue() const
{
	return m_value;
}

void Pieces::draw(sf::RenderWindow& w) const
{
	w.draw(m_piece);
}

void Pieces::setPosition(sf::Vector2f pos)
{
	m_piece.setPosition(pos);
}

/*
* gets the board, a direction in which to slide and vector to add moves to.
* goes in the given direction until hits a piece / 'wall'.
*/
void Pieces::slidingMoves(const int squares[], const int direction, std::vector<Move> &moves) const
{
	int pos = getPosition();

	bool run = true;
	for (int i = pos + direction; run && ( i < 64 && i > -1); i += direction)
	{
		// 'wall' does not mean we out of bounds
		// for example square 16 is a wall, but 16 - 9 still > 0
		// so we check i MOD 8, if its 0 or 7 it means we on the last tile.
		if ((i % 8) == 0 || (i % 8) == 7) run = false;
		if (!Board::instance().isOccupied(i))
		{
			moves.push_back({ pos, i });
			continue;
		}
		if (Board::instance().getPieceAt(i).getColor() == getColor()) return;

		moves.push_back({ pos, i });
		return;
	}
}

int Pieces::getPosition() const
{
	int x = m_piece.getPosition().x / 96;
	int y = m_piece.getPosition().y / 96;
	//std::cout << x << " " << y << std::endl;
	return x + y * 8;
}

Color Pieces::getColor() const
{
	return m_side;
}
