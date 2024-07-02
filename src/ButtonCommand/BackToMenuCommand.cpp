#include "ButtonCommand/BackToMenuCommand.h"
#include "Managers/GameManager.h"
#include "MainMenu/StateMachine.h"
#include "ChessLogic/NBoard.h"
BackToMenuCommand::BackToMenuCommand(StateMachine& stateMachine,GameManager &manager)
	: ButtonCommand(stateMachine), m_manager(manager) {}

void BackToMenuCommand::execute()
{
	m_manager.getWindow().close();
	m_stateMachine.returnToMenu();
}
