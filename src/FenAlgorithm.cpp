#include "FenAlgorithm.h"
#include "Assets.h"
#include "Board.h"
#include "Pieces.h"
#include "PiecesFactory.h"

#include <iostream> // DEBUG

FenAlgorithm::FenAlgorithm()
{
	m_piecesMap['k'] = 1;
	m_piecesMap['p'] = 2;
	m_piecesMap['n'] = 3;
	m_piecesMap['b'] = 4;
	m_piecesMap['r'] = 5;
	m_piecesMap['q'] = 6;
}

void FenAlgorithm::setBoard(std::array<std::shared_ptr<Tile>, 64> &tiles, int squares[], std::string stage)
{
	PiecesFactory theCreator;
	for (int j = 0 , point = 0; j < 64 && point < stage.size() ; j++ , point++) {
		if (isdigit(stage[point])) {

			int temp = int(stage[point]) - '0';
			j += temp - 1;
			continue;
		}
		tiles[j]->placePiece(theCreator.create(stage[point], tiles[j]->getPosition(), isupper(stage[point]) ? Black : White));

		int color = isupper(stage[point]) ? 16 : 8;
		squares[j] = m_piecesMap[tolower(stage[point])] | color | 32 ;
	}

	//for (int i = 0; i < 64; i++) {
	//	if (i % 8 == 0)
	//		std::cout << '\n';
	//	std::cout << squares[i] << ' ';
	//}
	//for (int i = 0; i < 64; i++) {
	//	if (i % 8 == 0)
	//		std::cout << '\n';
	//	std::cout << (squares[i]^32) << ' ';
	//}

}
