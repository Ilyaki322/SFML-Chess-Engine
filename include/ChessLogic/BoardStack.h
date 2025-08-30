#pragma once
#include "Utilities.h"
#include <vector>

class NBoard;
/*
* This class saves each move played.
* and saves all the game to a file.
*/
class BoardStack
{
public:
	BoardStack() = default;
    BoardStack(const BoardStack& other) : m_moves(other.m_moves), m_name(other.m_name) {}
    BoardStack& operator=(const BoardStack& other) {
        if (this != &other) {
            m_moves = other.m_moves;
            m_name = other.m_name;
        }
        return *this;
    }

	void insert(NBoard& board, Move move, int whiteKing, int blackKing, int enPassant);
	void clear(std::string name);
	MoveLog lastMove();
	void saveToFile();

private:
	
	std::vector<MoveLog> m_moves;
	std::string m_name;
};