#include "MenuFactory/MenuFactory.h"

MenuFactory::MenuFactory(sf::RenderWindow& window, StateMachine& stateMachine)
	: m_window(window), m_stateMachine(stateMachine) {}

bool MenuFactory::registerCreator(creatorPtr creator)
{
	getVector().push_back(std::move(creator));
	return true;
}

/*
* Since Menus transition from one to another, they need pointers to each other
* So we first have to create all menus first, and then add buttons to them.
*/
std::map<std::string, menuPtr> MenuFactory::initMenus()
{
	std::vector<std::shared_ptr<Menu>> menus;
	for (int i = 0; i < getVector().size(); i++)
	{
		menus.push_back(getVector()[i]->createMenu(m_window, m_stateMachine));
	}

	for (int i = 0; i < getVector().size(); i++)
	{
		getVector()[i]->addButtons(menus[i]);
	}

	std::map<std::string, menuPtr> map;

	for (auto& i : menus)
	{
		map.emplace(i->getName(), i);
	}

	return map;
}
