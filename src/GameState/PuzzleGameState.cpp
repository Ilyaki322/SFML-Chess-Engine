#include "GameState/PuzzleGameState.h"
#include "GameState/WaitGameState.h"
#include "Managers/GameManager.h"
#include "ChessLogic/NBoard.h"

#include <memory>

PuzzleGameState::PuzzleGameState(PuzzleManager& puzzle, GameManager& manager, uiPuzzlePtr ui)
	:GameState(manager), m_computerTurn(true), m_playerLastMove({ 0,0 }),
	m_puzzleManager(puzzle), m_ui(ui), m_waitingUndo(false), m_waitingNew(false)
{
	m_player = m_manager.getPlayer(0);
	m_ui->setName(m_puzzleManager.getName());
}

void PuzzleGameState::execute()
{
	Move undoMove = { -1,-1 };

	if (m_waitingUndo || m_waitingNew){ // waiting for undo
		if (m_ui->isUndo())m_waitingUndo = false;
		if(m_ui->isNew())m_waitingNew = false;
		m_manager.updateBoard();
		return;
	}

	if (m_computerTurn) { // AI turn
		if (correctMove()) {
			playComputerMove();
			return;
		}
		m_ui->needUndo();
		m_waitingUndo = true;
		m_computerTurn = false;
		m_manager.updateBoard();
	}

	else if (m_player->turnReady()) { // player turn
		auto move = m_player->playTurn();
		m_computerTurn = true;
		m_playerLastMove = move;
		m_manager.nextTurn(move);
		auto nextState = std::make_unique<PuzzleGameState>(*this);
		m_manager.setState(std::make_unique<WaitGameState>(m_manager, std::move(nextState)));
	}
}

void PuzzleGameState::draw(float)
{}

/*
* Checks whether the player played the correct move.
*/
bool PuzzleGameState::correctMove()
{
	if (m_playerLastMove.startSquare == 0 && m_playerLastMove.targetSquare == 0)return true;
	if (m_playerLastMove.startSquare != m_puzzleManager.getCurrMove().startSquare ||
		m_playerLastMove.targetSquare != m_puzzleManager.getCurrMove().targetSquare)
		return false;
	m_puzzleManager.deleteCurrMove();
	return true;
}

/*
* Gets the next puzzle move from the puzzleManager,
* and plays is.
*/
void PuzzleGameState::playComputerMove()
{
	Move move = m_puzzleManager.getCurrMove();
	if (move.startSquare == -1) {
		m_ui->needNext();
		m_waitingNew = true;
		m_computerTurn = true;
		m_playerLastMove = { 0,0 };
		return;
	}
	m_computerTurn = false;
	m_manager.nextTurn(move);
	m_puzzleManager.deleteCurrMove();
}
