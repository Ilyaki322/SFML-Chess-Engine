#include "StateMachine.h"
#include "MenuState.h"
#include "MainMenuState.h"
#include "PlayMenuState.h" // To delete
StateMachine::StateMachine()
	: m_changingState(false)
{
	m_window.create(sf::VideoMode(720, 578), "MainMenu");
	m_currState = std::make_unique<MainMenuState>(m_window, *this);
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
