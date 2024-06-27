#include "Assets.h"
#include "MainMenu/PlayMenuState.h"
#include "MainMenu/StateMachine.h"
#include "MainMenu/MainMenuState.h"
#include "MainMenu/ButtonFactory.h"

PlayMenuState::PlayMenuState(sf::RenderWindow& window, StateMachine& state)
	: MenuState(window, state)
{
	sf::Texture& texture = Assets::instance().getMenu('p');
	m_menuSprite.setTexture(texture);
	m_menuSprite.setScale(static_cast<float>(MENU_X) / texture.getSize().x, static_cast<float>(MENU_Y) / texture.getSize().y);

	/*ButtonFactory theCreator(state, window);

	m_buttons.push_back(theCreator.createButton(VsPlayer, sf::Vector2f(270, 60), sf::Vector2f(186, 223)));
	m_buttons.push_back(theCreator.createButton(Exit, sf::Vector2f(190, 50), sf::Vector2f(140, 572)));
	m_buttons.push_back(theCreator.createButton(VsPlayer, sf::Vector2f(250, 60), sf::Vector2f(590, 181)));
	m_buttons.push_back(theCreator.createButton(VsBlackAI, sf::Vector2f(250, 60), sf::Vector2f(198, 313)));
	m_buttons.push_back(theCreator.createButton(VsWhiteAI, sf::Vector2f(250, 60), sf::Vector2f(585, 276)));
	m_buttons.push_back(theCreator.createButton(Puzzles, sf::Vector2f(250, 60), sf::Vector2f(400, 400)));*/

}

void PlayMenuState::draw()
{
	m_window.clear(sf::Color(125, 125, 125));
	m_window.draw(m_menuSprite);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(m_window);
	}
	m_window.display();
}

void PlayMenuState::handleEvents()
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

void PlayMenuState::handleMouseClick(sf::Event& event)
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
