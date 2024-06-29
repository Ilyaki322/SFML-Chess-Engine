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
	m_sideGameStatus.loadFromFile("game_status.png");
	m_capture.loadFromFile("capture.wav");
	m_move.loadFromFile("move.wav");


	m_blackplayer.loadFromFile("blackplayer.png");
	m_blackwon.loadFromFile("blackwon.png");
	m_draw.loadFromFile("draw.png");
	m_magnus.loadFromFile("magnus.png");
	m_next.loadFromFile("next.png");
	m_prev.loadFromFile("prev.png");
	m_rematch.loadFromFile("rematch.png");
	m_review.loadFromFile("review.png");
	m_undo.loadFromFile("undo.png");
	m_whiteplayer.loadFromFile("whiteplayer.png");
	m_whitewon.loadFromFile("whitewon.png");
	m_pageup.loadFromFile("pageup.png");
	m_pagedown.loadFromFile("pagedown.png");

	m_UIMap["blackplayer"] = m_blackplayer;
	m_UIMap["blackwon"] = m_blackwon;
	m_UIMap["draw"] =  m_draw;
	m_UIMap["magnus"] =m_magnus;
	m_UIMap["next"] = m_next;
	m_UIMap["prev"] = m_prev;
	m_UIMap["rematch"] = m_rematch;
	m_UIMap["review"] =m_review;
	m_UIMap["undo"] = m_undo;
	m_UIMap["whiteplayer"] = m_whiteplayer;
	m_UIMap["whitewon"] = m_whitewon;
	m_UIMap["pageup"] = m_pageup;
	m_UIMap["pagedown"] = m_pagedown;



	m_mainMenu.loadFromFile("MainMenu.jpg");
	m_playMenu.loadFromFile("PlayMenu.jpg");
	m_puzzleMenu.loadFromFile("PuzzleMenu.jpg");
	m_historyMenu.loadFromFile("History.jpg");

	m_menusMap['m'] = m_mainMenu;
	m_menusMap['p'] = m_playMenu;
	m_menusMap['z'] = m_puzzleMenu;
	m_menusMap['h'] = m_historyMenu;

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

	case 's':
		return m_sideGameStatus;
	}

	// add exception here?
}

sf::Texture& Assets::getUITexture(const std::string name)
{
	return m_UIMap[name];
}

sf::Texture& Assets::getMenu(const char c)
{
	// exception?
	return m_menusMap[c];
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