#include "SFMLBoard.h"
#include "Tile.h"
#include "SFMLPieceFactory.h"

#include <map>
#include <SFML/Graphics.hpp>

SFMLBoard::SFMLBoard()
{
	int hui[64] = { 0,0,0,0,0,0,0,0,
				   0,18,17,18,19,18,20,0,
				   0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,
				   0,10,9,10,11,10,0,0,
				   0,0,0,0,0,0,0,0, };
	initTiles();
	initBoard(hui);
}


void SFMLBoard::initTiles()
{
	std::map<int, sf::Color> colors = { {1, sf::Color(161, 111, 92)}, {0, sf::Color(236, 211, 186)} };

	for (int y = 0, i = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++, i++)
		{
			m_tiles[i] = std::make_unique<Tile>(Tile(colors[(y + x) % 2],
				sf::Vector2f(float((x * TILE_SIZE) + 48), float((y * TILE_SIZE) + 48))));
		}
	}
}

void SFMLBoard::initBoard(const int const board[64])
{
	SFMLPieceFactory factory;

	for (int i = 0; i < 64; i++)
	{
		if (board[i] != 0)
		{
			m_tiles[i]->placePiece(factory.create(board[i], m_tiles[i]->getPosition()));
		}
	}
}

void SFMLBoard::draw(sf::RenderWindow& window)
{
	for (int x = 0; x < SIZE; x++)
	{
		m_tiles[x]->draw(window);
	}
}
