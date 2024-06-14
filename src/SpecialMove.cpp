#include "SpecialMove.h"

#include <iostream>
#include "Board.h"

SpecialMove::SpecialMove()
	:m_passant(-1) 
{
}

void SpecialMove::save()
{
	struct Stack s;
	s.backUpBlackThreatArray = blackThreatArray;
	s.backUpWhiteThreatArray = whiteThreatArray;
	s.backUpm_board = m_board;
	s.lastBKing = m_bKing;
	s.lastWKing = m_wKing;
	lastMoves.push_front(s);
}

void SpecialMove::undo()
{
	auto backUp = lastMoves.begin();
	blackThreatArray = backUp->backUpBlackThreatArray;
	whiteThreatArray = backUp->backUpWhiteThreatArray;
	m_board = backUp->backUpm_board;
	m_bKing= backUp->lastBKing ;
	m_wKing = backUp->lastWKing;
	lastMoves.pop_front();
}

SpecialMove& SpecialMove::instance()
{
	static SpecialMove ins;
	return ins;
}

void SpecialMove::setBoard(std::array<int, SIZE> arr)
{
	m_board = arr;
	std::vector<std::vector<Move>> threats = Board::instance().AllMoves();

	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}
	for (int i = 0, j = 0; i < SIZE; i++) {
		if (m_board[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
			if ((m_board[i] & 0b111) == KingVal) {
				int color = (m_board[i] & WHITE) > 0 ? WHITE : BLACK;
				if (color == WHITE)
				{
					m_wKing = i;
				}
				else
				{
					m_bKing = i;
				}
			}
		}
	}
	save();
}

void SpecialMove::handleThreats(int pieceIndex , std::vector<Move> threat )
{
	int color = (m_board[pieceIndex] & WHITE) > 0 ? WHITE : BLACK;
	for (int i = 0; i < threat.size(); i++) {
		if ((m_board[threat[i].startSquare] & 0b111) == PawnVal)
		{
			if (threat[i].startSquare + UP == threat[i].targetSquare || threat[i].startSquare + DOWN == threat[i].targetSquare ||
				threat[i].startSquare + UP*2 == threat[i].targetSquare || threat[i].startSquare +DOWN*2 == threat[i].targetSquare)
			{
				continue;
			}
		}
		if (color == WHITE)
		{
			whiteThreatArray[threat[i].targetSquare]++;
		}	
		else
		{
			blackThreatArray[threat[i].targetSquare]++;
		}
	}
}

bool SpecialMove::fakeMove(Move move ,  std::vector<std::vector<Move>> threats)
{
	save();
	bool check = true;
	int color = (m_board[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;
	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}

	m_board[move.targetSquare] = m_board[move.startSquare];
	m_board[move.startSquare] = 0;

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (m_board[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

	
	if (move.startSquare == m_bKing) m_bKing = move.targetSquare;
	if (move.startSquare == m_wKing) m_wKing = move.targetSquare;

	if (whiteThreatArray[m_bKing] != 0 && color == BLACK) {
		check = false;
	}

	if (blackThreatArray[m_wKing] != 0 && color == WHITE) {
		check= false;
	}
	undo();

	return check;
}

EndMove SpecialMove::MoveType(Move move)const
{
	if (move.targetSquare < 0) return Promotion;

	int startPiece = m_board[move.startSquare] & 0b111;
	int startColor = (m_board[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;
	int targetColor = (m_board[move.targetSquare] & WHITE) > 0 ? WHITE : BLACK;

	if (m_board[move.targetSquare]!= 0 &&  startColor == targetColor)
		return Castle; 

	int forward = startColor == WHITE ? 1 : -1;
	if (startPiece == PawnVal){
		if (m_board[move.targetSquare] == 0) {
			if (move.startSquare - move.targetSquare == 7 * forward ||
				move.startSquare - move.targetSquare == 9 * forward) {
				return EnPassant;
			}
		}
		if (move.targetSquare < FirstRow || move.targetSquare > LastRow) {
			return Promotion;
		}
	}
	return Regular;
}

void SpecialMove::doMove(Move move , std::vector<std::vector<Move>> threats)
{
	save();

	int color = (m_board[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;

	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}

	m_board[move.targetSquare] = m_board[move.startSquare];
	m_board[move.startSquare] = 0;

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (m_board[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

	if (move.startSquare == m_bKing) m_bKing = move.targetSquare;
	if (move.startSquare == m_wKing) m_wKing = move.targetSquare;

	int forward = color == WHITE ? 1 : -1;
	int piece = m_board[move.targetSquare] & 0b111;
	if (piece == PawnVal || piece == KingVal || piece == RookVal) {
		if ((m_board[move.targetSquare] & Moved) > 0) {
			m_board[move.targetSquare] = m_board[move.targetSquare] ^ Moved;
			if (move.startSquare - move.targetSquare == DOWN*2 * forward) {
				m_passant = move.targetSquare;
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
	if (king != BKingBegin && king != WKingBegin)
		return false;
	int color = (m_board[rook] & WHITE) > 0 ? WHITE : BLACK;
	if ((m_board[rook] & 0b111) != RookVal) {
		return false;
	}
	if (((m_board[rook] & Moved) == 0) || ((m_board[king] & Moved) == 0)) {
		return false;
	}
	int forward = king < rook ? 1 : -1;
	for (king+=forward; king != rook  && king < SIZE && king > -1 ; king += forward) {
		if (m_board[king] != 0)
			return false;
		if (color == WHITE && blackThreatArray[king] != 0)
			return false;
		else if (color == BLACK && whiteThreatArray[king] != 0)
			return false;
		
	}
	return king == rook;
}


void SpecialMove::castle(Move move, std::vector<std::vector<Move>> threats)
{
	save();
	int color = (m_board[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;
	if (move.startSquare < move.targetSquare) {
		m_board[move.targetSquare - 2] = m_board[move.targetSquare];
		m_board[move.startSquare + 2] = m_board[move.startSquare];
		if (color == WHITE) m_wKing = move.startSquare + 2;
		else m_bKing = move.startSquare + 2;
	}
	else {
		m_board[move.targetSquare + 3] = m_board[move.targetSquare];
		m_board[move.startSquare - 2] = m_board[move.startSquare];
		if (color == WHITE) m_wKing = move.startSquare - 2;
		else m_bKing = move.startSquare - 2;
	}
	m_board[move.targetSquare] = 0;
	m_board[move.startSquare] = 0;

	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (m_board[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

}

void SpecialMove::enPassantMove(Move move, std::vector<std::vector<Move>> threats)
{
	save();
	int side = (m_board[move.startSquare] & WHITE) > 0 ? DOWN : UP;

	m_board[move.targetSquare] = m_board[move.startSquare];
	m_board[move.startSquare] = 0;
	m_board[move.targetSquare + side] = 0;

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (m_board[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

}

void SpecialMove::promotionMove(Move move, std::vector<std::vector<Move>> threats, int promotedVal)
{
	save();
	int color = (m_board[move.startSquare] & 0b11000);
	m_board[move.startSquare] = 0;
	m_board[move.targetSquare] = promotedVal | color;

	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (m_board[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}
}

bool SpecialMove::check(int color)
{
	if (color == WHITE) return blackThreatArray[m_wKing] != 0;
	if (color == BLACK) return whiteThreatArray[m_bKing] != 0;
}

bool SpecialMove::canDouble(const int pos) const
{
	if ((m_board[pos] & 32) > 0)
	{
		return true;
	}

	return false;
}
