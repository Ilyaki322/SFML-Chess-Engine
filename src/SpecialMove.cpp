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
	s.backUpPieceArray = pieceArray;
	s.lastBKing = m_bKing;
	s.lastWKing = m_wKing;
	lastMoves.push_front(s);
}

void SpecialMove::undo()
{
	auto backUp = lastMoves.begin();
	blackThreatArray = backUp->backUpBlackThreatArray;
	whiteThreatArray = backUp->backUpWhiteThreatArray;
	pieceArray = backUp->backUpPieceArray;
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
	pieceArray = arr;
	std::vector<std::vector<Move>> threats = Board::instance().AllMoves();

	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}
	for (int i = 0, j = 0; i < SIZE; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
			if ((pieceArray[i] & 0b111) == KingVal) {
				int color = (pieceArray[i] & WHITE) > 0 ? WHITE : BLACK;
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
	int color = (pieceArray[pieceIndex] & WHITE) > 0 ? WHITE : BLACK;
	for (int i = 0; i < threat.size(); i++) {
		if ((pieceArray[threat[i].startSquare] & 0b111) == PawnVal)
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
	int color = (pieceArray[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;
	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}

	pieceArray[move.targetSquare] = pieceArray[move.startSquare];
	pieceArray[move.startSquare] = 0;

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (pieceArray[i] != 0) {
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

	int startPiece = pieceArray[move.startSquare] & 0b111;
	int startColor = (pieceArray[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;
	int targetColor = (pieceArray[move.targetSquare] & WHITE) > 0 ? WHITE : BLACK;

	if (pieceArray[move.targetSquare]!= 0 &&  startColor == targetColor)
		return Castle; 

	int forward = startColor == WHITE ? 1 : -1;
	if (startPiece == PawnVal){
		if (pieceArray[move.targetSquare] == 0) {
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

	int color = (pieceArray[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;

	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}

	pieceArray[move.targetSquare] = pieceArray[move.startSquare];
	pieceArray[move.startSquare] = 0;

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

	if (move.startSquare == m_bKing) m_bKing = move.targetSquare;
	if (move.startSquare == m_wKing) m_wKing = move.targetSquare;

	int forward = color == WHITE ? 1 : -1;
	int piece = pieceArray[move.targetSquare] & 0b111;
	if (piece == PawnVal || piece == KingVal || piece == RookVal) {
		if ((pieceArray[move.targetSquare] & Moved) > 0) {
			pieceArray[move.targetSquare] = pieceArray[move.targetSquare] ^ Moved;
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
	int color = (pieceArray[rook] & WHITE) > 0 ? WHITE : BLACK;
	if ((pieceArray[rook] & 0b111) != RookVal) {
		return false;
	}
	if (((pieceArray[rook] & Moved) == 0) || ((pieceArray[king] & Moved) == 0)) {
		return false;
	}
	int forward = king < rook ? 1 : -1;
	for (king+=forward; king != rook  && king < SIZE && king > -1 ; king += forward) {
		if (pieceArray[king] != 0)
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
	int color = (pieceArray[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;
	if (move.startSquare < move.targetSquare) {
		pieceArray[move.targetSquare - 2] = pieceArray[move.targetSquare];
		pieceArray[move.startSquare + 2] = pieceArray[move.startSquare];
		if (color == WHITE) m_wKing = move.startSquare + 2;
		else m_bKing = move.startSquare + 2;
	}
	else {
		pieceArray[move.targetSquare + 3] = pieceArray[move.targetSquare];
		pieceArray[move.startSquare - 2] = pieceArray[move.startSquare];
		if (color == WHITE) m_wKing = move.startSquare - 2;
		else m_bKing = move.startSquare - 2;
	}
	pieceArray[move.targetSquare] = 0;
	pieceArray[move.startSquare] = 0;

	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

}

void SpecialMove::enPassantMove(Move move, std::vector<std::vector<Move>> threats)
{
	save();
	int side = (pieceArray[move.startSquare] & WHITE) > 0 ? DOWN : UP;

	pieceArray[move.targetSquare] = pieceArray[move.startSquare];
	pieceArray[move.startSquare] = 0;
	pieceArray[move.targetSquare + side] = 0;

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

}

void SpecialMove::promotionMove(Move move, std::vector<std::vector<Move>> threats, int promotedVal)
{
	save();
	int color = (pieceArray[move.startSquare] & 0b11000);
	pieceArray[move.startSquare] = 0;
	pieceArray[move.targetSquare] = promotedVal | color;

	for (int i = 0; i < SIZE; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
	}

	for (int i = 0, j = 0; i < SIZE; i++) {
		if (pieceArray[i] != 0) {
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
	if ((pieceArray[pos] & 32) > 0)
	{
		return true;
	}

	return false;
}
