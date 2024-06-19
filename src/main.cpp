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
	fen.setBoard(arr, "RNBQ1K1RPP1pBPPP2P582b58ppp1nNpprnbqk2r"); // RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr
	inst.setBoard(arr);/// To change
	GameManager game;
	game.update();

	/*StateMachine game;
	game.update();*/

}
