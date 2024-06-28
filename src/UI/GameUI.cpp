#include "UI/GameUI.h"
#include "NBoard.h"
#include "ButtonCommand/RematchCommand.h"

GameUI::GameUI(StateMachine& stateMachine)
	:PlayUI(stateMachine),m_end(false)
{

}

void GameUI::draw(sf::RenderWindow &window)
{
	PlayUI::draw(window);
	if (m_end) {
		m_restartGame->draw(window);
	}
}

void GameUI::initButtons(GameManager& manager)
{
	PlayUI::initButtons(manager);
	m_restartGame = (std::make_unique<Button>("Rematch",
		std::make_unique<RematchCommand>(m_stateMachine,manager),
		sf::Vector2f(250, 150), sf::Vector2f(1000, 600)));
	//m_review = (std::make_unique<Button>("Review",
	//	std::make_unique<RematchCommand>(m_stateMachine, manager),
	//	sf::Vector2f(250, 150), sf::Vector2f(1000, 600)));
}

void GameUI::buttonClicked(const sf::Vector2f& loc)
{
	PlayUI::buttonClicked(loc);
	if (m_end)
		if(m_restartGame->getGlobalBounds().contains(loc))
			m_restartGame->click();
	
}

void GameUI::setEnd()
{
	m_end = true;
}

