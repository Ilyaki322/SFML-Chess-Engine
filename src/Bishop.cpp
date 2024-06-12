#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(sf::Texture& image, sf::Vector2f position, Color side, char symbol)
	:Pieces(image, position, side , symbol) {}


int Bishop::getValue() const
{
	return 0;
}


std::vector<Move> Bishop::generateMoves() const
{
	std::vector<Move> moves;
	slidingMoves(BOT_LEFT, moves);
	slidingMoves(BOT_RIGHT, moves);
	slidingMoves(TOP_LEFT, moves);
	slidingMoves(TOP_RIGHT, moves);

	return moves;
}
