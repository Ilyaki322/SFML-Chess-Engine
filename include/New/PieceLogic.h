#pragma once
#include "Utilities.h"
#include "NBoard.h"
#include <vector>

class PieceLogic {
public:
	PieceLogic();
	std::vector<Move> check(int color); // returns the "can do" moves or empty vector if the king is not in check
	virtual std::vector<Move> generate(std::vector<Move> Incheck) = 0;
	MovementDirection kingPin(int target); //return the type of can do move (forward / diagonal / sides) or 0 if the piece is not in pin


private:
};