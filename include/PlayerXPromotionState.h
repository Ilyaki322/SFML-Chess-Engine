#pragma once

#include "GameState.h"
#include "Controller.h"
#include "PromotionBox.h"

class PlayerXPromotionState : public GameState
{
public:
	PlayerXPromotionState(GameManager& manager, Color color, const int player, Move move);

	void execute() override;
	void draw() override;

private:

	Controller* m_playerController;
	Color m_color;
	Move m_move;
	const int m_player;

	PromotionBox m_box;
};