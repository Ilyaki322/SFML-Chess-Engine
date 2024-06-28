#pragma once
#include "Utilities.h"
#include <array>
#include "BoardStack.h"

class NBoard {
public:
	static NBoard& instance();
	//void setBoard(std::array<int,SIZE> arr );
	void setBoard(std::string fen, std::string name = "");
	void move(Move move);
	void undo();


	int getPiece(int x)const;
	bool enPassant(int x)const;
	int getKing(int color)const;
	std::array<int, SIZE> &getBoard();

	Move getLastMove() const;
	void saveGame();

private:
	NBoard();
	NBoard(const NBoard&) = default;
	NBoard& operator=(const NBoard&) = default;
	BoardStack m_stack;
	std::array<int, SIZE> m_board;
	int m_passant;
	int m_WKing;
	int m_BKing;

	Move m_lastMove;
};