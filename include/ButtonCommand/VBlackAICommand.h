#pragma once
#include "ButtonCommand/ButtonCommand.h"

/*This class executes a player vs black AI game command*/

class VBlackAICommand : public ButtonCommand
{
public:
	VBlackAICommand(StateMachine& stateMachine, const int difficulty);

	void execute() override;

private:

	const int m_difficulty;
};