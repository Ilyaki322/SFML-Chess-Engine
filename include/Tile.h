#pragma once

#include "SFMLPiece.h"
#include "SFML/Graphics.hpp"
#include "Utilities.h"

class Tile
{
public:

	Tile(sf::Color defaultColor, sf::Vector2f pos);

	bool isOccupied() const;

	void placePiece(std::unique_ptr<SFMLPiece> piece);
	void setColor(const sf::Color& color);
	void resetColor();
	void draw(sf::RenderWindow& window);
	void rotatePiece(const float rotation);

	sf::Vector2f getPosition() const;

private:

	std::unique_ptr<SFMLPiece> m_piece;
	
	sf::RectangleShape m_tile;
	const sf::Color m_defaultColor;
};