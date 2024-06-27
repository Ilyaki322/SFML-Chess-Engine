#include "MainMenu/Menu.h"
#include "Utilities.h"

#include <iostream>

Menu::Menu(sf::RenderWindow& window, StateMachine& state, sf::Texture& texture, std::string name)
	:MenuState(window, state), m_name(name)
{
	m_menuSprite.setTexture(texture);
	m_menuSprite.setScale(static_cast<float>(MENU_X) / texture.getSize().x, static_cast<float>(MENU_Y) / texture.getSize().y);
}

void Menu::draw()
{
	m_window.clear(sf::Color(125, 125, 125));
	m_window.draw(m_menuSprite);
	for (int i = 0; i < m_buttons.size(); i++) // for debug only
	{
		m_buttons[i]->draw(m_window);
	}
	m_window.display();
}

void Menu::handleEvents()
{
	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
			handleMouseClick(event);
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Menu::handleMouseClick(sf::Event& event)
{
	auto location =
		m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

	std::cout << location.x << " " << location.y << std::endl;

	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->getGlobalBounds().contains(location))
		{
			m_buttons[i]->click();
			return;
		}
	}
}

void Menu::addButton(buttonPtr button)
{
	m_buttons.push_back(std::move(button));
}

std::string Menu::getName() const
{
	return m_name;
}
