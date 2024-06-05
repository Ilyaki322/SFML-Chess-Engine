#include "PlayerController.h"
#include "Board.h"

#include <iostream>
#include "Assets.h"

PlayerController::PlayerController(sf::RenderWindow& window, Color color)
	: Controller(color), m_window(window), m_isMakingMove(false), m_firstClick(true)
{}


bool PlayerController::playTurn(Move& move)
{
	sf::Vector2f source;
	bool firstClick = false;

	rotateScreen();
	//sf::View view = m_window.getView();
	//view.setRotation(180);
	//m_window.setView(view);

	while (m_window.isOpen())
	{
		m_window.clear();
		m_window.clear(sf::Color(255, 255, 255, 255));

		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

				
			case sf::Event::MouseButtonReleased:
			{
				auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				sf::RectangleShape tempShape({ 768.f,768.f });

				if (tempShape.getGlobalBounds().contains(location)) {
					if (firstClick) {
						Board::instance().handleSecondClick(source,location);
						firstClick = false;
						return true;
					}
					else {
						firstClick = Board::instance().handleFirstClick(location);
						source = location;
					}
				}
			}
			}
		}
		Board::instance().draw(m_window);
		m_window.display();
	}

	return false;
}




void PlayerController::rotateScreen()
{
	float rotation;
	(m_color == Black) ? rotation = 180 : rotation = 0;

	sf::View view = m_window.getView();
	view.setRotation(rotation);
	m_window.setView(view);

	Board::instance().setRotation(rotation);
}
