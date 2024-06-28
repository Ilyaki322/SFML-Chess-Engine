#include "ButtonCommand/VWhiteAICommand.h"
#include "NBoard.h"
#include "Controllers/AIController.h"
#include "Controllers/PlayerController.h"
#include "GameState/PlayerXTurnState.h"
#include "GameManager.h"
#include "SFMLBoard.h"
#include "UI/GameUI.h"

VWhiteAICommand::VWhiteAICommand(StateMachine& stateMachine, const int difficulty)
	:ButtonCommand(stateMachine), m_difficulty(difficulty) {}

void VWhiteAICommand::execute()
{
	NBoard::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr", "AI Vs Player");
	SFMLBoard board;

	sf::Sprite pic1, pic2;

	pic1.setTexture(Assets::instance().getUITexture("magnus"));
	pic2.setTexture(Assets::instance().getUITexture("blackplayer"));

	auto ui = std::make_unique<GameUI>(m_stateMachine,pic1,pic2);
	GameManager manager(true, board,std::move(ui));
	manager.addPlayer(std::make_unique<AIController>(White, AIDifficult(m_difficulty)));
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), Black, board));
	manager.setStartState(std::make_unique<PlayerXTurnState>(manager, 0));

	manager.update();
}