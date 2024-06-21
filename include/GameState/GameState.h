#pragma once

class GameManager;
class GameState
{
public:
	GameState(GameManager& manager);
	virtual ~GameState() {};

	virtual void execute() = 0; 
	virtual void draw(float dt) = 0;

protected:
	GameManager& m_manager;
};