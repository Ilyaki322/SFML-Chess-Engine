#include "Tile.h"

#include <iostream> // DEBUGING

Tile::Tile(sf::Color defaultColor, sf::Vector2f pos)
	: m_defaultColor(defaultColor), m_piece(nullptr), m_tile(sf::Vector2f(TILE_SIZE, TILE_SIZE))
{
	m_tile.setPosition(pos);
	m_tile.setFillColor(defaultColor);
	m_tile.setOutlineColor(sf::Color::Black);
	m_tile.setOutlineThickness(1.f);
	m_tile.setOrigin(m_tile.getSize().x / 2.f, m_tile.getSize().y / 2.f);
}

bool Tile::isOccupied() const
{
	return (m_piece == nullptr) ? false : true;
}

std::shared_ptr<Pieces> Tile::getPiece()
{
	return m_piece;
}

const std::shared_ptr<Pieces> Tile::getPiece() const
{
	return m_piece;
}

void Tile::placePiece(std::shared_ptr<Pieces> pieces)
{
	m_piece = pieces;
	if(m_piece)
		m_piece->setPosition(getPosition());
}

void Tile::setColor(const sf::Color& color)
{
	m_tile.setFillColor(color);
}

void Tile::resetColor()
{
	m_tile.setFillColor(m_defaultColor);
}

void Tile::draw(sf::RenderWindow& window)
{
	window.draw(m_tile);
	if (m_piece != nullptr)
	{
		m_piece->draw(window);
	}
}

void Tile::rotatePiece(const float rotation)
{
	if (m_piece != nullptr)
	{
		m_piece->rotate(rotation);
	}
}

sf::Vector2f Tile::getPosition() const
{
	return m_tile.getPosition();
}
