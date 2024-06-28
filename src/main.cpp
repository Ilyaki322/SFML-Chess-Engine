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

	StateMachine game;
	game.update();

}
