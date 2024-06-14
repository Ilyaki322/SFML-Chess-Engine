#pragma once 
#include <array>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> //DEBUG
const int SIZE = 64;
const int FirstRow = 8 , LastRow = 55;
const int Moved = 32;
const int BKingBegin = 4, WKingBegin = 60;
enum EndMove {
	EnPassant,
	Castle,
	Promotion,
	Regular

};

enum Piece {
	KingVal = 1,
	PawnVal = 2,
	KnightVal = 3,
	BishopVal = 4,
	RookVal = 5,
	QueenVal = 6
};

struct Move
{
	//--- for normal move
	int startSquare;
	int targetSquare;

	//--- for specialMove

	int specialStartSquare;
	int specialTargetSquare;
	Piece promotionVal;

	/*
	* example specialMove:
	*	enPassant --> startSquare = start  -- targetSquare = end -- SpecialStart = start -- speciaTarget = enpassant pawn 
	*	castle --> startSquare = start  -- targetSquare = start+2 -- SpecialStart = RookPlace -- specialTarget = rookPlac-2 
	*	promotion --> startSquare = start  -- targetSquare = end -- promotionVal = val;
	*	
	*/
	
};
struct Stack {
	Move move;
	int lastWKing;
	int lastBKing;
	int enPassant;
	std::array<int, 64> backUpm_board;
	std::array<int, 64> backUpBlackThreatArray;
	std::array<int, 64> backUpWhiteThreatArray;
};

const int BLACK = 16;
const int WHITE = 8;

enum Color { White = WHITE, Black = BLACK };


enum MovementDirection { All = 0,  Forward = 8 ,  Diagonal1 = 9  , Diagonal2 = 7 , Side = 1 };

const int LEFT = -1;
const int RIGHT = 1;
const int TOP_RIGHT = -7;
const int TOP_LEFT = -9;
const int BOT_LEFT = 7;
const int BOT_RIGHT = 9;
const int UP = -8;
const int DOWN = 8;


const sf::Color MOVEABLE_TILE = sf::Color(sf::Uint32(0x00F0F0FF));
const sf::Color ERROR_TILE = sf::Color::Red;
const sf::Color LAST_TURN_TILE = sf::Color(255, 165, 0);

const int TILE_SIZE = 96;