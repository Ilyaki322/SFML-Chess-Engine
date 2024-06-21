#pragma once
#include "GameState/GameState.h"

class PuzzleManager;

class WaitGameState : public GameState
{
public:
	WaitGameState(GameManager& manager, PuzzleManager& puzzleManager);
	void execute() override;
	void draw(float dt) override;

private:

	PuzzleManager& m_puzzleManager;
	float m_waitTime;
};