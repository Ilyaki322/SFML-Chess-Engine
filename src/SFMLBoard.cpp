#include "SFMLBoard.h"
#include "Tile.h"
#include "SFMLPieceFactory.h"
#include "NBoard.h"

#include <map>
#include <SFML/Graphics.hpp>

SFMLBoard::SFMLBoard()
	: m_BoardRef(NBoard::instance())
{
	initTiles();
	updateBoard();
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

void SFMLBoard::updateBoard()
{
	SFMLPieceFactory factory;
	std::array<int, 64> &board = m_BoardRef.getBoard();

	for (int i = 0; i < 64; i++)
	{
		if (board[i] != 0)
		{
			m_tiles[i]->placePiece(factory.create(board[i], m_tiles[i]->getPosition()));
		}
		else
		{
			m_tiles[i]->placePiece(nullptr);
		}
	}
	Move move = NBoard::instance().getLastMove();

	resetTileColors();
	if (move.startSquare != -1 ) {
		colorTiles(move.startSquare, sf::Color::Red);
		colorTiles(move.targetSquare, sf::Color::Red);
	}
}

void SFMLBoard::draw(sf::RenderWindow& window)
{
	for (int x = 0; x < SIZE; x++)
	{
		m_tiles[x]->draw(window);
	}
}

bool SFMLBoard::clickedOnCorrectPiece(const int x, Color color)
{
	if (x < 0 || x > 64) return false;
	
	Color c = ((m_BoardRef.getPiece(x) & 0b10000) > 0) ? Black : White;
	if (m_tiles[x]->isOccupied() && c == color)
	{
		return true;
	}

	return false;
}

void SFMLBoard::colorTiles(int tile, const sf::Color& color)
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

//void SFMLBoard::makeMove(Move move)
//{
//	m_BoardRef.move(move);
//
//	m_tiles[move.targetSquare]->placePiece(m_tiles[move.startSquare]->getPiece());
//	m_tiles[move.startSquare]->placePiece(nullptr);
//
//	if (move.specialStartSquare == -1)
//	{
//		return;
//	}
//
//	m_tiles[move.specialTargetSquare]->placePiece(m_tiles[move.specialStartSquare]->getPiece());
//	m_tiles[move.specialStartSquare]->placePiece(nullptr);
//	
//}
