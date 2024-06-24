#include "UI/PlayUI.h"
#include "GameManager.h"

PlayUI::PlayUI(StateMachine& stateMachine)
	:m_stateMachine(stateMachine)
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



