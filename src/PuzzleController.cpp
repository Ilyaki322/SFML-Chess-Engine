#include "PuzzleController.h"
#include "GameManager.h"
#include "NBoard.h"

PuzzleController::PuzzleController(Color color, Difficult d, GameManager& manager , SFMLBoard &sfBoard)
	:GameState(manager) , m_first(true) , m_sfmlBoard(sfBoard)
{
	
	m_player = manager.getPlayer(0);
	m_file.open("PuzzleWhite.txt");
	int dif;
	std::string line;
	m_file >> dif;
	while (dif<d){
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
	m_currPuzzle = m_puzzle[random];
	//std::remove(m_puzzle.begin(),m_puzzle.end(), m_puzzle[random]);
	
	std::cout << m_currPuzzle.moves.front().startSquare<<' ' << m_currPuzzle.moves.front().targetSquare << '\n';

	FenAlgorithm fen;
	NBoard& inst = NBoard::instance();
	std::array<int, SIZE> arr;
	fen.setBoard(arr, m_currPuzzle.board );
	inst.setBoard(arr);/// To change
}

void PuzzleController::execute()
{
	if (m_first) {
		m_manager.nextTurn(m_currPuzzle.moves.front());
		m_currPuzzle.moves.erase(m_currPuzzle.moves.begin());
		m_first = false;
	}
	if (m_player->turnReady())
	{
		auto move = m_player->playTurn();
		m_manager.nextTurn(move);
		if (correctMove(move)) {
			m_currPuzzle.moves.erase(m_currPuzzle.moves.begin());
			if (!m_currPuzzle.moves.empty()) {
				m_manager.nextTurn(m_currPuzzle.moves.front());
				m_currPuzzle.moves.erase(m_currPuzzle.moves.begin());
			}
			else {
				int random = rand() % NumOfPuzzleInLevel;
				m_currPuzzle = m_puzzle[random];
				//std::remove(m_puzzle.begin(), m_puzzle.end(), m_puzzle[random]);
			}
		}
		else {
			//sf::sleep(sf::seconds(2.f));
			//NBoard::instance().undo();
			//m_sfmlBoard.updateBoard();
		}
	}
}

void PuzzleController::draw()
{
}

bool PuzzleController::correctMove(Move move)
{
	if (move.startSquare != m_currPuzzle.moves.front().startSquare ||
		move.targetSquare != m_currPuzzle.moves.front().targetSquare)
		return false;
	return true;
}

