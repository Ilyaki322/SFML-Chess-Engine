#include "Managers/GameManager.h"
#include "ChessLogic/NBoard.h"
#include "ChessLogic/FenAlgorithm.h"
#include "MainMenu/StateMachine.h"

#include <iostream>
#include <UI/GameUI.h>
#include <memory>
#include "GameState/ReviewState.h"
#include <thread>

int main()
{
	srand(unsigned(time(nullptr)));

	StateMachine game;
	game.update();

}
