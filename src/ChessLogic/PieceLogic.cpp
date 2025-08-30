#include "ChessLogic/PieceLogic.h"
#include "ChessLogic/NBoard.h"

//--------------------------------------------------------------------------
// This function goes through all the possible moves that can reach the king 
// and checks if it is threatened.
// 
// If the king is in check and no piece can defend it, the function will return false 
// If there are pieces who can protect him, it will return true
//---------------------------------------------------------------------------
bool PieceLogic::check(int king ,std::vector<int>& checkSquares , int color)
{
	std::vector<int> direction = { BOT_LEFT , BOT_RIGHT , TOP_LEFT , TOP_RIGHT , UP , DOWN , LEFT , RIGHT };
	int foundOne = 0;
	std::vector<Move> moves;
	std::vector<int> empty;

	for (auto i : direction) {
		moves = slidingMove(i, king, empty, color);
		if (checkCheck(moves, color, i, king)) {
			insertMoveToInt(moves, checkSquares);
			foundOne++;
		}
	}

	///----knight 
	if (king % 8 != 0 && king + 16 < 64) 
		if (checkInSquare(king, LEFT + DOWN * 2, color)) {
			checkSquares.push_back(king + LEFT + DOWN * 2);
			foundOne ++;
		}
	if (king % 8 != 7 && king + 16 < 64) 
		if (checkInSquare(king, (2 * DOWN) + RIGHT, color)) {
			checkSquares.push_back(king + (2 * DOWN) + RIGHT);
			foundOne++;
		}
	if (king - 16 > 0 && king % 8 != 7) 
		if (checkInSquare(king, (2 * UP) + RIGHT, color)) {
			checkSquares.push_back(king + (2 * UP) + RIGHT);
			foundOne++;
		}
	if (king - 16 > 0 && king % 8 != 0) 
		if (checkInSquare(king, (2 * UP) + LEFT, color)) {
			checkSquares.push_back(king + (2 * UP) + LEFT);
			foundOne++;
		}
	if (king % 8 > 1 && king + 8 < 64) 
		if (checkInSquare(king, (2 * LEFT) + DOWN, color)) {
			checkSquares.push_back(king + (2 * LEFT) + DOWN);
			foundOne++;
		}
	if (king % 8 > 1 && king - 8 > 0) 
		if (checkInSquare(king, (2 * LEFT) + UP, color)) {
			checkSquares.push_back(king + (2 * LEFT) + UP);
			foundOne++;
		}
	if (king % 8 < 6 && king - 8 > 0) 
		if (checkInSquare(king, (2 * RIGHT) + UP, color)) {
			checkSquares.push_back(king + (2 * RIGHT) + UP);
			foundOne++;
		}
	if (king % 8 < 6 && king + 8 < 64) 
		if (checkInSquare(king, (2 * RIGHT) + DOWN, color)) {
			checkSquares.push_back(king + (2 * RIGHT) + DOWN);
			foundOne++;
		}


	return foundOne <= 1;
}


std::vector<Move> PieceLogic::generate(std::vector<int> Incheck, int piecePlace)
{
	int piece = m_board.getPiece(piecePlace) & 0b111 ; // piece type
	switch (piece)
	{
	case PawnVal:
		return pawnMove(piecePlace, Incheck);
	case BishopVal:
		return bishopMove(piecePlace, Incheck);
	case RookVal:
		return rookMove(piecePlace, Incheck);
	case KingVal:
		return kingMove(piecePlace, Incheck);
	case QueenVal:
		return queenMove(piecePlace, Incheck);
	case KnightVal:
		return knightMove(piecePlace, Incheck);
	}
}

