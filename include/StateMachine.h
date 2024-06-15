#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "MenuState.h"

class StateMachine
{
public:
	StateMachine();

	void update();
	void changeState(std::unique_ptr<MenuState> newState);
	
private:

	sf::RenderWindow m_window;
	std::unique_ptr<MenuState> m_currState;

};