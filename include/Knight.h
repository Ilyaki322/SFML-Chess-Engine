#pragma once
#include "Pieces.h"

class Knight : public Pieces {
public:

	Knight(sf::Texture& image, sf::Vector2f position, Color side);

	int getValue()const;
	
	virtual std::vector<Move> generateMoves(const int squares[]) const override;

private:

	void checkDirection(std::vector<Move>& move, const int pos, const int direction) const;
};