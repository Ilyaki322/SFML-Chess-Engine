#pragma once

#include "SFML/Graphics.hpp"

class SFMLPiece
{
public:
	SFMLPiece(sf::Texture& image, sf::Vector2f position, sf::Vector2f size = sf::Vector2f(96.f, 96.f));

	void draw(sf::RenderWindow& w)const;
	void setPosition(sf::Vector2f pos);
	void rotate(const float rotation);

private:

	sf::Sprite m_piece;
};