#include "Queen.h"

Queen::Queen(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side) {}


int Queen::getValue() const
{
	return 0;
}


std::vector<Move> Queen::generateMoves(const int squares[]) const
{
	std::vector<Move> moves;
	slidingMoves(squares, BOT_LEFT, moves);
	slidingMoves(squares, BOT_RIGHT, moves);
	slidingMoves(squares, TOP_LEFT, moves);
	slidingMoves(squares, TOP_RIGHT, moves);
	slidingMoves(squares, UP, moves);
	slidingMoves(squares, DOWN, moves);
	slidingMoves(squares, LEFT, moves);
	slidingMoves(squares, RIGHT, moves);

	return moves;
}
