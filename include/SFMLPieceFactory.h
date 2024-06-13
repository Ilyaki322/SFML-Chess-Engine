#pragma once

#include "SFMLPiece.h"
#include <map>

class SFMLPieceFactory
{
public:
	SFMLPieceFactory();

	std::unique_ptr<SFMLPiece> create(const int val, const sf::Vector2f& pos);

private:
	std::map<int, char> m_piecesMap;
};