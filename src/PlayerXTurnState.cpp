#include "PlayerXTurnState.h"
#include "GameManager.h"

#include <iostream>

PlayerXTurnState::PlayerXTurnState(GameManager& manager, const int player, const int players)
	: GameState(manager), m_numOfPlayers(players), m_playerNum(player)
{
	m_playerController = m_manager.getPlayer(player);
}

void PlayerXTurnState::execute()
{
	if (m_playerController->turnReady())
	{
		auto move = m_playerController->playTurn();
		// tell board to update
		m_manager.nextTurn(move);
		m_manager.setState(std::make_unique<PlayerXTurnState>(m_manager, ((m_playerNum + 1) % m_numOfPlayers), m_numOfPlayers));
	}
}

void PlayerXTurnState::draw()
{
	return;
}
