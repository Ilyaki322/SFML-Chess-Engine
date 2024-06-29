#include "Button.h"
#include "Assets.h"


Button::Button(std::string text, commandPtr command,
	           sf::Vector2f size, sf::Vector2f pos)
	: m_box(size), m_command(std::move(command)),m_pic(false)
{
	m_box.setOrigin(m_box.getGlobalBounds().width / 2, m_box.getGlobalBounds().height / 2 - 5);
	m_box.setPosition(pos);
	m_box.setFillColor(sf::Color(100, 100, 100, 0));
	m_box.setOutlineColor(sf::Color::Red);
	m_box.setOutlineThickness(1.f);

	m_text.setString(text);
	m_text.setCharacterSize(20);
	m_text.setFont(Assets::instance().getFont());
	m_text.setFillColor(sf::Color::White);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_text.setPosition(m_box.getPosition());
}

Button::Button(commandPtr command, sf::Vector2f size, sf::Vector2f pos)
	: m_box(size), m_command(std::move(command)), m_pic(false)
{
	m_box.setOrigin(m_box.getGlobalBounds().width / 2, m_box.getGlobalBounds().height / 2 - 5);
	m_box.setPosition(pos);
	m_box.setFillColor(sf::Color(125, 125, 125, 0));

	m_text.setString(" ");
	m_text.setFont(Assets::instance().getFont());
	m_text.setFillColor(sf::Color::Black);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_text.setPosition(m_box.getPosition());
}

Button::Button(sf::Sprite& pic, commandPtr command,sf::Vector2f pos)
	: m_sprite(pic), m_box(sf::Vector2f(pic.getTexture()->getSize())), m_command(std::move(command)), m_pic(true)
{
	m_box.setPosition(pos);
	m_sprite.setPosition(pos);
}

sf::FloatRect Button::getGlobalBounds()
{
	return m_box.getGlobalBounds();
}

void Button::draw(sf::RenderWindow& window)
{
	if (m_pic) {
		window.draw(m_sprite);
		return;
	}

	window.draw(m_box);
	window.draw(m_text);
}

void Button::click()
{
	m_command->execute();
}
