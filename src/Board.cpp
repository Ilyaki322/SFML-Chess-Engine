#include "Board.h"
#include "FenAlgorithm.h"

#include <iostream> // for debug
#include <map>

Board::Board()
	:m_tiles(), m_square()
{
	/*
	for (int i = 0; i < 64; i++)
	{
		std::cout << m_square[i] << " ";
		//if (i % 8 == 0 && i != 0) std::cout << std::endl;
	} 
	*/

}

Board& Board::instance()
{
	static Board ins;
	return ins;
}

Pieces& Board::getPieceAt(const int x)
{
	return *m_tiles[x]->getPiece();
}

const Pieces& Board::getPieceAt(const int x) const
{
	return *m_tiles[x]->getPiece();
}

bool Board::isOccupied(const int x) const
{
	return m_tiles[x]->isOccupied();
}

bool Board::handleFirstClick(sf::Vector2f location)
{
	int y = location.y / 96;
	int x = location.x / 96 + y*8;
	if (m_square[x] == 0) return false;
	if (x != 0)
	{
		std::vector<Move> moves;
		moves = m_tiles[x]->getPiece()->generateMoves(m_square);

		m_tiles[x]->setColor(LAST_TURN_TILE);
		for (const auto& move : moves)
		{
			m_tiles[move.targetSquare]->setColor(MOVEABLE_TILE);
		}
	}
	return true;
}

void Board::handleSecondClick(sf::Vector2f source, sf::Vector2f target)
{
	for (int i = 0; i < 64; i++)
	{
		m_tiles[i]->resetColor();
	}

	int y = target.y / 96;
	int x = target.x / 96;
	int targetX = x+y*8;
	y = source.y / 96;
	x = source.x / 96;
	int sourceX = x+y*8;


	//if (m_square[targetX] < 0 || m_square[targetX] > 63) return;
	if (m_tiles[sourceX]->getPiece()->isValid(m_square, targetX))
	{
		m_tiles[targetX]->placePiece(m_tiles[sourceX]->getPiece());
		m_tiles[sourceX]->placePiece(nullptr);
		m_square[targetX] = m_square[sourceX ];
		m_square[sourceX] = 0;
	}
}

void Board::draw(sf::RenderWindow& window)
{
	for (int x = 0; x < 64; x++)
	{
		m_tiles[x]->draw(window);
	}
}

void Board::setBoard(std::string FENstring)
{
	for (int i = 0; i < 64; i++)
	{
		m_square[i] = 0;
	}
	initTiles();
	FenAlgorithm algo;
	algo.setBoard(m_tiles, m_square, FENstring);
}

void Board::setRotation(const float rotation)
{
	for (int i = 0; i < 64; i++)
	{
		m_tiles[i]->rotatePiece(rotation);
	}
}

void Board::initTiles()
{
	std::map<int, sf::Color> colors = { {1, sf::Color(161, 111, 92)}, {0, sf::Color(236, 211, 186)}};

	for (int y = 0 , i = 0 ; y < 8; y++)
	{
		for (int x = 0 ; x < 8; x++ , i++)
		{
			m_tiles[i] = std::make_unique<Tile>(Tile(colors[(y+x) % 2], 
				sf::Vector2f(float((x * TILE_SIZE) + 48), float((y * TILE_SIZE) + 48))));
		}
	}
}
