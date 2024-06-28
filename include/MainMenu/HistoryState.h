#pragma once
#include "MainMenu/MenuState.h"
#include "SFML/Graphics.hpp"
#include "Button.h"

#include <memory>
#include <array>

class StateMachine;

typedef std::unique_ptr<Button> buttonPtr;

class HistoryState : public MenuState
{
public:
	HistoryState(sf::RenderWindow& window, StateMachine& stateMachine);

	void draw() override;
	void handleEvents() override;

private:
	void handleMouseClick(sf::Event& event) override;

	buttonPtr m_exit;
	buttonPtr m_scrollDown;
	buttonPtr m_scrollUp;
	std::array<buttonPtr, 10> m_games;

};