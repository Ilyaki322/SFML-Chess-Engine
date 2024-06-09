#include "SpecialMove.h"

#include <iostream>
#include "Board.h"

SpecialMove::SpecialMove()
	:m_passant(-1) 
{
}

void SpecialMove::undo(std::array<int, 64> white, std::array<int, 64> black, int start, int end, int undoEnd)
{
	blackThreatArray = black;
	whiteThreatArray = white;
	pieceArray[start] = pieceArray[end];
	pieceArray[end] = undoEnd;

	for (int i = 0; i < 64; i++)
	{
		Board::instance().debug(sf::Color::White, i);
	}

	for (int i = 0; i < 64; i++)
	{
		if (whiteThreatArray[i] != 0)
		{
			Board::instance().debug(sf::Color::Red, i);
		}

	}
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

void SpecialMove::setBoard(std::array<int, 64> arr /*, std::vector<std::vector<Move>> threats*/)
{
	pieceArray = arr;
	std::vector<std::vector<Move>> threats = Board::instance().AllMoves();

	for (int i = 0; i < 64; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}
	for (int i = 0, j = 0; i < 64; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
			if ((pieceArray[i] & 0b111) == KingVal) {
				int color = (pieceArray[i] & WHITE) > 0 ? WHITE : BLACK;
				if (color == WHITE) m_wKing = i;
				else m_bKing = i;
			}
		}
	}
}

void SpecialMove::handleThreats(int pieceIndex , std::vector<Move> threat )
{
	std::cout << m_bKing << std::endl;
	int color = (pieceArray[pieceIndex] & WHITE) > 0 ? WHITE : BLACK;
	for (int i = 0; i < threat.size(); i++) {
		if ((pieceArray[threat[i].startSquare] & 0b111) == PawnVal)
		{
			if (threat[i].startSquare + 8 == threat[i].targetSquare || threat[i].startSquare - 8 == threat[i].targetSquare ||
				threat[i].startSquare + 16 == threat[i].targetSquare || threat[i].startSquare - 16 == threat[i].targetSquare)
			{
				continue;
			}
		}
		if (color == WHITE)
		{
			whiteThreatArray[threat[i].targetSquare]++;
			Board::instance().debug(sf::Color::Red, threat[i].targetSquare);
		}	
		else
		{
			blackThreatArray[threat[i].targetSquare]++;
		}
	}
}

/// <summary>
/// 
/// To Do:
/// 
/// after the update check if the king is in chess ---> undo the update and return false
/// 
/// </summary>

bool SpecialMove::update(int start , int end , std::vector<std::vector<Move>> threats, bool fakeMove)
{
	int color = (pieceArray[start] & WHITE) > 0 ? WHITE : BLACK;
	std::array<int, 64> undoBlackThreatArray(blackThreatArray);
	std::array<int, 64> undoWhiteThreatArray(whiteThreatArray);
	for (int i = 0; i < 64; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
		Board::instance().debug(sf::Color::White, i);
	}
	int undoLastMove = pieceArray[end];
	pieceArray[end] = pieceArray[start];
	pieceArray[start] = 0;

	for (int i = 0, j = 0; i < 64; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

	int wKingbackup = m_wKing;
	int bKingbackup = m_bKing;
	if (start == m_bKing) m_bKing = end;
	if (start == m_wKing) m_wKing = end;

	
	if (whiteThreatArray[m_bKing] != 0 && color == BLACK) {
		//m_bKing = start;
		undo(undoWhiteThreatArray, undoBlackThreatArray, start, end, undoLastMove);
		return false;
	}
	if (blackThreatArray[m_wKing] != 0 && color == WHITE) {
		//m_wKing = start;
		undo(undoWhiteThreatArray, undoBlackThreatArray, start, end, undoLastMove);
		return false;
	}
	if (fakeMove)
	{
		m_wKing = wKingbackup;
		m_bKing = bKingbackup;
		undo(undoWhiteThreatArray, undoBlackThreatArray, start, end, undoLastMove);
		return true;
	}

	int forward = color == WHITE ? 1 : -1;
	int piece = pieceArray[end] & 0b111;
	if (piece  == PawnVal  || piece == KingVal || piece == RookVal ) {
		if ((pieceArray[end] & 32) > 0) {
			pieceArray[end] = pieceArray[end] ^ 32;
			if (start - end == 16 * forward) {
				m_passant = end;
				return true;
			}
		}
	}
	m_passant = -1;
	return true;
}

bool SpecialMove::enPassant(int i)
{
	return i == m_passant;
}

bool SpecialMove::isCastle(int king ,int rook)
{
	int color = (pieceArray[rook] & WHITE) > 0 ? WHITE : BLACK;
	if ((pieceArray[rook] & 0b111) != RookVal) {
		return false;
	}
	if (((pieceArray[rook] & 32) == 0) || ((pieceArray[king] & 32) == 0)) {
		return false;
	}
	int forward = king < rook ? 1 : -1;
	for (king+=forward; king != rook  && king < 64 && king > -1 ; king += forward) {
		if (pieceArray[king] != 0)
			return false;
		if (color == WHITE && blackThreatArray[king] != 0)
			return false;
		else if (color == BLACK && whiteThreatArray[king] != 0)
			return false;
		
	}
	return king == rook;
}


void SpecialMove::castle(int king, int rook)
{
	int color = (pieceArray[king] & WHITE) > 0 ? WHITE : BLACK;
	if (king < rook) {
		pieceArray[rook - 2] = pieceArray[rook];
		pieceArray[king + 2] = pieceArray[king];
		if (color == WHITE) m_wKing = king + 2;
		else m_bKing = king + 2;
	}
	else {
		pieceArray[rook + 3] = pieceArray[rook];
		pieceArray[king - 2] = pieceArray[king];
		if (color == WHITE) m_wKing = king - 2;
		else m_bKing = king - 2;
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

bool SpecialMove::check(int color)
{
	if (color == WHITE) return blackThreatArray[m_wKing] != 0;
	if (color == BLACK) return whiteThreatArray[m_bKing] != 0;
}

bool SpecialMove::canDouble(const int pos) const
{
	if ((pieceArray[pos] & 32) > 0)
	{
		return true;
	}

	return false;
}
