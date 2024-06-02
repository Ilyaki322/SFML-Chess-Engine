#pragma once
#include "Pieces.h"

#include <SFML/Graphics.hpp>

const int TILE_SIZE = 96;
class Tile
{
public:

	Tile(sf::Color defaultColor, sf::Vector2f pos);

	bool isOccupied() const;

	std::shared_ptr<Pieces> getPiece();
	const std::shared_ptr<Pieces> getPiece() const;

	void placePiece(std::shared_ptr<Pieces> pieces);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;

private:

	std::shared_ptr<Pieces> m_piece;
	
	sf::RectangleShape m_tile;
	const sf::Color m_defaultColor;
};