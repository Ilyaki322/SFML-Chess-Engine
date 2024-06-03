#pragma once

#include "Board.h"


const int ScreenSizeX = 1800, ScreenSizeY = 768;

class GameManager {
public:
	GameManager ();
	void run(); // need to add the type of game (against computer/ puzzle / friend)
private:
	Board m_board;
	sf::RenderWindow m_window;
	bool m_firstClick;
};