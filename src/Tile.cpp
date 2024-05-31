#include "Tile.h"

Tile::Tile(sf::Color defaultColor, sf::Vector2f pos)
	: m_defaultColor(defaultColor), m_piece(nullptr), m_tile(sf::Vector2f(TILE_SIZE, TILE_SIZE))
{
	m_tile.setPosition(pos);
	m_tile.setFillColor(defaultColor);
	m_tile.setOutlineColor(sf::Color::Black);
	m_tile.setOutlineThickness(1.f);
}

bool Tile::isOccupied() const
{
	return (m_piece == nullptr) ? false : true;
}

Pieces* Tile::getPiece()
{
	return m_piece.get();
}

const Pieces* Tile::getPiece() const
{
	return m_piece.get();
}

void Tile::placePiece(std::shared_ptr<Pieces> pieces)
{
	m_piece = pieces;
}

void Tile::draw(sf::RenderWindow& window)
{
	window.draw(m_tile);
	if (m_piece != nullptr)
	{
		m_piece->draw(window);
	}
}

sf::Vector2f Tile::getPosition() const
{
	return m_tile.getPosition();
}
