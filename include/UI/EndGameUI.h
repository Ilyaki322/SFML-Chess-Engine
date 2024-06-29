#pragma once
#include "PlayUI.h"
#include <memory>

class EndGameUI : public PlayUI
{
public:
	EndGameUI(StateMachine& stateMachine , std::string winner);
	void draw(sf::RenderWindow& window) override;
	void initButtons(GameManager& manager) override;
	virtual void buttonClicked(const sf::Vector2f& loc)override;

private:
	sf::Sprite m_endGamePic;
};