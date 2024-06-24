#pragma once
#include "ButtonCommand/ButtonCommand.h"


class VBlackAICommand : public ButtonCommand
{
public:
	VBlackAICommand() {};

	void execute() override;
};