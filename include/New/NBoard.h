#pragma once
#include "Utilities.h"

class NBoard {
public:
	NBoard();
	void setBoard();
	void move(Move move);
	void undo();
	int m_passant;
	int m_Wking;
	int m_Bking;

private:
	int m_board[SIZE];
};