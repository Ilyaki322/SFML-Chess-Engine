#include "PlayerController.h"
#include "Board.h"
#include "GameManager.h"
#include "Assets.h"
#include "SFMLBoard.h"

#include <iostream> // debug


PlayerController::PlayerController(GameManager& manager, sf::RenderWindow& window, Color color, SFMLBoard& board)
	: IObserver(manager), Controller(color), m_window(window),
	  m_firstClick(true), m_turnReady(false), m_sfmlBoard(board)
{}


bool PlayerController::turnReady()
{
	return m_turnReady;
}


Move PlayerController::playTurn()
{
	Move move = { -1, -1 };
	//bool firstClick = false;

	////rotateScreen();

	//		{
	//			auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
	//			sf::RectangleShape tempShape({ 768.f,768.f });

	//			if (tempShape.getGlobalBounds().contains(location)) {
	//				if (firstClick) {
	//					firstClick = false;
	//					return Board::instance().handleSecondClick(location, move);
	//				}
	//				else {
	//					firstClick = Board::instance().handleFirstClick(location, m_color);
	//				}
	//			}
	//			
	//		}
	//		}
	//	}
	//	Board::instance().draw(m_window);
	//	m_window.display();
	//}

	//return false;

	m_turnReady = false;
	return move;
}

void PlayerController::eventUpdate(sf::Event& event, Color color)
{
	if (event.type != sf::Event::MouseButtonReleased || color != m_color)
	{
		return;
	}

	auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }); 
	sf::RectangleShape tempShape({ 768.f,768.f });

	if (tempShape.getGlobalBounds().contains(location))
	{
		if (m_firstClick)
		{
			if (m_sfmlBoard.clickedOnCorrectPiece(location, m_color))
			{
				int y = int(location.y / TILE_SIZE);
				int x = int(location.x / TILE_SIZE + y * DOWN);

				sf::Color color;
				m_color == Black ? color = sf::Color::Black : color = sf::Color::White;
				m_sfmlBoard.colorTiles(x, color);
				m_firstClick = false;
			}
			
		}
		else
		{
			m_sfmlBoard.resetTileColors();
			m_firstClick = true;
			m_turnReady = true;
		}
	}
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
