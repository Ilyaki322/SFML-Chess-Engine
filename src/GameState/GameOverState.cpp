#include "GameState/GameOverState.h"
#include "GameManager.h"
#include "NBoard.h"

GameOverState::GameOverState(GameManager& gameManager, GameOver status)
	: GameState(gameManager),m_status(status),m_once(true)
{
	//
	// download the relevant end pic from Assets
	//
	m_gameOverBox.setSize(sf::Vector2f(100, 100));
	m_gameOverBox.setPosition(300, 300);
	m_gameOverBox.setFillColor(sf::Color::Black);
	
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
	m_manager.getWindow().draw(m_gameOverBox);
}
