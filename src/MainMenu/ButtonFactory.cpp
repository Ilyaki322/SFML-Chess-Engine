#include "MainMenu/ButtonFactory.h"
#include "MainMenu/Menu.h"
#include "MainMenu/PlayMenuState.h"
#include "ButtonCommand/NextStateCommand.h"
#include "ButtonCommand/ExitCommand.h"
#include "ButtonCommand/PVPCommand.h"
#include "ButtonCommand/VBlackAICommand.h"
#include "ButtonCommand/VWhiteAICommand.h"
#include "ButtonCommand/PuzzleCommand.h"
#include "Assets.h"




ButtonFactory::ButtonFactory(StateMachine& stateMachine, sf::RenderWindow& window)
	: m_stateMachine(stateMachine), m_window(window) {}

buttonPtr ButtonFactory::createButton(ButtonName name, sf::Vector2f size, sf::Vector2f pos)
{
	switch (name)
	{
	case Play:
		return std::make_unique<Button>(" ",
			std::make_unique<NextStateCommand>(m_stateMachine,
				std::make_unique<PlayMenuState>(m_window, m_stateMachine)),
			size, pos);

	case Exit:
		return std::make_unique<Button>(" ",
			std::make_unique<ExitCommand>(m_stateMachine),
			size, pos);

	case Review:
		


	case VsPlayer:
		return std::make_unique<Button>(" ",
			std::make_unique<PVPCommand>(),
			size, pos);

	case VsBlackAI:
		return std::make_unique<Button>(" ",
			std::make_unique<VBlackAICommand>(),
			size, pos);

	case VsWhiteAI:
		return std::make_unique<Button>(" ",
			std::make_unique<VWhiteAICommand>(),
			size, pos);

	case Puzzles: {
		auto menu = std::make_unique<Menu>(m_window, m_stateMachine, Assets::instance().getMenu('z'));
		menu->addButton(createButton(Exit, sf::Vector2f(190, 50), sf::Vector2f(130, 560)));
		menu->addButton(createButton(FirstTimePuzzle, sf::Vector2f(190, 50), sf::Vector2f(361, 153)));
		menu->addButton(createButton(BeginnerPuzzle, sf::Vector2f(190, 50), sf::Vector2f(361, 243)));
		menu->addButton(createButton(IntermediatePuzzle, sf::Vector2f(190, 50), sf::Vector2f(361, 331)));
		menu->addButton(createButton(ExpertPuzzle, sf::Vector2f(190, 50), sf::Vector2f(361, 500)));
		menu->addButton(createButton(HardPuzzle, sf::Vector2f(190, 50), sf::Vector2f(361, 420)));

		return std::make_unique<Button>(" ",
			std::make_unique<NextStateCommand>(m_stateMachine,
				std::move(menu)), size, pos);
	}

	case FirstTimeAI:
		


	case IntermediateAI:
		


	case ExpertAI:
		


	case FirstTimePuzzle:
		return std::make_unique<Button>(" ",
			std::make_unique<PuzzleCommand>(FirstTime),
			size, pos);

	case BeginnerPuzzle:
		return std::make_unique<Button>(" ",
			std::make_unique<PuzzleCommand>(Beginner),
			size, pos);

	case IntermediatePuzzle:
		return std::make_unique<Button>(" ",
			std::make_unique<PuzzleCommand>(Intermediate),
			size, pos);

	case HardPuzzle:
		return std::make_unique<Button>(" ",
			std::make_unique<PuzzleCommand>(Hard),
			size, pos);

	case ExpertPuzzle:
		return std::make_unique<Button>(" ",
			std::make_unique<PuzzleCommand>(Expert),
			size, pos);
	default:
		break;
	}
}
