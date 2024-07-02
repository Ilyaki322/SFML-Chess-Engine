#include "GameState/WaitGameState.h"
#include "Managers/GameManager.h"

WaitGameState::WaitGameState(GameManager& manager, nextStatePtr nextState)
	: GameState(manager), m_nextState(std::move(nextState)), m_waitTime(0.5f) {}

void WaitGameState::execute()
{
	if (m_waitTime <= 0)
	{
		m_manager.setState(std::move(m_nextState));
	}
}

void WaitGameState::draw(float dt)
{
	m_waitTime -= dt;
}
