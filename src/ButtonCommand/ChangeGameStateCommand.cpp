#include "ButtonCommand/ChangeGameStateCommand.h"
#include "GameManager.h"

ChangeGameStateCommand::ChangeGameStateCommand(StateMachine& machine, GameManager& manager, gameStatePtr ptr)
	: ButtonCommand(machine), m_manager(manager), m_nextState(std::move(ptr))
{}

void ChangeGameStateCommand::execute()
{
	m_manager.setState(std::move(m_nextState));
}
