#pragma once
#include "Pieces.h"

class Bishop : public Pieces {
public:

	Bishop(sf::Texture& image, sf::Vector2f position, Color side);

	int getValue()const;
	bool isValid(const int squares[], const int target ) const override;

	std::vector<std::pair<int, int>> possibleMoves(Board*) const override;
	std::vector<Move> generateMoves(const int squares[]) const override;

private:


};