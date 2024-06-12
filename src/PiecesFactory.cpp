#include "PiecesFactory.h"
#include "Assets.h"
PiecesFactory::PiecesFactory()
{
}

std::shared_ptr<Pieces> PiecesFactory::create(char c, sf::Vector2f position, Color color)
{
	char piece = char(tolower(c));
	switch (piece)
	{
	case('p'):
		return std::make_shared<Pawn>(Assets::instance().getTexture(c), position, color , c);
	case('r'):
		return std::make_shared<Rook>(Assets::instance().getTexture(c), position, color, c);
	case('k'):
		return std::make_shared<King>(Assets::instance().getTexture(c), position, color,c);
	case('q'):
		return std::make_shared<Queen>(Assets::instance().getTexture(c), position, color,c);
	case('b'):
		return std::make_shared<Bishop>(Assets::instance().getTexture(c), position, color,c);
	case('n'):
		return std::make_shared<Knight>(Assets::instance().getTexture(c), position, color,c);
	}

	return nullptr;
}