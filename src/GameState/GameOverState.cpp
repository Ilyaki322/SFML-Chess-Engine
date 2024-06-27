#include "GameState/GameOverState.h"
#include "GameManager.h"

GameOverState::GameOverState(GameManager& gameManager)
	: GameState(gameManager)
{
	m_gameOverBox.setSize(sf::Vector2f(100, 100));
	m_gameOverBox.setPosition(300, 300);
	m_gameOverBox.setFillColor(sf::Color::Black);
}

void GameOverState::execute()
{
	return;
}

void GameOverState::draw(float dt)
{
	m_manager.getWindow().draw(m_gameOverBox);
}
