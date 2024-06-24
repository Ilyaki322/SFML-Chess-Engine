#pragma once
#include "ButtonCommand/ButtonCommand.h"


class VWhiteAICommand : public ButtonCommand
{
public:
	VWhiteAICommand(StateMachine& stateMachine):ButtonCommand(stateMachine) {};

	void execute() override;
};