#pragma once

#include "SFML/Graphics.hpp"

class SFMLPiece
{
public:
	SFMLPiece(sf::Texture& image, sf::Vector2f position);

	void draw(sf::RenderWindow& w)const;
	void setPosition(sf::Vector2f pos);
	void rotate(const float rotation);

private:

	int m_posOnBoard;
	sf::Sprite m_piece;
};