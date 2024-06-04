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

bool Board::handleFirstClick(sf::Vector2f location)
{
	int x = location.x / 96;
	int y = location.y / 96;
	return m_square[x + y * 8] != 0;
}

void Board::handleSecondClick(sf::Vector2f source, sf::Vector2f target)
{
	int targetX = target.x / 96;
	int targetY = target.y / 96;
	int sourceX = source.x / 96;
	int sourceY = source.y / 96;
	if (m_square[targetX + targetY * 8] < 0 || m_square[targetX + targetY * 8] > 63) return;
	if (m_tiles[sourceY][sourceX]->getPiece()->isValid(m_square, targetX + targetY * 8))
	{
		m_tiles[targetY][targetX]->placePiece(m_tiles[sourceY][sourceX]->getPiece());
		m_tiles[sourceY][sourceX]->placePiece(nullptr);
		m_square[targetX + targetY * 8] = m_square[sourceX + sourceY * 8];
		m_square[sourceX + sourceY * 8] = 0;
	}
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
