#include "GameManager.h"
#include "NBoard.h"
#include "FenAlgorithm.h"

#include <iostream>

int main()
{
	FenAlgorithm fen;
	NBoard& inst = NBoard::instance();
	fen.setBoard(inst.m_board, "RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");
	GameManager game;
	game.update();
}
