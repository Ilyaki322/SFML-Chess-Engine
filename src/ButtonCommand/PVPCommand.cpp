#include "ButtonCommand/PVPCommand.h"
#include "ChessLogic/NBoard.h"
#include "Controllers/PlayerController.h"
#include "GameState/PlayerXTurnState.h"
#include "Managers/GameManager.h"
#include "SFMLRelated/SFMLBoard.h"
#include "UI/GameUI.h"
#include "Assets.h"
#include <memory>

PVPCommand::PVPCommand(StateMachine& stateMachine)
	:ButtonCommand(stateMachine)
{
}

void PVPCommand::execute()
{
	NBoard::instance().setBoard(NEW_GAME, "Player VS Player");
	SFMLBoard board;

	sf::Sprite pic1, pic2;

	pic1.setTexture(Assets::instance().getUITexture("whiteplayer"));
	pic2.setTexture(Assets::instance().getUITexture("blackplayer"));

	auto ui = std::make_shared<GameUI>(m_stateMachine,pic1,pic2,board);
	
	GameManager manager(true, board, ui);
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), White, board));
	manager.addPlayer(std::make_unique<PlayerController>(manager, manager.getWindow(), Black, board));
	manager.setStartState(std::make_unique<PlayerXTurnState>(manager, 0));

	manager.update();
}
