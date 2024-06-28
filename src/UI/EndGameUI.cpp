#include "UI/EndGameUI.h"
#include "ButtonCommand/RematchCommand.h"
#include "ButtonCommand/ChangeGameStateCommand.h"
#include "GameState/ReviewState.h"
#include "Assets.h"

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
	newBackground = true;
	sf::Sprite pic;
	pic.setTexture(Assets::instance().getUITexture("rematch"));
	PlayUI::initButtons(manager);
	m_button.push_back(
		std::make_unique<Button>(pic,
		std::make_unique<RematchCommand>(m_stateMachine, manager),
		 sf::Vector2f(1000, 600)));
	pic.setTexture(Assets::instance().getUITexture("review"));
	m_button.push_back(
		std::make_unique<Button>(pic,
		std::make_unique<ChangeGameStateCommand>(m_stateMachine, manager,std::make_unique<ReviewState>(manager,0)),
		sf::Vector2f(1300, 600)));
}

void EndGameUI::buttonClicked(const sf::Vector2f& loc)
{
	PlayUI::buttonClicked(loc);
}
