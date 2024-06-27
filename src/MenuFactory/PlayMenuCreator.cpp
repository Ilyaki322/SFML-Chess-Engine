#include "MenuFactory/PlayMenuCreator.h"
#include "MenuFactory/MenuFactory.h"
#include "Assets.h"

#include "ButtonCommand/NextStateCommand.h"
#include "ButtonCommand/ExitCommand.h"
#include "ButtonCommand/PVPCommand.h"

std::shared_ptr<Menu> PlayMenuCreator::createMenu(sf::RenderWindow& window, StateMachine& stateMachine)
{
	m_window = &window;
	m_stateMachine = &stateMachine;
	return std::make_shared<Menu>(window, stateMachine, Assets::instance().getMenu('p'), "PlayMenu");
}

void PlayMenuCreator::addButtons(std::shared_ptr<Menu> menu)
{
	menu->addButton(std::make_unique<Button>(std::make_unique<PVPCommand>(*m_stateMachine),
		sf::Vector2f(300, 70), sf::Vector2f(186, 215)));
	menu->addButton(std::make_unique<Button>(std::make_unique<PVPCommand>(*m_stateMachine),
		sf::Vector2f(300, 70), sf::Vector2f(580, 180)));
	menu->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*m_stateMachine),
		sf::Vector2f(190, 50), sf::Vector2f(140, 570)));
	menu->addButton(std::make_unique<Button>(std::make_unique<NextStateCommand>(*m_stateMachine, "WhiteAI"),
		sf::Vector2f(300, 70), sf::Vector2f(195, 310)));
	menu->addButton(std::make_unique<Button>(std::make_unique<NextStateCommand>(*m_stateMachine, "BlackAI"),
		sf::Vector2f(300, 70), sf::Vector2f(585, 275)));
	menu->addButton(std::make_unique<Button>(std::make_unique<NextStateCommand>(*m_stateMachine, "Puzzle"),
		sf::Vector2f(300, 70), sf::Vector2f(390, 440)));
}

bool PlayMenuCreator::m_register = MenuFactory::registerCreator(std::make_unique<PlayMenuCreator>());
