#pragma once
#include "SFML/Graphics.hpp"

class StateMachine;

/*
* This is a base class for the states of the game menu
*/
class MenuState
{
public:
	MenuState(sf::RenderWindow& window, StateMachine& state) : m_window(window), m_stateMachine(state) {};
	virtual ~MenuState() {}
	virtual void draw() = 0;
	virtual void handleEvents() = 0;

private:

	virtual void handleMouseClick(sf::Event& event) = 0;

protected:

	StateMachine& m_stateMachine;
	sf::RenderWindow& m_window;
};