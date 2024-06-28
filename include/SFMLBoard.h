#pragma once

#include "Utilities.h"
#include "Tile.h"
//#include "SFMLPiece.h"

#include <array>
#include <memory>
#include <vector>

//class Tile;
class SFMLPiece;
class NBoard;

class SFMLBoard
{
public:
	SFMLBoard();

	void draw(sf::RenderWindow& window);
	bool clickedOnCorrectPiece(const int x, Color);

	void colorTiles(int tile, const sf::Color& color);
	void resetTileColors();
	void updateBoard();

private:

	void initTiles();
	
	std::array<std::unique_ptr<Tile>, SIZE> m_tiles;
	NBoard& m_BoardRef;
};