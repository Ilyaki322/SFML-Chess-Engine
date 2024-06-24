#pragma once

#include "MenuState.h"
#include "Button.h"

typedef std::unique_ptr<Button> buttonPtr;

class PlayMenuState : public MenuState
{
public:
	PlayMenuState(sf::RenderWindow& window, StateMachine& state);
	virtual ~PlayMenuState() {};

	virtual void draw() override;
	virtual void handleEvents() override;

private:

	void handleMouseClick(sf::Event& event) override;
	
	std::vector<buttonPtr> m_buttons;
	sf::Sprite m_menuSprite;
};