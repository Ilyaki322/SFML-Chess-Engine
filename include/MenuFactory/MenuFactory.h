#pragma once
#include "SFML/Graphics.hpp"
#include "MenuFactory/MenuCreator.h"
#include "MainMenu/Menu.h"

#include <vector>
#include <map>
#include <memory>

class StateMachine;

typedef std::unique_ptr<MenuCreator> creatorPtr;
typedef std::vector<creatorPtr> menuVector;
typedef std::shared_ptr<MenuState> menuPtr;

/*
* This is a Menu factory, each MenuCreator will register itself on start
* and the factory will generate all menus upfront.
* this way we create the menus once, and keep them all runtime.
*/

class MenuFactory
{
public:
	MenuFactory(sf::RenderWindow& window, StateMachine& stateMachine);

	static bool registerCreator(creatorPtr creator);

	std::map<std::string, menuPtr> initMenus();

private:

	static menuVector& getVector()
	{
		static menuVector m_creators;
		return m_creators;
	}

	sf::RenderWindow& m_window;
	StateMachine& m_stateMachine;

};