#include "GameManager.h"
#include "PlayerController.h"
#include "AIController.h"
#include "Utilities.h"

#include <iostream> // debug
#include "Assets.h" // for font

GameManager::GameManager()
	//: m_board("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr")
	: m_firstClick(false), m_whiteTurn(true)
{
	m_window.create(sf::VideoMode(ScreenSizeX, ScreenSizeY), "MainMenu");

	//Board::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");//"RNBQ1K1RPP1pBPPP2P582b58ppp1nNpprnbqk2r");

	m_whitePlayer = std::make_unique<PlayerController>(m_window, White);
	//m_blackPlayer = std::make_unique<PlayerController>(m_window, Black);
	m_blackPlayer = std::make_unique<AIController>(Black);


}

void GameManager::update()
{
	while (m_window.isOpen())
	{
		handleEvents();

		if (m_whiteTurn && m_whitePlayer->turnReady())
		{
			//Board::instance().makeMove(move);
			m_whiteTurn = false;
		}
		if (!m_whiteTurn && m_blackPlayer->turnReady())
		{
			//Board::instance().makeMove(move);
			m_whiteTurn = true;
		}

		draw();
	}
}

void GameManager::draw()
{
	m_window.clear();
	m_window.clear(sf::Color(125, 125, 125, 255));
	//Board::instance().draw(m_window);
	m_sfmlBoard.draw(m_window);
	m_window.display();
}

void GameManager::handleEvents()
{
	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		default:
			notify(event);
		}
	}
}

void GameManager::notify(sf::Event& event)
{
	Color color = (m_whiteTurn) ? White : Black;
	for (auto& i : m_observers)
	{
		i->eventUpdate(event, color);
	}
}
