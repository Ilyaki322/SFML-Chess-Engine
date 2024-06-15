#include "BoardStack.h"

BoardStack::BoardStack()
{
}

void BoardStack::insert(std::array<int, SIZE> arr, int whiteKing, int blackKing, int enPassant)
{
	Stack s;
	s.backUpm_board = arr;
	s.lastBKing = blackKing;
	s.lastWKing = whiteKing;
	s.enPassant = enPassant;

	m_stack.push_back(s);
}

Stack BoardStack::LastMove()
{
	auto back = m_stack.back();
	m_stack.pop_back();
	return back;
}

std::list<Stack> BoardStack::allMoves()
{
	return m_stack ;
}
