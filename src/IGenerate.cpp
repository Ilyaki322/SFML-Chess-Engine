#include "IGenerate.h"
#include "NBoard.h"
#include <iostream> // DEBUG
IGenerate::IGenerate()
{
}
//---------------------------------------------------------------------
// This function returns all possible moves currently on the board
//---------------------------------------------------------------------
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
//---------------------------------------------------------------------
// This function returns all possible moves for a single piece
//---------------------------------------------------------------------
std::vector<Move> IGenerate::generatePiece(int x)
{

	PieceLogic pieceLogic;
	int color = (NBoard::instance().getPiece(x) & White) > 0 ? White : Black;
	int king = NBoard::instance().getKing(color);

	std::vector<int> check;
	pieceLogic.check(king, check, color);
	return pieceLogic.generate(check,x);
}
//---------------------------------------------------------------------
// This function checks if the game is over
//---------------------------------------------------------------------
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

bool IGenerate::isDraw(int colorTurn)
{
	auto& ins = NBoard::instance();
	auto board = ins.getBoard();
	auto allMy = generateAll(colorTurn);
	bool foundMove = false;
	//---No possible moves
	for (auto piece : allMy) {
		if (piece.size() != 0) {
			foundMove = true;
			break;
		}
	}
	if (!foundMove)return true;

	//---  insufficient material
	int count = 0;
	int knights=0;
	std::vector<int> bishops;

	for (int i = 0; i < SIZE; i++){
		int piece = board[i] & 0b111;
		switch (piece) {
		case KnightVal: {
			knights++;
			break;
		}
		case BishopVal: {
			bishops.push_back(i);
			break;
		}
		default: {
			count++;
			break;
		}
		}
		if (count > 4)return false;
	}

	if (count == 2)return true;		//King vs.king


	//King and bishop vs.king  or  King and knight vs.king
	if (count == 3 && (knights!= 0 || bishops.size() != 0)) return true;
	
	
	//King and bishop vs.king and bishop of the same color as the opponent's bishop
	if (bishops.size() != 2)return false;
	Color firstBishop = (board[bishops[0]] & White) > 0 ? White : Black;
	Color secondBishop = (board[bishops[1]] & White) > 0 ? White : Black;
	if (firstBishop == secondBishop)return false;
	PieceLogic logic;
	if (logic.BishopOnWhiteSquare(bishops[0]) && logic.BishopOnWhiteSquare(bishops[1]))return true;
	if (!logic.BishopOnWhiteSquare(bishops[0]) && !logic.BishopOnWhiteSquare(bishops[1]))return true;

	return false;
}