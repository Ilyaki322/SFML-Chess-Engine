#include "MainMenu/HistoryState.h"
#include "ButtonCommand/ExitCommand.h"
#include "Assets.h"

#include "NBoard.h"
#include "Utilities.h"
#include "SFMLBoard.h"
#include "GameManager.h"
#include "GameState/ReviewState.h"

#include <fstream>
#include <string>

#include "iostream" // debug
#include <UI/GameUI.h>
#include "UI/ReviewUI.h"

HistoryState::HistoryState(sf::RenderWindow& window, StateMachine& stateMachine, sf::Texture& texture, std::string name)
	: Menu(window, stateMachine, texture, name), m_page(0)
{
	sf::Sprite arrow(Assets::instance().getUITexture("pageup"));
	m_pageUp = std::make_unique<Button>(arrow, nullptr, sf::Vector2f(20, 150));
	arrow.setTexture(Assets::instance().getUITexture("pagedown"));
	m_pageDown = std::make_unique<Button>(arrow, nullptr, sf::Vector2f(20, 300));

	m_games.reserve(10);
	load10Games();
}

void HistoryState::draw()
{
	m_window.clear(sf::Color(125, 125, 125));

	m_window.draw(m_menuSprite);

	
	for (int i = 0; i < m_games.size(); i++)
	{
		m_games[i]->draw(m_window);
	}
	for (int i = 0; i < m_buttons.size(); i++) // for debug only
	{
		m_buttons[i]->draw(m_window);
	}
	m_pageUp->draw(m_window);
	m_pageDown->draw(m_window);

	m_window.display();
}

void HistoryState::handleMouseClick(sf::Event& event)
{
	Menu::handleMouseClick(event);
	auto pos = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

	if (m_pageUp->getGlobalBounds().contains(pos))
	{
		if (m_page > 0) m_page--;
		load10Games();
	}
	if (m_pageDown->getGlobalBounds().contains(pos))
	{
		m_page++;
		load10Games();
	}
	for (int i = 0; i < m_games.size(); i++)
	{
		if (m_games[i]->getGlobalBounds().contains(pos))
		{
			startReview(i + m_page * 10);
		}
	}
}

void HistoryState::load10Games()
{
	std::ifstream games("GameHistory.txt");
	std::string line;

	int linesToSkip = m_page * 20;
	for (int i = 0; i < linesToSkip && !games.eof(); i++)
	{
		std::getline(games, line);
	}

	if (games.eof())
	{
		if (m_page > 0) m_page--;
		return;
	}
	m_games.clear();

	for (int i = 0; i < 10 && !games.eof(); i++)
	{
		std::getline(games, line);
		if (line.empty()) continue;
		
		std::string newline = std::to_string(i + 1 + m_page * 10) + "." + line;
		m_games.push_back(std::make_unique<Button>(newline, nullptr, sf::Vector2f(500.f, 40.f), sf::Vector2f(m_window.getSize().x / 2.f, 25.f + 50.f * i)));

		std::getline(games, line);
	}

	games.close();
}

void HistoryState::startReview(const int game)
{
	NBoard::instance().setBoard(NEW_GAME);
	SFMLBoard board;

	sf::Sprite pic1, pic2;

	auto ui = std::make_shared<ReviewUI>(m_stateMachine);

	GameManager manager(true, board, ui);
	manager.setStartState(std::make_unique<ReviewState>(manager, game));

	manager.update();
}
