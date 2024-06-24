#pragma once
#include "Utilities.h"

class Controller
{
public:
	Controller(Color color) : m_color(color){};
	virtual ~Controller() {};
	virtual Move playTurn() = 0;
	virtual bool turnReady() = 0;

protected:
	Color m_color;
};