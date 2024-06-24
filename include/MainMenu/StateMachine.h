#pragma once

#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>

#include "MenuState.h"

//typedef std::unique_ptr<MenuState> statePtr;
typedef std::shared_ptr<MenuState> statePtr;

class StateMachine
{
public:
	StateMachine();

	void update();
	void changeState(statePtr newState);
	void exit();
	
private:
	//void change();
	//void initStates();
	void pop();

	sf::RenderWindow m_window;

	/*statePtr m_currState;
	statePtr m_nextState;*/
	std::stack<statePtr> m_stateStack;
	//bool m_changingState;
	bool m_deleting;
};