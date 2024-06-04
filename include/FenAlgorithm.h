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
	void setBoard(std::array<std::shared_ptr<Tile>, 64> &tiles ,int squares[], std::string stage);

private:
	std::map<char, int> m_piecesMap;
};