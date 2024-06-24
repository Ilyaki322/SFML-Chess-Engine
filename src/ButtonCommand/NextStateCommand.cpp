#include "ButtonCommand/NextStateCommand.h"
#include "MainMenu/StateMachine.h"

NextStateCommand::NextStateCommand(StateMachine& machine, statePtr nextState)
	: ButtonCommand(machine), m_nextState(std::move(nextState)) {}

void NextStateCommand::execute()
{
	//m_machine.changeState(std::move(m_nextState));
	m_stateMachine.changeState(m_nextState);
}