#include "SFMLBoard.h"
#include "Tile.h"
#include "SFMLPieceFactory.h"
#include "NBoard.h"
#include "Assets.h"

#include <map>
#include <SFML/Graphics.hpp>

SFMLBoard::SFMLBoard(const bool useCaptrues)
	: m_BoardRef(NBoard::instance()), m_useCaptures(useCaptrues)
{
	initTiles();
	updateBoard();

	m_capture.setBuffer(Assets::instance().getSound('c'));
	m_move.setBuffer(Assets::instance().getSound('m'));
	m_capture.setVolume(100);
	m_move.setVolume(100);
}


void SFMLBoard::initTiles()
{
	std::map<int, sf::Color> colors = { {1, sf::Color(161, 111, 92)}, {0, sf::Color(236, 211, 186)} };

	for (int y = 0, i = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++, i++)
		{
			m_tiles[i] = std::make_unique<Tile>(Tile(colors[(y + x) % 2],
				sf::Vector2f(float((x * TILE_SIZE) + 200), float((y * TILE_SIZE) + 48))));
		}
	}
}

void SFMLBoard::playBoardSound(const Move& move)
{
	if (m_BoardRef.didCapture())// || 
		//((m_BoardRef.getPiece(move.targetSquare) & 0b111) == PawnVal && move.specialStartSquare != -1))
	{
		m_capture.play();
	}
	else if (move.startSquare != -1)
	{
		m_move.play();
	}
}

void SFMLBoard::updateCaptured(const Move& move)
{
	SFMLPieceFactory factory;
	int piece = m_BoardRef.didCapture();
	if (piece)
	{
		float x, y;
		Color color = Color(piece & 0b11000);
		if (color == White)
		{
			
			x = 10 + (m_capturedWhitePieces.size() % 8) * 20;
			y = (m_capturedWhitePieces.size() >= 8) ? 540 : 500;
			m_capturedWhitePieces.push_back(factory.create(piece,
				sf::Vector2f(x, y), sf::Vector2f(40, 40)));
				//sf::Vector2f(1000 + m_capturedWhitePieces.size() * 30, 600), sf::Vector2f(50, 50)));
		}
		else
		{
			x = 10 + (m_capturedBlackPieces.size() % 8) * 20;
			y = (m_capturedBlackPieces.size() >= 8) ? 250 : 210;
			m_capturedBlackPieces.push_back(factory.create(piece,
				sf::Vector2f(x, y), sf::Vector2f(40, 40)));
				//sf::Vector2f(1000 + m_capturedBlackPieces.size() * 30, 200), sf::Vector2f(50, 50)));
		}
	}
}

void SFMLBoard::updateBoard(bool fake)
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

	if (fake && !m_useCaptures) return;

	Move move = m_BoardRef.getLastMove();
	resetTileColors();
	if (move.startSquare != -1 ) {	
		colorTiles(move.startSquare, sf::Color(255, 127, 80));
		colorTiles(move.targetSquare, sf::Color(255, 127, 80));

		playBoardSound(move);
		if (m_useCaptures) updateCaptured(move);
	}
}

std::vector<piecePtr>& SFMLBoard::getCaptured(Color color) 
{
	return (color == White) ? m_capturedWhitePieces : m_capturedBlackPieces;
}

void SFMLBoard::draw(sf::RenderWindow& window)
{
	for (int x = 0; x < SIZE; x++)
	{
		m_tiles[x]->draw(window);
	}

	//for (const auto& i : m_capturedBlackPieces)
	//{
	//	i->draw(window);
	//}

	//for (const auto& i : m_capturedWhitePieces)
	//{
	//	i->draw(window);
	//}
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

void SFMLBoard::reset()
{
	m_capturedBlackPieces.clear();
	m_capturedWhitePieces.clear();
	resetTileColors();
	updateBoard();
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
