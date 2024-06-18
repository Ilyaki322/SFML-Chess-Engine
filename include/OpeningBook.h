#pragma once
#include "Utilities.h"

#include <vector> // vector?

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