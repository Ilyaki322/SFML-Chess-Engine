#include "GameManager.h"
#include "Utilities.h"
#include "NBoard.h"
#include "GameState/PlayerXTurnState.h"

#include <iostream> // debug

GameManager::GameManager(bool whiteTurn, SFMLBoard& board, uiPtr ui)
	: m_whiteTurn(whiteTurn), m_changeState(false), m_sfmlBoard(board), m_ui(ui)
{
	m_window.create(sf::VideoMode(ScreenSizeX, ScreenSizeY), "Game");
	m_ui->initButtons(*this);
}

void GameManager::addPlayer(controllerPtr p)
{
	m_players.push_back(std::move(p));
}

void GameManager::setStartState(gameStatePtr start)
{
	m_currentState = std::move(start);
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
	m_ui->draw(m_window);
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

		case sf::Event::MouseButtonReleased:
		{
			auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			m_ui->buttonClicked(location);
			[[fallthrough]];
		}
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

void GameManager::restartGame()
{
	m_whiteTurn = true;
	NBoard::instance().setBoard(NEW_GAME);
	m_sfmlBoard.updateBoard();
	setState(std::make_unique<PlayerXTurnState>(*this, 0));
}
