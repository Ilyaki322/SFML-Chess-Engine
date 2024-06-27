#pragma once
#include "ButtonCommand/ButtonCommand.h"


class VBlackAICommand : public ButtonCommand
{
public:
	VBlackAICommand(StateMachine& stateMachine, const int difficulty);

	void execute() override;

private:

	const int m_difficulty;
};