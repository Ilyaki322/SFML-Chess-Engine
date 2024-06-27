#include "MenuFactory/BlackAICreator.h"
#include "MenuFactory/MenuFactory.h"
#include "ButtonCommand/ExitCommand.h"
#include "ButtonCommand/VBlackAICommand.h"
#include "Assets.h"

std::shared_ptr<Menu> BlackAICreator::createMenu(sf::RenderWindow& window, StateMachine& stateMachine)
{
	m_window = &window;
	m_stateMachine = &stateMachine;
	return std::make_shared<Menu>(window, stateMachine, Assets::instance().getMenu('z'), "BlackAI");
}

void BlackAICreator::addButtons(std::shared_ptr<Menu> menu)
{
	menu->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*m_stateMachine, 1),
		sf::Vector2f(300, 70), sf::Vector2f(370, 150)));
	menu->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*m_stateMachine, 2),
		sf::Vector2f(300, 70), sf::Vector2f(370, 235)));
	menu->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*m_stateMachine, 3),
		sf::Vector2f(300, 70), sf::Vector2f(370, 325)));
	menu->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*m_stateMachine, 4),
		sf::Vector2f(300, 70), sf::Vector2f(370, 415)));
	menu->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*m_stateMachine, 5),
		sf::Vector2f(300, 70), sf::Vector2f(370, 495)));
	menu->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*m_stateMachine),
		sf::Vector2f(200, 50), sf::Vector2f(140, 570)));
}

bool BlackAICreator::m_register = MenuFactory::registerCreator(std::make_unique<BlackAICreator>());
