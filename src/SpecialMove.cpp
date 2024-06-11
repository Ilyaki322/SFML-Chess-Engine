#include "SpecialMove.h"

#include <iostream>
#include "Board.h"

SpecialMove::SpecialMove()
	:m_passant(-1) 
{
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

	struct Stack s;
	s.backUpBlackThreatArray = blackThreatArray;
	s.backUpWhiteThreatArray = whiteThreatArray;
	s.backUpPieceArray = pieceArray;
	s.lastBKing =  m_bKing; 
	s.lastWKing = m_wKing;
	lastMoves.push_front(s);
	//for (int i = 0; i < 64; i++) {
	//	if (i % 8 == 0)
	//		std::cout << '\n';
	//	std::cout << lastMoves.begin()->backUpPieceArray[i] << ' ';
	//}
	//std::cout << '\n';
	//for (int i = 0; i < 64; i++) {
	//	if (i % 8 == 0)
	//		std::cout << '\n';
	//	std::cout << pieceArray[i] << ' ';
	//}
	//m_lastStart = m_lastTarget = 0;

	//backUpBlackThreatArray = blackThreatArray;
	//backUpWhiteThreatArray = whiteThreatArray;

	//m_lastBKing = m_bKing;
	//m_lastWKing = m_wKing;
}

