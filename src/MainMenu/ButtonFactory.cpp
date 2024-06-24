#include "MainMenu/ButtonFactory.h"
#include "MainMenu/Menu.h"
#include "MainMenu/PlayMenuState.h"
#include "ButtonCommand/NextStateCommand.h"
#include "ButtonCommand/ExitCommand.h"
#include "ButtonCommand/PVPCommand.h"
#include "ButtonCommand/VBlackAICommand.h"
#include "ButtonCommand/VWhiteAICommand.h"

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

	case Puzzles:
		


	case FirstTimeAI:
		


	case IntermediateAI:
		


	case ExpertAI:
		


	case FirstTimePuzzle:
		


	case BeginnerPuzzle:
		


	case IntermediatePuzzle:
		


	case HardPuzzle:
		


	case ExpertPuzzle:
		


	default:
		break;
	}
}
