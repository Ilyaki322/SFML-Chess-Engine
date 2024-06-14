#include "IGenerate.h"
#include "NBoard.h"

IGenerate::IGenerate()
{
}

std::vector<std::vector<Move>> IGenerate::generateAll(int Color)
{
	PieceLogic pieceLogic;
	int color = (Color & White) > 0 ? White : Black;
	int king = color == White ? NBoard::instance().m_WKing : NBoard::instance().m_BKing;
	std::vector<int> check;
	std::vector < std::vector<Move>> all;
	if (pieceLogic.check(king, check, color)) {
		for (const auto& i : NBoard::instance().m_board) {
			int myColor = (i & White) > 0 ? White : Black;
			if (myColor == color) {
				int piece = (i & 0b111);
				all.push_back(pieceLogic.generate(check, piece));
			}
		}
	}
	else {
		all.push_back(pieceLogic.generate(check, king));
	}
	return all;
}

std::vector<Move> IGenerate::generatePiece(int x)
{
	PieceLogic pieceLogic;
	int piece = (NBoard::instance().m_board[x] & 0b111);
	int color = (NBoard::instance().m_board[x] & White) > 0 ? White : Black;
	int king = color == White ? NBoard::instance().m_WKing : NBoard::instance().m_BKing;
	std::vector<int> check;
	pieceLogic.check(king,check , color);
	return pieceLogic.generate(check, piece);
}
