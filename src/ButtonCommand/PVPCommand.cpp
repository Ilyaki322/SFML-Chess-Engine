#include "ButtonCommand/PVPCommand.h"
#include "NBoard.h"
#include "Controllers/PlayerController.h"
#include "GameState/PlayerXTurnState.h"
#include "GameManager.h"
#include "SFMLBoard.h"
#include "UI/GameUI.h"

#include <memory>

PVPCommand::PVPCommand(StateMachine& stateMachine)
	:ButtonCommand(stateMachine)
{
}

void PVPCommand::execute()
{
	NBoard::instance().setBoard(NEW_GAME, "Player VS Player");
	SFMLBoard board;
	auto ui = std::make_shared<GameUI>(m_stateMachine);
	
	GameManager manager(true, board, ui);
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), White, board));
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), Black, board));
	manager.setStartState(std::make_unique<PlayerXTurnState>(manager, 0));

	manager.update();
}
