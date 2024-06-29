#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "MainMenu/StateMachine.h"

/*
* This class executes a command to return to the main menu from the game manager
*/
class GameManager;

class BackToMenuCommand :public ButtonCommand {
public:
	BackToMenuCommand(StateMachine& stateMachine, GameManager &manager);
	virtual void execute() override;

private:
	GameManager& m_manager;
};