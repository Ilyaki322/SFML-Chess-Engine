#pragma once
#include "Pieces.h" // for MOVE struct AND Color ENUM, change later


class Controller
{
public:

	Controller(Color color) : m_color(color){};
	virtual bool playTurn(Move& move) = 0;

private:



protected:

	Color m_color;
};