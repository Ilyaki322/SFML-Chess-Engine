#include "ButtonCommand/NextPuzzleCommand.h"

NextPuzzleCommand::NextPuzzleCommand(StateMachine& stateMachine, PuzzleManager& manager)
	:ButtonCommand(stateMachine) , m_manager(manager)
{
}

void NextPuzzleCommand::execute()
{
	m_manager.loadNextPuzzle();
}
