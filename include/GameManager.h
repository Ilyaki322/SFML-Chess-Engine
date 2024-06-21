#pragma once
#include "Controller.h"
#include "SFMLBoard.h"
#include "IObservable.h"
#include "GameState/GameState.h"

const int ScreenSizeX = 1536, ScreenSizeY = 768;
//const int ScreenSizeX = 768, ScreenSizeY = 768;

typedef std::unique_ptr<GameState> gameStatePtr;
class GameManager : public IObservable
{
public:
	GameManager();

	void update();
	void setState(gameStatePtr newState);
	void nextTurn(Move &move);

	sf::RenderWindow& getWindow();
	Controller* getPlayer(const int i);
	int getNumOfPlayers() const;

private:

	void notify(sf::Event& event) override;
	void draw(float dt);
	void handleEvents();
	void change();

	sf::RenderWindow m_window;

	bool m_firstClick;
	bool m_whiteTurn;

	//std::unique_ptr<Controller> m_whitePlayer;
	//std::unique_ptr<Controller> m_blackPlayer;
	std::vector<std::unique_ptr<Controller>> m_players;


	gameStatePtr m_currentState;
	gameStatePtr m_nextState;
	bool m_changeState;

	SFMLBoard m_sfmlBoard;
};