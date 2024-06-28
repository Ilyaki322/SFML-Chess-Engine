#include "GameState/GameOverState.h"
#include "GameManager.h"
#include "IGenerate.h"

GameOverState::GameOverState(GameManager& gameManager, GameOver status)
	: GameState(gameManager),m_status(status)//,m_ui(gameManager.getUI())
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
	m_ui->setEnd();
}

void GameOverState::draw(float dt)
{
	m_manager.getWindow().draw(m_gameOverBox);
}
