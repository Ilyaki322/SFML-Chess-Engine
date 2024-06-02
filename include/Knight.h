#pragma once

#include "Pieces.h"

class Knight : public Pieces {
public:
	Knight(sf::Texture& image, sf::Vector2f position, Color side);
	int getValue()const;
	virtual bool isValid()const override;
	virtual std::vector<std::pair<int, int>> possibleMoves(Board*)const override;
private:
};