//--------------------------------------------------------------------------------
//This function checks the direction of the king for a piece of his color, 
// if after the piece there is an actual threat the function will 
// return the direction of the threat
//---------------------------------------------------------------------------------
MovementDirection PieceLogic::kingPin(int target)
{
	int color = (m_board.getPiece(target) & White) > 0 ? White : Black;
	int king = m_board.getKing(color);
	std::vector<Move> moves;
	std::vector<int> empty;
	if ((king - target) % Diagonal1 == 0) {
		moves = slidingMove(BOT_RIGHT, king, empty,color);
		if (!checkCheck(moves, color , BOT_RIGHT, king)) {
			if (checkPin(moves, color, BOT_RIGHT, king, target))
				return Diagonal1;
		}
		moves = slidingMove(TOP_LEFT, king, empty,color);
		if (!checkCheck(moves, color , TOP_LEFT, king)) {
			if (checkPin(moves, color, TOP_LEFT, king, target))
				return Diagonal1;
		}
	}
	if ((king - target) % Forward == 0) {
		moves = slidingMove(DOWN, king, empty,color);
		if (!checkCheck(moves, color,DOWN, king)) {
			if (checkPin(moves, color ,DOWN, king, target))
				return Forward;
		}
		moves = slidingMove(UP, king, empty,color);
		if (!checkCheck(moves, color ,UP, king)) {
			if (checkPin(moves, color, UP, king, target))
				return Forward;
		}
	}
	if ((king - target) % Diagonal2 == 0) {
		moves = slidingMove(BOT_LEFT, king, empty,color);
		if (!checkCheck(moves, color , BOT_LEFT, king)) {
			if (checkPin(moves, color, BOT_LEFT, king, target))
				return Diagonal2;
		}
		moves = slidingMove(TOP_RIGHT, king, empty,color);
		if (!checkCheck(moves, color , TOP_RIGHT, king)) {
			if (checkPin(moves, color, TOP_RIGHT, king, target))
				return Diagonal2;
		}
	}
	moves = slidingMove(LEFT, king, empty,color);
	if (!checkCheck(moves, color , LEFT, king)) {
		if (checkPin(moves, color, LEFT, king, target))
			return Side;
	}
	moves = slidingMove(RIGHT, king, empty,color);
	if (!checkCheck(moves, color , RIGHT, king)) {
		if (checkPin(moves, color, RIGHT, king, target))
			return Side;
	}
	return All;
}

//---------------------------------------------------------------------------------
//In the following Move functions we check the movement of the pieces in relation to the king 
// and whether there is a checker on the board
// In all of them, we will put the move into the vector only if it does not 
// put the king in check
//---------------------------------------------------------------------------------
std::vector<Move> PieceLogic::kingMove(int start, std::vector<int> Incheck)
{
	Piece p = PawnVal;
	std::vector<Move> moves;
	bool inCheck = !Incheck.empty();
	int color = (m_board.getPiece(start) & White) > 0 ? White : Black;
	bool castleRight, castleLeft;
	if (!inCheck) castleRight = castleLeft = true;
	else castleRight = castleLeft = false;


	if (start % 8 != 0) {
		if (checkDirection(start, LEFT, color)) {
			std::vector<int> checkSquares;
			if (check(start + LEFT, checkSquares, color) && (checkSquares.size() == 0)) {
				moves.push_back({ start, start + LEFT , -1 , -1 , p });
				castleLeft = true;
			}
		}
	}

	if (start % 8 != 7){
		if (checkDirection(start, RIGHT, color)) {
			std::vector<int> checkSquares;
			if (check(start + RIGHT, checkSquares, color) && checkSquares.size() == 0) {
					moves.push_back({ start, start + RIGHT , -1 , -1 , p });
					castleRight = true;
			}
		}
	}

	if (start - 8 > -1) {
		if (checkDirection(start, UP, color)) {
			std::vector<int> checkSquares;
			if (check(start + UP, checkSquares, color) && checkSquares.size() == 0)
					moves.push_back({ start, start + UP , -1 , -1 , p });
		}
	}


	if (start + 8 < 64) {
		if (checkDirection(start, DOWN, color)) {
			std::vector<int> checkSquares;
			if (check(start + DOWN, checkSquares, color) && checkSquares.size() == 0)
				moves.push_back({ start, start + DOWN , -1 , -1 , p });
		}
	}

	if (checkCorner(start, TOP_LEFT,color)) {
		std::vector<int> checkSquares;
		if (check(start + TOP_LEFT, checkSquares, color) && checkSquares.size() == 0) {
			moves.push_back({ start, start + TOP_LEFT , -1 , -1 , p });
		}
	}
	if (checkCorner(start, TOP_RIGHT,color)) {
		std::vector<int> checkSquares;
		if (check(start + TOP_RIGHT, checkSquares, color)&&checkSquares.size() == 0)
				moves.push_back({ start, start + TOP_RIGHT, -1 , -1 , p });
	}
	if (checkCorner(start, BOT_LEFT,color)){
		std::vector<int> checkSquares;
		if (check(start + BOT_LEFT, checkSquares, color)&&checkSquares.size() == 0)
				moves.push_back({ start, start + BOT_LEFT , -1 , -1 , p });
	}
	if(checkCorner(start, BOT_RIGHT,color)) {
		std::vector<int> checkSquares;
		if(check(start + BOT_RIGHT, checkSquares, color) && checkSquares.size() == 0) 
				moves.push_back({ start, start + BOT_RIGHT , -1 , -1 , p });
	}
	if (!inCheck&& castleLeft && castle(start, LEFT))moves.push_back({ start, start + LEFT*2  , start+LEFT*4 , start+LEFT , p });
	if (!inCheck && castleRight && castle(start , RIGHT)) moves.push_back({ start, start + RIGHT*2 , start+RIGHT*3 , start+RIGHT  , p});
	for (auto i = moves.begin(); i != moves.end();) {
		if (i->targetSquare != -1 && kingTeritory(i->targetSquare, color)) {
			i = moves.erase(i);
		}
		else i++;
	}
	return moves;
}

