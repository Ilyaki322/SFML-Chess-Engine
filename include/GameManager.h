#pragma once
#include "Board.h"
#include "Controller.h"

const int ScreenSizeX = 1536, ScreenSizeY = 768;
//const int ScreenSizeX = 768, ScreenSizeY = 768;

class GameManager {

public:

	GameManager ();

	void run(); // need to add the type of game (against computer/ puzzle / friend)

private:

	sf::RenderWindow m_window;

	bool m_firstClick;
	bool m_whiteTurn;

	std::unique_ptr<Controller> m_whitePlayer;
	std::unique_ptr<Controller> m_blackPlayer;

	sf::Text m_test;
};