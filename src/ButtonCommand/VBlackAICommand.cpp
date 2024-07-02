#include "ButtonCommand/VBlackAICommand.h"
#include "ChessLogic/NBoard.h"
#include "Controllers/AIController.h"
#include "Controllers/PlayerController.h"
#include "GameState/PlayerXTurnState.h"
#include "Managers/GameManager.h"
#include "SFMLRelated/SFMLBoard.h"
#include "UI/GameUI.h"

VBlackAICommand::VBlackAICommand(StateMachine& stateMachine, const int difficulty)
	: ButtonCommand(stateMachine), m_difficulty(difficulty) {}

void VBlackAICommand::execute()
{
	NBoard::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr", "Player Vs AI");
	SFMLBoard board;

	sf::Sprite pic1, pic2;

	pic1.setTexture(Assets::instance().getUITexture("whiteplayer"));
	pic2.setTexture(Assets::instance().getUITexture("magnus"));

	auto ui = std::make_unique<GameUI>(m_stateMachine,pic1,pic2,board);
	GameManager manager(true, board, std::move(ui));
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), White, board));
	manager.addPlayer(std::make_unique<AIController>(Black, AIDifficult(m_difficulty)));
	manager.setStartState(std::make_unique<PlayerXTurnState>(manager, 0));

	manager.update();
}
