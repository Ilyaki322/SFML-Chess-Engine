#include "Controllers/TestAI.h"
#include "NBoard.h"

#include <iostream>

Move TestAI::playTurn()
{
	std::cout << moveGenerationTest(4, true);

	Move move = { -1, -1 };
	return move;
}

int TestAI::moveGenerationTest(int depth, bool white)
{
	Color color = white ? White : Black;
	if (depth == 0)
	{
		return 1;
	}

	auto moves = generator.generateAll(color);
	int numPositions = 0;

	for (auto& i : moves)
	{
		for (auto& move : i)
		{
			NBoard::instance().move(move);
			numPositions += moveGenerationTest(depth - 1, !white);
			NBoard::instance().undo();
		}
	}
	
	return numPositions;
}
