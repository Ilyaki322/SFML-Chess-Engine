#include "Board.h"
#include "FenAlgorithm.h"
#include "SpecialMove.h"
#include "PiecesFactory.h"
#include <iostream> // for debug
#include <map>
#include "Queen.h" // for promotion ?

Board::Board()
	:m_tiles() {}

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

bool Board::handleFirstClick(sf::Vector2f location, Color color)
{
	int y = int(location.y / 96);
	int x = int(location.x / 96 + y*8);

	if (!m_tiles[x]->isOccupied()) return false;
	if (m_tiles[x]->getPiece()->getColor() != color) return false;

	m_moves = m_tiles[x]->getPiece()->generateMoves();
	
	for (auto i = m_moves.begin(); i != m_moves.end();)
	{
		/*if ((*i).targetSquare < 0)
		{
			i++;
			continue;
		}*/
		if (SpecialMove::instance().MoveType(*i) != Regular)
		{
			i++;
			continue;
		}

		fakeMove(*i);
		if (!SpecialMove::instance().fakeMove(*i, AllMoves()))
		{
			undoMove(*i);
			i = m_moves.erase(i);
			std::cout << "ERASED A MOVE\n";
		}
		else
		{
			undoMove(*i);
			i++;
		}	
	}

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

	m_temp = m_tiles[move.targetSquare]->getPiece();

	EndMove end = SpecialMove::instance().MoveType(move);
	std::cout << end << '\n';

	switch (end)
	{

	case EnPassant:
	{
		int side = m_tiles[move.startSquare]->getPiece()->getColor() == White ? 8 : -8;
		m_temp = m_tiles[move.targetSquare + side]->getPiece();
		m_tiles[move.targetSquare]->placePiece(m_tiles[move.startSquare]->getPiece());
		m_tiles[move.startSquare]->placePiece(nullptr);
		m_tiles[move.targetSquare + side]->placePiece(nullptr);

		SpecialMove::instance().enPassantMove(move, AllMoves());
		break;
	}

	case Castle:
	{
		castle(move);
		break;
	}

	case Promotion:
		promotion(move);
		break;

	case Regular:
	{
		std::cout << "start =  " << move.startSquare << " target = " << move.targetSquare << '\n';
		m_tiles[move.targetSquare]->placePiece(m_tiles[move.startSquare]->getPiece());
		m_tiles[move.startSquare]->placePiece(nullptr);
		SpecialMove::instance().doMove(move, AllMoves());
		break;
	}
	}
}

void Board::undoMove(Move move)
{
	m_tiles[move.startSquare]->placePiece(m_tiles[move.targetSquare]->getPiece());
	m_tiles[move.targetSquare]->placePiece(m_temp);
}

void Board::draw(sf::RenderWindow& window)
{
	for (int x = 0; x < 64; x++)
	{
		m_tiles[x]->draw(window);
		debugTiles[x]->draw(window);
	}
}

void Board::setBoard(std::string FENstring)
{
	std::array<int, SIZE> square = { 0 };

	initTiles();
	FenAlgorithm algo;
	algo.setBoard(m_tiles, square, FENstring);
	SpecialMove::instance().setBoard(square);
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
		if (m_tiles[i]->isOccupied())
		{
			allMoves.push_back(m_tiles[i]->getPiece()->generateMoves());
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

			debugTiles[i] = std::make_unique<Tile>(Tile(colors[(y + x) % 2],
				sf::Vector2f(float(768 + (x * TILE_SIZE) + 48), float((y * TILE_SIZE) + 48))));
			debugTiles[i]->setColor(sf::Color::Blue);
		}
	}

}

void Board::castle(Move move)
{
	auto king = m_tiles[move.startSquare]->getPiece();
	auto rook = m_tiles[move.targetSquare]->getPiece();
	
	if (move.startSquare < move.targetSquare)
	{
		m_tiles[move.targetSquare - 2]->placePiece(rook);
		m_tiles[move.startSquare + 2]->placePiece(king);
	}

	else
	{
		m_tiles[move.targetSquare + 3]->placePiece(rook);
		m_tiles[move.startSquare - 2]->placePiece(king);
	}

	m_tiles[move.startSquare]->placePiece(nullptr);
	m_tiles[move.targetSquare]->placePiece(nullptr);

	SpecialMove::instance().castle(move, AllMoves());
	return;
}

void Board::promotion(Move move)
{
	char piece;
	(m_tiles[move.startSquare]->getPiece()->getColor() == White) ? piece = 'q' : piece = 'Q';

	PiecesFactory factory;
	std::shared_ptr<Pieces> promotedPiece = factory.create(piece, m_tiles[move.targetSquare]->getPosition(), m_tiles[move.startSquare]->getPiece()->getColor());

	m_tiles[move.startSquare]->placePiece(nullptr);
	m_tiles[move.targetSquare]->placePiece(promotedPiece);

	SpecialMove::instance().promotionMove(move, AllMoves(), QueenVal);
}

void Board::fakeMove(Move move)
{
	auto type = SpecialMove::instance().MoveType(move);
	if (type != Regular) return;

	m_temp = m_tiles[move.targetSquare]->getPiece();

	m_tiles[move.targetSquare]->placePiece(m_tiles[move.startSquare]->getPiece());
	m_tiles[move.startSquare]->placePiece(nullptr);
	return;
}



