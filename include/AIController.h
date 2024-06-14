#pragma once
#include "Controller.h"
class AIController : public Controller
{
public:
	AIController(Color color = Black);
	bool playTurn(Move& move) override;

private:
	int minimax(int depth, int alpha, int beta, bool maximizingPlayer);
	int evaluateBoard();
	int depth;
};