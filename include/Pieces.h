#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Utilities.h"


class Pieces {
public:

	virtual ~Pieces() = default;
	Pieces(sf::Texture &image , sf::Vector2f position ,Color side , char symbol);

	int getValue()const;
	int getPosition() const;
	Color getColor() const;

	void draw(sf::RenderWindow& w)const;
	void setPosition(sf::Vector2f pos);
	void rotate(const float rotation);

	virtual std::vector<Move> generateMoves() const  = 0;
	char getSymbol();

private:

	
	int m_value;

protected:

	void slidingMoves(const int direction, std::vector<Move> &moves) const;

	sf::Sprite m_piece;
	Color m_side;
	char symbol;
};