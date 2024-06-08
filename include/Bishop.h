#pragma once
#include "Pieces.h"

class Bishop : public Pieces {
public:

	Bishop(sf::Texture& image, sf::Vector2f position, Color side);

	int getValue()const;

	std::vector<Move> generateMoves() const override;

private:
};