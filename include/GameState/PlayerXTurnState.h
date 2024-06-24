#pragma once
#include "GameState.h"
#include "Controllers/Controller.h"

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