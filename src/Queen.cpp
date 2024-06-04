#include "Queen.h"
#include "Board.h"

Queen::Queen(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side) {}

int Queen::getValue() const
{
	return 0;
}

bool Queen::isValid(const int squares[], const int target) const
{
	int pos = getPosition();
	if (Board::instance().isOccupied(target) &&
		Board::instance().getPieceAt(target).getColor() == getColor()) return false;

	int up = pos + UP, down = pos + DOWN, left = pos + LEFT, right = pos + RIGHT,
		topRight = pos + TOP_RIGHT, topLeft = pos + TOP_LEFT, botLeft = pos + BOT_LEFT,
		botRight = pos + BOT_RIGHT;


	while (target >= down || target >= right || target <= up || target <= left ||
		target >= botLeft || target >= botRight || target <= topLeft || target <= topRight) {
		if (down < 64) {
			if (target == down) return true;
			if (Board::instance().isOccupied(down)) down = 64;
			down += DOWN;
		}
		if (right < 64) {
			if (target == right) return true;
			if (Board::instance().isOccupied(right)) right = 64;
			right += RIGHT;
		}
		if (botLeft < 64) {
			if (target == botLeft) return true;
			if (Board::instance().isOccupied(botLeft)) botLeft = 64;
			botLeft += BOT_LEFT;
			
		}
		if (botRight < 64) {
			if (target == botRight) return true;
			if (Board::instance().isOccupied(botRight)) botRight = 64;
			botRight += BOT_RIGHT;
		}
		if (up > -1) {
			if (target == up) return true;
			if (Board::instance().isOccupied(up)) up = - 1;
			up += UP;
		}
		if (left > -1) {
			if (target == left) return true;
			if (Board::instance().isOccupied(left)) left =  - 1;
			left += LEFT;
		}
		if (topLeft > -1) {
			if (target == topLeft) return true;
			if (Board::instance().isOccupied(topLeft)) topLeft =  - 1;
			topLeft += TOP_LEFT;
		}
		if (topRight > -1) {
			if (target == topRight) return true;
			if (Board::instance().isOccupied(topRight)) topRight = - 1;
			topRight += TOP_RIGHT;
		}
	}
	return false;
}

std::vector<std::pair<int, int>> Queen::possibleMoves(Board*) const
{
	return std::vector<std::pair<int, int>>();
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
