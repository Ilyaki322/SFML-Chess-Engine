#include "PieceLogic.h"
#include "NBoard.h"

PieceLogic::PieceLogic()
{
}

bool PieceLogic::check(int king ,std::vector<int>& checkSquares , int color)
{
	int foundOne = 0;
	std::vector<Move> moves;
	std::vector<int> empty;
	moves = slidingMove(BOT_LEFT, king, empty);
	if (checkCheck(moves, color,BOT_LEFT)) {
		insertMoveToInt(moves, checkSquares);
		foundOne++;
	}
	moves = slidingMove(BOT_RIGHT, king, empty);
	if (checkCheck(moves, color, BOT_RIGHT)) {
		insertMoveToInt(moves, checkSquares);
		foundOne++;
	}
	moves = slidingMove(TOP_LEFT, king, empty);
	if (checkCheck(moves, color , TOP_LEFT)) {
		insertMoveToInt(moves, checkSquares);
		foundOne++;
	}
	moves = slidingMove(TOP_RIGHT, king, empty);
	if (checkCheck(moves, color , TOP_RIGHT)) {
		insertMoveToInt(moves, checkSquares);
		foundOne++;
	}
	moves = slidingMove(UP, king, empty);
	if (checkCheck(moves, color , UP)) {
		insertMoveToInt(moves, checkSquares);
		foundOne++;
	}
	moves = slidingMove(DOWN, king, empty);
	if (checkCheck(moves, color , DOWN)) {
		insertMoveToInt(moves, checkSquares);
		foundOne++;
	}
	moves = slidingMove(LEFT, king, empty);
	if (checkCheck(moves, color , LEFT)) {
		insertMoveToInt(moves, checkSquares);
		foundOne++;
	}
	moves = slidingMove(RIGHT, king, empty);
	if (checkCheck(moves, color , RIGHT)) {
		insertMoveToInt(moves, checkSquares);
		foundOne++;
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
	int piece = NBoard::instance().m_board[piecePlace] & 0b111 ; // piece type
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

MovementDirection PieceLogic::kingPin(int target)
{
	int color = (NBoard::instance().m_board[target] & White) > 0 ? White : Black;
	int king = color == BLACK ? NBoard::instance().m_BKing : NBoard::instance().m_WKing;
	std::vector<Move> moves;
	std::vector<int> empty;
	if ((king - target) % Diagonal1 == 0) {
		moves = slidingMove(BOT_RIGHT, king, empty);
		if (!checkCheck(moves, color , BOT_RIGHT)) {
			if (checkPin(moves, color, BOT_RIGHT))
				return Diagonal1;
		}
		moves = slidingMove(TOP_LEFT, king, empty);
		if (!checkCheck(moves, color , TOP_LEFT)) {
			if (checkPin(moves, color, TOP_LEFT))
				return Diagonal1;
		}
	}
	if ((king - target) % Forward == 0) {
		moves = slidingMove(DOWN, king, empty);
		if (!checkCheck(moves, color,DOWN)) {
			if (checkPin(moves, color ,DOWN))
				return Forward;
		}
		moves = slidingMove(UP, king, empty);
		if (!checkCheck(moves, color ,UP)) {
			if (checkPin(moves, color, UP))
				return Forward;
		}
	}
	if ((king - target) % Diagonal2 == 0) {
		moves = slidingMove(BOT_LEFT, king, empty);
		if (!checkCheck(moves, color , BOT_LEFT)) {
			if (checkPin(moves, color, BOT_LEFT))
				return Diagonal2;
		}
		moves = slidingMove(TOP_RIGHT, king, empty);
		if (!checkCheck(moves, color , TOP_RIGHT)) {
			if (checkPin(moves, color, TOP_RIGHT))
				return Diagonal2;
		}
	}
	moves = slidingMove(LEFT, king, empty);
	if (!checkCheck(moves, color , LEFT)) {
		if (checkPin(moves, color, LEFT))
			return Side;
	}
	moves = slidingMove(RIGHT, king, empty);
	if (!checkCheck(moves, color , RIGHT)) {
		if (checkPin(moves, color, RIGHT))
			return Side;
	}
	return All;
}

std::vector<Move> PieceLogic::kingMove(int start, std::vector<int> Incheck)
{
	Piece p = PawnVal;
	std::vector<Move> moves;
	bool inCheck = Incheck.size() != 0;
	std::vector<int> checkSquares;
	int color = (NBoard::instance().m_board[start] & White) > 0 ? White : Black;
	bool castleRight , castleLeft;
	if (!inCheck) castleRight =castleLeft = true;
	else castleRight = castleLeft = false;
		
	if (start % 8 != 0) 
		if (checkDirection(moves, start, LEFT)) {
			if(check(start+LEFT , checkSquares, color) && checkSquares.size()==0)
				if (inCheck) {
					if (std::find(Incheck.begin(), Incheck.end(), start + LEFT) != Incheck.end()) {
						moves.push_back({ start, start + LEFT , -1 , -1 , p });
					}
				}
				else {
					moves.push_back({ start, start + LEFT, -1 , -1 , p });
					castleLeft = true;
				}
		}
	if (start % 8 != 7) 
		if (checkDirection(moves, start, RIGHT)) {
			if (check(start + RIGHT, checkSquares, color) && checkSquares.size() == 0)
				if (inCheck) {
					if (std::find(Incheck.begin(), Incheck.end(), start + RIGHT) != Incheck.end()) {
						moves.push_back({ start, start + RIGHT , -1 , -1 , p });
					}
				}
				else {
					moves.push_back({ start, start + RIGHT , -1 , -1 , p });
					castleRight = true;
				}
		}
	if (start - 8 > 0) 
		if (checkDirection(moves, start, UP)) {
			if (check(start + UP, checkSquares, color) && checkSquares.size() == 0)
				if (inCheck) {
					if (std::find(Incheck.begin(), Incheck.end(), start + UP) != Incheck.end()) {
						moves.push_back({ start, start + UP , -1 , -1 , p });
					}
				}
				else moves.push_back({ start, start + UP, -1 , -1 , p });
		}
	if (start + 8 < 63)
		if (checkDirection(moves, start, DOWN)) {
			if (check(start + DOWN, checkSquares, color) && checkSquares.size() == 0)
				if (inCheck) {
					if (std::find(Incheck.begin(), Incheck.end(), start + DOWN) != Incheck.end()) {
						moves.push_back({ start, start + DOWN , -1 , -1 , p });
					}
				}
				else moves.push_back({ start, start + DOWN , -1 , -1 , p });
		}

	if (checkCorner(moves, start, TOP_LEFT)) {
		if (check(start + TOP_LEFT, checkSquares, color) && checkSquares.size() == 0)
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + TOP_LEFT) != Incheck.end()) {
					moves.push_back({ start, start + TOP_LEFT , -1 , -1 , p });
				}
			}
			else moves.push_back({ start, start + TOP_LEFT, -1 , -1 , p });
	}
	if (checkCorner(moves, start, TOP_RIGHT)) {
		if (check(start + TOP_RIGHT, checkSquares, color) && checkSquares.size() == 0)
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + TOP_RIGHT) != Incheck.end()) {
					moves.push_back({ start, start + TOP_RIGHT, -1 , -1 , p });
				}
			}
			else moves.push_back({ start, start + TOP_RIGHT , -1 , -1 , p });
	}
	if (checkCorner(moves, start, BOT_LEFT)){
		if (check(start + BOT_LEFT, checkSquares, color) && checkSquares.size() == 0)
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + BOT_LEFT) != Incheck.end()) {
					moves.push_back({ start, start + BOT_LEFT , -1 , -1 , p });
				}
			}
			else moves.push_back({ start, start + BOT_LEFT , -1 , -1 , p });
	}
	if(checkCorner(moves, start, BOT_RIGHT)) {
		if (check(start + BOT_RIGHT, checkSquares, color) && checkSquares.size() == 0)
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + BOT_RIGHT) != Incheck.end()) {
					moves.push_back({ start, start + BOT_RIGHT , -1 , -1 , p });
				}
			}
			else moves.push_back({ start, start + BOT_RIGHT, -1 , -1 , p });
	}
	if (castleLeft && castle(start, LEFT))moves.push_back({ start, start + LEFT*2  , start+LEFT*4 , start+LEFT , p });
	if (castleRight && castle(start , RIGHT)) moves.push_back({ start, start + RIGHT*2 , start+RIGHT*3 , start+RIGHT  , p});

	return moves;
}

