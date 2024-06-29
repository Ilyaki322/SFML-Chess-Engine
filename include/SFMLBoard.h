#pragma once
#include "SFML/Audio.hpp"
#include "Utilities.h"
#include "Tile.h"

#include <array>
#include <memory>
#include <vector>

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
	void playBoardSound(const Move& move);
	void updateCaptured(const Move& move);
	
	std::vector<SFMLPiece> m_capturedWhitePieces;
	std::vector<SFMLPiece> m_capturedBlackPieces;
	std::array<std::unique_ptr<Tile>, SIZE> m_tiles;
	NBoard& m_BoardRef;

	sf::Sound m_move;
	sf::Sound m_capture;
};