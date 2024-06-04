#include "GameManager.h"
#include "PlayerController.h"
#include "Pieces.h" // FOR ENUM CHANGE LATER

#include <iostream>

GameManager::GameManager()
	//: m_board("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr")
	: m_firstClick(false), m_whiteTurn(true)
{
	m_window.create(sf::VideoMode(ScreenSizeX, ScreenSizeY), "MainMenu");
	Board::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");

	m_whitePlayer = std::make_unique<PlayerController>(m_window, White);
	m_blackPlayer = std::make_unique<PlayerController>(m_window, Black);

}

void GameManager::run()
{
	sf::Vector2f source;
	Move move;

	while (m_window.isOpen())
	{
		m_window.clear();
		m_window.clear(sf::Color(125, 125, 125, 255));

		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			if (m_whiteTurn && m_whitePlayer->playTurn(move))
			{
				std::cout << "White Moved\n";
				m_whiteTurn = false;
			}
			if (!m_whiteTurn && m_blackPlayer->playTurn(move))
			{
				std::cout << "Black Moved\n";
				m_whiteTurn = true;
			}

			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

				/*
			case sf::Event::MouseButtonReleased:
			{
				auto location = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				sf::RectangleShape tempShape;
				tempShape.setSize({ 768.f,768.f });
				if (tempShape.getGlobalBounds().contains(location)) {
					if (m_firstClick) {
						Board::instance().handleSecondClick(source,location);
						m_firstClick = false;
					}
					else {
						m_firstClick = Board::instance().handleFirstClick(location);
						source = location;
					}
				}
			}
			*/
			}
		}

		Board::instance().draw(m_window);
		m_window.display();
	}
}
