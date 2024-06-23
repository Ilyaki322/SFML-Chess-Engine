#include "UI/GameUI.h"

GameUI::GameUI()
	:PlayUI()
{
	
}

void GameUI::draw(sf::RenderWindow& window)
{
	PlayUI::draw(window);
}

std::vector<Button> GameUI::getButton()
{
	return std::vector<Button>();
}
