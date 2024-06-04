#pragma once
#include "Pieces.h"

#include <SFML/Graphics.hpp>

const sf::Color MOVEABLE_TILE = sf::Color::Green;
const sf::Color ERROR_TILE = sf::Color::Red;
const sf::Color LAST_TURN_TILE = sf::Color(255,165,0);

const int TILE_SIZE = 96;
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