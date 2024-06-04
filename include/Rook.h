#pragma once

#include "Pieces.h"

class Rook : public Pieces {
public:
	Rook(sf::Texture& image, sf::Vector2f position, Color side);
	int getValue()const;
	virtual bool isValid(const int squares[], const int target)const override;
	virtual std::vector<std::pair<int, int>> possibleMoves(Board*)const override;
private:
	bool m_moved;
};