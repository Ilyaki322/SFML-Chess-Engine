#include "ButtonCommand/VBlackAICommand.h"
#include "NBoard.h"
#include "Controllers/AIController.h"
#include "Controllers/PlayerController.h"
#include "GameState/PlayerXTurnState.h"
#include "GameManager.h"
#include "SFMLBoard.h"
#include "UI/GameUI.h"

VBlackAICommand::VBlackAICommand(StateMachine& stateMachine, const int difficulty)
	: ButtonCommand(stateMachine), m_difficulty(difficulty) {}

void VBlackAICommand::execute()
{
	NBoard::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr", "Player Vs AI");
	SFMLBoard board;
	auto ui = std::make_unique<GameUI>(m_stateMachine);
	GameManager manager(true, board, std::move(ui));
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), White, board));
	manager.addPlayer(std::make_unique<AIController>(Black, AIDifficult(m_difficulty)));
	manager.setStartState(std::make_unique<PlayerXTurnState>(manager, 0));

	manager.update();
}
