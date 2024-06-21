#pragma once 
#include "Utilities.h"
#include <fstream>
#include "GameState/GameState.h"
#include "FenAlgorithm.h" 
#include "PlayerController.h"

class GameManager;

class PuzzleController : public GameState {
public:
	PuzzleController(Color color, Difficult d , GameManager& manager , SFMLBoard& sfBoard);
	virtual void execute()override;
	virtual void draw(float dt)override;
private:
	bool correctMove(Move move);
	std::vector<PuzzleStruct> m_puzzle;
	std::fstream m_file;
	Controller* m_player;
	PuzzleStruct m_currPuzzle;
	bool m_first;
	SFMLBoard& m_sfmlBoard;
};