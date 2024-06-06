#include "AIController.h"

AIController::AIController(Color color)
	: Controller(color)
{}

bool AIController::playTurn(Move& move)
{
	move = { -1, -1 }; // FOR AI TO SKIP TURN
	return true;
}
