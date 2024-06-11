#pragma once
#include <array>
#include <vector>
#include <list>
#include "Pieces.h" // FOR MOVE STRUCT


struct Stack {
	Move move;
	int lastWKing;
	int lastBKing;
	std::array<int, 64> backUpPieceArray;
	std::array<int, 64> backUpBlackThreatArray;
	std::array<int, 64> backUpWhiteThreatArray;
};

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
	void doMove(Move move, std::vector<std::vector<Move>> threats);
	//bool update(int start, int end, std::vector<std::vector<Move>> threats, bool fakeMove = false);

	bool enPassant (int i);
	bool isCastle(int king , int rook); 

	void castle(Move move, std::vector<std::vector<Move>> threats);
	void enPassantMove(Move move, std::vector<std::vector<Move>> threats);
	void promotionMove(Move move, std::vector<std::vector<Move>> threats, int promotedVal);

	bool check(int color);
	bool canDouble(const int pos) const;
	void undo();

private:
	SpecialMove();
	SpecialMove(const SpecialMove&) = default;
	SpecialMove& operator=(const SpecialMove&) = default;
	std::array<int, 64> pieceArray;
	std::array<int, 64> blackThreatArray; // This array sums all the threats to one square. white piece add 1 ans black add -1
	std::array<int, 64> whiteThreatArray; // This array sums all the threats to one square. white piece add 1 ans black add -1
	
	std::list<Stack> lastMoves;

	int m_bKing;
	int m_wKing;
	int m_passant;


	//std::array<int, 64> backUpBlackThreatArray;
	//std::array<int, 64> backUpWhiteThreatArray;
	//int m_lastStart;
	//int m_lastTarget;
	//int m_lastBKing;
	//int m_lastWKing;
	//int m_lastPiece;

};