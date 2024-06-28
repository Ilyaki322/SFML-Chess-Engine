#include "GameState/GameOverState.h"
#include "GameManager.h"
#include "NBoard.h"
#include "Assets.h"

GameOverState::GameOverState(GameManager& gameManager, GameOver status)
	: GameState(gameManager),m_status(status),m_once(true)
{
	switch (status)
	{
	case Draw:
		m_winner.setTexture(Assets::instance().getUITexture("draw"));
		break;
	case WhiteWon:
		m_winner.setTexture(Assets::instance().getUITexture("whitewon"));
		break;
	case BlackWon:
		m_winner.setTexture(Assets::instance().getUITexture("blackwon"));
		break;
	}
	m_winner.setPosition({ 768, 0 });
}

void GameOverState::execute()
{
	if (!m_once)return;
	NBoard::instance().saveGame();
	m_manager.setUI(std::make_shared<EndGameUI>(m_manager.getStateMachine()));
	m_once = false;
}

void GameOverState::draw(float dt)
{
	m_manager.getWindow().draw(m_winner);
}
