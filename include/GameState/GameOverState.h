#pragma once
#include "GameState/GameState.h"
#include "SFML/Graphics.hpp"
#include "Utilities.h"
#include "UI/GameUI.h"
#include<memory>

typedef std::shared_ptr<GameUI> gameUIPtr;

class GameOverState : public GameState
{
public:
	GameOverState(GameManager& gameManager, GameOver status);

	void execute() override;
	void draw(float dt) override;

private:
	GameOver m_status;
	sf::RectangleShape m_gameOverBox;
	gameUIPtr m_ui;
};