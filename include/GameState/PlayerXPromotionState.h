#pragma once

#include "GameState/GameState.h"
#include "Controllers/Controller.h"
#include "PromotionBox.h"

/*
* This class represents gamestate of promotion.
* Whenever the player promotes a pawn it will draw a choice window,
* and wait for click.
*/

class PlayerXPromotionState : public GameState
{
public:
	PlayerXPromotionState(GameManager& manager, Color color, const int player, Move move);

	void execute() override;
	void draw(float dt) override;

private:

	Controller* m_playerController;
	Color m_color;
	Move m_move;
	const int m_player;

	PromotionBox m_box;
};