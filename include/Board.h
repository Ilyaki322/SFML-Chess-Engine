#pragma once

#include <string>
#include <array>
#include <memory>

class Pieces;

#include "Tile.h"

class Board
{
public:
	Board(std::string FENstring);

	Pieces& getPieceAt(const int x, const int y);
	const Pieces& getPieceAt(const int x, const int y) const;
	bool isOccupied(const int x, const int y) const;

	void draw(sf::RenderWindow& window);


//====================================================

private:

	void initTiles();
	std::array<std::array<std::shared_ptr<Tile>, 8>, 8> m_tiles;
};