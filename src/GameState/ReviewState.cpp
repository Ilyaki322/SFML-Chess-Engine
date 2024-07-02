#include "GameState/ReviewState.h"
#include "GameManager.h"
#include "SFML/Graphics.hpp"
#include "NBoard.h"

#include <fstream>
#include <string>
#include <sstream>

ReviewState::ReviewState(GameManager& manager, const int game)
	: GameState(manager), IObserver(manager), m_currMove(0) ,m_once(true)
{
	loadGame(game);

	sf::Sprite pic;
	pic.setTexture(Assets::instance().getUITexture("next"));
	m_next = std::make_unique<Button>(pic, nullptr, sf::Vector2f(1000, 300));
	pic.setTexture(Assets::instance().getUITexture("prev"));
	m_prev = std::make_unique<Button>(pic, nullptr, sf::Vector2f(1000, 500));
}

void ReviewState::eventUpdate(sf::Event& event, Color)
{
	auto location = m_manager.getWindow().mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
	if (m_next->getGlobalBounds().contains(location))
	{
		if (m_currMove >= m_moveList.size() - 1) return;
		m_manager.nextTurn(m_moveList[m_currMove]);
		m_currMove++;
	}
	if (m_prev->getGlobalBounds().contains(location))
	{
		if (m_currMove <= 0) return;
		NBoard::instance().undo();
		m_manager.updateBoard();
		m_currMove--;
	}
}

void ReviewState::execute()
{
	if (!m_once)return;
	NBoard::instance().setBoard(NEW_GAME);
	Move move = { -1, -1 };
	m_manager.nextTurn(move);
	m_once = false;
}

void ReviewState::draw(float)
{
	m_next->draw(m_manager.getWindow());
	m_prev->draw(m_manager.getWindow());
}

/*
* loads the 'num' game from the file
*/
void ReviewState::loadGame(const int num)
{
	if (num == -1) 
	{
		loadLastGame();
		return;
	}
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

/*
* loads the last game in the file
*/
void ReviewState::loadLastGame()
{
	std::ifstream games("GameHistory.txt");
	
	std::string lastNonWhitespaceLine;
	std::string line;

	if (games.is_open())
	{
		while (std::getline(games, line))
		{
			if (!line.empty())
			{
				lastNonWhitespaceLine = line;
			}
		}
	}

	std::istringstream s(lastNonWhitespaceLine);

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