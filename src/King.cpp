#include "King.h"
#include "Board.h"

King::King(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side)  , m_moved(false) {}


int King::getValue() const
{
	return 0;
}


std::vector<Move> King::generateMoves(const int squares[]) const
{
	std::vector<Move> move;
	int pos = getPosition();

	if (pos % 8 != 0) checkDirection(move, pos, LEFT);
	if (pos % 8 != 7) checkDirection(move, pos, RIGHT);
	if (pos - 8 > 0) checkDirection(move, pos, UP);
	if (pos + 8 < 63) checkDirection(move, pos, DOWN);

	checkCorner(move, pos, TOP_LEFT);
	checkCorner(move, pos, TOP_RIGHT);
	checkCorner(move, pos, BOT_LEFT);
	checkCorner(move, pos, BOT_RIGHT);

	return move;
}


void King::checkDirection(std::vector<Move>& move, const int pos, const int direction) const
{
	if (!Board::instance().isOccupied(pos + direction))
	{
		move.push_back({ pos, pos + direction });
		return;
	}

	if (Board::instance().instance().getPieceAt(pos + direction).getColor() != m_side)
	{
		move.push_back({ pos, pos + direction });
	}
}


void King::checkCorner(std::vector<Move>& move, const int pos, const int corner) const
{
	if (pos + corner < 0 || pos + corner > 63) return;
	if (pos % 8 == 0 && (corner == TOP_LEFT || corner == BOT_LEFT)) return;
	if (pos % 8 == 7 && (corner == TOP_RIGHT || corner == BOT_RIGHT)) return;
	if (pos - 8 < 0  && (corner == TOP_RIGHT || corner == TOP_LEFT)) return;
	if (pos + 8 > 63  && (corner == BOT_LEFT || corner == BOT_RIGHT)) return;

	checkDirection(move, pos, corner);
}
