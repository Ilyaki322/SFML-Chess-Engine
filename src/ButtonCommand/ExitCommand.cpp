#include "ButtonCommand/ExitCommand.h"
#include "MainMenu/StateMachine.h"

ExitCommand::ExitCommand(StateMachine& machine)
	: m_machine(machine) {}

void ExitCommand::execute()
{
	m_machine.exit();
}


