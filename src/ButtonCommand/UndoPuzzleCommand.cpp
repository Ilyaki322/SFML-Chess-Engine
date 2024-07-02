#include "ButtonCommand/UndoPuzzleCommand.h"
#include "ChessLogic/NBoard.h"
#include "Managers/GameManager.h"
UndoPuzzleCommand::UndoPuzzleCommand(StateMachine& stateMachine,PuzzleUI& puzzle, GameManager& manager)
	:ButtonCommand(stateMachine), m_puzzle(puzzle), m_manager(manager)
{
}

void UndoPuzzleCommand::execute()
{
	NBoard::instance().undo();
	Move move(-1, -1);
	m_manager.nextTurn(move);
}
