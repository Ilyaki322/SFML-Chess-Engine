#pragma once

#include <string>
#include <array>
#include <memory>

class Pieces;

class Board
{
public:
	Board(std::string FENstring);

	Pieces& getPieceAt(const int x, const int y);
	const Pieces& getPieceAt(const int x, const int y) const;
	bool isOccupied(const int x, const int y) const;


//====================================================

private:
	std::array<std::array<std::shared_ptr<Pieces>,8>, 8> m_pieces;
};