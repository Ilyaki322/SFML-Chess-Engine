#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "UI/PuzzleUI.h"

/*This class executes a undo command in puzzle*/

class UndoPuzzleCommand :public ButtonCommand {
public:
	UndoPuzzleCommand(StateMachine& stateMachine,PuzzleUI& puzzle, GameManager& manager);
	virtual void execute() override;

private:
	PuzzleUI& m_puzzle;
	GameManager& m_manager;
};