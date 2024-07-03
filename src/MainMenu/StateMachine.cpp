#include "MainMenu/StateMachine.h"
#include "Assets.h"
#include "Utilities.h"
#include "MenuFactory/MenuFactory.h"

#include "FileExceptions/PuzzleFileException.h"
#include "FileExceptions/HistoryFileException.h"

StateMachine::StateMachine()
	: m_deleting(false), m_returnToMenu(false)
{
	m_window.create(sf::VideoMode(MENU_X, MENU_Y), "MainMenu");

	initStates();
	m_stateStack.push(m_menusMap["MainMenu"]);
}

void StateMachine::update()
{
	while (m_window.isOpen())
	{
		try
		{
			m_stateStack.top()->draw();
			m_stateStack.top()->handleEvents();
		}
		// if files did not load correctly, swap depending menus on error message
		catch (PuzzleFileException& e)
		{
			m_menusMap["Puzzle"] = (e.createErrorMenu(m_window, *this));
			exchangeState("Puzzle");
		}
		catch (HistoryFileException& e)
		{
			m_menusMap["GameHistory"] = (e.createErrorMenu(m_window, *this));
			exchangeState("GameHistory");
		}

		if (m_deleting)
			pop();

		if (m_returnToMenu)
			popAll();
	}
}

void StateMachine::changeState(std::string menu)
{
	m_stateStack.push(m_menusMap[menu]);
}

void StateMachine::exchangeState(std::string menu)
{
	m_stateStack.pop();
	m_stateStack.push(m_menusMap[menu]);
}

void StateMachine::exit()
{
	m_deleting = true;
}

void StateMachine::returnToMenu()
{
	m_returnToMenu = true;
}

void StateMachine::pop()
{
	m_deleting = false;

	if (m_stateStack.size() >= 2)
	{
		m_stateStack.pop();
		return;
	}

	m_window.close();
}

void StateMachine::popAll()
{
	for (size_t i = m_stateStack.size(); i > 1; i--) {
		m_stateStack.pop();
	}
	m_returnToMenu = false;
}

void StateMachine::initStates()
{
	MenuFactory factory(m_window, *this);
	m_menusMap = factory.initMenus();
}
