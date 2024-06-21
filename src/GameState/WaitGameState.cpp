#include "GameState/WaitGameState.h"
#include "GameManager.h"

WaitGameState::WaitGameState(GameManager& manager, PuzzleManager& puzzleManager)
	: GameState(manager), m_puzzleManager(puzzleManager), m_waitTime(1.f) {}

void WaitGameState::execute()
{
	if (m_waitTime <= 0)
	{
		// might also undo the last move here?
		// set PuzzleGameState here
		//m_manager.setState()
	}
}

void WaitGameState::draw(float dt)
{
	m_waitTime -= dt;
}
