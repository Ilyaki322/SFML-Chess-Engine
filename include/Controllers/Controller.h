#pragma once
#include "Utilities.h"

/*
* This is a base class for representing a chess player
*/
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