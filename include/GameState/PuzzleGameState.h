#pragma once
#include "GameState.h"
#include "PuzzleManager.h"
#include "Controllers/Controller.h"
#include <memory>

/*
* we can split this into 2 or leave it as 1.
* will do both player turn and pc turn just as we did before
* but will get a reference to PuzzleManager and get its next moves from there.
*/
class PuzzleGameState : public GameState
{
public:
	PuzzleGameState(Color color, PuzzleManager& puzzle ,GameManager& manager);
	virtual void execute()override;
	virtual void draw(float dt)override;
private:

	bool correctMove();
	void playComputerMove();

	Move m_playerLastMove;
	Controller* m_player;
	PuzzleManager& m_puzzleManager;
	bool m_computerTurn;
};