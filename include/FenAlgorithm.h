#pragma once 

#include <string>
#include "memory"
#include <array>
#include <map>
#include "Tile.h"


class Pieces;

class FenAlgorithm {
public:
	FenAlgorithm();
	void setBoard(std::array<int, 64> &squares, std::string stage);
	
private:
	std::map<char, int> m_piecesMap;
};