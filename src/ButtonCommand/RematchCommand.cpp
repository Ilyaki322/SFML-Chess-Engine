#include "ButtonCommand/RematchCommand.h"
#include "GameManager.h"
RematchCommand::RematchCommand(StateMachine& stateMachine, GameManager& manager)
	:ButtonCommand(stateMachine) , m_manager(manager)
{
}

void RematchCommand::execute()
{
	m_manager.restartGame();
}
