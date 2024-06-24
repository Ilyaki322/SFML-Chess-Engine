#pragma once
#include "ButtonCommand/ButtonCommand.h"


class VBlackAICommand : public ButtonCommand
{
public:
	VBlackAICommand(StateMachine &stateMachine):ButtonCommand(stateMachine) {};

	void execute() override;
};