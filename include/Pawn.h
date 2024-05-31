#pragma once

#include "Pieces.h"

class Pawn : public Pieces {
public:
	int getValue()const;
	virtual bool isValid()const override;
	virtual std::vector<std::pair<int, int>> possibleMoves(Board*)const override;
private:

};