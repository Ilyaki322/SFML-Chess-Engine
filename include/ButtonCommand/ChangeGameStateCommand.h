#pragma once
#include "ButtonCommand/ButtonCommand.h"
#include "UI/PlayUI.h"
#include "GameState/GameState.h"
#include <memory>

class GameManager;
typedef std::unique_ptr<GameState> gameStatePtr;
typedef std::shared_ptr<PlayUI> uiPtr;
/*This class executes a state change command*/

class ChangeGameStateCommand : public ButtonCommand
{
public:

	ChangeGameStateCommand(StateMachine& machine, GameManager& manager, gameStatePtr ptr,uiPtr ui);

	void execute();

private:
	uiPtr m_ui;
	GameManager& m_manager;
	gameStatePtr m_nextState;
};