#include "Assets.h"


Assets& Assets::instance()
{
	static Assets inst;
	return inst;
}


Assets::Assets()
{
	m_BBishop.loadFromFile("BBishop.png");
	m_BKing.loadFromFile("BKing.png");
	m_BKnight.loadFromFile("BKnight.png");
	m_BPawn.loadFromFile("BPawn.png");
	m_BQueen.loadFromFile("BQueen.png");
	m_BRook.loadFromFile("BRook.png");

	m_WBishop.loadFromFile("WBishop.png");
	m_WKing.loadFromFile("WKing.png");
	m_WKnight.loadFromFile("WKnight.png");
	m_WPawn.loadFromFile("WPawn.png");
	m_WQueen.loadFromFile("WQueen.png");
	m_WRook.loadFromFile("WRook.png");

	m_capture.loadFromFile("capture.wav");
	m_move.loadFromFile("move.wav");

	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}


sf::Font& Assets::getFont()
{
	return m_font;
}

sf::Texture& Assets::getTexture(const char c)
{
	bool isUpper = isupper(c);
	char piece = char(tolower(c));

	switch (piece)
	{
	case 'k':
		return isUpper ? m_BKing : m_WKing;

	case 'q':
		return isUpper ? m_BQueen : m_WQueen;

	case 'n':
		return isUpper ? m_BKnight : m_WKnight;

	case 'p':
		return isUpper ? m_BPawn : m_WPawn;

	case 'r':
		return isUpper ? m_BRook : m_WRook;

	case 'b':
		return isUpper ? m_BBishop : m_WBishop;
	}

	// add exception here?
}


sf::SoundBuffer& Assets::getSound(const char c)
{
	switch (c)
	{
	case 'm':
		return m_move;

	case 'c':
		return m_capture;
	}
	
	// add exception here?
}