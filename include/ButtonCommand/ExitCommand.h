#pragma once
#include "ButtonCommand/ButtonCommand.h"

/*This class executes a exit to the previous state command*/

class StateMachine;
class ExitCommand : public ButtonCommand
{
public:
	ExitCommand(StateMachine& machine);

	void execute() override;

};