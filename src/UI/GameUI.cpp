#include "UI/GameUI.h"


GameUI::GameUI(StateMachine& stateMachine, sf::Sprite& p1, sf::Sprite& p2)
	:PlayUI(stateMachine),m_player1(p1),m_player2(p2)
{
	m_player1.setPosition(1000,600);
	m_player2.setPosition(1000, 100);
}

void GameUI::draw(sf::RenderWindow &window)
{
	PlayUI::draw(window);
	window.draw(m_player1);
	window.draw(m_player2);
}

void GameUI::initButtons(GameManager& manager)
{
	newBackground = false;
	PlayUI::initButtons(manager);
}

void GameUI::buttonClicked(const sf::Vector2f& loc)
{
	PlayUI::buttonClicked(loc);
	
}
