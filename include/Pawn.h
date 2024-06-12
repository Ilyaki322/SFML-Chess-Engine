#pragma once
#include "Pieces.h"

class Pawn : public Pieces {
public:

	Pawn(sf::Texture &image, sf::Vector2f position, Color side, char symbol);

	int getValue()const;

	std::vector<Move> generateMoves() const override;

private:

	int m_firstMoveFlag;
};