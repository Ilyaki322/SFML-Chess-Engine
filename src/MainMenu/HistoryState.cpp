#include "MainMenu/HistoryState.h"
#include "ButtonCommand/ExitCommand.h"

#include <fstream>

HistoryState::HistoryState(sf::RenderWindow& window, StateMachine& stateMachine, sf::Texture& texture, std::string name)
	: Menu(window, stateMachine, texture, name), m_index(0)
{
	m_games.reserve(10);
}

void HistoryState::draw()
{
	Menu::draw();
}

void HistoryState::handleMouseClick(sf::Event& event)
{
	Menu::handleMouseClick(event);
}

void HistoryState::load10Games()
{

}

/*
* void ReviewState::loadGame(const int num)
{
	std::ifstream games("GameHistory.txt");

	std::string line;
	for (int i = 0; i < num; i++)
	{
		std::getline(games, line);
		std::getline(games, line);
	}

	std::getline(games, line);
	std::getline(games, line);
	std::istringstream s(line);

	while (!s.eof())
	{
		Move move;
		int promotion;
		s >> promotion;
		move.promotionVal = Piece(promotion);
		s >> move.specialStartSquare >> move.specialTargetSquare;
		s >> move.startSquare >> move.targetSquare;
		m_moveList.push_back(move);
	}
}
*/
