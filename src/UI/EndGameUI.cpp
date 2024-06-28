#include "UI/EndGameUI.h"
#include "ButtonCommand/RematchCommand.h"
#include "ButtonCommand/ChangeGameStateCommand.h"
#include "GameState/ReviewState.h"

EndGameUI::EndGameUI(StateMachine& stateMachine)
	:PlayUI(stateMachine)
{
}

void EndGameUI::draw(sf::RenderWindow& window)
{
	PlayUI::draw(window);
}

void EndGameUI::initButtons(GameManager& manager)
{
	PlayUI::initButtons(manager);
	m_button.push_back(std::make_unique<Button>("Rematch",
		std::make_unique<RematchCommand>(m_stateMachine, manager),
		sf::Vector2f(250, 150), sf::Vector2f(1000, 600)));
	m_button.push_back(std::make_unique<Button>("Review",
		std::make_unique<ChangeGameStateCommand>(m_stateMachine, manager,std::make_unique<ReviewState>(manager,0)),
		sf::Vector2f(250, 150), sf::Vector2f(1300, 600)));
}

void EndGameUI::buttonClicked(const sf::Vector2f& loc)
{
	PlayUI::buttonClicked(loc);
}
