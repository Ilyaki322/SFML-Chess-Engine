#pragma once
#include "Controllers/Controller.h"
#include "SFMLBoard.h"
#include "IObservable.h"
#include "GameState/GameState.h"
#include "UI/PlayUI.h"

const int ScreenSizeX = 1400, ScreenSizeY = 768;

typedef std::shared_ptr<PlayUI> uiPtr;
typedef std::unique_ptr<GameState> gameStatePtr;
typedef std::unique_ptr<Controller> controllerPtr;

/*
* Responsible for holding the GameState, the Menu.
* Holds the players, and whose turn it is. 
* Derives from IObservable so anyone interested in mouse clicks could listen.
*/
class GameManager : public IObservable
{
public:
	GameManager(bool whiteTurn, SFMLBoard& board , uiPtr ui);

	void addPlayer(controllerPtr p);
	void setStartState(gameStatePtr start);

	void update();
	void setState(gameStatePtr newState);
	void nextTurn(Move &move);
	void setUI(uiPtr ui);
	void setUI();

	void restartGame();
	void resetBoard();
	void updateBoard();

	sf::RenderWindow& getWindow();
	Controller* getPlayer(const int i);
	int getNumOfPlayers() const;
	bool getTurn()const;
	StateMachine& getStateMachine()const;

private:

	void notify(sf::Event& event) override;
	void draw(float dt);
	void handleEvents();
	void change();

	sf::RenderWindow m_window;

	bool m_whiteTurn;

	std::vector<std::unique_ptr<Controller>> m_players;
	uiPtr m_ui;
	uiPtr m_prevUI;
	uiPtr m_nextUI;

	gameStatePtr m_currentState;
	gameStatePtr m_nextState;
	bool m_changeState;
	bool m_changeUI;
	SFMLBoard& m_sfmlBoard;
};