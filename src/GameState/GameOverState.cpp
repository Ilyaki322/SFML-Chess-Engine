#include "GameState/GameOverState.h"
#include "Managers/GameManager.h"
#include "ChessLogic/NBoard.h"
#include "Assets.h"

GameOverState::GameOverState(GameManager& gameManager, GameOver status)
	: GameState(gameManager), m_status(status), m_once(true)
{
	switch (status)
	{
	case Draw:
		m_winner = "draw";
		break;
	case WhiteWon:
		m_winner = "whitewon";
		break;
	case BlackWon:
		m_winner = "blackwon";
		break;
	}
}

/*
* on the first run we update the manager,
* and then wait for user input in the EndGameUI.
*/
void GameOverState::execute()
{
	if (!m_once)return;
	NBoard::instance().saveGame();
	m_manager.resetBoard();
	m_manager.setUI(std::make_shared<EndGameUI>(m_manager.getStateMachine(), m_winner));
	m_once = false;
}

void GameOverState::draw(float)
{}
