#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "ButtonCommand/ButtonCommand.h"

typedef std::unique_ptr<ButtonCommand> commandPtr;

class Button
{
public:
	Button(std::string text, commandPtr command, sf::Vector2f size, sf::Vector2f pos);
	Button(commandPtr command, sf::Vector2f size, sf::Vector2f pos);

	sf::FloatRect getGlobalBounds();

	void draw(sf::RenderWindow& window);
	void click();

private:

	sf::Text m_text;
	sf::RectangleShape m_box;

	commandPtr m_command;
};