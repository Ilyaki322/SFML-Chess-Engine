#pragma once
#include "MainMenu/Menu.h"
#include "SFML/Graphics.hpp"
#include "Button.h"

#include <memory>
#include <vector>

class StateMachine;

typedef std::unique_ptr<Button> buttonPtr;

class HistoryState : public Menu
{
public:
	HistoryState(sf::RenderWindow& window, StateMachine& stateMachine, sf::Texture& texture, std::string name);

	void draw() override;

private:
	void handleMouseClick(sf::Event& event) override;

	void load10Games();

	std::vector<buttonPtr> m_games;
	int m_index;
};