#pragma once
#include "Controller.h"

class AIController : public Controller
{
public:
	AIController(Color color);

	bool playTurn(Move& move) override;

private:

};