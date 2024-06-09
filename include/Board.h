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

	bool handleFirstClick(sf::Vector2f location, Color color);
	bool handleSecondClick(sf::Vector2f target, Move& move);
	void makeMove(Move move);

	void draw(sf::RenderWindow& window);
	void setBoard(std::string FENstring);
	void setRotation(const float rotation);

	std::vector<std::vector<Move>> AllMoves();

	void debug(sf::Color color, int i)
	{
		debugTiles[i]->setColor(color);
	}

//====================================================

private:

	Board();
	Board(const Board&) = default;
	Board& operator=(const Board&) = default;

	void initTiles();
	void castle(Move move);

	void undoMove(Move move);

	std::array <std::shared_ptr<Tile>, SIZE> m_tiles;
	std::array <std::shared_ptr<Tile>, SIZE> debugTiles; // for threat debug
	
	std::vector<Move> m_moves;
	std::shared_ptr<Pieces> m_temp;
};