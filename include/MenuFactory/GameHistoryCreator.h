#pragma once
#include "MenuFactory/MenuCreator.h"

/*
* This class create the history menu
*/

class GameHistoryCreator : public MenuCreator
{
public:

	std::shared_ptr<Menu> createMenu(sf::RenderWindow& window, StateMachine& stateMachine) override;
	void addButtons(std::shared_ptr<Menu> menu) override;

private:

	static bool m_register;
};