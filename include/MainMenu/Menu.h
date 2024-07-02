#pragma once
#include "MainMenu/MenuState.h"
#include "Button.h"
#include "SFML/Graphics.hpp"

#include <memory>
#include <vector>
#include <string>

typedef std::unique_ptr<Button> buttonPtr;

/*
* This class represents the game menus and holds the buttons with the 
* relevant commands.
*/

class Menu : public MenuState
{
public:
	Menu(sf::RenderWindow& window, StateMachine& state, sf::Texture& texture, std::string name = " ");
	virtual ~Menu() {};

	virtual void draw() override;
	void handleEvents() override;

	void addButton(buttonPtr button);
	std::string getName() const;

protected:
	virtual void handleMouseClick(sf::Event& event) override;

	std::vector<buttonPtr> m_buttons;
	sf::Sprite m_menuSprite;
	const std::string m_name;
};