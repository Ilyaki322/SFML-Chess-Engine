#pragma once
#include "Utilities.h"
#include <vector> 

/*
* This struct represents a move from a movebook.
* the 'children' of it are opponent responses for this move.
* the AI will keep using the book, until we run out of responses.
*/
struct bookMove
{
	int start;
	int target;
	Color color;

	std::vector<bookMove> children;

	bookMove(int s = -1, int t = -1, Color c = White) 
		: start(s), target(t), color(c) {};

	bool operator==(const bookMove& other)
	{
		if (other.start == this->start && other.target == this->target)
		{
			return true;
		}

		return false;
	}
};

typedef std::vector<bookMove> book;

/*
* This class manages the opening of the game.
* Using over 20,000 proffesional level games, it builds a tree-like structure.
* It checks whether the move is in the book and plays opening 
* moves for it until it finds no suitable move (the book ended / no opponent response found)
* 
* It makes the AI open the game in different ways each time,
* making it 'fresh' every game.
*/
class OpeningBook
{
public:
	OpeningBook();

	book& getStart() { return m_book; };

private:
	void generateBook();

	book m_book;
};