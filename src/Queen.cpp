#include "Queen.h"

Queen::Queen(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side) {}


int Queen::getValue() const
{
	return 0;
}


std::vector<Move> Queen::generateMoves() const
{
	std::vector<Move> moves;
	slidingMoves(BOT_LEFT, moves);
	slidingMoves(BOT_RIGHT, moves);
	slidingMoves(TOP_LEFT, moves);
	slidingMoves(TOP_RIGHT, moves);
	slidingMoves(UP, moves);
	slidingMoves(DOWN, moves);
	slidingMoves(LEFT, moves);
	slidingMoves(RIGHT, moves);

	return moves;
}
