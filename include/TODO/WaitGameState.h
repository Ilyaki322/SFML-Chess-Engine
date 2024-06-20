#pragma once
#include "GameState.h"

/*
* will do nothing for x time then reset the board to prev position
* THIS NEEDS TO GET PuzzleManager ref to pass it back to PuzzleGameState
* we will delta time in GameManager for timers anyway, so just x - dt until x <= 0 and next state
*/
class WaitGameState : public GameState
{

};