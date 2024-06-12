#pragma once

#include <string>
#include <array>
#include <memory>
#include <unordered_set>
#include "Tile.h"
#include "Utilities.h"

class Pieces;

class Board
{
public:
	static Board& instance();
	void printAllMoves();
	Pieces& getPieceAt(const int x);
	const Pieces& getPieceAt(const int x) const;
	std::shared_ptr<Pieces> getPiece(const int x);
	bool isOccupied(const int x) const;

	bool handleFirstClick(sf::Vector2f location, Color color);
	bool handleSecondClick(sf::Vector2f target, Move& move);

	void makeMove(Move move);
	void fakeMove(Move move);
	void undoMove(Move move);


	void draw(sf::RenderWindow& window);
	void setBoard(std::string FENstring);
	void setRotation(const float rotation);
	std::vector<std::vector<Move>> AllMoves();
	std::vector<std::vector<Move>> allMovesOf(int color);


//====================================================

private:

	Board();
	Board(const Board&) = default;
	Board& operator=(const Board&) = default;
	void initTiles();

	void castle(Move move);
	void promotion(Move move);

	std::array <std::shared_ptr<Tile>, SIZE> m_tiles;
	
	std::vector<Move> m_moves;
	std::shared_ptr<Pieces> m_temp;

	int testAllMoves(int i, int num , bool white = true);
};