#pragma once
#include "PlayUI.h"
#include <memory>


class GameUI : public PlayUI
{
public:
	GameUI(StateMachine& stateMachine,sf::Sprite &p1 , sf::Sprite &p2);
	void draw(sf::RenderWindow& window) override;
	void initButtons(GameManager& manager) override;
	virtual void buttonClicked(const sf::Vector2f& loc)override;
private:
	sf::Sprite m_player1;
	sf::Sprite m_player2;
};