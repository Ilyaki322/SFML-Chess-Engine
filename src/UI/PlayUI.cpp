#include "UI/PlayUI.h"
#include "GameManager.h"

PlayUI::PlayUI(StateMachine& stateMachine)
	:m_stateMachine(stateMachine), m_newBackground(false)
{
	m_backGround.setTexture(Assets::instance().getUITexture("background"));
	m_backGround.setPosition({ 0, 0 });
}

void PlayUI::buttonClicked(const sf::Vector2f& loc)
{
	for (auto& button : m_button)
	{
		if (button->getGlobalBounds().contains(loc))
		{
			button->click();
		}
	}
}

StateMachine& PlayUI::getStateMachine() const
{
	return m_stateMachine;
}

void PlayUI::deleteButtons()
{
	m_button.clear();
}



