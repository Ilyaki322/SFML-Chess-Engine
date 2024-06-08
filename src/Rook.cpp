#include "Rook.h"


Rook::Rook(sf::Texture& image, sf::Vector2f position, Color side)
    :Pieces(image, position, side), m_moved(false) {}


int Rook::getValue() const
{
    return 5;
}


std::vector<Move> Rook::generateMoves() const
{
	std::vector<Move> moves;
	slidingMoves(UP, moves);
	slidingMoves(DOWN, moves);
	slidingMoves(LEFT, moves);
	slidingMoves(RIGHT, moves);

	return moves;
}