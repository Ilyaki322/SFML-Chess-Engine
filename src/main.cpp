#include "GameManager.h"
#include "NBoard.h"
#include "FenAlgorithm.h"
#include "StateMachine.h"

#include <iostream>
#include "OpeningBook.h"

int main()
{
	FenAlgorithm fen;
	NBoard& inst = NBoard::instance();
	std::array<int, SIZE> arr;
	fen.setBoard(arr, "RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr"); //5RK11P3PPPPQ3B2881p1q1n2p4ppp3r2k1
	inst.setBoard(arr);/// To change
	GameManager game;
	game.update();

	/*StateMachine game;
	game.update();*/

	/*OpeningBook book;
	book.printBook();*/

}
