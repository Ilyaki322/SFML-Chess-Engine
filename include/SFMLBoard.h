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
	bool clickedOnCorrectPiece(sf::Vector2f pos, Color);

	void colorTiles(int tile, sf::Color& color);
	void resetTileColors();

private:

	void initTiles();
	void initBoard(const int board[64]);

	std::array<std::unique_ptr<Tile>, SIZE> m_tiles;

	int hui[64] = { 0,0,0,0,0,0,0,0,
				   0,18,17,18,19,18,20,0,
				   0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,
				   0,10,9,10,11,10,0,0,
				   0,0,0,0,0,0,0,0, };
};