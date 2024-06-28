#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
class Assets
{
public:

	static Assets& instance();

	sf::Texture& getTexture(const char c);
	sf::Texture& getUITexture(const std::string);
	sf::Texture& getMenu(const char c);
	sf::Font& getFont();
	sf::SoundBuffer& getSound(const char c);

private:

	Assets();
	Assets(const Assets&) = default;
	Assets& operator=(const Assets&) = default;

	std::map<char, sf::Texture> m_menusMap;
	std::map<std::string, sf::Texture> m_UIMap;

	sf::Texture m_WKnight;
	sf::Texture m_WKing;
	sf::Texture m_WQueen;
	sf::Texture m_WRook;
	sf::Texture m_WPawn;
	sf::Texture m_WBishop;

	sf::Texture m_BKnight;
	sf::Texture m_BBishop;
	sf::Texture m_BKing;
	sf::Texture m_BRook;
	sf::Texture m_BQueen;
	sf::Texture m_BPawn;
	sf::Texture m_sideGameStatus;

	sf::Texture m_mainMenu;
	sf::Texture m_playMenu;
	sf::Texture m_puzzleMenu;

	sf::Texture m_blackplayer;
	sf::Texture m_blackwon;
	sf::Texture m_draw;
	sf::Texture m_magnus;
	sf::Texture m_next;
	sf::Texture m_prev;
	sf::Texture m_rematch;
	sf::Texture m_review;
	sf::Texture m_undo;
	sf::Texture m_whiteplayer;
	sf::Texture m_whitewon;



	sf::SoundBuffer m_move;
	sf::SoundBuffer m_capture;

	sf::Font m_font;
};