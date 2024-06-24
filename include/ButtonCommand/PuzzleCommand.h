#pragma once

#include "ButtonCommand/ButtonCommand.h"
#include "Utilities.h"
class PuzzleCommand : public ButtonCommand
{
public:
	PuzzleCommand(StateMachine& stateMachine, Difficult difficulty);

	void execute() override;
private:
	const Difficult m_diffculty;
};