#pragma once
#include "GameState/GameState.h"
#include <memory>

typedef std::unique_ptr<GameState> nextStatePtr;

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