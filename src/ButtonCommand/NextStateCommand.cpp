#include "ButtonCommand/NextStateCommand.h"
#include "MainMenu/StateMachine.h"

NextStateCommand::NextStateCommand(StateMachine& machine, std::string nextState)
	: ButtonCommand(machine), m_nextState(nextState) {}

void NextStateCommand::execute()
{
	m_stateMachine.changeState(m_nextState);
}