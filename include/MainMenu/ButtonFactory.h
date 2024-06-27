#pragma once
#include "Button.h"
#include "Utilities.h"

#include <memory>
#include <map>

typedef std::unique_ptr<Button> buttonPtr;
typedef std::map<ButtonName, std::unique_ptr<Button>(*)()> buttonMap;

class StateMachine;

class ButtonFactory
{
public:
	ButtonFactory() = default;

	buttonPtr createButton(ButtonName name, sf::Vector2f size, sf::Vector2f pos);
	static bool registerButton(const ButtonName name, std::unique_ptr<Button>(*f)());

private:

	static buttonMap& getMap()
	{
		static buttonMap m_map;
		return m_map;
	}
	//StateMachine& m_stateMachine;
	//sf::RenderWindow& m_window;
};