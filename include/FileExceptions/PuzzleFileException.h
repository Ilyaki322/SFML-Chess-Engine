#pragma once
#include "MainMenu/Menu.h"
#include "SFML/Graphics.hpp"
#include "MainMenu/StateMachine.h"

#include <memory>
#include <exception>
#include <string>

class PuzzleFileException : public std::exception
{
public:
	PuzzleFileException(std::string reason);

	const char* what() const noexcept;
	std::shared_ptr<Menu> createErrorMenu(sf::RenderWindow& window, StateMachine& stateMachine);

private:

	std::string m_reason;
};