#pragma once
#include "Pieces.h"

class Pawn : public Pieces {
public:

	Pawn(sf::Texture &image, sf::Vector2f position, Color side);

	int getValue()const;

	std::vector<Move> generateMoves(const int squares[]) const override;

	void setPosition(sf::Vector2f pos) override;

private:

	int m_firstMoveFlag;
};