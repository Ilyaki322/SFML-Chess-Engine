#include "ButtonCommand/PVPCommand.h"
#include "NBoard.h"
#include "Controllers/PlayerController.h"
#include "GameState/PlayerXTurnState.h"
#include "GameManager.h"
#include "SFMLBoard.h"
#include "UI/GameUI.h"

#include <memory>

void PVPCommand::execute()
{
	NBoard::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");
	SFMLBoard board;
	auto ui = std::make_unique<GameUI>();
	GameManager manager(true, board, std::move(ui));
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), White, board));
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), Black, board));
	manager.setStartState(std::make_unique<PlayerXTurnState>(manager, 0));

	manager.update();
}
