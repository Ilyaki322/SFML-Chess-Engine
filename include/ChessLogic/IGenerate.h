#pragma once
#include "Utilities.h"
#include "PieceLogic.h"

#include <vector>

class NBoard;

/*
* this class Generates moves for individual pieces or all of them.
*/
class IGenerate {
public:

	IGenerate() = default;

	std::vector<std::vector<Move>> generateAll(int color, const NBoard& ins);
	std::vector<Move> generatePiece(int x);
	bool isMate(int color);
	bool isDraw(int colorTurn);
};