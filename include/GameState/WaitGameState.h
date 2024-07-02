#pragma once
#include "GameState/GameState.h"
#include <memory>

typedef std::unique_ptr<GameState> nextStatePtr;

/*
* This GameState is responsible for a little delay between all actions
* in the game. Feels way better with 0.5 seconds delay.
*/
class WaitGameState : public GameState
{
public:
	WaitGameState(GameManager& manager, nextStatePtr nextState);
	void execute() override;
	void draw(float dt) override;

private:

	nextStatePtr m_nextState;
	float m_waitTime;
};