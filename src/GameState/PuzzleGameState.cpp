#include "GameState/PuzzleGameState.h"
#include "GameManager.h"
#include "NBoard.h"
PuzzleGameState::PuzzleGameState(Color color, PuzzleManager& puzzle, GameManager& manager)
	:GameState(manager), m_computerTurn(true) , m_playerLastMove({0,0})
{
	m_player = m_manager.getPlayer(0);
	m_puzzleManager = std::make_unique<PuzzleManager>(White, Intermediate); // ---> need to be(puzzle)
}

void PuzzleGameState::execute()
{
	if (m_computerTurn) {
		if (correctMove()) {
			playComputerMove();
			return;
		}
		//------start section for debug
		Move move = m_puzzleManager->getCurrMove();
		std::cout << move.startSquare << ' ' << move.targetSquare << '\n';
		std::cout << "try again\npress 'u' to undo\n";
		char c;
		std::cin >> c;
		while(c!='u')
			std::cin >> c;
		//------end section for debug
		NBoard::instance().undo();
		Move undoMove = { -1,-1 };
		m_computerTurn = false;
		m_manager.nextTurn(undoMove);
	}
	else if (m_player->turnReady()) {
		std::cout << "here\n";
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
	if (m_playerLastMove.startSquare != m_puzzleManager->getCurrMove().startSquare ||
		m_playerLastMove.targetSquare != m_puzzleManager->getCurrMove().targetSquare)
		return false;
	m_puzzleManager->deleteCurrMove();
	return true;
}

void PuzzleGameState::playComputerMove()
{
	Move move = m_puzzleManager->getCurrMove();
	std::cout << move.startSquare << ' ' << move.targetSquare << '\n';
	if (move.startSquare == -1) {
		//------section for debug
		std::cout << "good job!!!\npress 'c' for naxt puzzle\n";
		char c;
		std::cin >> c;
		while (c != 'c')
			std::cin >> c;
		//------end section for debug
		m_puzzleManager->loadNextPuzzle();
		m_computerTurn = true;
		m_playerLastMove = { 0,0 };
		return;
	}
	m_computerTurn = false;
	m_manager.nextTurn(move);
	m_puzzleManager->deleteCurrMove();
}
