#pragma once

#include "ButtonCommand/ButtonCommand.h"
#include "Utilities.h"

/*This class executes a puzzle game command*/

class PuzzleCommand : public ButtonCommand
{
public:
	PuzzleCommand(StateMachine& stateMachine, Difficult difficulty);

	void execute() override;
private:
	const Difficult m_diffculty;
};