#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "ButtonCommand/ButtonCommand.h"

typedef std::unique_ptr<ButtonCommand> commandPtr;

/*
* This class represents a button in the game.
* It holds shape with position, size and command
*/

class Button
{
public:
	Button(std::string text, commandPtr command, sf::Vector2f size, sf::Vector2f pos);
	Button(commandPtr command, sf::Vector2f size, sf::Vector2f pos);
	Button(sf::Sprite &pic, commandPtr command, sf::Vector2f pos);

	sf::FloatRect getGlobalBounds();

	void draw(sf::RenderWindow& window);
	void click();

private:
	bool m_pic;
	sf::Text m_text;
	sf::RectangleShape m_box;
	sf::Sprite m_sprite;
	commandPtr m_command;
};