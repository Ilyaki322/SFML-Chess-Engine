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
	bool handleSecondClick(sf::Vector2f target, Move& move);
	void makeMove(Move move);

	void draw(sf::RenderWindow& window);
	void setBoard(std::string FENstring);
	void setRotation(const float rotation);

//====================================================

private:
	Board();
	Board(const Board&) = default;
	Board& operator=(const Board&) = default;
	void addSpecialMoves(int index);
	void initTiles();

	std::array <std::shared_ptr<Tile>, SIZE> m_tiles;
	std::vector<Move> m_moves;
	
	int m_square[SIZE];
};