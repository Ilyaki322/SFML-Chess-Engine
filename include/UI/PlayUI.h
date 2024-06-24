#pragma once
#include "Utilities.h"
#include "Button.h"
#include "Assets.h"



class PlayUI {
public:
	PlayUI();
	virtual void draw(sf::RenderWindow& window) = 0 {
		window.draw(m_backGround);
	}
private:
	sf::Sprite m_backGround;
protected:
	std::vector<Button> m_button;
};