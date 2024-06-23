#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "MainMenu/MenuState.h"

class StateMachine;

typedef std::unique_ptr<MenuState> statePtr;

class NextStateCommand : public ButtonCommand
{
public:
	NextStateCommand(StateMachine& machine, statePtr nextState);

	void execute() override;

private:

	StateMachine& m_machine;
	statePtr m_nextState;
};