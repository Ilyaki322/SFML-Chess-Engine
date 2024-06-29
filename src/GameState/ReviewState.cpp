#include "GameState/ReviewState.h"
#include "GameManager.h"
#include "SFML/Graphics.hpp"
#include "NBoard.h"

#include <fstream>
#include <string>
#include <sstream>

#include <iostream> // debug

ReviewState::ReviewState(GameManager& manager, const int game)
	: GameState(manager), IObserver(manager), m_currMove(0) ,m_once(true)
{
	loadGame(game);

	sf::Sprite pic;
	pic.setTexture(Assets::instance().getUITexture("next"));
	std::cout << m_moveList.size();
	m_next = std::make_unique<Button>(pic, nullptr, sf::Vector2f(1000, 300));
	pic.setTexture(Assets::instance().getUITexture("prev"));
	m_prev = std::make_unique<Button>(pic, nullptr, sf::Vector2f(1000, 500));
	pic.setTexture(Assets::instance().getUITexture("exit"));
	m_exit = std::make_unique<Button>(pic,
			std::make_unique<BackToMenuCommand>(manager.getStateMachine(), manager),
			sf::Vector2f(1100, 600));

	m_background.setTexture(Assets::instance().getUITexture("background"));
	m_background.setPosition(0, 0);
}

void ReviewState::eventUpdate(sf::Event& event, Color color)
{
	auto location = m_manager.getWindow().mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
	if (m_next->getGlobalBounds().contains(location))
	{
		//m_next->click();
		if (m_currMove >= m_moveList.size()) return;
		NBoard::instance().move(m_moveList[m_currMove]);
		Move move = { -1, -1 };
		m_manager.nextTurn(move);
		m_currMove++;
	}
	if (m_prev->getGlobalBounds().contains(location))
	{
		if (m_currMove <= 0) return;
		NBoard::instance().undo();
		Move move = { -1, -1 };
		m_manager.nextTurn(move);
		//m_prev->click();
		m_currMove--;
	}
	if (m_exit->getGlobalBounds().contains(location))
		m_exit->click();
}

void ReviewState::execute()
{
	if (!m_once)return;
	NBoard::instance().setBoard(NEW_GAME);
	Move move = { -1, -1 };
	m_manager.nextTurn(move);
	m_once = false;
}

void ReviewState::draw(float dt)
{
	//m_manager.getWindow().draw(m_background);
	m_next->draw(m_manager.getWindow());
	m_prev->draw(m_manager.getWindow());
	m_exit->draw(m_manager.getWindow());
}

void ReviewState::loadGame(const int num)
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


