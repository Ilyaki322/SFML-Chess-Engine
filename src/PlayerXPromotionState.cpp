#include "PlayerXPromotionState.h"
#include "GameManager.h"
#include "PlayerXTurnState.h"

PlayerXPromotionState::PlayerXPromotionState(GameManager& manager, Color color, const int player, Move move)
 : GameState(manager), m_color(color), m_move(move), m_player(player),
   m_box(manager, m_color), m_playerController(manager.getPlayer(player)) {}

void PlayerXPromotionState::execute()
{
	if (m_box.getPiece() != PawnVal)
	{
		m_move.promotionVal = m_box.getPiece();
		m_manager.nextTurn(m_move);

		m_manager.setState(std::make_unique<PlayerXTurnState>(m_manager,((m_player + 1) % m_manager.getNumOfPlayers())));
	}
}

void PlayerXPromotionState::draw()
{
	m_box.draw();
}


