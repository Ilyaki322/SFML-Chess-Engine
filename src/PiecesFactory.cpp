#include "PiecesFactory.h"
#include "Assets.h"
PiecesFactory::PiecesFactory()
{
}

std::shared_ptr<Pieces> PiecesFactory::create(char c, sf::Vector2f position, Color color)
{
	//return std::shared_ptr<Pieces>();
	switch (c)
	{
	case('p'):
		return std::make_shared<Pawn>(Assets::instance().getTexture(c), position, color);
	}
	return nullptr;
}