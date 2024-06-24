#include "Button.h"
#include "Assets.h"


Button::Button(std::string text, commandPtr command,
	           sf::Vector2f size, sf::Vector2f pos)
	: m_box(size), m_command(std::move(command))
{
	m_box.setOrigin(m_box.getGlobalBounds().width / 2, m_box.getGlobalBounds().height / 2 - 5);
	m_box.setPosition(pos);
	m_box.setFillColor(sf::Color(125, 125, 125, 200));

	m_text.setString(text);
	m_text.setFont(Assets::instance().getFont());
	m_text.setFillColor(sf::Color::Black);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_text.setPosition(m_box.getPosition());
}

Button::Button(commandPtr command, sf::Vector2f size, sf::Vector2f pos)
	: m_box(size), m_command(std::move(command))
{
	m_box.setOrigin(m_box.getGlobalBounds().width / 2, m_box.getGlobalBounds().height / 2 - 5);
	m_box.setPosition(pos);
	m_box.setFillColor(sf::Color(125, 125, 125, 200));

	m_text.setString(" ");
	m_text.setFont(Assets::instance().getFont());
	m_text.setFillColor(sf::Color::Black);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_text.setPosition(m_box.getPosition());
}

sf::FloatRect Button::getGlobalBounds()
{
	return m_box.getGlobalBounds();
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_box);
	window.draw(m_text);
}

void Button::click()
{
	m_command->execute();
}
