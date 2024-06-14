#include "PlayerController.h"
#include "Board.h"
#include "GameManager.h"
#include "Assets.h"
#include "SFMLBoard.h"
#include "IGenerate.h"

#include <iostream> // debug


PlayerController::PlayerController(GameManager& manager, sf::RenderWindow& window, Color color, SFMLBoard& board)
	: IObserver(manager), Controller(color), m_window(window),
	m_firstClick(true), m_turnReady(false), m_sfmlBoard(board), m_chosenMove({ -1, -1 })
{}


bool PlayerController::turnReady()
{
	return m_turnReady;
}


Move PlayerController::playTurn()
{
	m_turnReady = false;
	return m_chosenMove;
}

void PlayerController::eventUpdate(sf::Event& event, Color color)
{
	if (event.type != sf::Event::MouseButtonReleased || color != m_color)
	{
		return;
	}

	auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }); 
	sf::RectangleShape tempShape({ 768.f,768.f });

	int y = int(location.y / TILE_SIZE);
	int x = int(location.x / TILE_SIZE + y * DOWN);

	if (tempShape.getGlobalBounds().contains(location))
	{
		if (m_firstClick)
		{
			if (m_sfmlBoard.clickedOnCorrectPiece(location, m_color))
			{
				IGenerate generator;
				m_moves = generator.generatePiece(x);
				for (auto& i : m_moves)
				{
					m_sfmlBoard.colorTiles(i.targetSquare, sf::Color::Green);
					if (i.specialStartSquare != -1) m_sfmlBoard.colorTiles(i.specialTargetSquare, sf::Color::Green);
				}

				m_firstClick = false;
			}
			
		}
		else
		{
			m_sfmlBoard.resetTileColors();

			m_firstClick = true;
			for (auto& i : m_moves)
			{
				if (i.targetSquare == x)
				{
					m_turnReady = true;
					m_chosenMove = i;
				}
			}
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
