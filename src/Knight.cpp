#include "Knight.h"
#include "Board.h"


Knight::Knight(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side) {}


int Knight::getValue() const
{
	return 3;
}


std::vector<Move> Knight::generateMoves(const int squares[]) const
{
	std::vector<Move> move;
	int pos = getPosition();
	
	if (pos % 8 != 0 && pos + 16 < 64) checkDirection(move, pos, (2*DOWN) + LEFT);
	if (pos % 8 != 7 && pos + 16 < 64) checkDirection(move, pos, (2*DOWN) + RIGHT);
	if (pos - 16 > 0 && pos % 8 != 7) checkDirection(move, pos, (2*UP) + RIGHT);
	if (pos - 16 > 0 && pos % 8 != 0) checkDirection(move, pos, (2*UP) + LEFT);
	if (pos % 8 > 1 && pos + 8 < 64) checkDirection(move, pos, (2*LEFT) + DOWN);
	if (pos % 8 > 1 && pos - 8 > 0) checkDirection(move, pos, (2*LEFT) + UP);
	if (pos % 8 < 6 && pos - 8 > 0) checkDirection(move, pos, (2*RIGHT) + UP);
	if (pos % 8 < 6 && pos + 8 < 64) checkDirection(move, pos, (2*RIGHT) + DOWN);
	
	return move;
}

void Knight::checkDirection(std::vector<Move>& move, const int pos, const int direction) const
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
