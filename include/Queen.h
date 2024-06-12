#pragma once
#include "Pieces.h"

class Queen : public Pieces {

public:

	Queen(sf::Texture& image, sf::Vector2f position, Color side, char symbol);

	int getValue()const;
	
	std::vector<Move> generateMoves() const override;

private:

};