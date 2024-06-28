#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "GameState/GameState.h"
#include <memory>

class GameManager;
typedef std::unique_ptr<GameState> gameStatePtr;

class ChangeGameStateCommand : public ButtonCommand
{
public:

	ChangeGameStateCommand(StateMachine& machine, GameManager& manager, gameStatePtr ptr);

	void execute();

private:

	GameManager& m_manager;
	gameStatePtr m_nextState;
};