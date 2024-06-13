#include "SFMLBoard.h"
#include "Tile.h"
#include "SFMLPieceFactory.h"

#include <map>
#include <SFML/Graphics.hpp>

SFMLBoard::SFMLBoard()
{
	
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

bool SFMLBoard::clickedOnCorrectPiece(sf::Vector2f pos, Color color)
{
	int y = int(pos.y / TILE_SIZE);
	int x = int(pos.x / TILE_SIZE + y * DOWN);

	if (x < 0 || x > 60) return false;
	
	Color c = ((hui[x] & 0b10000) > 0) ? Black : White;
	if (m_tiles[x]->isOccupied() && c == color)
	{
		return true;
	}

	return false;
}

void SFMLBoard::colorTiles(int tile, sf::Color& color)
{
	m_tiles[tile]->setColor(color);
}

void SFMLBoard::resetTileColors()
{
	for (auto& i : m_tiles)
	{
		i->resetColor();
	}
}
