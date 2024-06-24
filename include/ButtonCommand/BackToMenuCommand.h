#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "MainMenu/StateMachine.h"
class GameManager;
class BackToMenuCommand :public ButtonCommand {
public:
	BackToMenuCommand(StateMachine& stateMachine,GameManager &manager);
	virtual void execute() override;
private:
	GameManager& m_manager;
};