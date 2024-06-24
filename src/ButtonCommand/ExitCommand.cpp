#include "ButtonCommand/ExitCommand.h"
#include "MainMenu/StateMachine.h"

ExitCommand::ExitCommand(StateMachine& machine)
	:ButtonCommand(machine){}

void ExitCommand::execute()
{
	m_stateMachine.exit();
}


