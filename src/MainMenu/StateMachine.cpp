#include "MainMenu/StateMachine.h"
#include "MainMenu/MenuState.h"
#include "MainMenu/MainMenuState.h"
#include "MainMenu/PlayMenuState.h" // To delete

#include "MainMenu/Menu.h"
#include "Assets.h"
#include "Utilities.h"
#include "Button.h"
#include "ButtonCommand/NextStateCommand.h"

StateMachine::StateMachine()
	: m_changingState(false)
{
	m_window.create(sf::VideoMode(MENU_X, MENU_Y), "MainMenu");

	//m_currState = std::make_unique<MainMenuState>(m_window, *this);
	auto menu = std::make_unique<Menu>(m_window, *this, Assets::instance().getMenu('m'));
	menu->addButton(std::make_unique<Button>("Play",
		std::make_unique<NextStateCommand>(*this, std::make_unique<PlayMenuState>(m_window, *this)),
		sf::Vector2f(260, 50), sf::Vector2f(220, 510)));

	m_currState = std::move(menu);
}

void StateMachine::update()
{
	while (m_window.isOpen())
	{
		m_currState->draw();
		m_currState->handleEvents();

		if (m_changingState)
		{
			change();
		}
	}
}

void StateMachine::changeState(statePtr newState)
{
	m_changingState = true;
	m_nextState = std::move(newState);
}

void StateMachine::change()
{
	m_currState = std::move(m_nextState);
	m_changingState = false;
}
