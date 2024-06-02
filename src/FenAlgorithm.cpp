#include "FenAlgorithm.h"
#include "Assets.h"
#include "Board.h"
#include "Pieces.h"
#include "PiecesFactory.h"

FenAlgorithm::FenAlgorithm()
{
	m_piecesMap['k'] = 1;
	m_piecesMap['p'] = 2;
	m_piecesMap['n'] = 3;
	m_piecesMap['b'] = 4;
	m_piecesMap['r'] = 5;
	m_piecesMap['q'] = 6;
}

void FenAlgorithm::setBoard(std::array<std::array<std::shared_ptr<Tile>, 8>, 8> &tiles, int squares[], std::string stage)
{
	int index = 0;

	PiecesFactory theCreator;
	for (int i = 0 , point = 0 ; i < 8  && point < stage.size(); i++) {
		for (int j = 0; j < 8 && point < stage.size(); j++ , point++) {
			if (isdigit(stage[point])) {

				int temp = int(stage[point]) - '0';

				//j += atoi(&stage[point]) - 1;
				//index -= atoi(&stage[point]) + 1;
				j += temp - 1;
				index += temp;
				continue;
			}
			tiles[i][j]->placePiece(theCreator.create(stage[point], tiles[i][j]->getPosition(), isupper(stage[point]) ? Black : White));

			int color = isupper(stage[point]) ? 16 : 8;
			squares[index] = m_piecesMap[tolower(stage[point])] | color;
			index++;
		}
	}
}
