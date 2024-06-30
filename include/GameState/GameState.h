#pragma once

class GameManager;

/*
* Base abstract class for Game states,
* the GameManager will hold a state.
* and the state dictates the flow of the game.
* This way we have 1 gamemanager for all game modes,
* and just have to give it the GameState for each mode.
*/
class GameState
{
public:
	GameState(GameManager& manager);
	virtual ~GameState() {};

	virtual void execute() = 0; 
	virtual void draw(float dt) = 0;

protected:
	GameManager& m_manager;
};