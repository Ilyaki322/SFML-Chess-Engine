#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

enum Color {White = 8 , Black = 16};

const int LEFT = -1;
const int RIGHT = 1;
const int TOP_RIGHT = -7;
const int TOP_LEFT = -9;
const int BOT_LEFT = 7;
const int BOT_RIGHT = 9;
const int UP = 8;
const int DOWN = -8;

class Board;
//class Tile;

class Pieces {
public:
	virtual ~Pieces() = default;
	Pieces(sf::Texture &image , sf::Vector2f position ,Color side);
	int getValue()const;
	void draw(sf::RenderWindow& w)const;
	virtual bool isValid(const int squares[], const int target)const = 0;
	virtual std::vector<std::pair<int,int>> possibleMoves(Board *)const =0;
	void setPosition(sf::Vector2f pos);
	int getPosition() const;

private:
	sf::Sprite m_piece;
	int m_value;

protected:
	Color m_side;
};