#include "ButtonCommand/BackToMenuCommand.h"
#include "GameManager.h"
#include "MainMenu/StateMachine.h"
BackToMenuCommand::BackToMenuCommand(StateMachine& stateMachine,GameManager &manager)
	: ButtonCommand(stateMachine), m_manager(manager) {}

void BackToMenuCommand::execute()
{
	m_manager.getWindow().close();
	m_stateMachine.returnToMenu();
}
