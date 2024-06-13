#pragma once

#include "Utilities.h"
//#include "Tile.h"
//#include "SFMLPiece.h"

#include <array>
#include <memory>
#include <vector>

class Tile;
class SFMLPiece;

class SFMLBoard
{
public:
	SFMLBoard();

	void draw(sf::RenderWindow& window);

private:

	void initTiles();
	void initBoard(const int board[64]);

	std::array<std::unique_ptr<Tile>, SIZE> m_tiles;
	std::vector <std::unique_ptr<SFMLPiece>> m_pieces;
};