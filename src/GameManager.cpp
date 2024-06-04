#include "GameManager.h"

GameManager::GameManager()
	//: m_board("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr")
	: m_firstClick(false)
{
	m_window.create(sf::VideoMode(ScreenSizeX, ScreenSizeY), "Main Menu");
	Board::instance().setBoard("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");
}

void GameManager::run()
{
	sf::Vector2f source;
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
			}
		}
		Board::instance().draw(m_window);
		m_window.display();
	}
}
