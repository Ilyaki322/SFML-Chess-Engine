#include "FileExceptions/HistoryFileException.h"
#include "Assets.h"
#include "Button.h"
#include "ButtonCommand/ExitCommand.h"

HistoryFileException::HistoryFileException(std::string reason)
	: m_reason(reason) {}

const char* HistoryFileException::what() const noexcept
{
	return m_reason.c_str();
}

std::shared_ptr<Menu> HistoryFileException::createErrorMenu(sf::RenderWindow& window, StateMachine& stateMachine)
{
	auto menu = std::make_shared<Menu>(window, stateMachine, Assets::instance().getMenu('r'), "GameHistory");
	menu->addButton(std::make_unique<Button>(std::make_unique<ExitCommand>(stateMachine),
		sf::Vector2f(170, 60), sf::Vector2f(105, 560)));

	return std::move(menu);
}