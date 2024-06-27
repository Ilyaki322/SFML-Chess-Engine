#include "ButtonCommand/NextStateCommand.h"
#include "MainMenu/StateMachine.h"

NextStateCommand::NextStateCommand(StateMachine& machine, Menus nextState)
	: ButtonCommand(machine), m_nextState(nextState) {}

void NextStateCommand::execute()
{
	m_stateMachine.changeState(m_nextState);
}