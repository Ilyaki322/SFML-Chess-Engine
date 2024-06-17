#include "PromotionBox.h"
#include "Assets.h"
#include "GameManager.h"

PromotionBox::PromotionBox(GameManager& manager, Color color)
	: IObserver(manager), m_box({240, 70}), m_window(manager.getWindow()),
	  m_piece(PawnVal), m_color(color)
{
	char pieces[4] = { 'q', 'r', 'b', 'n' };
	if (color == Black)
	{
		for (int i = 0; i < 4; i++)
		{
			pieces[i] = toupper(pieces[i]);
		}
	}

	m_box.setFillColor(sf::Color::Magenta);
	m_box.setPosition({ 200, 200 });

	for (int i = 0; i < 4; i++)
	{
		auto &texture = Assets::instance().getTexture(pieces[i]);
		m_sprites[i].setTexture(texture);
		m_sprites[i].setScale(50.f / texture.getSize().x, 50.f / texture.getSize().y);
	}

	for (int i = 0; i < 4; i++)
	{
		m_buttons[i].setFillColor(sf::Color::Blue);
		m_buttons[i].setSize({ 50, 50 });
		m_buttons[i].setPosition(m_box.getPosition().x + 5 + 60 * i, m_box.getPosition().y + 10);
		m_sprites[i].setPosition(m_buttons[i].getPosition());
	}
}

void PromotionBox::draw()
{
	m_window.draw(m_box);

	for (int i = 0; i < 4; i++)
	{
		m_window.draw(m_buttons[i]);
		m_window.draw(m_sprites[i]);
	}
}

Piece PromotionBox::getPiece()
{
	return m_piece;
}

void PromotionBox::eventUpdate(sf::Event& event, Color color)
{
	if (event.type != sf::Event::MouseButtonReleased || color != m_color) return;

	auto pos = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
	sf::RectangleShape tempShape({ 768.f,768.f });

	if (m_buttons[0].getGlobalBounds().contains(pos))
	{
		m_piece = QueenVal;
	}
	else if (m_buttons[1].getGlobalBounds().contains(pos))
	{
		m_piece = RookVal;
	}
	else if (m_buttons[2].getGlobalBounds().contains(pos))
	{
		m_piece = BishopVal;
	}
	else if (m_buttons[3].getGlobalBounds().contains(pos))
	{
		m_piece = KnightVal;
	}
	else
	{
		m_piece = PawnVal;
	}
}
