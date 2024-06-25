#pragma once
#include "PlayUI.h"


class GameUI : public PlayUI
{
public:
	GameUI(StateMachine& stateMachine);

	void draw(sf::RenderWindow& window) override;
	void initButtons(GameManager& manager) override;
};