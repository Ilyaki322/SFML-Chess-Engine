#include "FenAlgorithm.h"
#include "Assets.h"
#include "Board.h"
#include "Pieces.h"
//#include "PiecesFactory.h"

FenAlgorithm::FenAlgorithm()
{
	m_piecesMap['k'] = 1;
	m_piecesMap['p'] = 2;
	m_piecesMap['n'] = 3;
	m_piecesMap['b'] = 4;
	m_piecesMap['r'] = 5;
	m_piecesMap['q'] = 6;
}

void FenAlgorithm::setBoard(/*std::array<std::shared_ptr<Tile>, 64> &tiles, */std::array<int, 64>& squares, std::string stage)
{
	for (int i = 0; i < 64; i++)
		squares[i]  = 0;
	for (int j = 0, point = 0; j < 64 && point < stage.size(); j++, point++) {
		if (isdigit(stage[point])) {

			int temp = int(stage[point]) - '0';
			j += temp - 1;
			continue;
		}

		int color = isupper(stage[point]) ? 16 : 8;
		squares[j] = m_piecesMap[char(tolower(stage[point]))] | color;
	}
	
	for (int i = 8; i < 16; i++) {
		int color = (squares[i] & White) > 0 ? White : Black;
		if ((squares[i] & 0b111) == PawnVal && color == Black)
			squares[i] = squares[i] | 32;
	}
	for (int i = 48; i < 56; i++) {
		int color = (squares[i] & White) > 0 ? White : Black;
		if ((squares[i] & 0b111) == PawnVal && color == White)
			squares[i] = squares[i] | 32;
	}
	int rook[] = {0,7,56,63};
	for (int i = 0; i < 4; i++) {
		int color = (squares[rook[i]] & White) > 0 ? White : Black;
		if ((color == Black && i > 1) || (color == White && i<2))continue;
		if ((squares[rook[i]] & 0b111) == RookVal)
			squares[rook[i]] = squares[rook[i]] | 32;
	}
	int king[] = { 4,60 };
	for (int i = 0; i < 2; i++) {
		int color = (squares[king[i]] & White) > 0 ? White : Black;
		if ((color == Black && i > 0) || (color == White && i <1 ))continue;
		if ((squares[king[i]] & 0b111) == KingVal)
			squares[king[i]] = squares[king[i]] | 32;
	}

}


