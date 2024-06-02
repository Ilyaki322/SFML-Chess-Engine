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

int Pieces::getPosition() const
{
	int x = m_piece.getPosition().x / 96;
	int y = m_piece.getPosition().y / 96;
	std::cout << x << " " << y << std::endl;
	return x + y * 8;
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
