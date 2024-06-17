#include "BoardStack.h"

BoardStack::BoardStack()
{
}

void BoardStack::insert(std::array<int, SIZE> arr)
{
	m_boardStack.push_back(arr);
}

void BoardStack::insert(Move move, int whiteKing, int blackKing, int enPassant, int tValue, int sValue, int specialtVal, int specialSval)
{
	Stack s;
	s.move = move;
	s.lastBKing = blackKing;
	s.lastWKing = whiteKing;
	s.enPassant = enPassant;
	s.startValue = sValue;
	s.targetValue = tValue;
	s.specialStartVal = specialSval;
	s.specialTargetVal = specialtVal;

	m_movesStack.push_back(s);
}

Stack BoardStack::LastMove()
{
	auto back = m_movesStack.back();
	m_movesStack.pop_back();
	return back;
}

std::list<std::array<int, SIZE>> BoardStack::allMoves()
{
	return m_boardStack ;
}
