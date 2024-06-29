#pragma once
#include "PlayUI.h"
#include <memory>

class ReviewUI : public PlayUI
{
public:
	ReviewUI(StateMachine& stateMachine);
	void draw(sf::RenderWindow& window) override;
	void initButtons(GameManager& manager) override;
	virtual void buttonClicked(const sf::Vector2f& loc)override;

private:
};