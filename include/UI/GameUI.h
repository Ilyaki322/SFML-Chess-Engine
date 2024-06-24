#pragma once
#include "PlayUI.h"
#include "SFMLPieceFactory.h"
#include "SFMLPiece.h"

const int NumOfPiece = 5;
enum PiecePlace{PawnPlace , KnightPlace , BishopPlace , RookPlace , QueenPlace};

class GameUI : public PlayUI {
public:
	GameUI();
	virtual void draw(sf::RenderWindow& window) override;
	virtual std::vector<Button> getButton() override;
private:
	std::vector<int> m_whitePiece;
	std::vector<int> m_blackPiece;
};