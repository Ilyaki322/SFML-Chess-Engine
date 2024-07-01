#pragma once
#include "SFML/Graphics.hpp"
#include "MainMenu/Menu.h"

#include <memory>

class StateMachine;

/*
* This is a base class for create menu 
*/

class MenuCreator
{
public:
	MenuCreator() = default;

	virtual std::shared_ptr<Menu> createMenu(sf::RenderWindow& window, StateMachine& stateMachine) = 0;
	virtual void addButtons(std::shared_ptr<Menu> menu) = 0;

protected:
	StateMachine* m_stateMachine;
	sf::RenderWindow* m_window;
};