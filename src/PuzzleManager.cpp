#include "PuzzleManager.h"
#include "NBoard.h"

PuzzleManager::PuzzleManager(Difficult d)
	:m_difficult(d)
{	
	srand(unsigned(time(nullptr)));
	m_file.open("PuzzleWhite.txt");
	int dif;
	std::string line;
	m_file >> dif;
	while (dif < d) {
		m_file >> dif;
		std::getline(m_file, line);
	}
	for (int i = 0; i < NumOfPuzzleInLevel && !m_file.eof(); i++) {
		PuzzleStruct s;
		m_file >> dif;
		m_file >> s.board;						//---- Board status
		int size;
		m_file >> size;
		for (int j = 0; j < size; j++) {		//---- reading vector of moves
			Move move;
			m_file >> move.startSquare;
			m_file >> move.targetSquare;
			s.moves.push_back(move);
		}
		std::getline(m_file, s.name);			//---- reading puzzle name
		m_puzzle.push_back(s);
	}
	loadNextPuzzle();
}

Move PuzzleManager::getCurrMove() const
{
	return !m_currPuzzle.moves.empty() ? m_currPuzzle.moves.front() : Move({-1, -1});
}

void PuzzleManager::deleteCurrMove()
{
	m_currPuzzle.moves.erase(m_currPuzzle.moves.begin());
}

void PuzzleManager::loadNextPuzzle()
{
	int random = rand() % m_puzzle.size();
	int count = 0;
	for (auto i = m_puzzle.begin(); i != m_puzzle.end(); i++, count++) {
		if (count == random) {
			m_currPuzzle = *i;
			m_puzzle.erase(i);
			break;
		}
	}

	NBoard& inst = NBoard::instance();
	inst.setBoard(m_currPuzzle.board);
}

std::string PuzzleManager::getName() const
{
	return m_currPuzzle.name;
}

