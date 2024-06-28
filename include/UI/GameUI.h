#pragma once
#include "PlayUI.h"
#include <memory>

typedef std::unique_ptr<Button> buttonPtr;

class GameUI : public PlayUI
{
public:
	GameUI(StateMachine& stateMachine);
	void draw(sf::RenderWindow& window) override;
	void initButtons(GameManager& manager) override;
	virtual void buttonClicked(const sf::Vector2f& loc)override;
	void setEnd();
	
private:

	bool m_end;

	buttonPtr m_restartGame;
	buttonPtr m_review;
};