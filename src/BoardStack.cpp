#include "BoardStack.h"
#include "NBoard.h"

#include <fstream>
#include <string>
#include <ctime>

//void BoardStack::insert(std::array<int, SIZE> arr, int whiteKing, int blackKing, int enPassant)
//{
//	Stack s = { 0 };
//	s.backUpm_board = arr;
//	s.lastBKing = blackKing;
//	s.lastWKing = whiteKing;
//	s.enPassant = enPassant;
//
//	m_stack.push_back(s);
//}
//
//void BoardStack::clean()
//{
//	m_stack.clear();
//}
//
//Stack BoardStack::LastMove()
//{
//	auto back = m_stack.back();
//	m_stack.pop_back();
//	return back;
//}
//
//std::list<Stack> BoardStack::allMoves()
//{
//	return m_stack ;
//}

void BoardStack::insert(Move move, int whiteKing, int blackKing, int enPassant)
{
	MoveLog log;
	log.enPassant = enPassant;
	log.lastBKing = blackKing;
	log.lastWKing = whiteKing;
	log.lastMove = move;

	log.targetPiece = NBoard::instance().getPiece(move.targetSquare);
	log.startPiece = NBoard::instance().getPiece(move.startSquare);

	if (move.specialStartSquare != -1)
	{
		log.specialTargetPiece = NBoard::instance().getPiece(move.specialTargetSquare);
		log.specialStartPiece = NBoard::instance().getPiece(move.specialStartSquare);
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