std::vector<Move> PieceLogic::bishopMove(int start, std::vector<int> Incheck)
{
	std::vector<Move> moves;
	std::vector<Move> toInsert;
	MovementDirection direction = kingPin(start);
	if (!Incheck.empty() && direction != All)return moves;  // ---cant move-- check and pin 
	int color = (m_board.getPiece(start) & White) > 0 ? White : Black;
	if (direction == Diagonal1 || direction == All) {
		toInsert = (slidingMove(BOT_RIGHT, start, Incheck,color));
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(TOP_LEFT, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Diagonal2 || direction == All) {
		toInsert = slidingMove(BOT_LEFT, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(TOP_RIGHT, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	return moves;
}

std::vector<Move> PieceLogic::knightMove(int start, std::vector<int> Incheck)
{
	std::vector<Move> move;
	MovementDirection direction = kingPin(start);
	if (direction != All)return move;  // ---cant move--

	Piece p = PawnVal;
	bool inCheck = !Incheck.empty();
	int color = (m_board.getPiece(start) & White) > 0 ? White : Black;
	if (start % 8 != 0 && start + 16 < 64) 
		if(checkDirection(start, (2 * DOWN) + LEFT , color))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * DOWN) + LEFT) != Incheck.end()) {
					move.push_back({ start, start + (2 * DOWN) + LEFT , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * DOWN) + LEFT, -1 , -1 , p });
	if (start % 8 != 7 && start + 16 < 64) 
		if (checkDirection(start, (2 * DOWN) + RIGHT,color))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * DOWN) + RIGHT) != Incheck.end()) {
					move.push_back({ start, start + (2 * DOWN) + RIGHT , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * DOWN) + RIGHT, -1 , -1 , p });
	if (start - 16 > -1 && start % 8 != 7) 
		if(checkDirection(start, (2 * UP) + RIGHT,color))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * UP) + RIGHT) != Incheck.end()) {
					move.push_back({ start, start + (2 * UP) + RIGHT , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * UP) + RIGHT, -1 , -1 , p });
	if (start - 16 > 0 && start % 8 != 0) 
		if(checkDirection(start, (2 * UP) + LEFT,color))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * UP) + LEFT) != Incheck.end()) {
					move.push_back({ start, start + (2 * UP) + LEFT , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * UP) + LEFT, -1 , -1 , p });
	if (start % 8 > 1 && start + 8 < 64) 
		if(checkDirection(start, (2 * LEFT) + DOWN,color))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * LEFT) + DOWN) != Incheck.end()) {
					move.push_back({ start, start + (2 * LEFT) + DOWN , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * LEFT) + DOWN, -1 , -1 , p });
	if (start % 8 > 1 && start - 8 > 0) 
		if(checkDirection(start, (2 * LEFT) + UP,color))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * LEFT) + UP) != Incheck.end()) {
					move.push_back({ start, start + (2 * LEFT) + UP , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * LEFT) + UP, -1 , -1 , p });
	if (start % 8 < 6 && start - 8 > 0) 
		if(checkDirection(start, (2 * RIGHT) + UP,color))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * RIGHT) + UP) != Incheck.end()) {
					move.push_back({ start, start + (2 * RIGHT) + UP , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * RIGHT) + UP, -1 , -1 , p });
	if (start % 8 < 6 && start + 8 < 64) 
		if(checkDirection(start, (2 * RIGHT) + DOWN,color))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * RIGHT) + DOWN) != Incheck.end()) {
					move.push_back({ start, start + (2 * RIGHT) + DOWN , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * RIGHT) + DOWN, -1 , -1 , p });

	return move;
}

