#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "MainMenu/MenuState.h"
#include "MainMenu/StateMachine.h"

class NextStateCommand : public ButtonCommand
{
public:
	NextStateCommand(StateMachine& machine, std::string nextState);

	void execute() override;

private:
	const std::string m_nextState;
};