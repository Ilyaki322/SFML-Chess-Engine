#pragma once
#include <fstream>
#include "Utilities.h"
#include "FenAlgorithm.h" 

/*
* this class will do:
* 1. open the puzzle file and get all the puzzles of selected difficulty.
* 2. will select a random puzzle, load it to Nboard and delete it from the puzzles list
* 3. will have a public function to return the current move of the selected puzzle or -1 -1 if puzzle is finished
* 4. will have a function to load next puzzle.
*/
class PuzzleManager {
public:
	PuzzleManager(Difficult d);

	Move getCurrMove()const;
	void deleteCurrMove();
	void loadNextPuzzle();
	std::string getName()const;

private:
	Difficult m_difficult;
	std::vector<PuzzleStruct> m_puzzle;
	PuzzleStruct m_currPuzzle;
	std::fstream m_file;
};