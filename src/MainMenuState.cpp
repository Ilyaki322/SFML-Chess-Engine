#include "Assets.h"
#include "MainMenuState.h"
#include "StateMachine.h"
#include "PlayMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow& window, StateMachine& state)
 : MenuState(window, state)
{
	m_text[0].setString("Play");
	m_text[1].setString("Replays");
	m_text[2].setString("Exit");

	for (int i = 0; i < 3; i++)
	{
		m_text[i].setFont(Assets::instance().getFont());
		m_text[i].setFillColor(sf::Color::White);
		m_text[i].setOrigin(m_text[i].getGlobalBounds().width / 2, m_text[i].getGlobalBounds().height / 2);
		m_text[i].setPosition((float)m_window.getSize().x / 2, (float)m_window.getSize().y / 4 + 100 * i);
	}
}

void MainMenuState::draw()
{
	m_window.clear(sf::Color(125, 125, 125));
	for (int i = 0; i < 3; i++)
	{
		m_window.draw(m_text[i]);
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

	// clicked exit
	if (m_text[2].getGlobalBounds().contains(location))
	{
		m_window.close();
	}

	// clicked play
	if (m_text[0].getGlobalBounds().contains(location))
	{
		m_stateMachine.changeState(std::make_unique<PlayMenuState>(m_window, m_stateMachine));
	}

	// clicked replays
	if (m_text[1].getGlobalBounds().contains(location))
	{
		// nothing for now
	}

	// clicked on nothing
	else
	{
		return;
	}
}
