#pragma once
#include "Controllers/Controller.h"
#include "SFMLBoard.h"
#include "IObservable.h"
#include "GameState/GameState.h"
#include "UI/PlayUI.h"

const int ScreenSizeX = 1536, ScreenSizeY = 768;
//const int ScreenSizeX = 768, ScreenSizeY = 768;
typedef std::shared_ptr<PlayUI> uiPtr;
typedef std::unique_ptr<GameState> gameStatePtr;
typedef std::unique_ptr<Controller> controllerPtr;
class GameManager : public IObservable
{
public:
	//GameManager();
	GameManager(bool whiteTurn, SFMLBoard& board , uiPtr ui);

	void addPlayer(controllerPtr p);
	void setStartState(gameStatePtr start);

	void update();
	void setState(gameStatePtr newState);
	void nextTurn(Move &move);
	void setUI(uiPtr ui);
	void restartGame();

	sf::RenderWindow& getWindow();
	Controller* getPlayer(const int i);
	int getNumOfPlayers() const;
	bool getTurn()const;

private:

	void notify(sf::Event& event) override;
	void draw(float dt);
	void handleEvents();
	void change();

	sf::RenderWindow m_window;

	bool m_whiteTurn;

	std::vector<std::unique_ptr<Controller>> m_players;
	uiPtr m_ui;

	gameStatePtr m_currentState;
	gameStatePtr m_nextState;
	bool m_changeState;

	SFMLBoard& m_sfmlBoard;
};