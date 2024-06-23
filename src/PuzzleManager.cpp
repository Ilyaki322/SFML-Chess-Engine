#include "PuzzleManager.h"
#include "NBoard.h"
PuzzleManager::PuzzleManager(Color color , Difficult d)
	:m_difficult(d)
{	
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

	int random = rand() % NumOfPuzzleInLevel;
	int count = 0;
	for (auto i = m_puzzle.begin();i != m_puzzle.end(); i++ , count++) {
		if (count = random) {
			m_currPuzzle = *i;
			m_puzzle.erase(i);
			break;
		}
	}
	FenAlgorithm fen;
	NBoard& inst = NBoard::instance();
	std::array<int, SIZE> arr;
	fen.setBoard(arr, m_currPuzzle.board);
	inst.setBoard(arr);
	std::cout << m_currPuzzle.name << '\n';
}

Move PuzzleManager::getCurrMove() const
{
	return  !m_currPuzzle.moves.empty() ? m_currPuzzle.moves.front() : Move({-1, -1});
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
		if (count = random) {
			m_currPuzzle = *i;
			m_puzzle.erase(i);
			break;
		}
	}

	FenAlgorithm fen;
	NBoard& inst = NBoard::instance();
	std::array<int, SIZE> arr;
	fen.setBoard(arr, m_currPuzzle.board);
	inst.setBoard(arr);
	std::cout << m_currPuzzle.name << '\n';
}
