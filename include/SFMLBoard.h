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

class SFMLBoard
{
public:
	SFMLBoard(const bool useCaptrues = true);

	void draw(sf::RenderWindow& window);
	bool clickedOnCorrectPiece(const int x, Color);

	void reset();
	void colorTiles(int tile, const sf::Color& color);
	void resetTileColors();
	void updateBoard(bool fake = false);

private:

	void initTiles();
	void playBoardSound(const Move& move);
	void updateCaptured(const Move& move);
	
	std::vector<piecePtr> m_capturedWhitePieces;
	std::vector<piecePtr> m_capturedBlackPieces;
	std::array<std::unique_ptr<Tile>, SIZE> m_tiles;
	NBoard& m_BoardRef;

	sf::Sound m_move;
	sf::Sound m_capture;

	bool m_useCaptures;
};