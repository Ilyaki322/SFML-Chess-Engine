#pragma once
#include "PlayUI.h"

class GameUI : public PlayUI {
public:
	GameUI();
	virtual void draw(sf::RenderWindow& window) override;
	virtual std::vector<Button> getButton() override;
private:

};