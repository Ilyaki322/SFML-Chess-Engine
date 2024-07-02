#include "GameState/PlayerXTurnState.h"
#include "GameState/PlayerXPromotionState.h"
#include "GameState/GameOverState.h"
#include "GameState/WaitGameState.h"
#include "Managers/GameManager.h"

#include "ChessLogic/IGenerate.h"

PlayerXTurnState::PlayerXTurnState(GameManager& manager, const int player)
	: GameState(manager), m_playerNum(player)
{
	m_playerController = m_manager.getPlayer(player);
}

void PlayerXTurnState::execute()
{
	IGenerate generator;
	Color color = m_playerNum == 0 ? White : Black;

	if (generator.isMate(color)) {// the loser announces the lose.
		m_manager.setState(std::make_unique<GameOverState>(m_manager,color == White? BlackWon : WhiteWon));
		return;
	}
	if (generator.isDraw(color)) {
		m_manager.setState(std::make_unique<GameOverState>(m_manager,Draw));
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
		auto nextState = std::make_unique<PlayerXTurnState>(m_manager, ((m_playerNum + 1) % m_manager.getNumOfPlayers()));
		m_manager.setState(std::make_unique<WaitGameState>(m_manager, std::move(nextState)));
	}
}

void PlayerXTurnState::draw(float)
{
	return;
}
