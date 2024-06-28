#include "MainMenu/HistoryState.h"
#include "ButtonCommand/ExitCommand.h"

HistoryState::HistoryState(sf::RenderWindow& window, StateMachine& stateMachine)
	: MenuState(window, stateMachine)
{
	m_exit = std::make_unique<Button>(std::make_unique<ExitCommand>(m_stateMachine),
		sf::Vector2f(170, 60), sf::Vector2f(105, 560));
}

void HistoryState::draw()
{

}

void HistoryState::handleEvents()
{

}

void HistoryState::handleMouseClick(sf::Event& event)
{

}
