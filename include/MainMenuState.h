#pragma once
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
	MainMenuState(sf::RenderWindow& window, StateMachine& state);
	virtual ~MainMenuState() {};

	void draw() override;
	void handleEvents() override;

private:

	void handleMouseClick(sf::Event& event) override;

	sf::Text m_text[3];
};