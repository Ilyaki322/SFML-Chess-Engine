#pragma once
#include "MainMenu/MenuState.h"
#include "Button.h"
#include "SFML/Graphics.hpp"

#include <memory>
#include <vector>

typedef std::unique_ptr<Button> buttonPtr;

class Menu : public MenuState
{
public:
	Menu(sf::RenderWindow& window, StateMachine& state, sf::Texture& texture);
	virtual ~Menu() {};

	void draw() override;
	void handleEvents() override;

	void addButton(buttonPtr button);

private:

	void handleMouseClick(sf::Event& event) override;

	std::vector<buttonPtr> m_buttons;
	sf::Sprite m_menuSprite;
};