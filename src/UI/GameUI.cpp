#include "UI/GameUI.h"
#include "NBoard.h"

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

