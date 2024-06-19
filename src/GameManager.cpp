#include "GameManager.h"
#include "PlayerController.h"
#include "AIController.h"
#include "Utilities.h"
#include "PlayerXTurnState.h"
#include "NBoard.h"

#include <iostream> // debug
#include "Assets.h" // for font
#include "TestAI.h"


GameManager::GameManager()
	//: m_board("RNBQKBNRPPPPPPPP8888pppppppprnbqkbnr") //"RNBQ1K1RPP1pBPPP2P582b58ppp1nNpprnbqk2r");
	: m_firstClick(false), m_whiteTurn(true), m_sfmlBoard()
{
	m_window.create(sf::VideoMode(ScreenSizeX, ScreenSizeY), "MainMenu");

	//m_whitePlayer = std::make_unique<PlayerController>(m_window, White);
	//m_blackPlayer = std::make_unique<PlayerController>(m_window, Black);
	//m_blackPlayer = std::make_unique<AIController>(Black);

	m_players.push_back(std::make_unique<TestAI>(White));
	//m_players.push_back(std::make_unique<PlayerController>(*this, m_window, White, m_sfmlBoard));
	//m_players.push_back(std::make_unique<AIController>(Black));
	
	m_players.push_back(std::make_unique<PlayerController>(*this, m_window, Black, m_sfmlBoard));

	m_currentState = std::make_unique<PlayerXTurnState>(*this, 0);

}

void GameManager::update()
{
	while (m_window.isOpen())
	{
		handleEvents();
		m_currentState->execute();
		draw();
	}
}

void GameManager::draw()
{
	m_window.clear(sf::Color(125, 125, 125, 255));
	m_sfmlBoard.draw(m_window);
	m_currentState->draw();
	m_window.display();
}

void GameManager::handleEvents()
{
	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		default:
			notify(event);
			break;
		}
	}
}

void GameManager::notify(sf::Event& event)
{
	Color color = (m_whiteTurn) ? White : Black;
	for (auto& i : m_observers)
	{
		i->eventUpdate(event, color);
	}
}

sf::RenderWindow& GameManager::getWindow()
{
	return m_window;
}

Controller* GameManager::getPlayer(const int i)
{
	return m_players[i].get();
}

int GameManager::getNumOfPlayers() const
{
	return int(m_players.size());
}

void GameManager::setState(std::unique_ptr<GameState> newState)
{
	m_currentState = std::move(newState);
}

void GameManager::nextTurn(Move& move)
{
	NBoard::instance().move(move);
	m_sfmlBoard.updateBoard();
	m_whiteTurn = !m_whiteTurn;
}
