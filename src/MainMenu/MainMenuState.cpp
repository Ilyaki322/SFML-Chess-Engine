#include "Assets.h"
#include "MainMenu/MainMenuState.h"
#include "MainMenu/StateMachine.h"
#include "MainMenu/PlayMenuState.h"
#include "ButtonCommand/NextStateCommand.h"

MainMenuState::MainMenuState(sf::RenderWindow& window, StateMachine& state)
	: MenuState(window, state)
{
	//m_buttons.push_back(std::make_unique<Button>("Exit", 
		//sf::Vector2f(120, 50), sf::Vector2f((float)m_window.getSize().x / 2, 400)));

	m_buttons.push_back(std::make_unique<Button>("Play",
		std::make_unique<NextStateCommand>(m_stateMachine, std::make_unique<PlayMenuState>(m_window, m_stateMachine)),
		sf::Vector2f(120, 50), sf::Vector2f((float)m_window.getSize().x / 2, 100)));

	//m_buttons.push_back(std::make_unique<Button>("Replays", 
		//sf::Vector2f(120, 50), sf::Vector2f((float)m_window.getSize().x / 2, 250)));
}

void MainMenuState::draw()
{
	m_window.clear(sf::Color(125, 125, 125));
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(m_window);
	}
	m_window.display();
}

void MainMenuState::handleEvents()
{
	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
			handleMouseClick(event);
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void MainMenuState::handleMouseClick(sf::Event& event)
{
	auto location =
		m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->getGlobalBounds().contains(location))
		{
			m_buttons[i]->click();
			return;
		}
	}
}
