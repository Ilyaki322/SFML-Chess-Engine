#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "MainMenu/MenuState.h"
#include "MainMenu/StateMachine.h"

class NextStateCommand : public ButtonCommand
{
public:
	NextStateCommand(StateMachine& machine, Menus nextState);

	void execute() override;

private:
	Menus m_nextState;
};