#include "SpecialMove.h"

#include <iostream>
#include "Board.h"

SpecialMove::SpecialMove()
	:m_passant(-1) 
{
}

/// <summary>
/// 
/// To Do:
/// 
/// the sum can be 0 although the square is in threat.
/// there are 2 options
/// 1---> change it to other sum (mabye mull of 2 prime num)
/// 
/// 2---> do 2 differents array one to the white and one to the black
/// 
/// </summary>

SpecialMove& SpecialMove::instance()
{
	static SpecialMove ins;
	return ins;
}

void SpecialMove::setBoard(int arr[] /*, std::vector<std::vector<Move>> threats*/)
{
	pieceArray = arr;
	std::vector<std::vector<Move>> threats = Board::instance().AllMoves();
	for (int i = 0; i < 64; i++) {
		threatArray[i] = 0;
	}
	for (int i = 0, j = 0; i < 64; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}
}

void SpecialMove::handleThreats(int pieceIndex , std::vector<Move> threat )
{
	int color = (pieceArray[pieceIndex] & 8) > 0 ? 8 : 16;
	int forward = color == 16 ? -1 : 1;
	int value = forward;
	/*if (pieceArray[pieceIndex] - color == PawnVal) {
		if((pieceIndex%8 !=0 || color != 16 ) && (pieceIndex % 8 != 7 || color != 8 ))
			threatArray[pieceIndex + value * 9] += value;
		if ((pieceIndex % 8 != 0 || color != 8) && (pieceIndex % 8 != 7 || color != 16))
			threatArray[pieceIndex + value * 7] += value;
		return;
	}*/
	for (int i = 0; i < threat.size(); i++) {
		threatArray[threat[i].targetSquare] += value;
	}
}

/// <summary>
/// 
/// To Do:
/// 
/// after the update check if the king is in chess ---> undo the update and return false
/// 
/// </summary>

void SpecialMove::update(int start , int end , std::vector<std::vector<Move>> threats)
{
	for (int i = 0; i < 64; i++) {
		threatArray[i] = 0;
	}
	pieceArray[end] = pieceArray[start];
	pieceArray[start] = 0;

	for (int i = 0, j = 0; i < 64; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

	int color = (pieceArray[end] & 8) > 0 ? 8 : 16;
	int forward = color == 8 ? -1 : 1;
	int piece = pieceArray[end] - color;
	if (piece == PawnVal  || piece == KingVal || piece == RookVal ) {
		if ((pieceArray[end] & 32) > 0) {
			pieceArray[end] = pieceArray[end] ^ 32;
			if (start - end == 16 * forward) {
				m_passant = end;
				return;
			}
		}
	}
	m_passant = -1;
}

bool SpecialMove::enPassant(int i)
{
	return i == m_passant;
}

bool SpecialMove::isCastle(int king ,int rook)
{
	int color = (pieceArray[rook] & WHITE) > 0 ? WHITE : BLACK;
	if ((pieceArray[rook] & RookVal) != RookVal) {
		return false;
	}
	if (((pieceArray[rook] & 32) == 0) || ((pieceArray[king] & 32) == 0)) {
		return false;
	}
	int forward = king < rook ? 1 : -1;
	for (king+=forward; king != rook  && king < 64 && king > -1 ; king += forward) {
		if (pieceArray[king] != 0 || threatArray[king]!=0 )
			return false;
	}
	return king == rook;
}


void SpecialMove::castle(int king, int rook)
{
	if (king < rook) {
		pieceArray[rook - 2] = pieceArray[rook];
		pieceArray[king + 2] = pieceArray[king];
	}
	else {
		pieceArray[rook + 3] = pieceArray[rook];
		pieceArray[king - 2] = pieceArray[king];
	}
	pieceArray[rook] = 0;
	pieceArray[king] = 0;
}
/// <summary>
/// 
/// To Do:
/// 
/// save the position of the king each turn so we can check check in O(1)
/// 
/// </summary>

bool SpecialMove::check()
{
	//return threatArray[m_kingPlace] != 0;
	return false;
}
