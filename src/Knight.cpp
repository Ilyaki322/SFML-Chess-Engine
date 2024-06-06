#include "Knight.h"
#include "Board.h"
#include "iostream"
Knight::Knight(sf::Texture& image, sf::Vector2f position, Color side)
	:Pieces(image, position, side)
{
}

int Knight::getValue() const
{
	return 3;
}

bool Knight::isValid(const int squares[], const int target) const
{
	int pos = getPosition();

	if (Board::instance().isOccupied(target) &&
		Board::instance().getPieceAt(target).getColor() == getColor()) return false;

	if (pos + DOWN * 2 + RIGHT == target) return true;
	if (pos + DOWN * 2 + LEFT == target) return true;
	if (pos + RIGHT * 2 + DOWN == target) return true;
	if (pos + RIGHT * 2 + UP == target) return true;
	if (pos + LEFT * 2 + UP == target) return true;
	if (pos + LEFT * 2 + DOWN == target) return true;
	if (pos + UP * 2 + RIGHT == target) return true;
	if (pos + UP * 2 + LEFT == target) return true;

	return false;
}

std::vector<std::pair<int, int>> Knight::possibleMoves(Board*) const
{
	return std::vector<std::pair<int, int>>();
}

std::vector<Move> Knight::generateMoves(const int squares[]) const
{
	std::vector<Move> move;

	int pos = getPosition();
	std::cout << pos + DOWN * 2 + RIGHT;
	if ((pos + DOWN * 2 + RIGHT > -1 && pos + DOWN * 2 + RIGHT<64)&&(
		!Board::instance().isOccupied(pos + DOWN * 2 + RIGHT) ||
		Board::instance().getPieceAt(pos + DOWN * 2 + RIGHT).getColor() != getColor()))
			move.push_back({pos,pos + DOWN * 2 + RIGHT });

	if ((pos + DOWN * 2 + LEFT > -1 && pos + DOWN * 2 + LEFT < 64) &&(
		!Board::instance().isOccupied(pos + DOWN * 2 + LEFT) ||
		Board::instance().getPieceAt(pos + DOWN * 2 + LEFT).getColor() != getColor()))
			move.push_back({ pos,pos + DOWN * 2 + LEFT });

	if ((pos + RIGHT * 2 + DOWN > -1 && pos + RIGHT * 2 + DOWN < 64) &&(
		!Board::instance().isOccupied(pos + RIGHT * 2 + DOWN) ||
		Board::instance().getPieceAt(pos + RIGHT * 2 + DOWN).getColor() != getColor()))
			move.push_back({ pos,pos + RIGHT * 2 + DOWN });

	if ((pos + RIGHT * 2 + UP > -1 && pos + RIGHT * 2 + UP < 64) &&(
		!Board::instance().isOccupied(pos + RIGHT * 2 + UP) ||
		Board::instance().getPieceAt(pos + RIGHT * 2 + UP).getColor() != getColor()))
			move.push_back({ pos,pos + RIGHT * 2 + UP });

	if ((pos + LEFT * 2 + UP > -1 && pos + LEFT * 2 + UP < 64) &&(
		!Board::instance().isOccupied(pos + LEFT * 2 + UP) ||
		Board::instance().getPieceAt(pos + LEFT * 2 + UP).getColor() != getColor()))
			move.push_back({ pos,pos + LEFT * 2 + UP });

	if ((pos + LEFT * 2 + DOWN > -1 && pos + LEFT * 2 + DOWN < 64) &&(
		!Board::instance().isOccupied(pos + LEFT * 2 + DOWN) ||
		Board::instance().getPieceAt(pos + LEFT * 2 + DOWN).getColor() != getColor()))
			move.push_back({ pos,pos + LEFT * 2 + DOWN });

	if ((pos + UP * 2 + RIGHT > -1 && pos + UP * 2 + RIGHT < 64) &&(
		!Board::instance().isOccupied(pos + UP * 2 + RIGHT) ||
		Board::instance().getPieceAt(pos + UP * 2 + RIGHT).getColor() != getColor()))
			move.push_back({ pos,pos + UP * 2 + RIGHT });

	if ((pos + UP * 2 + LEFT > -1 && pos + UP * 2 + LEFT < 64) &&(
		!Board::instance().isOccupied(pos + UP * 2 + LEFT) ||
		Board::instance().getPieceAt(pos + UP * 2 + LEFT).getColor() != getColor()))
		move.push_back({ pos,pos + UP * 2 + LEFT });


	return move;


}
