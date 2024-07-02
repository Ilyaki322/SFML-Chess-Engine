#pragma once
#include "Utilities.h"
#include "PieceLogic.h"

#include <vector>

/*
* this class Generates moves for individual pieces or all of them.
*/
class IGenerate {
public:

	IGenerate() = default;

	std::vector<std::vector<Move>> generateAll(int color);
	std::vector<Move> generatePiece(int x);
	bool isMate(int color);
	bool isDraw(int colorTurn);
};