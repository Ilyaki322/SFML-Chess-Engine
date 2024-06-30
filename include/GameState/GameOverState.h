#pragma once
#include "GameState/GameState.h"
#include "SFML/Graphics.hpp"
#include "Utilities.h"
#include "UI/EndGameUI.h"

/*
* this state will update the UI based on the winner,
* and will wait for button click in the UI.
*/
class GameOverState : public GameState
{
public:
	GameOverState(GameManager& gameManager, GameOver status);

	void execute() override;
	void draw(float dt) override;

private:

	GameOver m_status;
	bool m_once;
	std::string m_winner;
};