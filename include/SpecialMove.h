#pragma once
#include <array>
#include <vector>
#include <unordered_set>

#include "Pieces.h" // FOR MOVE STRUCT
/// <summary>
/// 
/// en passent 
/// castle
/// chess
/// promotion
/// 
/// </summary>
/// 


enum EndMove {
			EnPassant,
			Castle,
			Promotion,
			Regular

};

enum Piece { 
			KingVal = 1, 
			PawnVal = 2, 
			KnightVal = 3, 
			BishopVal = 4, 
			RookVal = 5, 
			QueenVal = 6 
};


class SpecialMove {
public:
	static SpecialMove& instance();
	void setBoard(std::array<int, 64> /*, std::vector<std::vector<Move>> threats*/);
	void handleThreats(int, std::vector<Move> threat );
	bool fakeMove(Move move , std::vector<std::vector<Move>> threats);
	EndMove MoveType(Move move)const;
	void doMove(Move move);
	bool update(int start, int end, std::vector<std::vector<Move>> threats, bool fakeMove = false);
	bool enPassant (int i);
	bool isCastle(int king , int rook); 
	void castle(int king, int rook);
	bool check(int color);
	bool canDouble(const int pos) const;

private:
	SpecialMove();
	SpecialMove(const SpecialMove&) = default;
	SpecialMove& operator=(const SpecialMove&) = default;
	void undo(std::array<int, 64> white, std::array<int, 64> black, int start,int end,int undoEnd);
	std::array<int, 64> pieceArray;
	std::array<int, 64> blackThreatArray; // This array sums all the threats to one square. white piece add 1 ans black add -1
	std::array<int, 64> whiteThreatArray; // This array sums all the threats to one square. white piece add 1 ans black add -1
	
	int m_bKing;
	int m_wKing;
	int m_passant;
	
};