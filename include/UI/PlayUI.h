#pragma once
#include "Utilities.h"
#include "Button.h"
#include "Assets.h"
#include "ButtonCommand/BackToMenuCommand.h"
#include "MainMenu/StateMachine.h"

class GameManager;
typedef std::unique_ptr<Button> buttonPtr;

/*
* Abstract base class for the in game UI.
*/
class PlayUI {
public:
	PlayUI(StateMachine& stateMachine);
	virtual ~PlayUI() {}

	virtual void buttonClicked(const sf::Vector2f& loc);

	virtual void draw(sf::RenderWindow &window) = 0
	{
		if(!m_newBackground) window.draw(m_backGround);
		for (const auto &i : m_button) {
			i->draw(window);
		}
	}

	virtual void initButtons(GameManager& manager) = 0
	{
		sf::Sprite pic;
		pic.setTexture(Assets::instance().getUITexture("exit"));
		m_button.push_back(std::make_unique<Button>(pic,
			std::make_unique<BackToMenuCommand>(m_stateMachine, manager),
			sf::Vector2f(1250, 650)));
	}

	StateMachine& getStateMachine()const;
	void deleteButtons();

private:
	sf::Sprite m_backGround;

protected:
	bool m_newBackground;
	std::vector<buttonPtr> m_button;
	StateMachine& m_stateMachine;
};


