#pragma once
#include "Utilities.h"
#include "BoardStack.h"
#include <array>

/*
* This Singleton is the 'Logical' board of the game.
* it contains a 64 int board, each value of this board consists of 6 bits:
* first 3 000abc to represent a piece,
* next 2 for color 0xy000, 16 is black, 8 white.
* and last one is 'did move' flag z00000
* This allows the AI that checks millions of possible turns every turn
* to access data quickly, in order to reach deeper depths.
*/
class NBoard {
public:
	static NBoard& instance();
	NBoard GetCopy() const { // board copy for threaded AI
		NBoard copy;
		copy.m_board = m_board;
		copy.m_stack = m_stack;
		copy.m_lastMove = m_lastMove;
		copy.m_passant = m_passant;
		copy.m_WKing = m_WKing;
		copy.m_BKing = m_BKing;
		copy.m_capture = m_capture;
		return copy;
	}

	void setBoard(std::string fen, std::string name = "");
	void move(Move move);
	void undo();

	int getPiece(int x) const;
	bool enPassant(int x) const;
	int didCapture() const;
	int getKing(int color) const;
	std::array<int, SIZE> &getBoard();

	Move getLastMove() const;
	void saveGame();

private:
	NBoard();
	NBoard(const NBoard&) = default;
	NBoard& operator=(const NBoard&) = default;

	BoardStack m_stack;
	std::array<int, SIZE> m_board;
	Move m_lastMove;

	int m_passant; // tracks on which tile an en passant has occured.
	int m_WKing; // tracks black and white king locations.
	int m_BKing;
	int m_capture; // tracks the last captured piece.
};