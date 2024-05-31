#include "FenAlgorithm.h"
#include "Assets.h"
#include "Board.h"
#include "Pieces.h"

FenAlgorithm::FenAlgorithm(){}

void FenAlgorithm::setBoard(std::array<std::array<std::shared_ptr<Tile>, 8>, 8> &tiles, std::string stage)
{
	for (int i = 0 , point = 0 ; i < 8; i++) {
		for (int j = 0; j < 8; j++ , point++) {
			if (isdigit(stage[point])) {
				j += atoi(&stage[point]) - 1;
				continue;
			}
			tiles[i][j].placePiece(std::make_shared<Pieces>(Assets::instance().getTexture(stage[point]), tiles[i][j].getPosition(), isupper(stage[point]) ? Black : White));
		}
	}
}
