#include "GameManager.h"
#include "NBoard.h"
#include "FenAlgorithm.h"
#include "MainMenu/StateMachine.h"

#include <iostream>

int main()
{
	srand(time(nullptr));
	FenAlgorithm fen;
	NBoard& inst = NBoard::instance();
	std::array<int, SIZE> arr;
	fen.setBoard(arr, "RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr");
	inst.setBoard(arr);/// To change
	GameManager game;
	game.update();

	//StateMachine game;
	//game.update();

}
