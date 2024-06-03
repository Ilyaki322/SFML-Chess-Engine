#include "Board.h"
#include "Pieces.h"
#include "FenAlgorithm.h"

#include <iostream> // for debug
#include <map>

Board::Board(std::string FENstring)
	:m_tiles(), m_square()
{
	for (int i = 0; i < 64; i++)
	{
		m_square[i] = 0;
	}

	initTiles();
	FenAlgorithm algo;
	algo.setBoard( m_tiles, m_square, FENstring);

	/*
	for (int i = 0; i < 64; i++)
	{
		std::cout << m_square[i] << " ";
		//if (i % 8 == 0 && i != 0) std::cout << std::endl;
	} 
	*/

	if (m_tiles[3][4]->getPiece()->isValid(m_square, 10))
	{
		m_tiles[2][3]->placePiece(m_tiles[3][4]->getPiece());
		m_tiles[3][4]->placePiece(nullptr);

	}
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
	std::map<int, sf::Color> colors = { {1, sf::Color(161, 111, 92)}, {0, sf::Color(236, 211, 186)}};

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
