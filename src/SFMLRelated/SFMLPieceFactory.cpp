#include "SFMLRelated/SFMLPieceFactory.h"
#include "Utilities.h"
#include "Assets.h"

SFMLPieceFactory::SFMLPieceFactory()
{
	m_piecesMap[KingVal] = 'k';
	m_piecesMap[PawnVal] = 'p';
	m_piecesMap[KnightVal] = 'n';
	m_piecesMap[BishopVal] = 'b';
	m_piecesMap[RookVal] = 'r';
	m_piecesMap[QueenVal] = 'q';
}

std::unique_ptr<SFMLPiece> SFMLPieceFactory::create(const int val, const sf::Vector2f& pos)
{
	bool black = ((0b10000 & val) > 0);
	char c = m_piecesMap[(0b111 & val)];
	
	if (black)
	{
		c = char(toupper(c));
	}

	return std::make_unique<SFMLPiece>(Assets::instance().getTexture(c), pos);
}

/*
* an overloading incase we want a piece of different size than the default one
*/
std::unique_ptr<SFMLPiece> SFMLPieceFactory::create(const int val, const sf::Vector2f& pos, const sf::Vector2f& size)
{
	bool black = ((0b10000 & val) > 0);
	char c = m_piecesMap[(0b111 & val)];

	if (black)
	{
		c = char(toupper(c));
	}

	return std::make_unique<SFMLPiece>(Assets::instance().getTexture(c), pos, size);
}
