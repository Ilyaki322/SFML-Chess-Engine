#include "ButtonCommand/UndoPuzzleCommand.h"
#include "NBoard.h"
UndoPuzzleCommand::UndoPuzzleCommand(StateMachine& stateMachine,PuzzleUI& puzzle)
	:ButtonCommand(stateMachine), m_puzzle(puzzle)
{
}

void UndoPuzzleCommand::execute()
{
	NBoard::instance().undo();
}
