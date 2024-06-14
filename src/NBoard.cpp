#include "NBoard.h"

NBoard::NBoard()
{
}

NBoard& NBoard::instance()
{
	static NBoard ins;
	return ins;
}

void NBoard::setBoard(std::array<int, SIZE> arr)
{
	m_board = arr;
	for (int i = 0 ; i < SIZE; i++) {
		if (m_board[i] != 0) {
			if ((m_board[i] & 0b111) == KingVal) {
				int color = (m_board[i] & WHITE) > 0 ? WHITE : BLACK;
				if (color == WHITE)
				{
					m_WKing = i;
				}
				else
				{
					m_BKing = i;
				}
			}
		}
	}
	m_passant = -1;
}

void NBoard::move(Move move)
{
	m_stack.insert(m_board, m_WKing, m_BKing, m_passant);

	int color = (m_board[move.startSquare] & WHITE) > 0 ? WHITE : BLACK;
	if (move.promotionVal == PawnVal) { 
		m_board[move.targetSquare] = m_board[move.startSquare];
		m_board[move.startSquare] = 0;
		if (move.specialStartSquare != -1) {// -- en passant or castle
			m_board[move.specialTargetSquare] = m_board[move.specialStartSquare];
			m_board[move.specialStartSquare] = 0;
		}
	}
	if (move.promotionVal != PawnVal) { //--- promotion
		m_board[move.targetSquare] = move.promotionVal | color ;
		m_board[move.startSquare] = 0;
	}

	if (move.startSquare == m_BKing) m_BKing = move.targetSquare;
	if (move.startSquare == m_WKing) m_WKing = move.targetSquare;

	int forward = color == WHITE ? 1 : -1;
	int piece = m_board[move.targetSquare] & 0b111;
	if (piece == PawnVal || piece == KingVal || piece == RookVal) {
		if ((m_board[move.targetSquare] & Moved) > 0) {
			m_board[move.targetSquare] = m_board[move.targetSquare] ^ Moved;
			if (move.startSquare - move.targetSquare == DOWN * 2 * forward) {
				m_passant = move.targetSquare;
				return;
			}
		}
	}
	m_passant = -1;
}

void NBoard::undo()
{
	Stack s =  m_stack.LastMove();
	m_board = s.backUpm_board;
	m_BKing = s.lastBKing;
	m_WKing = s.lastWKing;
	m_passant = s.enPassant;
}
