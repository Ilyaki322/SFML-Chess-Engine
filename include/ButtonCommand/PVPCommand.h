#pragma once
#include "ButtonCommand/ButtonCommand.h"
/*This class executes a player vs player game command*/
class PVPCommand : public ButtonCommand
{
public:
	PVPCommand(StateMachine& stateMachine);

	void execute() override;
};