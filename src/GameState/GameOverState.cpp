#include "GameState/GameOverState.h"
#include "GameManager.h"
#include "IGenerate.h"

GameOverState::GameOverState(GameManager& gameManager)
	: GameState(gameManager)
{
	m_gameOverBox.setSize(sf::Vector2f(100, 100));
	m_gameOverBox.setPosition(300, 300);
	m_gameOverBox.setFillColor(sf::Color::Black);
}

void GameOverState::execute()
{
	IGenerate generator;
	Color color = m_manager.getTurn() ? White : Black;
	if (generator.isMate(color)) {
		m_manager.setEndUI(color == White ? BlackWon : WhiteWon);
	}
	else if (generator.isDraw(color)) {
		m_manager.setEndUI(Draw);
	}
	//
	// else {
	//		nextState()....
	//	}
	//

}

void GameOverState::draw(float dt)
{
	m_manager.getWindow().draw(m_gameOverBox);
}
