#include "Controllers/PlayerController.h"
#include "Managers/GameManager.h"
#include "Assets.h"
#include "SFMLRelated/SFMLBoard.h"
#include "ChessLogic/IGenerate.h"

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
	if (m_chosenMove.promotionVal != PawnVal) m_chosenMove.promotionVal = PlayerPromotion;
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
	tempShape.setPosition(152,0);

	int y = int(location.y / TILE_SIZE);
	int x = int((location.x - 152) / TILE_SIZE + y * DOWN);

	

	if (tempShape.getGlobalBounds().contains(location))
	{
		if (m_firstClick)
		{
			firstClick(x);
		}

		else // second click
		{
			m_sfmlBoard.resetTileColors();

			m_firstClick = true;
			for (auto& i : m_moves)
			{
				if (i.targetSquare == x)
				{
					m_turnReady = true;
					m_chosenMove = i;
					return;
				}
			}

			firstClick(x);
		}
	}
}

void PlayerController::firstClick(const int pos)
{
	if (m_sfmlBoard.clickedOnCorrectPiece(pos, m_color))
	{
		IGenerate generator;
		m_moves = generator.generatePiece(pos);

		if (m_moves.empty()) m_sfmlBoard.colorTiles(pos, sf::Color::Red);
		for (auto& i : m_moves)
		{
			m_sfmlBoard.colorTiles(i.targetSquare, MOVEABLE_TILE);
			if (i.specialStartSquare != -1) m_sfmlBoard.colorTiles(i.specialTargetSquare, sf::Color::Green);
		}

		m_firstClick = false;
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

	//Board::instance().setRotation(rotation);
}