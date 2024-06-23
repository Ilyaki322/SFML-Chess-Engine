#pragma once

#include "MenuState.h"

class PlayMenuState : public MenuState
{
public:
	PlayMenuState(sf::RenderWindow& window, StateMachine& state);
	virtual ~PlayMenuState() {};

	virtual void draw() override;
	virtual void handleEvents() override;

private:

	void handleMouseClick(sf::Event& event) override;
	void setText(sf::Text& text, sf::Color color, sf::Vector2f pos);

	sf::Text m_exit;
	sf::Text m_PvP[3];
	sf::Text m_PvB[3];
	sf::Text m_BvP[3];
	//sf::Text m_BvB?
	sf::Text m_Puzzle;
};