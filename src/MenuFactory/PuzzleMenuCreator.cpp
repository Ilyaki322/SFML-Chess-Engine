#include "MenuFactory/PuzzleMenuCreator.h"
#include "MenuFactory/MenuFactory.h"
#include "ButtonCommand/ExitCommand.h"
#include "ButtonCommand/PuzzleCommand.h"
#include "Assets.h"

std::shared_ptr<Menu> PuzzleMenuCreator::createMenu(sf::RenderWindow& window, StateMachine& stateMachine)
{
	m_window = &window;
	m_stateMachine = &stateMachine;
	return std::make_shared<Menu>(window, stateMachine, Assets::instance().getMenu('z'), "Puzzle");
}

void PuzzleMenuCreator::addButtons(std::shared_ptr<Menu> menu)
{
	menu->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*m_stateMachine, FirstTime),
		sf::Vector2f(300, 70), sf::Vector2f(370, 150)));
	menu->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*m_stateMachine, Beginner),
		sf::Vector2f(300, 70), sf::Vector2f(370, 235)));
	menu->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*m_stateMachine, Intermediate),
		sf::Vector2f(300, 70), sf::Vector2f(370, 325)));
	menu->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*m_stateMachine, Hard),
		sf::Vector2f(300, 70), sf::Vector2f(370, 415)));
	menu->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*m_stateMachine, Expert),
		sf::Vector2f(300, 70), sf::Vector2f(370, 495)));
	menu->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*m_stateMachine),
		sf::Vector2f(200, 50), sf::Vector2f(140, 570)));
}

bool PuzzleMenuCreator::m_register = MenuFactory::registerCreator(std::make_unique<PuzzleMenuCreator>());