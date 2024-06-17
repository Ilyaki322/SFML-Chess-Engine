#pragma once
#include "Utilities.h"
#include "IObserver.h"

class GameManager;
class PromotionBox : public IObserver
{
public:
	PromotionBox(GameManager& manager, Color color);

	void draw();
	void eventUpdate(sf::Event& event, Color color) override;

	Piece getPiece();

private:

	sf::RectangleShape m_box;
	sf::RectangleShape m_buttons[4];
	sf::Sprite m_sprites[4];

	sf::RenderWindow& m_window;

	Piece m_piece;
	Color m_color;

};