
#include <iostream>
#include "Board.h"
#include "SFML/Graphics.hpp"
int main()
{
	std::cout << "chess\n";
	Board board("pp3pppp");

	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode(768, 768), "Main Menu");

	while (m_window.isOpen())
	{
		m_window.clear();

		m_window.clear(sf::Color(125, 125, 125, 255));
		board.draw(m_window);
		m_window.display();

		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			}
		}
	}
}
