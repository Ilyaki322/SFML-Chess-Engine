#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "MainMenu/MenuState.h"
#include "MainMenu/StateMachine.h"

/*This class executes a next state command*/
class NextStateCommand : public ButtonCommand
{
public:
	NextStateCommand(StateMachine& machine, std::string nextState);

	void execute() override;

private:
	const std::string m_nextState;
};