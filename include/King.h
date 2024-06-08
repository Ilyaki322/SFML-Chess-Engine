#pragma once
#include "Pieces.h"

class King : public Pieces {
public:

	King(sf::Texture& image, sf::Vector2f position, Color side);

	int getValue()const;
	
	virtual std::vector<Move> generateMoves() const override;

private:

	void checkDirection(std::vector<Move>& move, const int pos, const int direction) const;
	void checkCorner(std::vector<Move>& move, const int pos, const int corner) const;

	bool m_moved;
};