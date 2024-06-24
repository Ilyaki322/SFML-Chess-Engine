#include "ButtonCommand/VWhiteAICommand.h"
#include "NBoard.h"
#include "Controllers/AIController.h"
#include "Controllers/PlayerController.h"
#include "GameState/PlayerXTurnState.h"
#include "GameManager.h"
#include "SFMLBoard.h"

void VWhiteAICommand::execute()
{
	NBoard::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");
	SFMLBoard board;
	GameManager manager(true, board);
	manager.addPlayer(std::make_unique<AIController>(White));
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), Black, board));
	manager.setStartState(std::make_unique<PlayerXTurnState>(manager, 0));

	manager.update();
}