void SpecialMove::handleThreats(int pieceIndex , std::vector<Move> threat )
{
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

bool SpecialMove::fakeMove(Move move ,  std::vector<std::vector<Move>> threats)
{
	//bool check = true;
	//int color = (pieceArray[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;
	//backUpBlackThreatArray = blackThreatArray;
	//backUpWhiteThreatArray = whiteThreatArray;
	//for (int i = 0; i < 64; i++) {
	//	blackThreatArray[i] = 0;
	//	whiteThreatArray[i] = 0;
	//	Board::instance().debug(sf::Color::White, i);
	//}
	//m_lastPiece = pieceArray[move.targetSquare];
	//m_lastStart = move.startSquare;
	//m_lastTarget = move.targetSquare;
	//pieceArray[move.targetSquare] = pieceArray[move.startSquare];
	//pieceArray[move.startSquare] = 0;

	//for (int i = 0, j = 0; i < 64; i++) {
	//	if (pieceArray[i] != 0) {
	//		handleThreats(i, threats[j]);
	//		j++;
	//	}
	//}
	//m_lastBKing = m_bKing;
	//m_lastWKing = m_wKing;
	//
	//if (move.startSquare == m_bKing) m_bKing = move.targetSquare;
	//if (move.startSquare == m_wKing) m_wKing = move.targetSquare;

	//if (whiteThreatArray[m_bKing] != 0 && color == BLACK) {
	//	check = false;
	//}

	//if (blackThreatArray[m_wKing] != 0 && color == WHITE) {
	//	check= false;
	//}


	//undo();

	//return check;

	struct Stack s;
	s.backUpBlackThreatArray = blackThreatArray;
	s.backUpWhiteThreatArray = whiteThreatArray;
	s.backUpPieceArray = pieceArray;
	s.lastBKing = m_bKing;
	s.lastWKing = m_wKing;
	lastMoves.push_front(s);
	bool check = true;
	int color = (pieceArray[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;
	for (int i = 0; i < 64; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
		Board::instance().debug(sf::Color::White, i);
	}

	pieceArray[move.targetSquare] = pieceArray[move.startSquare];
	pieceArray[move.startSquare] = 0;

	for (int i = 0, j = 0; i < 64; i++) {
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
		if (move.targetSquare < 8 || move.targetSquare > 55) {
			return Promotion;
		}
	}
	return Regular;
}

void SpecialMove::doMove(Move move , std::vector<std::vector<Move>> threats)
{
	//m_lastPiece = pieceArray[move.targetSquare];
	//m_lastStart = move.startSquare;
	//m_lastTarget = move.targetSquare;
	//m_lastBKing = m_bKing;
	//m_lastWKing = m_wKing;
	//
	//int color = (pieceArray[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;

	//for (int i = 0; i < 64; i++) {
	//	blackThreatArray[i] = 0;
	//	whiteThreatArray[i] = 0;
	//	Board::instance().debug(sf::Color::White, i);
	//}

	//pieceArray[move.targetSquare] = pieceArray[move.startSquare];
	//pieceArray[move.startSquare] = 0;

	//for (int i = 0, j = 0; i < 64; i++) {
	//	if (pieceArray[i] != 0) {
	//		handleThreats(i, threats[j]);
	//		j++;
	//	}
	//}

	//if (move.startSquare == m_bKing) m_bKing = move.targetSquare;
	//if (move.startSquare == m_wKing) m_wKing = move.targetSquare;

	//int forward = color == WHITE ? 1 : -1;
	//int piece = pieceArray[move.targetSquare] & 0b111;
	//if (piece == PawnVal || piece == KingVal || piece == RookVal) {
	//	if ((pieceArray[move.targetSquare] & 32) > 0) {
	//		pieceArray[move.targetSquare] = pieceArray[move.targetSquare] ^ 32;
	//		if (move.startSquare - move.targetSquare == 16 * forward) {
	//			m_passant = move.targetSquare;
	//			return ;
	//		}
	//	}
	//}
	//m_passant = -1;


	struct Stack s;
	s.backUpBlackThreatArray = blackThreatArray;
	s.backUpWhiteThreatArray = whiteThreatArray;
	s.backUpPieceArray = pieceArray;
	s.lastBKing = m_bKing;
	s.lastWKing = m_wKing;
	lastMoves.push_front(s);

	int color = (pieceArray[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;

	for (int i = 0; i < 64; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
		Board::instance().debug(sf::Color::White, i);
	}

	pieceArray[move.targetSquare] = pieceArray[move.startSquare];
	pieceArray[move.startSquare] = 0;

	for (int i = 0, j = 0; i < 64; i++) {
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
		if ((pieceArray[move.targetSquare] & 32) > 0) {
			pieceArray[move.targetSquare] = pieceArray[move.targetSquare] ^ 32;
			if (move.startSquare - move.targetSquare == 16 * forward) {
				m_passant = move.targetSquare;
				return;
			}
		}
	}
	m_passant = -1;
}

//bool SpecialMove::update(int start , int end , std::vector<std::vector<Move>> threats, bool fakeMove)
//{
//	int color = (pieceArray[start] & WHITE) > 0 ? WHITE : BLACK;
//	std::array<int, 64> undoBlackThreatArray(blackThreatArray);
//	std::array<int, 64> undoWhiteThreatArray(whiteThreatArray);
//	for (int i = 0; i < 64; i++) {
//		blackThreatArray[i] = 0;
//		whiteThreatArray[i] = 0;
//		Board::instance().debug(sf::Color::White, i);
//	}
//	int undoLastMove = pieceArray[end];
//	pieceArray[end] = pieceArray[start];
//	pieceArray[start] = 0;
//
//	for (int i = 0, j = 0; i < 64; i++) {
//		if (pieceArray[i] != 0) {
//			handleThreats(i, threats[j]);
//			j++;
//		}
//	}
//
//	int wKingbackup = m_wKing;
//	int bKingbackup = m_bKing;
//	if (start == m_bKing) m_bKing = end;
//	if (start == m_wKing) m_wKing = end;
//
//	
//	if (whiteThreatArray[m_bKing] != 0 && color == BLACK) {
//		m_bKing = bKingbackup;
//		undo(undoWhiteThreatArray, undoBlackThreatArray, start, end, undoLastMove);
//		return false;
//	}
//	if (blackThreatArray[m_wKing] != 0 && color == WHITE) {
//		m_wKing = wKingbackup;
//		undo(undoWhiteThreatArray, undoBlackThreatArray, start, end, undoLastMove);
//		return false;
//	}
//	if (fakeMove)
//	{
//		m_wKing = wKingbackup;
//		m_bKing = bKingbackup;
//		undo(undoWhiteThreatArray, undoBlackThreatArray, start, end, undoLastMove);
//		return true;
//	}
//
//	int forward = color == WHITE ? 1 : -1;
//	int piece = pieceArray[end] & 0b111;
//	if (piece  == PawnVal  || piece == KingVal || piece == RookVal ) {
//		if ((pieceArray[end] & 32) > 0) {
//			pieceArray[end] = pieceArray[end] ^ 32;
//			if (start - end == 16 * forward) {
//				m_passant = end;
//				return true;
//			}
//		}
//	}
//	m_passant = -1;
//	return true;
//}

bool SpecialMove::enPassant(int i)
{
	return i == m_passant;
}

bool SpecialMove::isCastle(int king ,int rook)
{
	if (king != 4 && king != 60)
		return false;
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


void SpecialMove::castle(Move move, std::vector<std::vector<Move>> threats)
{
	struct Stack s;
	s.backUpBlackThreatArray = blackThreatArray;
	s.backUpWhiteThreatArray = whiteThreatArray;
	s.backUpPieceArray = pieceArray;
	s.lastBKing = m_bKing;
	s.lastWKing = m_wKing;
	lastMoves.push_front(s);
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

	for (int i = 0; i < 64; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
		Board::instance().debug(sf::Color::White, i);
	}

	for (int i = 0, j = 0; i < 64; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

}

void SpecialMove::enPassantMove(Move move, std::vector<std::vector<Move>> threats)
{
	struct Stack s;
	s.backUpBlackThreatArray = blackThreatArray;
	s.backUpWhiteThreatArray = whiteThreatArray;
	s.backUpPieceArray = pieceArray;
	s.lastBKing = m_bKing;
	s.lastWKing = m_wKing;
	lastMoves.push_front(s);
	int side = (pieceArray[move.startSquare] & WHITE) > 0 ? 8 : -8;

	pieceArray[move.targetSquare] = pieceArray[move.startSquare];
	pieceArray[move.startSquare] = 0;
	pieceArray[move.targetSquare + side] = 0;

	for (int i = 0; i < 64; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
		Board::instance().debug(sf::Color::White, i);
	}

	for (int i = 0, j = 0; i < 64; i++) {
		if (pieceArray[i] != 0) {
			handleThreats(i, threats[j]);
			j++;
		}
	}

}

void SpecialMove::promotionMove(Move move, std::vector<std::vector<Move>> threats, int promotedVal)
{
	struct Stack s;
	s.backUpBlackThreatArray = blackThreatArray;
	s.backUpWhiteThreatArray = whiteThreatArray;
	s.backUpPieceArray = pieceArray;
	s.lastBKing = m_bKing;
	s.lastWKing = m_wKing;
	lastMoves.push_front(s);
	int color = (pieceArray[move.startSquare] & 0b11000);
	pieceArray[move.startSquare] = 0;
	pieceArray[move.targetSquare] = promotedVal | color;

	for (int i = 0; i < 64; i++) {
		blackThreatArray[i] = 0;
		whiteThreatArray[i] = 0;
		Board::instance().debug(sf::Color::White, i);
	}

	for (int i = 0, j = 0; i < 64; i++) {
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
