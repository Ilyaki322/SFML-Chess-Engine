#include "Pieces.h"
#include "Board.h"


Pieces::Pieces(sf::Texture image, sf::Vector2f position , Color side, int val )
	: m_side(side), m_value(val)
{
	m_piece.setPosition(position);
	m_piece.setTexture(image);
}

int Pieces::getValue() const
{
	return m_value;
}

void Pieces::draw(sf::RenderWindow& w) const
{
	w.draw(m_piece);
}

//std::vector<std::pair<int, int>> Pieces::possibleMoves(Board board*) const
//{
//	std::vector<std::pair<int, int>> v;
//	for (int i = 0; i < 8; i++) {
//		for (int j = 0; j < 8; j++) {
//			if (board.isOccupied(i, j)) {
//				v.push_back({ i, j });
//			}
//		}
//	}
//}
