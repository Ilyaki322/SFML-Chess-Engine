#pragma once
#include "PlayUI.h"
#include <memory>
#include <map>
#include <SFMLRelated/SFMLBoard.h>

/*
* Represents the regular Chess gamemode UI.
* shows things like score, and captured pieces.
*/
class GameUI : public PlayUI
{
public:
	GameUI(StateMachine& stateMachine,sf::Sprite &p1 , sf::Sprite &p2,SFMLBoard &board);
	void draw(sf::RenderWindow& window) override;
	void initButtons(GameManager& manager) override;
	virtual void buttonClicked(const sf::Vector2f& loc)override;
private:
	sf::Sprite m_player1;
	sf::Sprite m_player2;

	sf::Text m_Bscore;
	sf::Text m_Wscore;

	int m_whiteScore;
	int m_blackScore;
	std::map<int, int> m_scoreMap;

	SFMLBoard& m_board;
};