#pragma once
#include "Controller.h"
#include "ChessLogic/IGenerate.h"

/*
* This is a Test AI, used to count moves to make sure we got
* all the chess rules correct.
* Typicaly used with a certein FEN string on catchy board setups
*/
class TestAI : public Controller
{
public:
	TestAI(Color color = Black) : Controller(color) {};

	Move playTurn() override;
	bool turnReady() override { return true; };

private:

	int moveGenerationTest(int depth, bool white);

	IGenerate generator;
};