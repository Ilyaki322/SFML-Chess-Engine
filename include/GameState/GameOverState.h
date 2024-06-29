#pragma once
#include "GameState/GameState.h"
#include "SFML/Graphics.hpp"
#include "Utilities.h"
#include "UI/EndGameUI.h"
#include<memory>

class GameOverState : public GameState
{
public:
	GameOverState(GameManager& gameManager, GameOver status);

	void execute() override;
	void draw(float dt) override;

private:
	GameOver m_status;
	//sf::Sprite m_winner;
	bool m_once;
	std::string m_winner;
};