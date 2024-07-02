#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "UI/PuzzleUI.h"
#include "Managers/PuzzleManager.h"

/*This class executes a next puzzle command*/

class NextPuzzleCommand :public ButtonCommand {
public:
	NextPuzzleCommand(StateMachine& stateMachine, PuzzleManager& manager);
	virtual void execute() override;

private:
	PuzzleManager& m_manager;
};