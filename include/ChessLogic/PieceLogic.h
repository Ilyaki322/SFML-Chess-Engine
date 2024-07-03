#pragma once
#include <algorithm>
#include "Utilities.h"

/*
* This class represents all of the pieces movement rules.
*/
class PieceLogic {
public:
	PieceLogic() = default;

	bool check(int king ,std::vector<int>& ,int color); 

	std::vector<Move> generate(std::vector<int> Incheck , int piecePlace );
	MovementDirection kingPin(int target); 

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
	bool checkPin(std::vector<Move> moves, int color , int direction, int king,int target);
	bool checkInSquare(int place , int jump , int color); // for knight move
	bool checkDirection(const int pos, const int direction,int color) const;
	bool checkCorner(const int pos, const int corner,int color) const;
	bool castle(int king, int direction);
	bool kingTeritory(int king , int color);
	void insertMoveToInt(std::vector<Move> from, std::vector<int>& to);
};