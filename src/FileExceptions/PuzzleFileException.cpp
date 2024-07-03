#include "FileExceptions/PuzzleFileException.h"
#include "Assets.h"
#include "Button.h"
#include "ButtonCommand/ExitCommand.h"

PuzzleFileException::PuzzleFileException(std::string reason)
	: m_reason(reason) {}

const char* PuzzleFileException::what() const noexcept
{
	return m_reason.c_str();
}

std::shared_ptr<Menu> PuzzleFileException::createErrorMenu(sf::RenderWindow& window, StateMachine& stateMachine)
{
	auto menu = std::make_shared<Menu>(window, stateMachine, Assets::instance().getMenu('e'), "Puzzle");
	menu->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(stateMachine),
		sf::Vector2f(170, 60), sf::Vector2f(105, 560)));

	return std::move(menu);
}
