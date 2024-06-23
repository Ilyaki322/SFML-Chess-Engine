#pragma once
#include "Utilities.h"
#include "Button.h"
#include "Assets.h"

/*
* this is a base class for the UI in the game/puzzle
* the class download the background pic and know to draw it 
* it holds button vector in protected vector so each of the
* game and puzzle can excute commands
*/

class PlayUI {
public:
	PlayUI();
	virtual void draw(sf::RenderWindow& window) = 0 {
		window.draw(m_backGround);
	}
	virtual std::vector<Button> getButton() = 0;
private:
	sf::Sprite m_backGround;
protected:
	std::vector<Button> m_button;
};