#pragma once
#include "ButtonCommand/ButtonCommand.h"

class StateMachine;
class ExitCommand : public ButtonCommand
{
public:
	ExitCommand(StateMachine& machine);

	void execute() override;

private:

	StateMachine& m_machine;
};