std::vector<Move> PieceLogic::bishopMove(int start, std::vector<int> Incheck)
{
	std::vector<Move> moves;
	std::vector<Move> toInsert;
	MovementDirection direction = kingPin(start);
	if (!Incheck.empty() && direction != All)return moves;  // ---cant move-- check and pin 

	if (direction == Diagonal1 || direction == All) {
		toInsert = (slidingMove(BOT_RIGHT, start, Incheck));
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(TOP_LEFT, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Diagonal2 || direction == All) {
		toInsert = slidingMove(BOT_LEFT, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(TOP_RIGHT, start, Incheck);
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

	if (start % 8 != 0 && start + 16 < 64) 
		if(checkDirection(move, start, (2 * DOWN) + LEFT))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * DOWN) + LEFT) != Incheck.end()) {
					move.push_back({ start, start + (2 * DOWN) + LEFT , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * DOWN) + LEFT, -1 , -1 , p });
	if (start % 8 != 7 && start + 16 < 64) 
		if (checkDirection(move, start, (2 * DOWN) + RIGHT))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * DOWN) + RIGHT) != Incheck.end()) {
					move.push_back({ start, start + (2 * DOWN) + RIGHT , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * DOWN) + RIGHT, -1 , -1 , p });
	if (start - 16 > 0 && start % 8 != 7) 
		if(checkDirection(move, start, (2 * UP) + RIGHT))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * UP) + RIGHT) != Incheck.end()) {
					move.push_back({ start, start + (2 * UP) + RIGHT , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * UP) + RIGHT, -1 , -1 , p });
	if (start - 16 > 0 && start % 8 != 0) 
		if(checkDirection(move, start, (2 * UP) + LEFT))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * UP) + LEFT) != Incheck.end()) {
					move.push_back({ start, start + (2 * UP) + LEFT , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * UP) + LEFT, -1 , -1 , p });
	if (start % 8 > 1 && start + 8 < 64) 
		if(checkDirection(move, start, (2 * LEFT) + DOWN))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * LEFT) + DOWN) != Incheck.end()) {
					move.push_back({ start, start + (2 * LEFT) + DOWN , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * LEFT) + DOWN, -1 , -1 , p });
	if (start % 8 > 1 && start - 8 > 0) 
		if(checkDirection(move, start, (2 * LEFT) + UP))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * LEFT) + UP) != Incheck.end()) {
					move.push_back({ start, start + (2 * LEFT) + UP , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * LEFT) + UP, -1 , -1 , p });
	if (start % 8 < 6 && start - 8 > 0) 
		if(checkDirection(move, start, (2 * RIGHT) + UP))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * RIGHT) + UP) != Incheck.end()) {
					move.push_back({ start, start + (2 * RIGHT) + UP , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * RIGHT) + UP, -1 , -1 , p });
	if (start % 8 < 6 && start + 8 < 64) 
		if(checkDirection(move, start, (2 * RIGHT) + DOWN))
			if (inCheck) {
				if (std::find(Incheck.begin(), Incheck.end(), start + (2 * LEFT) + DOWN) != Incheck.end()) {
					move.push_back({ start, start + (2 * LEFT) + DOWN , -1 , -1 , p });
				}
			}
			else move.push_back({ start, start + (2 * LEFT) + DOWN, -1 , -1 , p });

	return move;
}

