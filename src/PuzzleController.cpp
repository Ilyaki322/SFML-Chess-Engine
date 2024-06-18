#include "PuzzleController.h"

PuzzleController::PuzzleController(Difficult d)
{
	m_file.open("PuzzleWhite.txt");
	int dif;
	m_file >> dif;
	while (dif<d){
		m_file >> dif;
	}
	for (int i = 0; i < NumOfPuzzleInLevel && !m_file.eof(); i++) {
		PuzzleStruct s;
		m_file >> s.board;//---- Board status
		int size;
		m_file >> size;
		for (int j = 0; j < size; j++) {//---- reading vector of moves
			Move move;
			m_file >> move.startSquare;
			m_file >> move.targetSquare;
			s.moves.push_back(move);
		}
		std::getline(m_file, s.name);//---- reading puzzle name
		m_puzzle.push_back(s);
	}
}
