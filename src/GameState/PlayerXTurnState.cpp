#include "GameState/PlayerXTurnState.h"
#include "GameState/PlayerXPromotionState.h"
#include "GameState/GameOverState.h"
#include "GameManager.h"

#include "IGenerate.h"

PlayerXTurnState::PlayerXTurnState(GameManager& manager, const int player)
	: GameState(manager), m_playerNum(player)
{
	m_playerController = m_manager.getPlayer(player);
}

void PlayerXTurnState::execute()
{
	IGenerate generator;
	Color color = m_playerNum == 0 ? White : Black;

	if (generator.isMate(color)) // the loser announces the lose.
	{
		m_manager.restartGame();
		return;

		m_manager.setState(std::make_unique<GameOverState>(m_manager));
		return;
	}

	if (m_playerController->turnReady())
	{
		auto move = m_playerController->playTurn();
		if (move.promotionVal == PlayerPromotion)
		{
			m_manager.setState(std::make_unique<PlayerXPromotionState>(m_manager, color, m_playerNum, move));
			return;
		}
		
		m_manager.nextTurn(move);
		m_manager.setState(std::make_unique<PlayerXTurnState>(m_manager, ((m_playerNum + 1) % m_manager.getNumOfPlayers())));
	}
}

void PlayerXTurnState::draw(float dt)
{
	return;
}
