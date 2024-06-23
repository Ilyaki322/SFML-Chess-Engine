#pragma once
#include "MenuState.h"
#include "Button.h"

#include <memory>

typedef std::unique_ptr<Button> buttonPtr;

class MainMenuState : public MenuState
{
public:
	MainMenuState(sf::RenderWindow& window, StateMachine& state);
	virtual ~MainMenuState() {};

	void draw() override;
	void handleEvents() override;

private:

	void handleMouseClick(sf::Event& event) override;

	std::vector<buttonPtr> m_buttons;
};