std::vector<Move> PieceLogic::queenMove(int start, std::vector<int> Incheck)
{
	std::vector<Move> moves;
	std::vector<Move> toInsert;
	MovementDirection direction = kingPin(start);
	if (!Incheck.empty() && direction != All)return moves;  // ---cant move-- check and pin 
	int color = (m_board.getPiece(start) & White) > 0 ? White : Black;
	if (direction == Forward || direction == All) {
		toInsert = (slidingMove(UP, start, Incheck,color));
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(DOWN, start, Incheck , color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Side || direction == All) {
		toInsert = slidingMove(LEFT, start, Incheck , color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(RIGHT, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Diagonal1 || direction == All) {
		toInsert = (slidingMove(BOT_RIGHT, start, Incheck,color));
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(TOP_LEFT, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Diagonal2 || direction == All) {
		toInsert = slidingMove(BOT_LEFT, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(TOP_RIGHT, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	return moves;
}

std::vector<Move> PieceLogic::pawnMove(int start, std::vector<int> Incheck)
{
	std::vector<Move> moves;
	int forward;
	int pos = start;
	MovementDirection direction = kingPin(start);
	if (!Incheck.empty() && direction != All)return moves;  // ---cant move-- check and pin
	int color = (m_board.getPiece(pos) & White) > 0 ? White : Black;
	bool inCheck = !Incheck.empty();
	if (direction == Diagonal1 && color == BLACK)
		direction = Diagonal2;
	else if (direction == Diagonal2 && color == BLACK)
		direction = Diagonal1;
	(color == BLACK) ? forward = DOWN : forward = UP;

	Move move = {  pos, pos + forward  , -1 , -1 , QueenVal  };
	Piece p = PawnVal;

	if (pos + forward > 64 || pos + forward < 0) { // Out of Range
		return moves;
	}

	if (direction == All || direction == Forward) {
		if (m_board.getPiece(pos + forward) == 0)
		{
				if (inCheck) {
					if (std::find(Incheck.begin(), Incheck.end(), pos + forward) != Incheck.end()) {
						if ((pos + forward > 55 || pos + forward < 8)) {//promotion
							moves.push_back({ pos, pos + forward  , -1 , -1 , QueenVal });
							moves.push_back({ pos, pos + forward  , -1 , -1 , RookVal });
							moves.push_back({ pos, pos + forward  , -1 , -1 , KnightVal});
							moves.push_back({ pos, pos + forward  , -1 , -1 ,  BishopVal });
						}
						else moves.push_back({ pos, pos + forward  , -1 , -1 , p });
					}
				}
				else {
					if ((pos + forward > 55 || pos + forward < 8)) {//promotion
						moves.push_back({ pos, pos + forward  , -1 , -1 , QueenVal });
						moves.push_back({ pos, pos + forward  , -1 , -1 , RookVal });
						moves.push_back({ pos, pos + forward  , -1 , -1 , KnightVal });
						moves.push_back({ pos, pos + forward  , -1 , -1 ,  BishopVal });
					}
					else moves.push_back({ pos, pos + forward , -1 , -1 , p });
				}
	
			if ((m_board.getPiece(pos) & Moved) > 0 && (m_board.getPiece(pos + forward * 2) == 0))
			{
				if (inCheck) {
					if (std::find(Incheck.begin(), Incheck.end(), pos + forward*2) != Incheck.end()) {
						moves.push_back({ pos, pos + forward*2  , -1 , -1 , p });
					}
				}
				else moves.push_back({ pos, pos + forward * 2 , -1 , -1 , p });
			}
		}
	}
	if (direction == All || direction == Diagonal2 ) {
		if (pos % 8 != 7)
		{
			if (m_board.getPiece(pos + forward + RIGHT) != 0) {
				int enemyColor = (m_board.getPiece(pos + forward + RIGHT) & White) > 0 ? White : Black;
				if (enemyColor != color) {
					if (inCheck) {
						if (std::find(Incheck.begin(), Incheck.end(), pos + forward +RIGHT) != Incheck.end()) {
							if ((pos + forward > 55 || pos + forward < 8)) {//promotion
								moves.push_back({ pos, pos + forward + RIGHT  , -1 , -1 , QueenVal });
								moves.push_back({ pos, pos + forward + RIGHT , -1 , -1 , RookVal });
								moves.push_back({ pos, pos + forward + RIGHT , -1 , -1 , KnightVal });
								moves.push_back({ pos, pos + forward + RIGHT , -1 , -1 ,  BishopVal });
							}
							else moves.push_back({ pos, pos + forward + RIGHT, -1 , -1 , p });
						}
					}
					else if ((pos + forward > 55 || pos + forward < 8)) {//promotion
						moves.push_back({ pos, pos + forward + RIGHT  , -1 , -1 , QueenVal });
						moves.push_back({ pos, pos + forward + RIGHT , -1 , -1 , RookVal });
						moves.push_back({ pos, pos + forward + RIGHT , -1 , -1 , KnightVal });
						moves.push_back({ pos, pos + forward + RIGHT , -1 , -1 ,  BishopVal });
					}
					else moves.push_back({ pos, pos + forward + RIGHT, -1 , -1 , p });
					
				}
			}

			if (m_board.getPiece(pos + RIGHT) != 0) {
				int enemyColor = (m_board.getPiece(pos + RIGHT) & White) > 0 ? White : Black;
				if (color != enemyColor) {
					if (m_board.enPassant(pos + RIGHT))
					{
						if (inCheck) {
							if (std::find(Incheck.begin(), Incheck.end(), pos + forward + RIGHT) != Incheck.end()) {
								moves.push_back({ pos, pos + RIGHT , pos + RIGHT , pos + RIGHT + forward, p });
							}
						}
						else moves.push_back({ pos, pos + RIGHT , pos + RIGHT , pos + RIGHT + forward, p });
						
					}
				}
			}
		}
	}
	if (direction == All || direction == Diagonal1) {
		if (pos % 8 != 0)
		{
			if (m_board.getPiece(pos + forward + LEFT)) {
				int enemyColor = (m_board.getPiece(pos + forward + LEFT) & White) > 0 ? White : Black;
				if (enemyColor != color) {
					if (inCheck) {
						if (std::find(Incheck.begin(), Incheck.end(), pos + forward + LEFT) != Incheck.end()) {
							if ((pos + forward > 55 || pos + forward < 8)) {//promotion
								moves.push_back({ pos, pos + forward + LEFT   , -1 , -1 , QueenVal });
								moves.push_back({ pos, pos + forward + LEFT  , -1 , -1 , RookVal });
								moves.push_back({ pos, pos + forward + LEFT  , -1 , -1 , KnightVal });
								moves.push_back({ pos, pos + forward + LEFT  , -1 , -1 ,  BishopVal });
							}
							else moves.push_back({ pos, pos + forward + LEFT , -1 , -1 , p });
						}
					}
					else if ((pos + forward > 55 || pos + forward < 8)) {//promotion
						moves.push_back({ pos, pos + forward + LEFT   , -1 , -1 , QueenVal });
						moves.push_back({ pos, pos + forward + LEFT  , -1 , -1 , RookVal });
						moves.push_back({ pos, pos + forward + LEFT  , -1 , -1 , KnightVal });
						moves.push_back({ pos, pos + forward + LEFT  , -1 , -1 ,  BishopVal });
					}
					else moves.push_back({ pos, pos + forward + LEFT , -1 , -1 , p });
				}
			}
			if (m_board.getPiece(pos + LEFT) != 0) {
				int enemyColor = (m_board.getPiece(pos + LEFT) & White) > 0 ? White : Black;
				if (color != enemyColor) {
					if (m_board.enPassant(pos + LEFT))
					{
						if (inCheck) {
							if (std::find(Incheck.begin(), Incheck.end(), pos + forward + LEFT) != Incheck.end()) {
								moves.push_back({ pos, pos + LEFT , pos + LEFT , pos + LEFT + forward, p });
							}
						}
						else moves.push_back({ pos, pos + LEFT , pos + LEFT , pos + LEFT + forward, p });
					}
				}
			}
		}
	}
	return moves;
}

std::vector<Move> PieceLogic::rookMove(int start, std::vector<int> Incheck)
{
	std::vector<Move> moves;
	std::vector<Move> toInsert;
	MovementDirection direction = kingPin(start);
	int color = (m_board.getPiece(start) & White) > 0 ? White : Black;
	if (!Incheck.empty() && direction != All)return moves;  // ---cant move-- check and pin 

	if (direction == Forward || direction == All) {
		toInsert = (slidingMove(UP, start, Incheck,color));
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(DOWN, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Side || direction == All) {
		toInsert = slidingMove(LEFT, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(RIGHT, start, Incheck,color);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	return moves;
}
//-----------------------------------------------------------------------------------------------
// This function performs continuous movement
// Used by the queen, rook, bishop and for checking check
//-----------------------------------------------------------------------------------------
std::vector<Move> PieceLogic::slidingMove(int direction, int start, std::vector<int> inCheck , int color)
{
	std::vector<Move> moves;
	int pos = start;
	if (pos % 8 == 0 && (direction == BOT_LEFT || direction == TOP_LEFT || direction == LEFT)) return moves;
	if (pos % 8 == 7 && (direction == TOP_RIGHT || direction == BOT_RIGHT || direction == RIGHT)) return moves;
	if (pos - 8 < 0 && (direction == TOP_RIGHT || direction == TOP_LEFT || direction == UP)) return moves;
	if (pos + 8 > 63 && (direction == BOT_LEFT || direction == BOT_RIGHT || direction == DOWN)) return moves;
	Piece p = PawnVal;

	bool isCheck = !inCheck.empty();
	bool run = true;
	
	for (int i = pos + direction; run && (i < SIZE && i > -1); i += direction)
	{
		// 'wall' does not mean we out of bounds
		// for example square 16 is a wall, but 16 - 9 still > 0
		// so we check i MOD 8, if its 0 or 7 it means we on the last tile.
		if ((i % 8) == 0 || (i % 8) == 7)
		{
			if (direction != UP && direction != DOWN) run = false;
		}
		if (m_board.getPiece(i)==0) // empty square
		{
			if (isCheck) {
				if (std::find(inCheck.begin(), inCheck.end(), i) != inCheck.end()) {
					moves.push_back({ pos, i , -1 , -1 , p });
				}
			}
			else 
				moves.push_back({ pos, i , -1 , -1 , p });
			continue;
		}
		int enemyColor = (m_board.getPiece(i) & White) > 0 ? White : Black;
		if (color == enemyColor) return moves;
		if (isCheck) {
			if (std::find(inCheck.begin(), inCheck.end(), i) != inCheck.end()) {
				moves.push_back({ pos, i , -1 , -1 , p });
			}
		}
		else moves.push_back({ pos, i , -1 , -1 , p });
		return moves;
	}
	return moves;
}
//-------------------------------------------------
//This function checks whether the king is in check
//--------------------------------------------------
bool PieceLogic::checkCheck(std::vector<Move>& moves, int color,int direction,int king)
{
	bool firstMoves = true;
	std::vector<int>empty;
	if (moves.empty()) {
		if ((king + direction) < 64 && king + direction > -1 &&
			(m_board.getPiece(king + direction) & 0b111) == KingVal) {
			moves = slidingMove(direction, king + direction, empty, color);
			firstMoves = false;
		}
		else return false;
	}
	if (moves.empty())return false;

	if (m_board.getPiece(moves.back().targetSquare) == 0) return false;
	int piece = (m_board.getPiece(moves.back().targetSquare) & 0b111);
	if (direction % Forward == 0 || Side % direction == 0) {
		if (piece == RookVal || piece == QueenVal) return true;
		return false;
	}
	if (direction % Diagonal1 == 0 || direction % Diagonal2 == 0) {
		if (piece == BishopVal || piece == QueenVal) return true;
		if (firstMoves && moves.size() == 1 && piece == PawnVal) {
			if (color == White && moves.back().targetSquare < moves.back().startSquare)return true;
			if (color == Black && moves.back().targetSquare > moves.back().startSquare)return true;
		}
		return false;
	}
	
	return false;
}

//----------------------------------------------------------------------
//This function checks whether the piece is pin to the king
//----------------------------------------------------------------------
bool PieceLogic::checkPin(std::vector<Move> moves, int color, int direction,int king,int target)
{
	std::vector<int> empty;
	if (moves.empty()) {
		if ((king + direction) < 64 && king + direction > -1 &&
			m_board.getPiece(king + direction) != 0 && king + direction == target) {
			moves = slidingMove(direction, king + direction, empty,color);
			if (checkCheck(moves, color, direction, king)) {
				if ((m_board.getPiece(moves.back().targetSquare) & 0b111) != PawnVal)return true;
			}
			return false;
		}
		else return false;
	}
	if (m_board.getPiece(moves.back().targetSquare) != 0) return false;
	if (moves.back().targetSquare + direction > 63 || moves.back().targetSquare + direction < 0) return false;
	if ((moves.back().targetSquare + direction) % 8 == 0 && moves.back().targetSquare % 8 == 7)return false;
	if ((moves.back().targetSquare + direction) % 8 == 7 && moves.back().targetSquare % 8 == 0)return false;
	if (moves.back().targetSquare + direction != target) return false;
	moves = slidingMove(direction, moves.back().targetSquare + direction, empty,color);
	if (checkCheck(moves, color , direction, king)) {
		if ((m_board.getPiece(moves.back().targetSquare) & 0b111) != PawnVal)return true;
	}
	return false;
}

void PieceLogic::insertMoveToInt(std::vector<Move> from, std::vector<int>& to)
{
	for (const auto& i : from) {
		to.push_back(i.targetSquare);
	}
}

bool PieceLogic::checkInSquare(int place, int jump, int color)
{
	if ((m_board.getPiece(place + jump) & 0b111) == KnightVal) {
		int enemyColor = (m_board.getPiece(place + jump) & White) > 0 ? White : Black;
		if (enemyColor != color) {
			return true;
		}
	}
	return false;
}

bool PieceLogic::checkDirection(const int pos, const int direction, int color) const
{
	if (m_board.getPiece(pos + direction)==0){
		return true;
	}
	int enemyColor = (m_board.getPiece(pos + direction) & White) > 0 ? White : Black;
	if (enemyColor != color)
	{
		return true;
	}
	return false;
}

bool PieceLogic::checkCorner(const int pos, const int corner,int color) const
{
	if (pos + corner < 0 || pos + corner > 63) return false;
	if (pos % 8 == 0 && (corner == TOP_LEFT || corner == BOT_LEFT)) return false;
	if (pos % 8 == 7 && (corner == TOP_RIGHT || corner == BOT_RIGHT)) return false;
	if (pos - 8 < 0 && (corner == TOP_RIGHT || corner == TOP_LEFT)) return false;
	if (pos + 8 > 63 && (corner == BOT_LEFT || corner == BOT_RIGHT)) return false;

	return checkDirection(pos, corner,color);
}
//--------------------------------------------------------------------------------
// This function checks whether (according to the rules of chess) the king can castle
//--------------------------------------------------------------------------------
bool PieceLogic::castle(int king, int direction)
{
	int color = (m_board.getPiece(king) & White) > 0 ? White : Black;
	int rook = direction == RIGHT ? 7 : 0;
	std::vector<int> checkSquares;
	rook += color == White ?  56 : 0;
	
	if ((m_board.getPiece(rook) & 0b111) != RookVal) return false;
	if (((m_board.getPiece(king) & Moved) == 0))return false;
	if (((m_board.getPiece(rook) & Moved) == 0))return false;

	if (m_board.getPiece(king + direction) != 0 ||
		m_board.getPiece(king + direction*2) != 0){
		return false;
	}
	if (direction == LEFT && m_board.getPiece(king + direction * 3) != 0)
		return false;
	if ((!check(king + direction, checkSquares, color) || checkSquares.size() != 0))return false;
	if ((!check(king + direction * 2, checkSquares, color) || checkSquares.size() != 0))return false;
	return true;
}
//-----------------------------------------------------------------
//This function check if the king is not in other king terrtitory
// This behavior is different from checkCheck function
//------------------------------------------------------------------
bool PieceLogic::kingTeritory(int king, int color)
{
	int enemyKing = m_board.getKing(color == White ? Black : White);

	if (king + 8 == enemyKing || king - 8 == enemyKing)return true;
	if(king % 8 != 0)
		if (king + 7 == enemyKing || king - 9 == enemyKing|| king - 1 == enemyKing)return true;
	if(king % 8 != 7 )
		if (king + 9 == enemyKing || king - 7 == enemyKing || king + 1 == enemyKing)return true;
	return false;
}

bool PieceLogic::BishopOnWhiteSquare(int pos)
{
	bool positiveSquare = false;
	bool positiveRow = false;
	int row = pos / 8;
	if (pos % 2 == 0) positiveSquare = true;
	if (row % 2 == 0) positiveRow = true;

	if (positiveRow && positiveSquare)return true;
	if (!positiveRow && !positiveSquare)return true;
	return false;
}

