#include "GameState/PuzzleGameState.h"
#include "GameManager.h"
#include "NBoard.h"
PuzzleGameState::PuzzleGameState(Color color, PuzzleManager& puzzle, GameManager& manager, uiPuzzlePtr ui)
	:GameState(manager), m_computerTurn(true), m_playerLastMove({ 0,0 }),
	m_puzzleManager(puzzle), m_ui(ui), m_waitingUndo(false), m_waitingNew(false)
{
	m_player = m_manager.getPlayer(0);
	m_ui->setName(m_puzzleManager.getName());
}

void PuzzleGameState::execute()
{
	Move undoMove = { -1,-1 };
	if (m_waitingUndo || m_waitingNew){
		if (m_ui->isUndo())m_waitingUndo = false;
		if(m_ui->isNew())m_waitingNew = false;
		m_manager.nextTurn(undoMove);
		m_manager.nextTurn(undoMove); //---- wtf!??!
		return;
	}

	if (m_computerTurn) {
		if (correctMove()) {
			playComputerMove();
			return;
		}
		m_ui->needUndo();
		m_waitingUndo = true;
		m_computerTurn = false;
		m_manager.nextTurn(undoMove);
	}
	else if (m_player->turnReady()) {
		auto move = m_player->playTurn();
		m_computerTurn = true;
		m_playerLastMove = move;
		m_manager.nextTurn(move);
	}
}

void PuzzleGameState::draw(float dt)
{
}

bool PuzzleGameState::correctMove()
{
	if (m_playerLastMove.startSquare == 0 && m_playerLastMove.targetSquare == 0)return true;
	if (m_playerLastMove.startSquare != m_puzzleManager.getCurrMove().startSquare ||
		m_playerLastMove.targetSquare != m_puzzleManager.getCurrMove().targetSquare)
		return false;
	m_puzzleManager.deleteCurrMove();
	return true;
}

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
