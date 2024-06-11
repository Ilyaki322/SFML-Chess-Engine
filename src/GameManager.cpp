#include "GameManager.h"
#include "PlayerController.h"
#include "AIController.h"


#include "Pieces.h" // FOR ENUM CHANGE LATER
#include <iostream> // debug
#include "Assets.h" // for font

GameManager::GameManager()
	//: m_board("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr")
	: m_firstClick(false), m_whiteTurn(true)
{
	m_window.create(sf::VideoMode(ScreenSizeX, ScreenSizeY), "MainMenu");

	Board::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");//"RNBQ1K1RPP1pBPPP2P582b58ppp1nNpprnbqk2r");

	m_whitePlayer = std::make_unique<PlayerController>(m_window, White);
	m_blackPlayer = std::make_unique<PlayerController>(m_window, Black);
	//m_blackPlayer = std::make_unique<AIController>(Black);

	m_test.setFont(Assets::instance().getFont());
	m_test.setCharacterSize(10);
	m_test.setFillColor(sf::Color::Red);
	m_test.setString("TEST TEST TEST");
	m_test.setPosition(100, 100);
}

void GameManager::run()
{
	//Board::instance().printAllMoves();
	sf::Vector2f source;
	Move move;

	while (m_window.isOpen())
	{
		m_window.clear();
		m_window.clear(sf::Color(125, 125, 125, 255));
		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			}
		}

		if (m_whiteTurn && m_whitePlayer->playTurn(move))
		{
			Board::instance().makeMove(move);
			m_whiteTurn = false;
		}
		if (!m_whiteTurn && m_blackPlayer->playTurn(move))
		{
			Board::instance().makeMove(move);
			m_whiteTurn = true;
		}
		

		Board::instance().draw(m_window);
		m_window.draw(m_test);
		m_window.display();
	}
}
