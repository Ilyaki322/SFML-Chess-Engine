#include "Assets.h"
#include "PlayMenuState.h"
#include "StateMachine.h"
#include "MainMenuState.h"

PlayMenuState::PlayMenuState(sf::RenderWindow& window, StateMachine& state)
	: MenuState(window, state)
{
	m_exit.setString("Exit");
	m_Puzzle.setString("Puzzles");

	m_PvP[0].setString("Player");
	m_PvB[0].setString("Player");
	m_BvP[0].setString("AI");

	m_PvP[1].setString(" VS ");
	m_PvB[1].setString(" VS ");
	m_BvP[1].setString(" VS ");

	m_PvP[2].setString("Player");
	m_PvB[2].setString("AI");
	m_BvP[2].setString("Player");

	setText(m_exit, sf::Color::Red, {(float)m_window.getSize().x / 2, (float)m_window.getSize().y / 8 + 400 });
	setText(m_Puzzle, sf::Color::Red, {(float)m_window.getSize().x / 2, (float)m_window.getSize().y / 8 });

	setText(m_PvP[0], sf::Color::White, { (float)m_window.getSize().x / 2 - 100, (float)m_window.getSize().y / 4 + 30 });
	setText(m_PvB[0], sf::Color::White, { (float)m_window.getSize().x / 2 - 100, (float)m_window.getSize().y / 4 + 130 });
	setText(m_BvP[0], sf::Color::White, { (float)m_window.getSize().x / 2 - 100, (float)m_window.getSize().y / 4 + 230 });

	setText(m_PvP[1], sf::Color::Red, { m_PvP[0].getGlobalBounds().getPosition().x + 120, m_PvP[0].getGlobalBounds().getPosition().y + 5 });
	setText(m_PvB[1], sf::Color::Red, { m_PvB[0].getGlobalBounds().getPosition().x + 120, m_PvB[0].getGlobalBounds().getPosition().y + 5 });
	setText(m_BvP[1], sf::Color::Red, { m_BvP[0].getGlobalBounds().getPosition().x + 70, m_BvP[0].getGlobalBounds().getPosition().y + 3 });

	setText(m_PvP[2], sf::Color::Black, { m_PvP[1].getGlobalBounds().getPosition().x + 110, m_PvP[0].getGlobalBounds().getPosition().y + 6 });
	setText(m_PvB[2], sf::Color::Black, { m_PvB[1].getGlobalBounds().getPosition().x + 100, m_PvB[0].getGlobalBounds().getPosition().y + 6 });
	setText(m_BvP[2], sf::Color::Black, { m_BvP[1].getGlobalBounds().getPosition().x + 110, m_BvP[0].getGlobalBounds().getPosition().y + 6 });
}

void PlayMenuState::draw()
{
	m_window.clear(sf::Color(125, 125, 125));
	m_window.draw(m_exit);
	for (int i = 0; i < 3; i++)
	{
		m_window.draw(m_PvP[i]);
		m_window.draw(m_PvB[i]);
		m_window.draw(m_BvP[i]);
	}
	m_window.draw(m_Puzzle);
	m_window.display();
}

void PlayMenuState::handleEvents()
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

void PlayMenuState::handleMouseClick(sf::Event& event)
{
	auto location =
		m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

	// clicked exit
	if (m_exit.getGlobalBounds().contains(location))
	{
		m_stateMachine.changeState(std::make_unique<MainMenuState>(m_window, m_stateMachine));
	}

	for (int i = 0; i < 3; i++)
	{
		// White AI vs Black Player
		if (m_BvP[i].getGlobalBounds().contains(location))
		{
			//
		}

		// Player vs Player
		if (m_PvP[i].getGlobalBounds().contains(location))
		{
			//
		}

		// White Player vs Black AI
		if (m_PvB[i].getGlobalBounds().contains(location))
		{
			//
		}
	}

	if (m_Puzzle.getGlobalBounds().contains(location))
	{
		//
	}

	// clicked on nothing
	else
	{
		return;
	}
}

void PlayMenuState::setText(sf::Text& text, sf::Color color, sf::Vector2f pos)
{
	text.setFont(Assets::instance().getFont());
	text.setFillColor(color);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(pos);
}
