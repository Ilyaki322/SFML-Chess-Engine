#include "ButtonCommand/PuzzleCommand.h"
#include "PuzzleManager.h"
#include "GameManager.h"
#include "Controllers/PlayerController.h"
#include "GameState/PuzzleGameState.h"
#include "UI/PuzzleUI.h"
#include "UI/GameUI.h" ////  To DELETE

PuzzleCommand::PuzzleCommand(StateMachine& stateMachine,Difficult difficulty)
	:ButtonCommand(stateMachine),m_diffculty(difficulty)
{
}

void PuzzleCommand::execute()
{
	PuzzleManager puzzleManager(White,m_diffculty);
	SFMLBoard board;
	auto ui = std::make_unique<GameUI>(m_stateMachine);
	GameManager manager(false, board, std::move(ui));
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), White, board));
	manager.setStartState(std::make_unique<PuzzleGameState>(White , puzzleManager, manager));

	manager.update();
}
