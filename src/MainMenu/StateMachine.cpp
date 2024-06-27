#include "MainMenu/StateMachine.h"
#include "MainMenu/MenuState.h"

#include "MainMenu/Menu.h"
#include "Assets.h"
#include "Utilities.h"
#include "Button.h"

#include "ButtonCommand/ExitCommand.h"
#include "ButtonCommand./NextStateCommand.h"
#include "ButtonCommand./PVPCommand.h"
#include "ButtonCommand./VBlackAICommand.h"
#include "ButtonCommand./VWhiteAICommand.h"
#include "ButtonCommand./PuzzleCommand.h"

StateMachine::StateMachine()
	: m_deleting(false), m_returnToMenu(false)
{
	m_window.create(sf::VideoMode(MENU_X, MENU_Y), "MainMenu");

	initStates();
	m_stateStack.push(m_menusMap[mainMenu]);
}

void StateMachine::update()
{
	while (m_window.isOpen())
	{
		m_stateStack.top()->draw();
		m_stateStack.top()->handleEvents();

		if (m_deleting)
			pop();

		if (m_returnToMenu)
			popAll();
	}
}

void StateMachine::changeState(Menus menu)
{
	m_stateStack.push(m_menusMap[menu]);
}

void StateMachine::exit()
{
	m_deleting = true;
}

void StateMachine::returnToMenu()
{
	m_returnToMenu = true;
}

void StateMachine::pop()
{
	m_deleting = false;

	if (m_stateStack.size() >= 2)
	{
		m_stateStack.pop();
		return;
	}

	m_window.close();
}

void StateMachine::popAll()
{
	for (int i = m_stateStack.size(); i > 1; i--) {
		m_stateStack.pop();
	}
	m_returnToMenu = false;
}

void StateMachine::initStates()
{
	auto mainMenuState = std::make_shared<Menu>(m_window, *this, Assets::instance().getMenu('m'));
	auto playMenuState = std::make_shared<Menu>(m_window, *this, Assets::instance().getMenu('p'));
	auto BlackAIDifficulty = std::make_shared<Menu>(m_window, *this, Assets::instance().getMenu('z'));
	auto WhiteAIDifficulty = std::make_shared<Menu>(m_window, *this, Assets::instance().getMenu('z'));
	auto PuzzleDifficultyState = std::make_shared<Menu>(m_window, *this, Assets::instance().getMenu('z'));

	mainMenuState->addButton(std::make_unique<Button>(std::make_unique<NextStateCommand>(*this, playMenu),
		sf::Vector2f(260, 50), sf::Vector2f(220, 510)));
	mainMenuState->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*this),
		sf::Vector2f(260, 50), sf::Vector2f(375, 580)));

	playMenuState->addButton(std::make_unique<Button>(std::make_unique<PVPCommand>(*this),
		sf::Vector2f(300, 70), sf::Vector2f(186, 215)));
	playMenuState->addButton(std::make_unique<Button>(std::make_unique<PVPCommand>(*this),
		sf::Vector2f(300, 70), sf::Vector2f(580, 180)));
	playMenuState->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*this),
		sf::Vector2f(190, 50), sf::Vector2f(140, 570)));
	playMenuState->addButton(std::make_unique<Button>(std::make_unique<NextStateCommand>(*this, WhiteAI),
		sf::Vector2f(300, 70), sf::Vector2f(195, 310)));
	playMenuState->addButton(std::make_unique<Button>(std::make_unique<NextStateCommand>(*this, BlackAI),
		sf::Vector2f(300, 70), sf::Vector2f(585, 275)));
	playMenuState->addButton(std::make_unique<Button>(std::make_unique<NextStateCommand>(*this, Puzzle),
		sf::Vector2f(300, 70), sf::Vector2f(390, 440)));

	BlackAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*this, 1),
		sf::Vector2f(300, 70), sf::Vector2f(370, 150)));
	BlackAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*this, 2),
		sf::Vector2f(300, 70), sf::Vector2f(370, 235)));
	BlackAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*this, 3),
		sf::Vector2f(300, 70), sf::Vector2f(370, 325)));
	BlackAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*this, 4),
		sf::Vector2f(300, 70), sf::Vector2f(370, 415)));
	BlackAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VBlackAICommand>(*this, 5),
		sf::Vector2f(300, 70), sf::Vector2f(370, 495)));
	BlackAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*this),
		sf::Vector2f(200, 50), sf::Vector2f(140, 570)));

	WhiteAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VWhiteAICommand>(*this, 1),
		sf::Vector2f(300, 70), sf::Vector2f(370, 150)));
	WhiteAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VWhiteAICommand>(*this, 2),
		sf::Vector2f(300, 70), sf::Vector2f(370, 235)));
	WhiteAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VWhiteAICommand>(*this, 3),
		sf::Vector2f(300, 70), sf::Vector2f(370, 325)));
	WhiteAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VWhiteAICommand>(*this, 4),
		sf::Vector2f(300, 70), sf::Vector2f(370, 215)));
	WhiteAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<VWhiteAICommand>(*this, 5),
		sf::Vector2f(300, 70), sf::Vector2f(370, 495)));
	WhiteAIDifficulty->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*this),
		sf::Vector2f(200, 50), sf::Vector2f(140, 570)));

	PuzzleDifficultyState->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*this, FirstTime),
		sf::Vector2f(300, 70), sf::Vector2f(370, 150)));
	PuzzleDifficultyState->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*this, Beginner),
		sf::Vector2f(300, 70), sf::Vector2f(370, 235)));
	PuzzleDifficultyState->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*this, Intermediate),
		sf::Vector2f(300, 70), sf::Vector2f(370, 325)));
	PuzzleDifficultyState->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*this, Hard),
		sf::Vector2f(300, 70), sf::Vector2f(370, 415)));
	PuzzleDifficultyState->addButton(std::make_unique<Button>(std::make_unique<PuzzleCommand>(*this, Expert),
		sf::Vector2f(300, 70), sf::Vector2f(370, 495)));
	PuzzleDifficultyState->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(*this),
		sf::Vector2f(200, 50), sf::Vector2f(140, 570)));

	m_menusMap[mainMenu] = mainMenuState;
	m_menusMap[playMenu] = playMenuState;
	m_menusMap[BlackAI] = BlackAIDifficulty;
	m_menusMap[WhiteAI] = WhiteAIDifficulty;
	m_menusMap[Puzzle] = PuzzleDifficultyState;
}
