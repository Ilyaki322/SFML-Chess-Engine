#pragma once 

#include <string>
#include "Board.h"

class FenAlgorithm {
public:
	FenAlgorithm();
	void setBoard(std::array<std::array<std::shared_ptr<Pieces>, 8>, 8> m_tiles ,std::string stage);
};