#include "Board.h"

#include <iostream> // for debug

Board::Board(std::string FENstring)
	: m_board()
{
	//m_board = FEN
}


Piece& Board::getPieceAt(const int x, const int y)
{
	return *m_board[x][y];
}

const Piece& Board::getPieceAt(const int x, const int y) const
{
	return *m_board[x][y];
}