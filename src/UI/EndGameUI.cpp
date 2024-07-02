#include "UI/EndGameUI.h"
#include "UI/ReviewUI.h"
#include "ButtonCommand/RematchCommand.h"
#include "ButtonCommand/ChangeGameStateCommand.h"
#include "ButtonCommand/BackToMenuCommand.h"
#include "GameState/ReviewState.h"
#include "Assets.h"

EndGameUI::EndGameUI(StateMachine& stateMachine, std::string winner)
	:PlayUI(stateMachine)
{
	m_endGamePic.setTexture(Assets::instance().getUITexture(winner));
	m_endGamePic.setPosition(0, 0);
}

void EndGameUI::draw(sf::RenderWindow& window)
{
	window.draw(m_endGamePic);
	PlayUI::draw(window);
}

void EndGameUI::initButtons(GameManager& manager)
{
	m_newBackground = true;
	sf::Sprite pic;
	pic.setTexture(Assets::instance().getUITexture("rematch"));
	PlayUI::initButtons(manager);
	m_button.push_back(
		std::make_unique<Button>(pic,
		std::make_unique<RematchCommand>(m_stateMachine, manager),
		 sf::Vector2f(950, 500)));
	pic.setTexture(Assets::instance().getUITexture("review"));
	m_button.push_back(
		std::make_unique<Button>(pic,
		std::make_unique<ChangeGameStateCommand>(m_stateMachine, manager,std::make_unique<ReviewState>(manager,-1), std::make_shared<ReviewUI>(m_stateMachine)),
		sf::Vector2f(1250, 500)));

}

void EndGameUI::buttonClicked(const sf::Vector2f& loc)
{
	PlayUI::buttonClicked(loc);
}
