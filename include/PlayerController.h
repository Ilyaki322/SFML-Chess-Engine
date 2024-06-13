#pragma once
#include "Controller.h"
#include "IObserver.h"

#include <SFML/Graphics.hpp>

class GameManager;

class PlayerController : public Controller, public IObserver
{
public:
	PlayerController(GameManager& manager, sf::RenderWindow& window, Color color);

	bool turnReady() override;
	Move playTurn() override;

	void eventUpdate(sf::Event& event, Color color) override;

private:

	void rotateScreen();

	sf::RenderWindow& m_window;

	sf::Vector2i m_startPosition;
	sf::Vector2i m_endPosition;

	bool m_firstClick;
	bool m_turnReady;
};