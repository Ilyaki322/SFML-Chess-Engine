#include "ButtonCommand/VBlackAICommand.h"
#include "NBoard.h"
#include "Controllers/AIController.h"
#include "Controllers/PlayerController.h"
#include "GameState/PlayerXTurnState.h"
#include "GameManager.h"
#include "SFMLBoard.h"

void VBlackAICommand::execute()
{
	NBoard::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");
	SFMLBoard board;
	GameManager manager(true, board);
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), White, board));
	manager.addPlayer(std::make_unique<AIController>(Black));
	manager.setStartState(std::make_unique<PlayerXTurnState>(manager, 0));

	manager.update();
}
