#include "UI/ReviewUI.h"

ReviewUI::ReviewUI(StateMachine& stateMachine)
	:PlayUI(stateMachine)
{
}

void ReviewUI::draw(sf::RenderWindow& window)
{
	PlayUI::draw(window);
}

void ReviewUI::initButtons(GameManager& manager)
{
	PlayUI::initButtons(manager);
}

void ReviewUI::buttonClicked(const sf::Vector2f& loc)
{
	PlayUI::buttonClicked(loc);
}
