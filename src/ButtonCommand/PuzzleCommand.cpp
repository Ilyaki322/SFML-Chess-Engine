#include "ButtonCommand/PuzzleCommand.h"
#include "PuzzleManager.h"
#include "GameManager.h"
#include "Controllers/PlayerController.h"
#include "GameState/PuzzleGameState.h"

PuzzleCommand::PuzzleCommand(Difficult difficulty)
	:m_diffculty(difficulty)
{
}

void PuzzleCommand::execute()
{
	PuzzleManager puzzleManager(White,m_diffculty);
	SFMLBoard board;
	GameManager manager(false, board);
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), White, board));
	manager.setStartState(std::make_unique<PuzzleGameState>(White , puzzleManager, manager));

	manager.update();
}
