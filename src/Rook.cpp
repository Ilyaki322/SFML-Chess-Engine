#include "Rook.h"


Rook::Rook(sf::Texture& image, sf::Vector2f position, Color side)
    :Pieces(image, position, side), m_moved(false) {}


int Rook::getValue() const
{
    return 5;
}


std::vector<Move> Rook::generateMoves(const int squares[]) const
{
	std::vector<Move> moves;
	slidingMoves(squares, UP, moves);
	slidingMoves(squares, DOWN, moves);
	slidingMoves(squares, LEFT, moves);
	slidingMoves(squares, RIGHT, moves);

	return moves;
}