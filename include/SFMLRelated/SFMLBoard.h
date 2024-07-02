#pragma once
#include "SFML/Audio.hpp"
#include "Utilities.h"
#include "Tile.h"

#include <array>
#include <memory>
#include <vector>

class SFMLPiece;
class NBoard;

typedef std::unique_ptr<SFMLPiece> piecePtr;

/*
* This class represents the chessboard to the screen
* It draws the pieces in the appropriate position,
* colors the tiles based on actions,
* and plays sound based on last move.
*/

class SFMLBoard
{
public:
	SFMLBoard();

	void draw(sf::RenderWindow& window);
	bool clickedOnCorrectPiece(const int x, Color);

	void reset();
	void colorTiles(int tile, const sf::Color& color);
	void resetTileColors();

	void updateBoard();
	void makeMove();

	std::vector<piecePtr>& getCaptured(Color color);

private:

	void initTiles();
	void playBoardSound(const Move& move);
	void updateCaptured();
	
	std::vector<piecePtr> m_capturedWhitePieces;
	std::vector<piecePtr> m_capturedBlackPieces;
	std::array<std::unique_ptr<Tile>, SIZE> m_tiles;
	NBoard& m_BoardRef;

	sf::Sound m_move;
	sf::Sound m_capture;
};