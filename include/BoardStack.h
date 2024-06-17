#pragma once
#include "Utilities.h"
#include <list>

class BoardStack {
public:
	BoardStack();
	void insert(std::array<int,SIZE> arr);
	void insert(Move move, int whiteKing, int blackKing, int enPassant,int tValue, int sValue, int specialtVal , int specialSval);
	Stack LastMove();
	std::list<std::array<int, SIZE>> allMoves();

private:
	std::list<std::array<int, SIZE>> m_boardStack;
	std::vector <Stack> m_movesStack;
};