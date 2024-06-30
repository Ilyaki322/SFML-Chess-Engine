#pragma once
#include "Utilities.h"
#include <vector>

/*
* This class saves each move played.
* has the ability to give the last move,
* and save all the game to a file.
*/
class BoardStack
{
public:
	BoardStack() = default;

	void insert(Move move, int whiteKing, int blackKing, int enPassant);
	void clear(std::string name);
	MoveLog lastMove();
	void saveToFile();

private:
	
	std::vector<MoveLog> m_moves;
	std::string m_name;
};