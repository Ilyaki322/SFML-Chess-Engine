#include "GameManager.h"
#include "NBoard.h"
#include "FenAlgorithm.h"

#include "StateMachine.h"

#include <iostream>

int main()
{
	/*FenAlgorithm fen;
	NBoard& inst = NBoard::instance();
	fen.setBoard(inst.m_board, "RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");
	inst.setBoard(inst.m_board);/// change
	GameManager game;
	game.update();*/
	//hui

	StateMachine game;
	game.update();
}
