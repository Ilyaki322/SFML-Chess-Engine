#include "OpeningBook.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

OpeningBook::OpeningBook()
{
	generateBook();
}

void OpeningBook::generateBook()
{
	std::ifstream bookFile("games_base.txt");

	book* current = &m_book;
	bool isWhite = true;

	std::string line;
	while (std::getline(bookFile, line))
	{
		if (line.starts_with("G"))
		{
			isWhite = true;
			current = &m_book;
			continue;
		}
		if (!line.empty())
		{
			Color color = isWhite ? White : Black;
			std::istringstream s(line);
			bookMove newMove;
			s >> newMove.start >> newMove.target;
			newMove.color = color;
			isWhite = !isWhite;

			auto match = std::find(current->begin(), current->end(), newMove);
			if (match == current->end()) // new entry
			{
				current->push_back(newMove);
				current = &newMove.children;
			}
			else // already have
			{
				current = &(*match).children;
			}
		}
	}
}

void OpeningBook::printBook()
{
	std::cout << m_book.size() << std::endl;
	auto& hui = m_book[0].children;
	for (auto& i : hui)
	{
		std::cout << i.start << " " << i.target << std::endl;
	}
}
