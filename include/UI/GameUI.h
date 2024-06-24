#pragma once
#include "PlayUI.h"

const int NumOfPiece = 5;
enum PiecePlace{PawnPlace , KnightPlace , BishopPlace , RookPlace , QueenPlace};

class GameUI : public PlayUI
{
public:
	GameUI(StateMachine& stateMachine);

	void draw(sf::RenderWindow& window) override;
	void initButtons(GameManager& manager) override;
};