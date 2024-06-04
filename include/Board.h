#pragma once

#include <string>
#include <array>
#include <memory>

class Pieces;

#include "Tile.h"
const int SIZE = 64;
class Board
{
public:
	static Board& instance();
	Pieces& getPieceAt(const int x);
	const Pieces& getPieceAt(const int x) const;
	bool isOccupied(const int x) const;
	bool handleFirstClick(sf::Vector2f location);
	void handleSecondClick(sf::Vector2f source , sf::Vector2f target);
	void draw(sf::RenderWindow& window);
	void setBoard(std::string FENstring);

//====================================================

private:
	void initTiles();
	std::array <std::shared_ptr<Tile>, SIZE> m_tiles;
	Board();
	int m_square[SIZE];
};