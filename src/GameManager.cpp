#include "GameManager.h"
#include "PlayerController.h"
#include "AIController.h"
#include "Utilities.h"
#include "GameState/PlayerXTurnState.h"
#include "NBoard.h"
#include "GameState/PuzzleGameState.h" // need to be in menu
#include "TODO/PuzzleManager.h" // need to be in menu
#include <iostream> // debug
#include "Assets.h" // for font
#include "TestAI.h"


GameManager::GameManager()
	: m_firstClick(false), m_whiteTurn(false), m_changeState(false), m_sfmlBoard()
{
	m_window.create(sf::VideoMode(ScreenSizeX, ScreenSizeY), "MainMenu");

	//m_whitePlayer = std::make_unique<PlayerController>(m_window, White);
	//m_blackPlayer = std::make_unique<PlayerController>(m_window, Black);
	//m_blackPlayer = std::make_unique<AIController>(Black);
	PuzzleManager p(White, Intermediate);
	//m_players.push_back(std::make_unique<TestAI>(White));
	m_players.push_back(std::make_unique<PlayerController>(*this, m_window, White, m_sfmlBoard));
	//m_players.push_back(std::make_unique<AIController>(Black));
	
	m_currentState = std::make_unique<PuzzleGameState>(White, p ,*this);
	//m_players.push_back(std::make_unique<PlayerController>(*this, m_window, Black, m_sfmlBoard));
	//m_currentState = std::make_unique<PlayerXTurnState>(*this, 0);
}

void GameManager::update()
{
	sf::Clock deltaClock;
	float dt;

	while (m_window.isOpen())
	{
		dt = deltaClock.restart().asSeconds();
		handleEvents();
		m_currentState->execute();
		draw(dt);

		if (m_changeState)
		{
			change();
		}
	}
}

void GameManager::draw(float dt)
{
	m_window.clear(sf::Color(125, 125, 125, 255));
	m_sfmlBoard.draw(m_window);
	m_currentState->draw(dt);
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

void GameManager::setState(gameStatePtr newState)
{
	m_nextState = std::move(newState);
	m_changeState = true;
}

void GameManager::change()
{
	m_currentState = std::move(m_nextState);
	m_nextState = nullptr;
	m_changeState = false;
}


void GameManager::nextTurn(Move& move)
{
	if(move.startSquare!=-1)
		NBoard::instance().move(move);
	m_sfmlBoard.updateBoard();
	m_whiteTurn = !m_whiteTurn;
}
