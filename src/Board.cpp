#include "Board.h"
#include "Pieces.h"
#include <iostream> // for debug

Board::Board(std::string FENstring)
	: m_pieces()
{
	//m_board = FEN
}


Pieces& Board::getPieceAt(const int x, const int y)
{
	return *m_pieces[x][y];
}

const Pieces& Board::getPieceAt(const int x, const int y) const
{
	return *m_pieces[x][y];
}

bool Board::isOccupied(const int x, const int y) const
{
	return m_pieces[x][y]!=nullptr;
}
