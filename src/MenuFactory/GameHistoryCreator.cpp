#include "MenuFactory/GameHistoryCreator.h"
#include "MenuFactory/MenuFactory.h"
#include "MainMenu/HistoryState.h"
#include "Assets.h"

#include "ButtonCommand/ExitCommand.h"

std::shared_ptr<Menu> GameHistoryCreator::createMenu(sf::RenderWindow& window, StateMachine& stateMachine)
{
	m_window = &window;
	m_stateMachine = &stateMachine;
	return std::make_shared<HistoryState>(window, stateMachine, Assets::instance().getMenu('h'), "GameHistory");
}

void GameHistoryCreator::addButtons(std::shared_ptr<Menu> menu)
{
	menu->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*m_stateMachine),
		sf::Vector2f(170, 60), sf::Vector2f(105, 560)));
}

bool GameHistoryCreator::m_register = MenuFactory::registerCreator(std::make_unique<GameHistoryCreator>());
