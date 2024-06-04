#pragma once
#include "Controller.h"

#include <SFML/Graphics.hpp>

class PlayerController : public Controller
{
public:

	PlayerController(sf::RenderWindow& window, Color color);

	bool playTurn(Move& move) override;

private:

	void rotateScreen();

	sf::RenderWindow& m_window;
};