#include "MainMenu/StateMachine.h"
#include "MainMenu/MenuState.h"
#include "MainMenu/MainMenuState.h"
#include "MainMenu/PlayMenuState.h" // To delete

#include "MainMenu/Menu.h"
#include "Assets.h"
#include "Utilities.h"
#include "Button.h"
#include "ButtonCommand/NextStateCommand.h"
#include "MainMenu/ButtonFactory.h"

StateMachine::StateMachine()
	: m_deleting(false), m_returnToMenu(false)//m_changingState(false)
{
	m_window.create(sf::VideoMode(MENU_X, MENU_Y), "MainMenu");

	//m_currState = std::make_unique<MainMenuState>(m_window, *this);
	auto menu = std::make_unique<Menu>(m_window, *this, Assets::instance().getMenu('m'));

	ButtonFactory theCreator(*this, m_window);

	menu->addButton(theCreator.createButton(Play, sf::Vector2f(260, 50), sf::Vector2f(220, 510)));
	menu->addButton(theCreator.createButton(Exit, sf::Vector2f(260, 50), sf::Vector2f(378, 582)));
	/*menu->addButton(std::make_unique<Button>("Play",
		std::make_unique<NextStateCommand>(*this, std::make_unique<PlayMenuState>(m_window, *this)),
		sf::Vector2f(260, 50), sf::Vector2f(220, 510)));*/

	//m_currState = std::move(menu);
	m_stateStack.push(std::move(menu));
}

void StateMachine::update()
{
	while (m_window.isOpen())
	{
		//m_currState->draw();
		//m_currState->handleEvents();
		m_stateStack.top()->draw();
		m_stateStack.top()->handleEvents();

		if (m_deleting)
			pop();

		if (m_returnToMenu)
			popAll();
	}
}

void StateMachine::changeState(statePtr newState)
{
	//m_changingState = true;
	/*m_nextState = std::move(newState);*/
	//m_stateStack.push(std::move(newState));
	m_stateStack.push(newState);
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
	for (int i = m_stateStack.size(); i > 1; i--) {
		m_stateStack.pop();
	}
	m_returnToMenu = false;
}

//void StateMachine::change()
//{
//	m_currState = std::move(m_nextState);
//	m_changingState = false;
//}
