#pragma once
#include "Controller.h"
#include "Board.h"
class AIController : public Controller
{
public:
	AIController(Color color = Black);
	Move playTurn() override;
	bool turnReady() override;

private:
	int minimax(int depth, int alpha, int beta, bool maximizingPlayer);
	int evaluateBoard();
	int depth;
};