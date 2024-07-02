#pragma once
#include "Utilities.h"
#include "IObserver.h"

class GameManager;

/*
*This class represents promotion in chess.
* It presents to the board the options that the player has to choose from 
* and after it is chosen, it updates the new piece 
*/
class PromotionBox : public IObserver
{
public:
	PromotionBox(GameManager& manager, Color color);

	void draw();
	void eventUpdate(sf::Event& event, Color color) override;

	Piece getPiece() const;

private:

	sf::RectangleShape m_box;
	sf::RectangleShape m_buttons[4];
	sf::Sprite m_sprites[4];

	sf::RenderWindow& m_window;

	Piece m_piece;
	Color m_color;

};