#pragma once
#include "Utilities.h"
#include <array>
#include "BoardStack.h"

class NBoard {
public:
	static NBoard& instance();
	void setBoard(std::array<int,SIZE> arr );
	void move(Move move);
	void undo();
	int m_passant;
	int m_WKing;
	int m_BKing;
	std::array<int,SIZE> m_board ;
private:
	NBoard();
	NBoard(const NBoard&) = default;
	NBoard& operator=(const NBoard&) = default;
	BoardStack m_stack;
};