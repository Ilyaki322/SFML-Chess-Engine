#pragma once

#include <memory>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>

#include "MainMenu/Menu.h"

typedef std::shared_ptr<MenuState> statePtr;

/*
* This class manages all the states of the game.
* It holds a stack of share ptr of states and 
* knows how to replace and update them accordingly
*/
class StateMachine
{
public:
	StateMachine();

	void update();
	void changeState(std::string menu);
	void exit();
	void returnToMenu();
	
private:
	void exchangeState(std::string menu);
	void pop();
	void popAll();
	void initStates();

	sf::RenderWindow m_window;

	bool m_returnToMenu;
	bool m_deleting;

	std::stack<statePtr> m_stateStack;
	std::map<std::string, statePtr> m_menusMap;
};