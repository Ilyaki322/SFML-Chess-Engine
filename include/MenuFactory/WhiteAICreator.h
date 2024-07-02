#pragma once
#include "MenuFactory/MenuCreator.h"


/*
* This class creates the menu
* that lets the player choose the difficulty of the white AI.
*/

class WhiteAICreator : public MenuCreator
{
public:

	std::shared_ptr<Menu> createMenu(sf::RenderWindow& window, StateMachine& stateMachine) override;
	void addButtons(std::shared_ptr<Menu> menu) override;

private:

	static bool m_register;
};