#pragma once

#include <memory>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>

#include "MenuState.h"

enum Menus
{
	mainMenu,
	playMenu,
	BlackAI,
	WhiteAI,
	Puzzle,
};

//typedef std::unique_ptr<MenuState> statePtr;
typedef std::shared_ptr<MenuState> statePtr;

class StateMachine
{
public:
	StateMachine();

	void update();
	void changeState(Menus menu);
	void exit();
	void returnToMenu();
	
private:
	//void change();
	//void initStates();
	void pop();
	void popAll();
	void initStates();

	sf::RenderWindow m_window;
	bool m_returnToMenu;
	/*statePtr m_currState;
	statePtr m_nextState;*/
	std::stack<statePtr> m_stateStack;
	//bool m_changingState;
	bool m_deleting;

	std::map<Menus, statePtr> m_menusMap;
};