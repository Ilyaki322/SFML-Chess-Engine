#include "GameState/PlayerXTurnState.h"
#include "GameState/PlayerXPromotionState.h"
#include "GameManager.h"

PlayerXTurnState::PlayerXTurnState(GameManager& manager, const int player)
	: GameState(manager), m_playerNum(player)
{
	m_playerController = m_manager.getPlayer(player);
}

void PlayerXTurnState::execute()
{
	if (m_playerController->turnReady())
	{
		auto move = m_playerController->playTurn();
		if (move.promotionVal != PawnVal)
		{
			Color color = m_playerNum == 0 ? White : Black;
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
