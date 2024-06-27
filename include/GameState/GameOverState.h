#pragma once
#include "GameState/GameState.h"
#include "SFML/Graphics.hpp"

class GameOverState : public GameState
{
public:
	GameOverState(GameManager& gameManager);

	void execute() override;
	void draw(float dt) override;

private:

	sf::RectangleShape m_gameOverBox;

};