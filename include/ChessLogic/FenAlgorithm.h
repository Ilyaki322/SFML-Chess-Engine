#pragma once 
#include <string>
#include <array>
#include <map>

class Pieces;

/*
* Fen Algorithm translates a string to a board position.
* We will keep puzzles as a fen string, and a new game.
* used during testing to play various positions without placing the pieces by hand.
*/
class FenAlgorithm {
public:
	FenAlgorithm();
	void setBoard(std::array<int, 64> &squares, std::string stage);
	
private:
	std::map<char, int> m_piecesMap;
};