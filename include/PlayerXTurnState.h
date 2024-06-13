#pragma once
#include "GameState.h"

class Controller;

class PlayerXTurnState : public GameState
{
public:
	PlayerXTurnState(GameManager& manager, const int player, const int players);

	void execute() override;
	void draw() override;

private:

	Controller* m_playerController;
	const int m_numOfPlayers;
	const int m_playerNum;
};