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
	bool clickedOnCorrectPiece(sf::Vector2f pos, Color);

	void colorTiles(int tile, const sf::Color& color);
	void resetTileColors();
	void updateBoard();
	//void makeMove(Move move);

private:

	void initTiles();
	
	std::array<std::unique_ptr<Tile>, SIZE> m_tiles;
	NBoard& m_BoardRef;

	/*int hui[64] = { 0,0,0,0,0,0,0,0,
				   0,18,17,18,19,18,20,0,
				   0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,
				   0,10,9,10,11,10,0,0,
				   0,0,0,0,0,0,0,0, };*/
};