#pragma once
#include "Utilities.h"

#include <vector>

//class BoardStack {
//public:
//	BoardStack();
//
//	void insert(std::array<int,SIZE> arr , int whiteKing , int blackKing , int enPassant );
//	void clean();
//	Stack LastMove();
//	std::list<Stack> allMoves();
//
//private:
//
//	std::list<Stack> m_stack;
//};

class BoardStack
{
public:
	BoardStack() = default;

	void insert(Move move, int whiteKing, int blackKing, int enPassant);
	void clear();
	MoveLog lastMove();
	void saveToFile();

private:
	
	std::vector<MoveLog> m_moves;
};