#pragma once
#include "Utilities.h"

#include <vector> 


/*
* This struct represents an opening from a movebook
*/

struct bookMove
{
	int start;
	int target;
	Color color;

	std::vector<bookMove> children;

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
* This class manages the opening of the game, 
* it checks whether the move is in the book and builds opening 
* moves for it until it finds no suitable move
*/

class OpeningBook
{
public:
	OpeningBook();

	void printBook();
	book& getStart() { return m_book; };


private:
	void generateBook();

	book m_book;
};