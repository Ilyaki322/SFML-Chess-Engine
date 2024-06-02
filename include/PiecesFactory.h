#pragma once

#include <string>
#include "memory"
#include "Pieces.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
class PiecesFactory {
public:
	PiecesFactory();
	std::shared_ptr<Pieces> create(char c , sf::Vector2f position , Color color);
};