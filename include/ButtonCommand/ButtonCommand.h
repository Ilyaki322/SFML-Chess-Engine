#pragma once

class ButtonCommand
{
public:
	virtual ~ButtonCommand() {};
	virtual void execute() = 0;
};