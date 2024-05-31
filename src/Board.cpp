#include "Board.h"
#include "Pieces.h"
#include "FenAlgorithm.h"

#include <iostream> // for debug
#include <map>

Board::Board(std::string FENstring)
	:m_tiles()
{
	initTiles();
	FenAlgorithm algo;
	algo.setBoard( m_tiles, FENstring);
}

Pieces& Board::getPieceAt(const int x, const int y)
{
	return *m_tiles[x][y]->getPiece();
}

const Pieces& Board::getPieceAt(const int x, const int y) const
{
	return *m_tiles[x][y]->getPiece();
}

bool Board::isOccupied(const int x, const int y) const
{
	return m_tiles[x][y]->isOccupied();
}

void Board::draw(sf::RenderWindow& window)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			m_tiles[x][y]->draw(window);
		}
	}
}

void Board::initTiles()
{
	std::map<int, sf::Color> colors = { {0, sf::Color(161, 111, 92)}, {1, sf::Color(236, 211, 186)}};

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			m_tiles[y][x] = std::make_unique<Tile>(Tile(colors[(y+x) % 2],
				                                   sf::Vector2f(float(x * TILE_SIZE),
					                               float(y * TILE_SIZE))));
		}
	}
}
