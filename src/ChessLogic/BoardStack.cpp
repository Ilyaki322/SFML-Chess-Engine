#include "ChessLogic/BoardStack.h"
#include "ChessLogic/NBoard.h"

#include <fstream>
#include <string>
#include <ctime>

/*
* inserts a struct of all the pieces and tiles tied to the move played.
*/
void BoardStack::insert(NBoard& board, Move move, int whiteKing, int blackKing, int enPassant)
{
	MoveLog log;
	log.enPassant = enPassant;
	log.lastBKing = blackKing;
	log.lastWKing = whiteKing;
	log.lastMove = move;

	log.targetPiece = board.getPiece(move.targetSquare);
	log.startPiece = board.getPiece(move.startSquare);

	if (move.specialStartSquare != -1)
	{
		log.specialTargetPiece = board.getPiece(move.specialTargetSquare);
		log.specialStartPiece = board.getPiece(move.specialStartSquare);
	}
	
	m_moves.emplace_back(log);
}

void BoardStack::clear(std::string name)
{
	if(name.size() > 1) m_name = name;
	m_moves.clear();
}

MoveLog BoardStack::lastMove()
{
	MoveLog back = m_moves.back();
	m_moves.pop_back();
	return back;
}

void BoardStack::saveToFile()
{
	std::ofstream History("GameHistory.txt", std::ios::app);

	std::time_t currentTime = std::time(0);
	char buffer[26];
	ctime_s(buffer, sizeof(buffer), &currentTime);

	std::string timeString(buffer);
	History << m_name << " " << timeString;

	for (const auto& i : m_moves)
	{
		History << i.lastMove.promotionVal << " " << i.lastMove.specialStartSquare << " ";
		History << i.lastMove.specialTargetSquare << " " << i.lastMove.startSquare << " " << i.lastMove.targetSquare << " ";
	}

	History << std::endl;
	History.close();
}
