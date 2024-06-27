#pragma once
#include "ButtonCommand/ButtonCommand.h"


class VWhiteAICommand : public ButtonCommand
{
public:
	VWhiteAICommand(StateMachine& stateMachine, const int difficulty);

	void execute() override;

private:

	const int m_difficulty;
};