#pragma once
#include "ButtonCommand/ButtonCommand.h"

class PVPCommand : public ButtonCommand
{
public:
	PVPCommand() {};

	void execute() override;
};