#pragma once
#include "ButtonCommand/ButtonCommand.h"

class PVPCommand : public ButtonCommand
{
public:
	PVPCommand(StateMachine& stateMachine);

	void execute() override;
};