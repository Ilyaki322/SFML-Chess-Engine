#pragma once
class StateMachine;
class ButtonCommand
{
public:
	ButtonCommand(StateMachine& stateMachine):m_stateMachine(stateMachine){}
	virtual ~ButtonCommand() {};
	virtual void execute() = 0;
protected:
	StateMachine& m_stateMachine;
};