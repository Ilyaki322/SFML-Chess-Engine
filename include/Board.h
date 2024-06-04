#pragma once

#include <string>
#include <array>
#include <memory>

class Pieces;

#include "Tile.h"

class Board
{
public:
	static Board& instance();
	Pieces& getPieceAt(const int x, const int y);
	const Pieces& getPieceAt(const int x, const int y) const;
	bool isOccupied(const int x, const int y) const;
	bool handleFirstClick(sf::Vector2f location);
	void handleSecondClick(sf::Vector2f source , sf::Vector2f target);
	void draw(sf::RenderWindow& window);
	void setBoard(std::string FENstring);

//====================================================

private:
	void initTiles();
	std::array<std::array<std::shared_ptr<Tile>, 8>, 8> m_tiles;
	Board(std::string FENstring = "RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");
	int m_square[64];
};