#include "ChessLogic/OpeningBook.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

OpeningBook::OpeningBook()
{
	generateBook();
}

/*
* Using a data base of 20,000 proffesional games.
* builds a tree-like structure, where each node is a move.
* and the childern are the opponent answer.
* each turn the AI will move deeper into the tree.
* 
* The AI will play a move from the book, then check if the opponent move 
* is in one of the childern of its move, and so on.
*/
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