std::vector<Move> PieceLogic::rookMove(int start, std::vector<int> Incheck)
{
	std::vector<Move> moves;
	std::vector<Move> toInsert;
	MovementDirection direction = kingPin(start);
	if (!Incheck.empty() && direction != All)return moves;  // ---cant move-- check and pin 

	if (direction == Forward || direction == All) {
		toInsert = (slidingMove(UP, start, Incheck));
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(DOWN, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Side || direction == All) {
		toInsert = slidingMove(LEFT, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(RIGHT, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Diagonal1 || direction == All) {
		toInsert = (slidingMove(BOT_RIGHT, start, Incheck));
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(TOP_LEFT, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Diagonal2 || direction == All) {
		toInsert = slidingMove(BOT_LEFT, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(TOP_RIGHT, start, Incheck);
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
	int color = (NBoard::instance().m_board[pos] & White) > 0 ? White : Black;
	bool inCheck = !Incheck.empty();


	(color == BLACK) ? forward = DOWN : forward = UP;
	Piece p = PawnVal;

	if (pos + forward > 64 || pos + forward < 0) { // Out of Range
		return moves;
	}

	if (direction == All || direction == Forward) {
		if (NBoard::instance().m_board[pos + forward] == 0)
		{
			if (!(pos + forward > 55 || pos + forward < 8)) {
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
			}
	
			if ((NBoard::instance().m_board[pos] & Moved) > 0 && (NBoard::instance().m_board[pos + forward * 2] == 0))
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
	if (direction == All || direction == Diagonal2) {
		if (pos % 8 != 7)
		{
			if (NBoard::instance().m_board[pos + forward + RIGHT] != 0) {
				int enemyColor = (NBoard::instance().m_board[pos + forward + RIGHT] & White) > 0 ? White : Black;
				if (enemyColor != color) {
					if (inCheck) {
						if (std::find(Incheck.begin(), Incheck.end(), pos + forward +RIGHT) != Incheck.end()) {
							moves.push_back({ pos, pos + forward + RIGHT , -1 , -1 , p });
						}
					}
					else moves.push_back({ pos, pos + forward + RIGHT , -1 , -1 , p });
					
				}
			}

			if (NBoard::instance().m_board[pos + RIGHT] != 0) {
				int enemyColor = (NBoard::instance().m_board[pos + RIGHT] & White) > 0 ? White : Black;
				if (color != enemyColor) {
					if (pos + RIGHT == NBoard::instance().m_passant)
					{
						if (inCheck) {
							if (std::find(Incheck.begin(), Incheck.end(), pos + forward + RIGHT) != Incheck.end()) {
								moves.push_back({ pos, pos + forward + RIGHT , pos , pos + RIGHT, p });
							}
						}
						else moves.push_back({ pos, pos + forward + RIGHT , pos , pos + RIGHT, p });
						
					}
				}
			}
		}
	}
	if (direction == All || direction == Diagonal1) {
		if (pos % 8 != 0)
		{
			if (NBoard::instance().m_board[pos + forward + LEFT]) {
				int enemyColor = (NBoard::instance().m_board[pos + forward + LEFT] & White) > 0 ? White : Black;
				if (enemyColor != color) {
					if (inCheck) {
						if (std::find(Incheck.begin(), Incheck.end(), pos + forward + LEFT) != Incheck.end()) {
							moves.push_back({ pos, pos + forward + LEFT , -1 , -1 , p });
						}
					}
					else moves.push_back({ pos, pos + forward + LEFT , -1 , -1 , p });
					
				}
			}
			if (NBoard::instance().m_board[pos + LEFT] != 0) {
				int enemyColor = (NBoard::instance().m_board[pos + LEFT] & White) > 0 ? White : Black;
				if (color != enemyColor) {
					if (pos + LEFT == NBoard::instance().m_passant)
					{
						if (inCheck) {
							if (std::find(Incheck.begin(), Incheck.end(), pos + forward + LEFT) != Incheck.end()) {
								moves.push_back({ pos, pos + forward + LEFT , pos , pos + LEFT, p });
							}
						}
						else moves.push_back({ pos, pos + forward + LEFT , pos , pos + LEFT, p });
					}
				}
			}
		}
	}
	return moves;
}

std::vector<Move> PieceLogic::queenMove(int start, std::vector<int> Incheck)
{
	std::vector<Move> moves;
	std::vector<Move> toInsert;
	MovementDirection direction = kingPin(start);
	if (!Incheck.empty() && direction != All)return moves;  // ---cant move-- check and pin 

	if (direction == Forward || direction == All) {
		toInsert = (slidingMove(UP, start, Incheck));
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(DOWN, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	if (direction == Side || direction == All) {
		toInsert = slidingMove(LEFT, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
		toInsert = slidingMove(RIGHT, start, Incheck);
		moves.insert(moves.end(), toInsert.begin(), toInsert.end());
	}
	return moves;
}

std::vector<Move> PieceLogic::slidingMove(int direction, int start, std::vector<int> inCheck)
{
	Piece p = PawnVal;
	std::vector<Move> moves;
	int pos = start;
	int color = (NBoard::instance().m_board[start] & White) > 0 ? White : Black;
	if (pos % 8 == 0 && (direction == BOT_LEFT || direction == TOP_LEFT || direction == LEFT)) return moves;
	if (pos % 8 == 7 && (direction == TOP_RIGHT || direction == BOT_RIGHT || direction == RIGHT)) return moves;
	if (pos - 8 < 0 && (direction == TOP_RIGHT || direction == TOP_LEFT || direction == UP)) return moves;
	if (pos + 8 > 63 && (direction == BOT_LEFT || direction == BOT_RIGHT || direction == DOWN)) return moves;
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
		if (NBoard::instance().m_board[i]==0) // empty square
		{
			if (isCheck) {
				if (std::find(inCheck.begin(), inCheck.end(), i) != inCheck.end()) {
					moves.push_back({ pos, i , -1 , -1 , p });
				}
			}
			else moves.push_back({ pos, i , -1 , -1 , p });
			continue;
		}
		int enemyColor = (NBoard::instance().m_board[i] & White) > 0 ? White : Black;
		if (color == enemyColor) return moves;
		if (isCheck) {
			if (std::find(inCheck.begin(), inCheck.end(), i) != inCheck.end()) {
				moves.push_back({ pos, i , -1 , -1 , p });
			}
		}
		else moves.push_back({ pos, i , -1 , -1 , p });
		return moves;
	}
}

bool PieceLogic::checkCheck(std::vector<Move> moves, int color,int direction)
{
	if (moves.empty()) return false;
	if (NBoard::instance().m_board[moves.back().targetSquare] == 0) return false;
	int piece = (NBoard::instance().m_board[moves.back().targetSquare] & 0b111);
	if (direction % Forward == 0 || Side % direction == 0) {
		if (piece == RookVal || piece == QueenVal) return true;
		return false;
	}
	if (direction % Diagonal1 == 0 || direction % Diagonal2 == 0) {
		if (piece == BishopVal || piece == QueenVal) return true;
		if (moves.size() == 1 && piece == PawnVal) {
			if (color == White && moves.back().targetSquare < moves.back().startSquare)return true;
			if (color == Black && moves.back().targetSquare > moves.back().startSquare)return true;
		}
		return false;
	}
	
	return false;
}

bool PieceLogic::checkPin(std::vector<Move> moves, int color, int direction)
{
	std::vector<int> empty;
	if (moves.back().targetSquare + direction > 63 || moves.back().targetSquare + direction < 0) return false;
	if ((moves.back().targetSquare + direction) % 8 == 0 && moves.back().targetSquare % 8 == 7)return false;
	if ((moves.back().targetSquare + direction) % 8 == 7 && moves.back().targetSquare % 8 == 0)return false;
	
	moves = slidingMove(direction, moves.back().targetSquare + direction, empty);
	if (checkCheck(moves, color , direction)) {
		return true;
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
	if ((NBoard::instance().m_board[place + jump] & 0b111) == KnightVal) {
		int enemyColor = (NBoard::instance().m_board[place + jump] & White) > 0 ? White : Black;
		if (enemyColor != color) {
			return true;
		}
	}
	return false;
}

bool PieceLogic::checkDirection(std::vector<Move>& move, const int pos, const int direction) const
{
	int color = (NBoard::instance().m_board[pos] & White) > 0 ? White : Black;
	if (NBoard::instance().m_board[pos + direction]==0){
		return true;
	}
	int enemyColor = (NBoard::instance().m_board[pos + direction] & White) > 0 ? White : Black;
	if (enemyColor != color)
	{
		return true;
	}
	return false;
}

bool PieceLogic::checkCorner(std::vector<Move>& move, const int pos, const int corner) const
{
	if (pos + corner < 0 || pos + corner > 63) return false;
	if (pos % 8 == 0 && (corner == TOP_LEFT || corner == BOT_LEFT)) return false;
	if (pos % 8 == 7 && (corner == TOP_RIGHT || corner == BOT_RIGHT)) return false;
	if (pos - 8 < 0 && (corner == TOP_RIGHT || corner == TOP_LEFT)) return false;
	if (pos + 8 > 63 && (corner == BOT_LEFT || corner == BOT_RIGHT)) return false;

	return checkDirection(move, pos, corner);
}

bool PieceLogic::castle(int king, int direction)
{
	int color = (NBoard::instance().m_board[king] & White) > 0 ? White : Black;
	int rook = direction == RIGHT ? 7 : 0;
	std::vector<int> checkSquares;
	rook += color == White ?  56 : 0;

	if ((NBoard::instance().m_board[rook] & 0b111) != RookVal) return false;
	if (!((NBoard::instance().m_board[king] & Moved) > 0))return false;
	if (!((NBoard::instance().m_board[rook] & Moved) > 0))return false;

	if (NBoard::instance().m_board[king + direction] == 0 && 
		NBoard::instance().m_board[king + direction*2] == 0){
		if (!(check(king + direction, checkSquares, color) && checkSquares.size() == 0))return false;
		if (!(check(king + direction*2, checkSquares, color) && checkSquares.size() == 0))return false;
	}
	return true;
}

