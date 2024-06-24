#pragma once
#include "Button.h"
#include "Utilities.h"

#include <memory>

typedef std::unique_ptr<Button> buttonPtr;

class StateMachine;
class ButtonFactory
{
public:
	ButtonFactory(StateMachine& stateMachine, sf::RenderWindow& window);

	buttonPtr createButton(ButtonName name, sf::Vector2f size, sf::Vector2f pos);

private:

	StateMachine& m_stateMachine;
	sf::RenderWindow& m_window;
};