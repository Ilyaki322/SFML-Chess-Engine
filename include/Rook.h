#pragma once
#include "Pieces.h"

class Rook : public Pieces {
public:

	Rook(sf::Texture& image, sf::Vector2f position, Color side);

	int getValue()const;
	
	virtual std::vector<Move> generateMoves(const int squares[]) const override;

private:

	bool m_moved;
};