#include "GameManager.h"
#include "NBoard.h"
#include "FenAlgorithm.h"
#include "MainMenu/StateMachine.h"

#include <iostream>
#include <UI/GameUI.h>
#include <memory>
#include "GameState/ReviewState.h"

int main()
{
	srand(time(nullptr));

	//StateMachine game;
	//NBoard::instance().setBoard(NEW_GAME);
	//SFMLBoard board;
	//auto ui = std::make_unique<GameUI>(game);

	//GameManager manager(true, board, std::move(ui));
	//manager.setStartState(std::make_unique<ReviewState>(manager, 0));

	//manager.update();

	StateMachine game;
	game.update();

}
