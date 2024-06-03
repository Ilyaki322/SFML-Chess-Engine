#pragma once

#include "Pieces.h"

class King : public Pieces {
public:
	King(sf::Texture& image, sf::Vector2f position, Color side);
	int getValue()const;
	virtual bool isValid(const int squares[], const int target)const override;
	virtual std::vector<std::pair<int, int>> possibleMoves(Board*)const override;
	virtual std::vector<Move> generateMoves(const int squares[]) const override { return std::vector<Move>(); }; ///// CHANGE THIS
private:
};