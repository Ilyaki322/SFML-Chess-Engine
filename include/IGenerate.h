#pragma once
#include "Utilities.h"
#include <vector>
#include "PieceLogic.h"
class IGenerate {
public:
	IGenerate();
	std::vector<std::vector<Move>> generateAll(int color);
	std::vector<Move> generatePiece(int x);
	bool isMate(int color);

private:
};