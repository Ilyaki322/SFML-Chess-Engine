#include "MenuFactory/MainMenuCreator.h"
#include "MenuFactory/MenuFactory.h"
#include "Assets.h"

#include "Button.h"
#include "ButtonCommand/ExitCommand.h"
#include "ButtonCommand/NextStateCommand.h"

std::shared_ptr<Menu> MainMenuCreator::createMenu(sf::RenderWindow& window, StateMachine& stateMachine)
{
	m_stateMachine = &stateMachine;
	m_window = &window;
	return std::make_shared<Menu>(window, stateMachine, Assets::instance().getMenu('m'), "MainMenu");
}

void MainMenuCreator::addButtons(std::shared_ptr<Menu> menu)
{
	menu->addButton(std::make_unique<Button>(std::make_unique<NextStateCommand>(*m_stateMachine, "PlayMenu"),
		sf::Vector2f(260, 50), sf::Vector2f(220, 510)));
	menu->addButton(std::make_unique<Button>(std::make_unique<NextStateCommand>(*m_stateMachine, "GameHistory"),
		sf::Vector2f(260, 50), sf::Vector2f(530, 510)));
	menu->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*m_stateMachine),
		sf::Vector2f(260, 50), sf::Vector2f(375, 580)));
}

bool MainMenuCreator::m_register = MenuFactory::registerCreator(std::make_unique <MainMenuCreator>());
