#pragma once
#include "Pieces.h"

#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Tile
{
public:
	Tile(sf::Color defaultColor, sf::Vector2f pos);
	bool isOccupied() const;

	std::shared_ptr<Pieces> getPiece();
	const std::shared_ptr<Pieces> getPiece() const;

	void placePiece(std::shared_ptr<Pieces> pieces);
	void setColor(const sf::Color& color);
	void resetColor();
	void draw(sf::RenderWindow& window);
	void rotatePiece(const float rotation);

	sf::Vector2f getPosition() const;

private:

	std::shared_ptr<Pieces> m_piece;
	
	sf::RectangleShape m_tile;
	const sf::Color m_defaultColor;
};