#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "MainMenu/MenuState.h"

class StateMachine;

//typedef std::unique_ptr<MenuState> statePtr;
typedef std::shared_ptr<MenuState> statePtr;

class NextStateCommand : public ButtonCommand
{
public:
	NextStateCommand(StateMachine& machine, statePtr nextState);

	void execute() override;

private:
	statePtr m_nextState;
};