#pragma once

#include "SFMLPiece.h"
#include "SFML/Graphics.hpp"
#include "Utilities.h"

/*
* This class represents a tile on the chessboard.
* It lights up squares in a certain color according to the user's movement or click
*/
class Tile
{
public:

	Tile(sf::Color defaultColor, sf::Vector2f pos);

	bool isOccupied() const;

	void placePiece(std::unique_ptr<SFMLPiece> piece);
	std::unique_ptr<SFMLPiece> getPiece();
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