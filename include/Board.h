#pragma once

#include <string>

class Piece;
class Board
{
public:

	Board(std::string FENstring);

	Piece& getPieceAt(const int x, const int y);
	const Piece& getPieceAt(const int x, const int y) const;

//====================================================

private:

	Piece* m_board[8][8];
};