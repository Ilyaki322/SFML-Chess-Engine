#include "PlayerController.h"
#include "Board.h"

#include <iostream>
#include "Assets.h"

PlayerController::PlayerController(sf::RenderWindow& window, Color color)
	: Controller(color), m_window(window), m_isMakingMove(false), m_firstClick(true)
{}


bool PlayerController::playTurn(Move& move)
{
	bool firstClick = false;

	rotateScreen();

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
				auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				sf::RectangleShape tempShape({ 768.f,768.f });

				if (tempShape.getGlobalBounds().contains(location)) {
					if (firstClick) {
						firstClick = false;
						return Board::instance().handleSecondClick(location, move);
					}
					else {
						firstClick = Board::instance().handleFirstClick(location, m_color);
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
	//int offset;
	(m_color == Black) ? rotation = 180 : rotation = 0;
	//(m_color == Black) ? offset = -1 : offset = 1;
	//float x = offset * (768 - 1300);

	sf::View view = m_window.getView();
	view.setRotation(rotation);
	//view.move({x, 0});
	
	m_window.setView(view);

	Board::instance().setRotation(rotation);
}
