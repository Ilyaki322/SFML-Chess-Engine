#pragma once 

#include "Pieces.h"
#include <memory>

class PiecesFactory {
public:
	PiecesFactory() {}
	std::shared_ptr<Pieces> create(std::string s , sf::Vector2f position);
};