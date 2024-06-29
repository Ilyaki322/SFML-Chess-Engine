#include "NBoard.h"
#include "FenAlgorithm.h"
#include <iostream> 

NBoard::NBoard()
	:m_lastMove({ -1, -1 }), m_capture(0)
{
}

NBoard& NBoard::instance()
{
	static NBoard ins;
	return ins;
}

//void NBoard::setBoard(std::array<int, SIZE> arr)
//{
//	m_board = arr;
//	for (int i = 0 ; i < SIZE; i++) {
//		if (m_board[i] != 0) {
//			if ((m_board[i] & 0b111) == KingVal) {
//				int color = (m_board[i] & WHITE) > 0 ? WHITE : BLACK;
//				if (color == WHITE)
//				{
//					m_WKing = i;
//				}
//				else
//				{
//					m_BKing = i;
//				}
//			}
//		}
//	}
//	m_passant = -1;
//}

void NBoard::setBoard(std::string fen, std::string name)
{
	m_stack.clear(name);
	FenAlgorithm fenAlgo;
	fenAlgo.setBoard(m_board, fen);
	m_capture = 0;

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
	//m_stack.insert(m_board, m_WKing, m_BKing, m_passant);
	m_stack.insert(move, m_WKing, m_BKing, m_passant);
	m_lastMove = move;
	m_capture = getPiece(move.targetSquare);

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

//void NBoard::undo()
//{
//	Stack s =  m_stack.LastMove();
//	m_board = s.backUpm_board;
//	m_BKing = s.lastBKing;
//	m_WKing = s.lastWKing;
//	m_passant = s.enPassant;
//}
void NBoard::undo()
{
	m_capture = 0;
	MoveLog last = m_stack.lastMove();
	m_BKing = last.lastBKing;
	m_WKing = last.lastWKing;
	m_passant = last.enPassant;

	if (last.lastMove.specialStartSquare != -1)
	{
		m_board[last.lastMove.specialStartSquare] = last.specialStartPiece;
		m_board[last.lastMove.specialTargetSquare] = last.specialTargetPiece;
	}

	m_board[last.lastMove.startSquare] = last.startPiece;
	m_board[last.lastMove.targetSquare] = last.targetPiece;
}

int NBoard::getPiece(int x)const
{
	return m_board[x];
}

bool NBoard::enPassant(int x)const
{
	return x == m_passant;
}

int NBoard::didCapture() const
{
	return m_capture;
}

int NBoard::getKing(int color)const
{
	return (color & White) > 0 ? m_WKing : m_BKing;
}


std::array<int, SIZE>& NBoard::getBoard()
{
	return m_board;
}

Move NBoard::getLastMove() const
{
	return m_lastMove;
}

void NBoard::saveGame()
{
	m_stack.saveToFile();
	m_stack.clear("");
}
