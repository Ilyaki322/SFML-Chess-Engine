#pragma once
#include "GameState.h"
#include "Controllers/Controller.h"

/*
* This class represents gamestate of controller turn
* Player or AI.
*/

class PlayerXTurnState : public GameState
{
public:
	PlayerXTurnState(GameManager& manager, const int player);

	void execute() override;
	void draw(float dt) override;

private:
	Controller* m_playerController;
	const int m_playerNum;
};