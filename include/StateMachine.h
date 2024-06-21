#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "MenuState.h"

typedef std::unique_ptr<MenuState> statePtr;

class StateMachine
{
public:
	StateMachine();

	void update();
	void changeState(statePtr newState);
	
private:
	void change();

	sf::RenderWindow m_window;

	statePtr m_currState;
	statePtr m_nextState;
	bool m_changingState;

};