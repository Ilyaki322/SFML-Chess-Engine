#include "ButtonCommand/NextStateCommand.h"
#include "StateMachine.h"

NextStateCommand::NextStateCommand(StateMachine& machine, statePtr nextState)
	: m_machine(machine), m_nextState(std::move(nextState)) {}

void NextStateCommand::execute()
{
	m_machine.changeState(std::move(m_nextState));
}