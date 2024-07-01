#pragma once

#include "SFMLPiece.h"
#include <map>

/*This class create a chess piece in SFML*/

class SFMLPieceFactory
{
public:
	SFMLPieceFactory();

	std::unique_ptr<SFMLPiece> create(const int val, const sf::Vector2f& pos);
	std::unique_ptr<SFMLPiece> create(const int val, const sf::Vector2f& pos, const sf::Vector2f& size);

private:
	std::map<int, char> m_piecesMap;
};