#pragma once
#include "Controller.h"
#include "IGenerate.h"

class TestAI : public Controller
{
public:
	TestAI(Color color = Black) : Controller(color) {};

	Move playTurn() override;
	bool turnReady() override { return true; };

private:

	int moveGenerationTest(int depth);

	IGenerate generator;
};