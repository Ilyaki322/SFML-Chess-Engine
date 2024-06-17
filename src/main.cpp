#include "GameManager.h"
#include "NBoard.h"
#include "FenAlgorithm.h"
#include "StateMachine.h"

#include <iostream>

int main()
{
	FenAlgorithm fen;
	NBoard& inst = NBoard::instance();
	std::array<int, SIZE> arr;
	fen.setBoard(arr, "5RK11P3PPPPQ3B2881p1q1n2p4ppp3r2k1");//"RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");
	inst.setBoard(arr);/// To change
	GameManager game;
	game.update();

	/*StateMachine game;
	game.update();*/

}
