#pragma once

#include <string>
#include "memory"
#include "Pieces.h"
#include "Pawn.h"
class PiecesFactory {
public:
	PiecesFactory();
	std::shared_ptr<Pieces> create(char c , sf::Vector2f position , Color color);
};