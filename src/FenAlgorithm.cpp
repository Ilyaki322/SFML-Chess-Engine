#include "FenAlgorithm.h"
#include "Assets.h"
#include "Board.h"
#include "Pieces.h"
#include "PiecesFactory.h"

FenAlgorithm::FenAlgorithm(){}

void FenAlgorithm::setBoard(std::array<std::array<std::shared_ptr<Tile>, 8>, 8> &tiles, std::string stage)
{
	PiecesFactory theCreator;
	for (int i = 0 , point = 0 ; i < 8  && point < stage.size(); i++) {
		for (int j = 0; j < 8 && point < stage.size(); j++ , point++) {
			if (isdigit(stage[point])) {
				j += atoi(&stage[point]) - 1;
				continue;
			}
			tiles[i][j]->placePiece(theCreator.create(stage[point], tiles[i][j]->getPosition(), isupper(stage[point]) ? Black : White));
		}
	}
}
