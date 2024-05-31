#pragma once 

#include <string>
#include "memory"
#include <array>
//#include "Tile.h"

class Tile;
class Pieces;

class FenAlgorithm {
public:
	FenAlgorithm();
	void setBoard(std::array<std::array<std::shared_ptr<Tile>, 8>, 8> &tiles ,std::string stage);
};