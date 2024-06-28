#include "UI/GameUI.h"


GameUI::GameUI(StateMachine& stateMachine)
	:PlayUI(stateMachine)
{
}

void GameUI::draw(sf::RenderWindow &window)
{
	PlayUI::draw(window);
}

void GameUI::initButtons(GameManager& manager)
{
	PlayUI::initButtons(manager);

}

void GameUI::buttonClicked(const sf::Vector2f& loc)
{
	PlayUI::buttonClicked(loc);
	
}
