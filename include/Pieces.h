#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

enum Color {White , Black};

class Board;
//class Tile;

class Pieces {
public:
	virtual ~Pieces() = default;
	Pieces(sf::Texture image , sf::Vector2f position ,Color side);
	int getValue()const;
	void draw(sf::RenderWindow& w)const;
	virtual bool isValid()const =0;
	virtual std::vector<std::pair<int,int>> possibleMoves(Board *)const =0;

private:
	sf::Sprite m_piece;
	Color m_side;
	int m_value;
};