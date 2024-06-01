#include "GameManager.h"

GameManager::GameManager()
	: m_board("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr")
{
	m_window.create(sf::VideoMode(ScreenSizeX, ScreenSizeY), "Main Menu");
}

void GameManager::run()
{
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

			case sf::Event::MouseButtonReleased:
			{
				auto location = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				//if is in board()
				//		so firstClick = board.handleFirstClick(location);
				//if(firstClick){
				//		wait fot second;
				//
			}
			}
		}
		m_board.draw(m_window);
		m_window.display();
	}
}
