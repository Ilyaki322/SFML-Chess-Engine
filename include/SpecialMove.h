#pragma once
#include <array>
#include <vector>
#include <unordered_set>
/// <summary>
/// 
/// en passent 
/// castle
/// chess
/// promotion
/// 
/// </summary>
/// 


enum Piece { 
			KingVal = 1, 
			PawnVal = 2, 
			KnightVal = 3, 
			BishopVal = 4, 
			RookVal = 5, 
			QueenVal = 6 
};

struct Move
{
	int startSquare;
	int targetSquare;
};

class SpecialMove {
public:
	SpecialMove(std::array<int, 64> arr , std::vector<std::vector<Move>> threats );
	void handleThreats(int, std::vector<Move> threat );
	void update(int start, int end, std::vector<std::vector<Move>> threats);
	bool enPassant (int i);
	bool isCastle(int king , int rook); 
	void castle(int king, int rook);
	bool chess();

private:
	std::array<int, 64> pieceArray;
	std::array<int, 64> threatArray; // This array sums all the threats to one square. white piece add 1 ans black add -1
	//std::array<int, 64> pinArray; // This array check all the roots to the king

	int m_passant;
	
};