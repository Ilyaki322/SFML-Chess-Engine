#pragma once
#include "Utilities.h"
#include <list>

class BoardStack {
public:
	BoardStack();
	void insert(std::array<int,SIZE> arr , int whiteKing , int blackKing , int enPassant );
	Stack LastMove();
	std::list<Stack> allMoves();

private:
	std::list<Stack> m_stack;


};