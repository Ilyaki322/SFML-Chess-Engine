#pragma once
#include "Controller.h"
#include "SFMLBoard.h"
#include "IObservable.h"
#include "GameState.h"

const int ScreenSizeX = 1536, ScreenSizeY = 768;
//const int ScreenSizeX = 768, ScreenSizeY = 768;

class GameManager : public IObservable
{
public:
	GameManager(std::array<int, SIZE> board);

	void update();
	void setState(std::unique_ptr<GameState> newState);
	void nextTurn();

	Controller* getPlayer(const int i);

private:

	void notify(sf::Event& event) override;
	void draw();
	void handleEvents();

	sf::RenderWindow m_window;

	bool m_firstClick;
	bool m_whiteTurn;

	//std::unique_ptr<Controller> m_whitePlayer;
	//std::unique_ptr<Controller> m_blackPlayer;
	std::vector<std::unique_ptr<Controller>> m_players;
	std::unique_ptr<GameState> m_currentState;

	SFMLBoard m_sfmlBoard;
};