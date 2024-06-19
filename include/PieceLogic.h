#pragma once
#include <algorithm>
#include "Utilities.h"

class PieceLogic {
public:
	PieceLogic();
	bool check(int king ,std::vector<int>& ,int color); // returns true if pieces can move (if the king is in check it will return the "can do" squares in vector) or false if only the king can move
	std::vector<Move> generate(std::vector<int> Incheck , int piecePlace );
	MovementDirection kingPin(int target); //return the type of can do move (forward / diagonal / sides) or 0 if the piece is not in pin
	std::vector<Move> kingMove(int start, std::vector<int> Incheck);
	bool BishopOnWhiteSquare(int pos);
private:
	std::vector<Move> bishopMove(int start , std::vector<int> Incheck);
	std::vector<Move> knightMove(int start, std::vector<int> Incheck);
	std::vector<Move> rookMove(int start, std::vector<int> Incheck);
	std::vector<Move> pawnMove(int start, std::vector<int> Incheck);
	std::vector<Move> queenMove(int start, std::vector<int> Incheck);
	std::vector<Move> slidingMove(int direction ,int start , std::vector<int> inCheck , int color);
	bool checkCheck(std::vector<Move> &moves, int color , int direction,int king);
	bool checkPin(std::vector<Move> moves, int color , int direction, int king);
	void insertMoveToInt(std::vector<Move> from, std::vector<int>& to);
	bool checkInSquare(int place , int jump , int color); // for knight move
	bool checkDirection(std::vector<Move>& move, const int pos, const int direction,int color) const;
	bool checkCorner(std::vector<Move>& move, const int pos, const int corner,int color) const;
	bool castle(int king, int direction);
	bool kingTeritory(int king , int color);
};