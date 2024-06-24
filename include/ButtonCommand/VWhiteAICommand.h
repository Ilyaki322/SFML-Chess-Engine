#pragma once
#include "ButtonCommand/ButtonCommand.h"


class VWhiteAICommand : public ButtonCommand
{
public:
	VWhiteAICommand() {};

	void execute() override;
};