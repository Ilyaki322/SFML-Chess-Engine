#pragma once
#include "Pieces.h" // for MOVE struct AND Color ENUM, change later


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