#include "Board.h"
#include "FenAlgorithm.h"

#include <iostream> // for debug
#include <map>

Board::Board()
	:m_tiles(), m_square() {}

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
	int y = int(location.y / 96);
	int x = int(location.x / 96 + y*8);
	if (m_square[x] == 0) return false;

	m_moves = m_tiles[x]->getPiece()->generateMoves(m_square);
	addSpecialMoves(x);

	m_tiles[x]->setColor(LAST_TURN_TILE);
	for (const auto& move : m_moves)
	{
		m_tiles[move.targetSquare]->setColor(MOVEABLE_TILE);
	}
	
	return true;
}

bool Board::handleSecondClick(sf::Vector2f target, Move& move)
{
	for (int i = 0; i < 64; i++)
	{
		m_tiles[i]->resetColor();
	}

	int y = int(target.y / 96);
	int x = int(target.x / 96);
	int targetX = x+y*8;

	for (const auto& i : m_moves)
	{
		if (i.targetSquare == targetX)
		{
			move = i;
			return true;
		}
	}

	return false;
}

void Board::makeMove(Move move)
{
	if (move.startSquare == -1) return; // AI SKIP TURN


	m_tiles[move.targetSquare]->placePiece(m_tiles[move.startSquare]->getPiece());
	m_tiles[move.startSquare]->placePiece(nullptr);

	m_square[move.targetSquare] = m_square[move.startSquare];
	m_square[move.startSquare] = 0;
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

void Board::addSpecialMoves(int index)
{
	//if (m_tiles[index]->getPiece()->specialMove()) {
	// 
		//enPassant(index);
	//}
	// m_tiles[index]->specialMove();
	// if (m_tiles[index - 1]->getPiece()->getType() == "pawn"){
	//		if(m_tiles[index - 1]->getPiece()->enPassent(){
	//			m_move.push_back();
	//		}
	// }
	// m_tiles[index + ]->getPiece()->getType() == "pawn" ; 

	//if (m_tiles[index]->getPiece()->getType() == "king") {
		//castle(index);
	//}
}

void Board::setRotation(const float rotation)
{
	for (int i = 0; i < 64; i++)
	{
		m_tiles[i]->rotatePiece(rotation);
	}
}

std::vector<std::vector<Move>> Board::AllMoves()
{
	std::vector<std::vector<Move>> allMoves;

	for (int i = 0; i < 64; i++)
	{
		if (m_square[i] != 0)
		{
			allMoves.push_back(m_tiles[i]->getPiece()->generateMoves(m_square));
		}
	}

	return allMoves;
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
