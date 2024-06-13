#pragma once
#include "Board.h"
#include "Controller.h"
#include "SFMLBoard.h"
#include "IObservable.h"

const int ScreenSizeX = 1536, ScreenSizeY = 768;
//const int ScreenSizeX = 768, ScreenSizeY = 768;

class GameManager : public IObservable
{
public:
	GameManager ();

	void update();

private:

	void notify(sf::Event& event) override;
	void draw();
	void handleEvents();

	sf::RenderWindow m_window;

	bool m_firstClick;
	bool m_whiteTurn;

	std::unique_ptr<Controller> m_whitePlayer;
	std::unique_ptr<Controller> m_blackPlayer;
	
	SFMLBoard m_sfmlBoard;
};