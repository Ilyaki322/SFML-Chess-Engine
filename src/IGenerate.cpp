#include "IGenerate.h"
#include "NBoard.h"
#include <iostream> // DEBUG
IGenerate::IGenerate()
{
}

std::vector<std::vector<Move>> IGenerate::generateAll(int Color)
{
	NBoard& ins = NBoard::instance();
	PieceLogic pieceLogic;
	int color = (Color & White) > 0 ? White : Black;
	int king = ins.getKing(color);
	std::vector<int> check;
	std::vector < std::vector<Move>> all;
	if (pieceLogic.check(king, check, color)) {
		for (int i = 0; i < SIZE; i++){
			if (ins.getPiece(i) == 0) continue;
			int myColor = (ins.getPiece(i) & White) > 0 ? White : Black;
			if (myColor == color) {
				all.push_back(pieceLogic.generate(check, i));
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
	int color = (NBoard::instance().getPiece(x) & White) > 0 ? White : Black;
	int king = NBoard::instance().getKing(color);

	std::vector<int> check;
	pieceLogic.check(king, check, color);
	return pieceLogic.generate(check,x);
}

bool IGenerate::isMate(int color)
{
	NBoard& ins = NBoard::instance();
	PieceLogic pieceLogic;
	int king = ins.getKing(color);

	std::vector<int> check;
	std::vector < std::vector<Move>> all;
	if (pieceLogic.check(king, check, color) && check.size() == 0) return false;
	if (pieceLogic.check(king, check, color)) {
		for (int i = 0; i < SIZE; i++) {
			if (ins.getPiece(i) == 0) continue;
			int myColor = (ins.getPiece(i) & White) > 0 ? White : Black;
			if (myColor == color) {
				all.push_back(pieceLogic.generate(check, i));
			}
		}
	}
	for (auto pieceMove : all)
		if (pieceMove.size() != 0)return false;

	return true;
}
