#pragma once
#include "Utilities.h"
#include "Button.h"
#include "Assets.h"
#include "ButtonCommand/BackToMenuCommand.h"
class StateMachine;
class GameManager;

typedef std::unique_ptr<Button> buttonPtr;

class PlayUI {
public:
	PlayUI(StateMachine& stateMachine);
	virtual ~PlayUI() {}
	virtual void draw(sf::RenderWindow &window) = 0 {
		window.draw(m_backGround);
	}
	virtual void initButtons(GameManager& manager) = 0 {
		m_button.push_back(std::make_unique<Button>(" ",
			std::make_unique<BackToMenuCommand>(manager,m_stateMachine)))
	}
private:
	sf::Sprite m_backGround;
	StateMachine& m_stateMachine;
protected:
	std::vector<buttonPtr> m_button;
};


