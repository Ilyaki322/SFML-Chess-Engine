#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "MainMenu/StateMachine.h"

class GameManager;

class RematchCommand :public ButtonCommand {
public:
	RematchCommand(StateMachine& stateMachine, GameManager& manager);
	virtual void execute() override;

private:
	GameManager& m_manager;
};