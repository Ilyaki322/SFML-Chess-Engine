#pragma once
#include "ButtonCommand/ButtonCommand.h"

/*This class executes a player vs white AI game command*/
class VWhiteAICommand : public ButtonCommand
{
public:
	VWhiteAICommand(StateMachine& stateMachine, const int difficulty);

	void execute() override;

private:

	const int m_difficulty;
};