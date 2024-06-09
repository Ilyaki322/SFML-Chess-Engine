#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

const int BLACK = 16;
const int WHITE = 8;

enum Color {White = WHITE , Black = BLACK};

struct Move
{
	int startSquare;
	int targetSquare;
};

const int LEFT = -1;
const int RIGHT = 1;
const int TOP_RIGHT = -7;
const int TOP_LEFT = -9;
const int BOT_LEFT = 7;
const int BOT_RIGHT = 9;
const int UP = -8;
const int DOWN = 8;


class Pieces {
public:

	virtual ~Pieces() = default;
	Pieces(sf::Texture &image , sf::Vector2f position ,Color side);

	int getValue()const;
	int getPosition() const;
	Color getColor() const;

	void draw(sf::RenderWindow& w)const;
	void setPosition(sf::Vector2f pos);
	void rotate(const float rotation);

	virtual std::vector<Move> generateMoves() const  = 0;
	
private:

	
	int m_value;

protected:

	void slidingMoves(const int direction, std::vector<Move> &moves) const;

	sf::Sprite m_piece;
	Color m_side;
};