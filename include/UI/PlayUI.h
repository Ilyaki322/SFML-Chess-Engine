#pragma once
#include "Utilities.h"
#include "Button.h"
#include "Assets.h"
#include "ButtonCommand/BackToMenuCommand.h"
#include "MainMenu/StateMachine.h"
class GameManager;

typedef std::unique_ptr<Button> buttonPtr;

class PlayUI {
public:
	PlayUI(StateMachine& stateMachine);
	virtual ~PlayUI() {}

	virtual void buttonClicked(const sf::Vector2f& loc);

	virtual void draw(sf::RenderWindow &window) = 0 {
		window.draw(m_backGround);
		m_button[0]->draw(window);
	}

	virtual void initButtons(GameManager& manager) = 0 {
		m_button.push_back(std::make_unique<Button>(std::make_unique<BackToMenuCommand>(m_stateMachine, manager),
			sf::Vector2f(170, 50), sf::Vector2f(910, 710)));
	}

private:
	sf::Sprite m_backGround;

protected:
	std::vector<buttonPtr> m_button;
	StateMachine& m_stateMachine;
};


