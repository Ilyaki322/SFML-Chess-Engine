#include "StateMachine.h"
#include "MenuState.h"
#include "MainMenuState.h"
#include "PlayMenuState.h" // To delete
StateMachine::StateMachine()
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
	}
}

void StateMachine::changeState(std::unique_ptr<MenuState> newState)
{
	m_currState = std::move(newState);
}
