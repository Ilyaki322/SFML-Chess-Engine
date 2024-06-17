#include "TestAI.h"
#include "NBoard.h"

#include <iostream>

Move TestAI::playTurn()
{
	std::cout << moveGenerationTest(2);

	Move move = { -1, -1 };
	return move;
}

int TestAI::moveGenerationTest(int depth)
{
	if (depth == 0)
	{
		return 1;
	}

	auto moves = generator.generateAll(m_color);
	int numPositions = 0;

	for (auto& i : moves)
	{
		for (auto& move : i)
		{
			NBoard::instance().move(move);
			numPositions += moveGenerationTest(depth - 1);
			NBoard::instance().undo();
		}
	}
	
	return numPositions;
}
