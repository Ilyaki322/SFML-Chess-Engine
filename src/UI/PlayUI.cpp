#include "UI/PlayUI.h"
#include "GameManager.h"

PlayUI::PlayUI(StateMachine& stateMachine)
	:m_stateMachine(stateMachine), newBackground(false)
{
	m_backGround.setTexture(Assets::instance().getTexture('s'));
	m_backGround.setPosition({ 768, 0 });
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



