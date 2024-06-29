#include "ButtonCommand/ChangeGameStateCommand.h"
#include "GameManager.h"

ChangeGameStateCommand::ChangeGameStateCommand(StateMachine& machine, GameManager& manager, gameStatePtr ptr,uiPtr ui)
	: ButtonCommand(machine), m_manager(manager), m_nextState(std::move(ptr)),m_ui(ui)
{}

void ChangeGameStateCommand::execute()
{
	m_manager.setState(std::move(m_nextState));
	m_manager.setUI(m_ui);
}
