#pragma once
#include "PlayUI.h"

const int NumOfPiece = 5;
enum PiecePlace{PawnPlace , KnightPlace , BishopPlace , RookPlace , QueenPlace};

class GameUI : public PlayUI {
public:
	GameUI(StateMachine& stateMachine);
	virtual void draw(sf::RenderWindow& window) override;

private:
};