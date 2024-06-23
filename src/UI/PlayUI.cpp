#include "UI/PlayUI.h"

PlayUI::PlayUI()
{
	m_backGround.setTexture(Assets::instance().getTexture('s'));
	m_backGround.setPosition({ 768, 0 });
}
