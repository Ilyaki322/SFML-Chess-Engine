#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side) {}


int Bishop::getValue() const
{
	return 0;
}


std::vector<Move> Bishop::generateMoves(const int squares[]) const
{
	std::vector<Move> moves;
	slidingMoves(squares, BOT_LEFT, moves);
	slidingMoves(squares, BOT_RIGHT, moves);
	slidingMoves(squares, TOP_LEFT, moves);
	slidingMoves(squares, TOP_RIGHT, moves);

	return moves;
}
