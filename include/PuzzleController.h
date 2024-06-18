#pragma once 
#include "Utilities.h"
#include <fstream>
class PuzzleController {
public:
	PuzzleController(Difficult d);

private:
	std::vector<PuzzleStruct> m_puzzle;
	std::fstream m_file;
};