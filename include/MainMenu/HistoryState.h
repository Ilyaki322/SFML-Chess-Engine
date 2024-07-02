#pragma once
#include "MainMenu/Menu.h"
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "Assets.h"

#include <memory>
#include <vector>

class StateMachine;

typedef std::unique_ptr<Button> buttonPtr;

/*
* This class manages the review menu.
* It reads from a text file games that have already been played
* and call to game manager with the review state to start reviewing
*/

class HistoryState : public Menu
{
public:
	HistoryState(sf::RenderWindow& window, StateMachine& stateMachine, sf::Texture& texture, std::string name);

	void draw() override;

private:
	void handleMouseClick(sf::Event& event) override;

	void load10Games();
	void startReview(const int game);

	std::vector<buttonPtr> m_games;
	int m_page;

	buttonPtr m_pageUp;
	buttonPtr m_pageDown;
};