#pragma once
#include "GameState.h"
#include "PuzzleManager.h"
#include "Controllers/Controller.h"
#include <memory>
#include "UI/PuzzleUI.h"

typedef std::shared_ptr<PuzzleUI> uiPuzzlePtr;
class PuzzleGameState : public GameState
{
public:
	PuzzleGameState(Color color, PuzzleManager& puzzle ,GameManager& manager, uiPuzzlePtr ui);
	virtual void execute()override;
	virtual void draw(float dt)override;
private:

	bool correctMove();
	void playComputerMove();

	Move m_playerLastMove;
	Controller* m_player;
	PuzzleManager& m_puzzleManager;
	bool m_computerTurn;
	bool m_waitingUndo;
	bool m_waitingNew;
	uiPuzzlePtr m_ui;
};