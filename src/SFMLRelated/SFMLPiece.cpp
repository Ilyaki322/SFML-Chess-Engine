#include "SFMLRelated/SFMLPiece.h"

SFMLPiece::SFMLPiece(sf::Texture& image, sf::Vector2f position, sf::Vector2f size)
{
	m_piece.setPosition(position);
	m_piece.setOrigin(image.getSize().x / 2.f, image.getSize().y / 2.f);
	m_piece.setTexture(image);
	m_piece.setScale(size.x / image.getSize().x, size.y / image.getSize().y);
}

void SFMLPiece::draw(sf::RenderWindow& w) const
{
	w.draw(m_piece);
}

void SFMLPiece::setPosition(sf::Vector2f pos)
{
	m_piece.setPosition(pos);
}

void SFMLPiece::rotate(const float rotation)
{
	m_piece.setRotation(rotation);
}
